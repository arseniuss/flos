/**
 *  Cell language token library
 *  Copyright (C) 2019  Armands Arseniuss Skolmeisters
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this library.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined(__TOKEN_TYPE) || __TOKEN_TYPE==TOKEN_SYSTEM
__(EOF, eof, "end of file")
#endif

#if !defined(__TOKEN_TYPE) || __TOKEN_TYPE==TOKEN_LITERAL
__(COMMENT, comment, "comment")
__(IDENT, ident, "identifier")
__(INT, int, "number")
__(FLOAT, float, "floting point number") 
__(CHAR, char, "character") 
__(STR, str, "string literal")
__(OPER, oper, "operator")
__(NEWLINE, newline, "newline")        
#endif

#if !defined(__TOKEN_TYPE) || __TOKEN_TYPE==TOKEN_BRACKETS
__(LPAREN,, "(")
__(LQBRACK,, "[")
__(LCBRACK,, "{")
__(RPAREM,, ")")
__(RQBRACK,, "]")
__(RCBRACK,, "}")
__(SEMICOLON,, ";") 
__(COMMA,, ",") 
__(HASH,, "#") 
#endif
        
#if !defined(__TOKEN_TYPE) || __TOKEN_TYPE==TOKEN_OPER     
__(PLUS,, "+")
__(MINUS,, "-")
__(MUL,, "*")
__(DIV,, "/")
__(XOR,, "^")
__(AND,, "&")
__(OR,, "|")
__(LT,, "<")
__(GT,, ">")
__(EQ,, "=")
__(RDIV,, "\\")
__(TILDE,, "~")
__(PERIOD,, "/") 
__(DOT,, ".") 
__(COLON,, ":") 
__(QUEST,, "?") 
__(EXCLAM,, "!") 
__(AT,, "@")
#endif

#if !defined(__TOKEN_TYPE) || __TOKEN_TYPE==TOKEN_KEYWORDS
__(MODULE, module, "module")
__(IMPORT, import, "import")
__(FROM, from, "from")
__(VAR, var, "var")
__(TYPE, type, "type")
__(ALIAS, alias, "alias")
__(STRUCT, struct, "struct")
__(FUNC, func, "func")
__(INTERFACE, interface, "interface")
__(CONST, const, "const")
__(RETURN, return, "return")
__(BREAK, break, "break")
__(CASE, case, "case") 
__(CONTINUE, continue, "continue") 
__(DEFAULT, default, "default") 
__(IF, if, "if")
__(ELSE, else, "else")
__(FOR, for, "for")
#endif

#undef __
#undef __TOKEN_TYPE
