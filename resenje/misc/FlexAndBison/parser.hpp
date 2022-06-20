/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_RESENJE_MISC_FLEXANDBISON_PARSER_HPP_INCLUDED
# define YY_YY_RESENJE_MISC_FLEXANDBISON_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 19 "./resenje/misc/parser.y"


#include "../hpp/Lines.hpp"
#include "../hpp/JumpOperand.hpp"
#include "../hpp/DataOperand.hpp"


#line 56 "./resenje/misc/FlexAndBison/parser.hpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    REGISTER = 258,
    SYMBOL = 259,
    STRING = 260,
    NUMBER = 261,
    GLOBAL = 262,
    EXTERN = 263,
    SECTION = 264,
    WORD = 265,
    SKIP = 266,
    ASCII = 267,
    EQU = 268,
    END = 269,
    HALT = 270,
    INT = 271,
    IRET = 272,
    RET = 273,
    CALL = 274,
    JMP = 275,
    JGT = 276,
    JEQ = 277,
    JNE = 278,
    PUSH = 279,
    POP = 280,
    XCHG = 281,
    ADD = 282,
    SUB = 283,
    MUL = 284,
    DIV = 285,
    CMP = 286,
    NOT = 287,
    AND = 288,
    OR = 289,
    XOR = 290,
    TEST = 291,
    SHL = 292,
    SHR = 293,
    LDR = 294,
    STR = 295,
    PLUS = 296,
    COMMENT = 297,
    PERCENT = 298,
    STAR = 299,
    DOLLAR = 300,
    LEFT_BR = 301,
    RIGHT_BR = 302,
    COLON = 303,
    SEMI_COLON = 304,
    NEW_LINE = 305,
    COMMA = 306,
    DOT = 307
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 29 "./resenje/misc/parser.y"

  Line *line;
  Symbol_Literal_List * sym_lit_list;
  //Symbol_Literal_List *list_of_symbols;
  std::string *symbol;
  Directive* dir;
  Instruction* ins;
  Label* lbl;
  JumpOperand* jmpOp;
  DataOperand* dataOp;
  short reg;
  int number;
  int token;

#line 135 "./resenje/misc/FlexAndBison/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_RESENJE_MISC_FLEXANDBISON_PARSER_HPP_INCLUDED  */
