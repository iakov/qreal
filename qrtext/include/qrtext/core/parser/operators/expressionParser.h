#pragma once

#include "qrtext/core/ast/binaryOperator.h"
#include "qrtext/core/parser/operators/parserInterface.h"
#include "qrtext/core/parser/parserRef.h"
#include "qrtext/core/parser/precedenceTable.h"
#include "qrtext/core/parser/temporaryNodes/temporaryErrorNode.h"
#include "qrtext/core/parser/temporaryNodes/temporaryDiscardableNode.h"

namespace qrtext {
namespace core {

/// Parser for expressions using Precedence Climbing algorithm, see http://www.engr.mun.ca/~theo/Misc/exp_parsing.htm.
template<typename TokenType>
class ExpressionParser : public ParserInterface<TokenType>
{
public:
	/// Constructor for general case, takes precedence table, parser for primary expression and parser for binary
	/// operator.
	ExpressionParser(QSharedPointer<PrecedenceTable<TokenType>> const &precedenceTable
			, ParserRef<TokenType> const &primary
			, ParserRef<TokenType> const &binOp)
		: mPrecedenceTable(precedenceTable)
		, mStartPrecedence(0)
		, mPrimary(primary)
		, mBinOp(binOp)
	{
	}

	/// Constructor for using with unary operators, takes precedence table, unary operator, which precedence will be
	/// used as starting, parser for primary expression and parser for binary operator.
	ExpressionParser(QSharedPointer<PrecedenceTable<TokenType>> const &precedenceTable
			, TokenType startingUnaryOperator
			, ParserRef<TokenType> primary
			, ParserRef<TokenType> binOp)
		: mPrecedenceTable(precedenceTable)
		, mStartPrecedence(mPrecedenceTable->precedence(startingUnaryOperator, Arity::unary))
		, mPrimary(primary)
		, mBinOp(binOp)
	{
	}

	QSharedPointer<ast::Node> parse(TokenStream<TokenType> &tokenStream
			, ParserContext<TokenType> &parserContext) const override
	{
		return parse(tokenStream, parserContext, mStartPrecedence);
	}

	QSet<TokenType> first() const override
	{
		return mPrimary->first();
	}

private:
	QSharedPointer<ast::Node> parse(TokenStream<TokenType> &tokenStream, ParserContext<TokenType> &parserContext
			, int currentPrecedence) const
	{
		QSharedPointer<ast::Node> resultAst = mPrimary->parse(tokenStream, parserContext);

		if (resultAst->is<TemporaryErrorNode>()) {
			return resultAst;
		}

		while (mPrecedenceTable->binaryOperators().contains(tokenStream.next().token())
				&& mPrecedenceTable->precedence(tokenStream.next().token(), Arity::binary) >= currentPrecedence)
		{
			const int newPrecedence = mPrecedenceTable->associativity(tokenStream.next().token()) == Associativity::left
					? 1 + mPrecedenceTable->precedence(tokenStream.next().token(), Arity::binary)
					: mPrecedenceTable->precedence(tokenStream.next().token(), Arity::binary)
					;

			const QSharedPointer<ast::Node> binOpResult = mBinOp->parse(tokenStream, parserContext);
			if (binOpResult->is<TemporaryErrorNode>()) {
				// There was an error when parsing binary operator, it shall be already reported.
				return binOpResult;
			}

			auto op = as<ast::BinaryOperator>(binOpResult);
			if (!op) {
				parserContext.reportInternalError(QObject::tr("Binary operator in expression is of the wrong type"));
				return wrap(new TemporaryErrorNode());
			}

			const QSharedPointer<ast::Node> rightOperandResult = parse(tokenStream, parserContext, newPrecedence);
			if (rightOperandResult->is<TemporaryErrorNode>()) {
				return rightOperandResult;
			} else if (rightOperandResult->is<TemporaryDiscardableNode>()) {
				parserContext.reportError(QObject::tr("Right operand required"));
				return wrap(new TemporaryErrorNode());
			}

			op->setLeftOperand(resultAst);
			op->setRightOperand(rightOperandResult);
			resultAst = op;
		}

		return resultAst;
	}

	QSharedPointer<PrecedenceTable<TokenType>> mPrecedenceTable;
	const int mStartPrecedence;

	ParserRef<TokenType> const mPrimary;
	ParserRef<TokenType> const mBinOp;
};

}
}
