/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_CALC_SINTAXIS_TAB_H_INCLUDED
# define YY_YY_CALC_SINTAXIS_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    ID = 259,
    VAR = 260,
    CLASS = 261,
    IF = 262,
    THEN = 263,
    ELSE = 264,
    TRUE = 265,
    FALSE = 266,
    RETURN = 267,
    VOID = 268,
    INTRES = 269,
    BOOL = 270,
    WHILE = 271,
    MAS = 272,
    MENOS = 273,
    POR = 274,
    EXCLAMACION = 275,
    DIVISION = 276,
    MOD = 277,
    COMA = 278,
    PUNTOYCOMA = 279,
    PARENTESISABRE = 280,
    PARENTESISCIERRA = 281,
    ASIG = 282,
    EQUALS = 283,
    MAYORQUE = 284,
    MENORQUE = 285,
    AND = 286,
    OR = 287,
    LLAVEABRE = 288,
    LLAVECIERRA = 289,
    UNARIO = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 1084 "calc-sintaxis.y" /* yacc.c:1909  */
 int i; char *s; char c; struct nodoArbol *p; struct infoString *infos; struct infoInt *infoi  ;

#line 93 "calc-sintaxis.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CALC_SINTAXIS_TAB_H_INCLUDED  */
