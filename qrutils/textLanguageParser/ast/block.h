#pragma once

#include "textLanguageParser/ast/node.h"
#include "textLanguageParser/ast/expression.h"

namespace textLanguageParser {
namespace ast {

class QRUTILS_EXPORT Block : public Node {
public:
	Block(QList<QSharedPointer<Node>> const &statements)
		: mStatements(statements)
	{
	}

private:
	QList<QSharedPointer<Node>> mStatements;
};

}
}
