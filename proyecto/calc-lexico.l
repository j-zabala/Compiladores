%{

/*

Pre-Proyecto de Compiladores 2017

Integrantes: Bruno Zergoni Coronel, Joaquin Zabala, Valentin Vivaldi

*/




#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "infostring.c"
#include "infoint.c"
#include "calc-sintaxis.tab.h"

%}
%x comment
%option noyywrap
%option yylineno

alpha [a-zA-Z]
digit [0-9]
alpha_num ({alpha}|{digit}|_)


%%


"/*"          { BEGIN(comment); }
<comment>"*/" { BEGIN(INITIAL); }
<comment>\n   { }
<comment>.    { }
<comment><<EOF>> {
                  //printf("comentario no cierra antes del fin del archivo. ¿Falta cierre de comentario?");

                  }



{digit}+                     { yylval.infoi =malloc(sizeof(InfoInt));
                              yylval.infoi->info = atoi(yytext);
                              yylval.infoi->linea = yylineno;

                                //printf("INT : %d\n",atoi(yytext));
                                return INT;}




class {
        //printf("CLASS \n");
        yylval.i=yylineno;return CLASS;}
if  {
        //printf("if \n");
        yylval.i=yylineno;return IF;}
else  {
      //printf("else \n");
      yylval.i=yylineno;return ELSE;}
void  {
      //printf("VOID \n");
      yylval.i=yylineno;return VOID;}
then  {
      //printf("then \n");
      yylval.i=yylineno;return THEN;}
int  {
      //printf("int \n");
      yylval.i=yylineno;return INTRES;}
bool  {
      //printf("bool \n");
      yylval.i=yylineno;return BOOL;}
return {
      //printf("RETURN \n");
      yylval.i=yylineno;return RETURN;}
while  {
      //printf("WHILE \n");
      yylval.i=yylineno;return WHILE;}
true  {
      //printf("true \n");
      yylval.i=yylineno;return TRUE;}
false  {
      //printf("false \n");
      yylval.i=yylineno;return FALSE;}



{alpha}{alpha_num}*    {        yylval.infos =malloc(sizeof(InfoString));
                                yylval.infos->info = malloc(sizeof(char*)*yyleng);
                                strcpy(yylval.infos->info , yytext);
                                yylval.infos->linea = yylineno;
                            //    printf("ID : %s\n",yytext);
                                return ID;
                              }



[+]                   {
                          //printf("%s\n",yytext);
                          yylval.infos =malloc(sizeof(InfoString));
                          yylval.infos->info = malloc(sizeof(char*)*yyleng);
                          strcpy(yylval.infos->info, yytext);
                          yylval.infos->linea = yylineno;

                          return MAS;}

[-]                   {
                          //printf("%s\n",yytext);
                          yylval.infos =malloc(sizeof(InfoString));
                          yylval.infos->info = malloc(sizeof(char*)*yyleng);
                          strcpy(yylval.infos->info, yytext);
                          yylval.infos->linea = yylineno;
                          return MENOS;}
[!]                   {
                          //printf("%s\n",yytext);
                          yylval.infos =malloc(sizeof(InfoString));
                          yylval.infos->info = malloc(sizeof(char*)*yyleng);
                          strcpy(yylval.infos->info, yytext);
                          yylval.infos->linea = yylineno;
                          return EXCLAMACION;}


[/]                   {
                          //printf("%s\n",yytext);
                          yylval.infos =malloc(sizeof(InfoString));
                          yylval.infos->info = malloc(sizeof(char*)*yyleng);
                        strcpy(yylval.infos->info, yytext);
                        yylval.infos->linea = yylineno;
                        return DIVISION;}

[%]                   {
                          //printf("%s\n",yytext);
                          yylval.infos =malloc(sizeof(InfoString));
                          yylval.infos->info = malloc(sizeof(char*)*yyleng);

                          strcpy(yylval.infos->info, yytext);
                          yylval.infos->linea = yylineno;
                          return MOD;}

[*]                   {
                          //printf("%s\n",yytext);
                          yylval.infos =malloc(sizeof(InfoString));
                          yylval.infos->info = malloc(sizeof(char*)*yyleng);
                        strcpy(yylval.infos->info, yytext);
                        yylval.infos->linea = yylineno;
                        return POR;}

[;]                   {
                        //printf("%s\n",yytext);
                        yylval.infos =malloc(sizeof(InfoString));
                        yylval.infos->info = malloc(sizeof(char*)*yyleng);
                        strcpy(yylval.infos->info, yytext);
                        yylval.infos->linea = yylineno;
                        return PUNTOYCOMA;}
[(]                   {
                        //printf("%s\n",yytext);
                        yylval.infos =malloc(sizeof(InfoString));
                        yylval.infos->info = malloc(sizeof(char*)*yyleng);
                        strcpy(yylval.infos->info, yytext);
                        yylval.infos->linea = yylineno;
                        return PARENTESISABRE;}
[)]                   {
//printf("%s\n",yytext);
yylval.infos =malloc(sizeof(InfoString));
                          yylval.infos->info = malloc(sizeof(char*)*yyleng);
                          strcpy(yylval.infos->info, yytext);
                          yylval.infos->linea = yylineno;
                          return PARENTESISCIERRA;}
[=]                   {
                          //printf("%s\n",yytext);
                          yylval.infos =malloc(sizeof(InfoString));
                          yylval.infos->info = malloc(sizeof(char*)*yyleng);
                          strcpy(yylval.infos->info, yytext);
                          yylval.infos->linea = yylineno;
                          return ASIG;}
==                   {
//printf("%s\n",yytext);
yylval.infos =malloc(sizeof(InfoString));
                          yylval.infos->info = malloc(sizeof(char*)*yyleng);
                          strcpy(yylval.infos->info, yytext);
                          yylval.infos->linea = yylineno;
                          return EQUALS;}
[>]                   {
                          // printf("%s\n",yytext);
                          yylval.infos =malloc(sizeof(InfoString));
                          yylval.infos->info = malloc(sizeof(char*)*yyleng);
                          strcpy(yylval.infos->info, yytext);
                          yylval.infos->linea = yylineno;
                          return MAYORQUE;}
[<]                   {
                        //printf("%s\n",yytext);
                        yylval.infos =malloc(sizeof(InfoString));
                        yylval.infos->info = malloc(sizeof(char*)*yyleng);
                        strcpy(yylval.infos->info, yytext);
                        yylval.infos->linea = yylineno;
                        return MENORQUE;}
"&&"                   {
                          //printf("%s\n",yytext);
                          yylval.infos =malloc(sizeof(InfoString));
                            yylval.infos->info = malloc(sizeof(char*)*yyleng);
                          strcpy(yylval.infos->info, yytext);
                          yylval.infos->linea = yylineno;
                          return AND;}
"||"                   {
                          //printf("%s\n",yytext);
                            yylval.infos =malloc(sizeof(InfoString));
                          yylval.infos->info = malloc(sizeof(char*)*yyleng);
                        strcpy(yylval.infos->info, yytext);
                        yylval.infos->linea = yylineno;
                        return OR;}
[{]                   {
                          //printf("%s\n",yytext);
                          yylval.infos =malloc(sizeof(InfoString));
                          //printf("llaveqabre");
                          yylval.infos->info = malloc(sizeof(char*)*yyleng);
                          strcpy(yylval.infos->info, yytext);
                          yylval.infos->linea = yylineno;
                          return LLAVEABRE;}


[}]                   {
                        //printf("%s\n",yytext);
                        yylval.infos =malloc(sizeof(InfoString));
                        yylval.infos->info = malloc(sizeof(char*)*yyleng);
                        strcpy(yylval.infos->info, yytext);
                        yylval.infos->linea = yylineno;
                        return LLAVECIERRA;}

[,]                   {
                        //printf("%s\n",yytext);
                        yylval.infos =malloc(sizeof(InfoString));yylval.infos->info = malloc(sizeof(char*)*yyleng);
                        strcpy(yylval.infos->info, yytext);
                        yylval.infos->linea = yylineno;
                        return COMA;}

"//"(.*[ \t]*.*)*[\n]+  ; /*ignorar lineas comentadas*/


.|\n                          ; /* ignore all the rest */


%%

void yyerror(){
	printf("%s%d\n","-> ERROR Sintactico en la linea: ",yylineno);
}

int main(int argc,char *argv[]){
	++argv,--argc;
	if (argc > 0)
		yyin = fopen(argv[0],"r");
	else
		yyin = stdin;

	yyparse();

}
