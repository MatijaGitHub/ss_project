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
#line 12 "./resenje/misc/parser.y"


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
    SP = 259,
    PC = 260,
    PSW = 261,
    SYMBOL = 262,
    NUMBER = 263,
    GLOBAL = 264,
    EXTERN = 265,
    SECTION = 266,
    WORD = 267,
    SKIP = 268,
    ASCII = 269,
    EQU = 270,
    END = 271,
    HALT = 272,
    INT = 273,
    IRET = 274,
    RET = 275,
    CALL = 276,
    JMP = 277,
    JGT = 278,
    JEQ = 279,
    JNE = 280,
    PUSH = 281,
    POP = 282,
    XCHG = 283,
    ADD = 284,
    SUB = 285,
    MUL = 286,
    DIV = 287,
    CMP = 288,
    NOT = 289,
    AND = 290,
    OR = 291,
    XOR = 292,
    TEST = 293,
    SHL = 294,
    SHR = 295,
    LDR = 296,
    STR = 297,
    PLUS = 298,
    COMMENT = 299,
    PERCENT = 300,
    STAR = 301,
    DOLLAR = 302,
    LEFT_BR = 303,
    RIGHT_BR = 304,
    COLON = 305,
    SEMI_COLON = 306,
    NEW_LINE = 307,
    COMMA = 308
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 22 "./resenje/misc/parser.y"

  Line *line;
  Symbol_Literal_List * sym_lit_list;
  Symbol_Literal_List *list_of_symbols;
  std::string *symbol;
  Directive* dir;
  Instruction* ins;
  Label* lbl;
  JumpOperand* jmpOp;
  DataOperand* dataOp;
  short reg;
  int number;
  int token;

#line 136 "./resenje/misc/FlexAndBison/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_RESENJE_MISC_FLEXANDBISON_PARSER_HPP_INCLUDED  */
