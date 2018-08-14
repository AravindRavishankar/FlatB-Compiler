%{
//#include<stdio.h>
#include<bits/stdc++.h>
#include "ast.h"
//#include<stdlib.h>
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern int LINENUM; 
void yyerror(const char *s);
#include "lex.yy.c"

interpretVisitor *visitor = new interpretVisitor();
int cnt=0;
%}

%union
{

	int num;
	char *str;
	AstProgram *program;
	AstEmptyD *emptyd;
	AstEmptyC *emptyc;
	AstCStatement *cstatement;
	vector<AstCStatement *> *cstatements;
	AstIdentifier *id;
	vector<AstIdentifier *> *ids;
	AstPrintVals  *printval;
	vector<AstPrintVals *> *printvals;
	AstExp *expr;
	BooleanOperator *BoolOp;
	AstBoolExp *bexpr;
	AstTerm *term;
	AstLabel *label;
}
%type  <program> 	PROGRAM
%type <emptyd>	EMPTYD
%type <ids> DSTATEMENTS
%type <ids> DSTATEMENT
%type<id>IDENTIFIERS
%type<label> LABEL
%type<ids> MULTIDENTIFIERS
%type <emptyc>	EMPTYC
%type <cstatements> CSTATEMENTS
%type <cstatement> CSTATEMENT
%type <cstatement> ASSIGNMENT
%type <cstatement> PRINTING
%type <printvals> EXPRESSION
%type <printval> PRINTVALS 
%type <cstatement> FORLOOP
%type <cstatement> WHILELOOP
%type <cstatement> IFELSE
%type <cstatement> GOTOO
%type <cstatement> READING
%type <expr> EXP
%type <bexpr> BOOLEXP
%type <term> TERM
%type <str> IDENTIFIER
%type <str> STRING
%type <num> NUMBER


%token IDENTIFIER
%token STRING
%token NUMBER
%token PRINT
%token PRINTLN
%token READ
%token FOR
%token DECLBLOCK
%token CODEBLOCK
%token WHILE
%token INT
%token IF
%token ELSE
%token GOTO
%token GOT
%token PLUS
%token MINUS
%token MUL
%token DIV
%token ETOK
%token LT
%token GE
%token LE
%token GT
%token EQEQ
%token NEQ

%left   LT GE   LE GT NEQ EQEQ 
%left PLUS MINUS
%left MUL DIV







%%


PROGRAM : DECLBLOCK  EMPTYD CODEBLOCK EMPTYC { $$=new AstProgram($2,$4);	root=$$;} 



/*decl statement */

EMPTYD : '{' DSTATEMENTS '}' { $$=new AstEmptyD($2); }
	   | '{' '}'	 {$$= NULL; }


DSTATEMENTS : DSTATEMENT  { $$ =$1; }
			 | DSTATEMENTS DSTATEMENT  { $1->insert($1->end(),$2->begin(),$2->end()); }
			 

DSTATEMENT : INT MULTIDENTIFIERS ';' { $$=$2;}
			| ';'  { $$= new vector<AstIdentifier *>; }


MULTIDENTIFIERS : IDENTIFIERS {$$=new vector<AstIdentifier *>; $$->push_back($1); } 
				| MULTIDENTIFIERS ',' IDENTIFIERS { $1->push_back($3); $$=$1;} 


/*code statement */

EMPTYC : '{' CSTATEMENTS '}' { $$=new AstEmptyC($2); } 
	   | '{' '}' { $$=NULL; }



CSTATEMENTS  :  LABEL CSTATEMENTS   { visitor->lT[($1->id)]=*$2; $$=$2; } 
			| CSTATEMENT  CSTATEMENTS { $2->insert($2->begin(),$1);
										$$ =$2;
										}

			 | CSTATEMENT 	{	 $$=new vector<AstCStatement *>;
			 					$$->push_back($1);
								}
									


		
CSTATEMENT  :  ASSIGNMENT ';' { $$=$1; } 
		     | PRINTING ';'	 { $$=$1; }
			 | FORLOOP 	 { $$=$1;} 
			 | WHILELOOP { $$=$1; }
			 | READING ';' { $$=$1; }
			 | IFELSE { $$=$1; }
			 | GOTOO ';' { $$=$1; }
			 | ';'  { $$=new AstCStatement(); }
			 

LABEL : IDENTIFIER ':' { $$=new AstLabel($1); }

/* assignment */
ASSIGNMENT : IDENTIFIERS '=' EXP { $$=new AstAssignment($1,$3); }
	

/* printing */
PRINTING  : PRINT  EXPRESSION { $$=new AstPrinting($2); } 
		  |PRINTLN EXPRESSION {$$=new AstPrinting($2,"\n"); }

EXPRESSION : PRINTVALS { $$ =new vector<AstPrintVals *> ;
		   						$$->push_back($1); 
								}
		   | EXPRESSION ',' PRINTVALS { $1->push_back($3); $$=$1; }

PRINTVALS : EXP  { $$ =new AstPrintVals($1); } 
		  |   STRING   {$$ =new AstPrintVals($1); }
			 

/*for loop */
FORLOOP  : FOR IDENTIFIERS '=' NUMBER ',' NUMBER EMPTYC { $$=new AstForLoop($2,$4,$6,$7); }
		 | FOR IDENTIFIERS '=' NUMBER ',' NUMBER ',' NUMBER EMPTYC { $$=new AstForLoop($2,$4,$6,$8,$9); }

/*while loop */
WHILELOOP :   WHILE  BOOLEXP EMPTYC  { $$=new AstWhileLoop($2,$3); }

/*if else */
IFELSE :  IF BOOLEXP EMPTYC ELSE EMPTYC   { $$=new AstIfElse($2,$3,$5); } 
	   | IF BOOLEXP EMPTYC	{ $$=new AstIfElse($2,$3); }



/* go to */

GOTOO : GOTO IDENTIFIER IF BOOLEXP  { $$=new AstGoToo($2,$4); }
	  | GOTO IDENTIFIER  { $$=new AstGoToo($2); } 



/*read */
READING : READ MULTIDENTIFIERS { $$=new AstReading($2); } 


/* exp */
EXP : TERM   { $$=$1; }
	| EXP PLUS EXP  { $$=new AstBinaryExp($1,$3,BinaryOperator::plus); }
	| EXP MINUS EXP { $$=new AstBinaryExp($1,$3,BinaryOperator::minus); }
	| EXP MUL EXP { $$=new AstBinaryExp($1,$3,BinaryOperator::mul); }
	| EXP DIV EXP { $$=new AstBinaryExp($1,$3,BinaryOperator::dv); }

BOOLEXP	  : EXP GT EXP { $$=new AstBoolExp($1,$3,BooleanOperator::gt); }
		  | EXP LT EXP { $$=new AstBoolExp($1,$3,BooleanOperator::lt); }
	      |  EXP GE EXP{ $$=new AstBoolExp($1,$3,BooleanOperator::ge); }
	      | EXP LE EXP{ $$=new AstBoolExp($1,$3,BooleanOperator::le); }
		  | EXP NEQ EXP{ $$=new AstBoolExp($1,$3,BooleanOperator::neq); }
		  | EXP EQEQ EXP{ $$=new AstBoolExp($1,$3,BooleanOperator::eqeq); }

TERM : IDENTIFIERS { $$=new AstTerm($1); }
	 | NUMBER { $$=new AstTerm($1);}



/*identifier */
IDENTIFIERS : IDENTIFIER 	{ $$=new AstIdentifier($1); }
			| IDENTIFIER '[' EXP ']'  { $$= new AstIdentifier($1,$3); }

%%
int main(int, char** argv) {
	// open a file handle to a particular file:
	FILE *myfile = fopen(argv[1], "r");
			// make sure it is valid:
	if (!myfile) {
		cout << "I can't open sumN.b" << endl;
		return -1;
		}
										// set flex to read from it instead of defaulting to STDIN:
		yyin = myfile;
		do 
		{
				yyparse();
		} while (!feof(yyin));
		cout<<"Compiled successfully \n";

		if(root)
			root->visit(visitor);

//		llvmVisitor *visitorr=new llvmVisitor(root);
//		llvm::legacy::PassManager pm;
//		pm.add(llvm::createPrintModulePass(llvm::outs()));
//		pm.run(*visitorr->TheModule);

}
void yyerror(const char *s) {
	cout << "EEK, parse error!  Message: " << s << endl;
	cout<< "Line " << LINENUM+1 <<endl;
		// might as well halt now:
			exit(-1);
			}

			 

