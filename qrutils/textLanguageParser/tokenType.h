#pragma once

#include <type_traits>
#include <QtCore/QHash>
#include <QtCore/QDebug>

namespace textLanguageParser {

enum class TokenType {
	whitespace  // 0
	, newline
	, identifier

	, andKeyword
	, breakKeyword
	, doKeyword  // 5
	, elseKeyword
	, elseifKeyword
	, endKeyword
	, falseKeyword
	, forKeyword  // 10
	, functionKeyword
	, gotoKeyword
	, ifKeyword
	, inKeyword
	, localKeyword  //15
	, nilKeyword
	, notKeyword
	, orKeyword
	, repeatKeyword
	, returnKeyword  // 20
	, thenKeyword
	, trueKeyword
	, untilKeyword
	, whileKeyword

	, plus  // 25
	, minus
	, asterick
	, slash
	, percent
	, hat  // 30
	, sharp

	, ampersand
	, tilda
	, verticalLine
	, doubleLess  // 35
	, doubleGreater
	, doubleSlash

	, doubleEquals
	, tildaEquals
	, lessEquals  // 40
	, greaterEquals
	, less
	, greater
	, equals

	, openingBracket  // 45
	, closingBracket
	, openingCurlyBracket
	, closingCurlyBracket
	, openingSquareBracket
	, closingSquareBracket  // 50
	, doubleColon

	, semicolon
	, colon
	, comma
	, dot  // 55
	, doubleDot
	, tripleDot

	, string
	, integerLiteral
	, floatLiteral  // 60
	, comment
};

inline uint qHash(TokenType const &key)
{
	return ::qHash(static_cast<std::underlying_type<TokenType>::type>(key));
}

inline QDebug operator <<(QDebug debug, TokenType const &token)
{
	debug << static_cast<std::underlying_type<TokenType>::type>(token);
	return debug;
}

}
