#ifndef _LLVMV_H
#define _LLVMV_H
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>	
#include <llvm/IR/IRBuilder.h>
#include <llvm/Bitcode/BitstreamReader.h>
#include <llvm/Bitcode/BitstreamWriter.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include<bits/stdc++.h>
using namespace std;
enum BinaryOperator
{
	plus,
	minus,
	mul,
	dv
		
};
enum BooleanOperator
{
	gt,
	lt,
	ge,
	le,
	neq,
	eqeq
};
class AstNode{
	public:
};
class AstTerm;
class AstIdentifier;
class AstNumber;
class AstExp;
class AstBoolExp;
class AstBinaryExp;
class AstReading;
class AstGoToo;
class AstLabel;
class AstIfElse;
class AstProgram;
class AstEmptyC;
class AstEmptyD;
class AstCStatement;
class AstAssignment;
class AstPrinting;
class AstExpression;
class AstPrintvals;
class AstForLoop;
class AstWhileLoop;
class AstLabel;
class AstReading;
class AstPrinting;
class AstPrintVals;

class visitor{
	public:
		virtual void *go(AstProgram* node) = 0;
		virtual void *go(AstEmptyD* node) = 0; 
		virtual void *go(AstEmptyC* node) = 0;
		virtual void *go(AstIdentifier* node) = 0;
		virtual void *go(AstCStatement* node) = 0;
		virtual void *go(AstAssignment* node) = 0;
		virtual void *go(AstPrinting* node) = 0;
		virtual void *go(AstForLoop* node) = 0;
		virtual void *go(AstIfElse* node) = 0;
		virtual void *go(AstWhileLoop* node) = 0;
		virtual void *go(AstReading* node) = 0;
		virtual void *go(AstPrintVals* node)=0;
		virtual void *go(AstExp* node) = 0;
		virtual void *go(AstBoolExp* node) = 0;
		virtual void *go(AstBinaryExp* node) = 0;
		virtual void *go(AstTerm* node) = 0;
		virtual void *go(AstLabel *node)=0;
		virtual void *evaluate(AstIdentifier * node)=0;
};
class AstProgram : public AstNode{
	
	public : 
		AstEmptyD *emptyd;
		AstEmptyC *emptyc;
 		AstProgram(AstEmptyD *emptyd, AstEmptyC *emptyc) 		  
		{
			this->emptyd = emptyd;
			this->emptyc = emptyc;
		}
		 void *visit(visitor* _visitor) 
		{
			return _visitor->go(this);
		}

};
AstProgram *root;
class AstEmptyD : public AstNode {

	
	public : 
		vector<AstIdentifier *> *statements;
		AstEmptyD(vector<AstIdentifier *> *statements)
		{
			this->statements=statements;
		}
		 void *visit(visitor* _visitor) 
		{
			return _visitor->go(this);
		}
};
class AstEmptyC: public AstNode {
	public:
		vector<AstCStatement *> *cstatements;
		AstEmptyC(vector<AstCStatement *> *cstatements)
		{
			this->cstatements=cstatements;
		}
		AstEmptyC()
		{
			this->cstatements=NULL;
		}
		void *visit(visitor* _visitor) 
		{
			return _visitor->go(this);
		}
};
class AstCStatement : public AstNode
{
	public:
		virtual ~AstCStatement()
		{
		}
		 void *visit(visitor* _visitor) 
		{
			return _visitor->go(this);
		}
};
class AstAssignment : public AstCStatement
{
	public :
		AstIdentifier *id;
		AstExp  *exp;
		AstAssignment(AstIdentifier *id,AstExp *exp)
		{
			this->id=id;
			this->exp=exp;
		}

		 void *visit(visitor *_visitor) 
		{
			return _visitor->go(this);
		}
};
class AstPrinting : public AstCStatement
{
	public :
		vector<AstPrintVals *>  *printvals;
		string last="";
		AstPrinting(vector<AstPrintVals *> *printvals)
		{
			this->printvals=printvals;
		}
		AstPrinting(vector<AstPrintVals *> *printvals,string last)
		{
			this->printvals=printvals;
			this->last=last;
		}

		 void *visit(visitor* _visitor) 
		{
			return _visitor->go(this);
		}
};
class AstPrintVals : public AstNode
{
	public:
	 string txt;
	 AstExp *exp;
	AstPrintVals(string txt)
	{
		this->txt=txt;
		this->exp=NULL;
	}
	AstPrintVals(AstExp* exp)
	{
		this->exp=exp;
	}

	 void *visit(visitor* _visitor) 
	{
	  return _visitor->go(this);
	}

};
class AstForLoop :public AstCStatement 
{
	public :
		AstIdentifier *id;
		AstEmptyC *emptyc;
		int start,step=0,end;
		AstForLoop ( AstIdentifier  *id,int start,int end,AstEmptyC *emptyc)
		{
			this->id=id;
			this->start=start;
			this->end=end;
			this->emptyc=emptyc;
		}
		AstForLoop (AstIdentifier *id,int start,int step,int end,AstEmptyC *emptyc)
		{
			this->id=id;
			this->start=start;
			this->step=step;
			this->end=end;
			this->emptyc=emptyc;
		}

		 void *visit(visitor* _visitor) 
		{
			return _visitor->go(this);
		}
};
class AstWhileLoop: public AstCStatement
{
	public :
		AstBoolExp *boolexp;
		AstEmptyC *emptyc;
		AstWhileLoop(AstBoolExp *boolexp,AstEmptyC *emptyc)
		{
			this->boolexp=boolexp;
			this->emptyc=emptyc;

		}

		 void *visit(visitor* _visitor) 
		{
		   return _visitor->go(this);
		}
};
class AstIfElse: public AstCStatement{
	public :
		AstBoolExp *boolexp;
		AstEmptyC *then_emptyc;
		AstEmptyC *else_emptyc;
		AstIfElse(AstBoolExp *boolexp,AstEmptyC *then_emptyc,AstEmptyC *else_emptyc)
		{

			this->boolexp=boolexp;
			this->then_emptyc=then_emptyc;
			this->else_emptyc=else_emptyc;
		}
		AstIfElse(AstBoolExp *boolexp,AstEmptyC *then_emptyc)
		{
			this->boolexp=boolexp;
			this->then_emptyc=then_emptyc;
		}
		 void *visit(visitor* _visitor) 
		{
		  return _visitor->go(this);
		}
		
		
};
class AstLabel:public AstNode{
	public:
		string id;
		AstLabel(string id)
		{
			this->id=id;
		}
		 void *visit(visitor* _visitor) 
		{
		 	return _visitor->go(this);

		}
};
class AstGoToo : public AstCStatement
{
	public:
		string id;
		AstBoolExp *boolexp=NULL;
		AstGoToo(string id)
		{
			this->id=id;
		}
		AstGoToo(string id,AstBoolExp *boolexp)
		{
			this->id=id;
			this->boolexp=boolexp;

		}
		void *visit(visitor* _visitor) 
		{
			return _visitor->go(this);
		}
};
class AstReading: public AstCStatement
{
	public:
		vector<AstIdentifier *> *id;
		AstReading(vector<AstIdentifier *> *id)
		{
			this->id=id;
		}

		 void *visit(visitor* _visitor) 
		{
			return _visitor->go(this);

		}
};
class AstExp : public AstNode
{
	public:
	virtual ~AstExp()
	{
	}

	 void *visit(visitor* _visitor) 
	{
		return _visitor->go(this);

	}
};
class AstBinaryExp : public AstExp
{
	public:
		AstExp *left;
		AstExp *right;
		BinaryOperator op;
		AstBinaryExp(AstExp *left,AstExp *right,BinaryOperator op)
		{
			this->left=left;
			this->right=right;
			this->op=op;
		}

		 void *visit(visitor* _visitor) 
		{
			return _visitor->go(this);

		}
};
class AstBoolExp : public AstExp
{
	public :
		AstExp *left;
		AstExp *right;
		BooleanOperator op;
		AstBoolExp(AstExp *left,AstExp *right,BooleanOperator op)
		{
			this->left=left;
			this->right=right;
			this->op=op;
		}

		 void *visit(visitor* _visitor) 
		{
			return _visitor->go(this);
		}
};

class AstTerm :public AstExp
{
	public : int number;
	AstIdentifier *identifier;
	AstTerm(int number)
	{
		this->number=number;
		this->identifier=NULL;
	}
	AstTerm(AstIdentifier *identifier)
	{
		this->identifier=identifier;
	}

	 void *visit(visitor* _visitor) 
	{
		return _visitor->go(this);
	}
};
class AstIdentifier :public AstNode
{
	public :
		string id;
		int index;
		AstIdentifier(string id)
		{
			this->id=id;
			this->index=INT_MAX;
			
		}
		AstIdentifier(string id,int index)
		{
			this->id=id;
			this->index=index;
		}
		 void *visit(visitor* _visitor) 
		{
			return _visitor->go(this);
		}
		 void *evaluate(visitor* _visitor)
	 	{
			 return _visitor->evaluate(this);
	 	}
};
class interpretVisitor  : public visitor
{
	public:
	map <string,int> vT;
	map <string,vector<AstCStatement *> > lT;
	vector< AstCStatement*> *stmnts;
	void *go(AstProgram *node)
	{
		if(node->emptyd!=NULL)
		node->emptyd->visit(this);
		if(node->emptyc!=NULL)
		node->emptyc->visit(this);
		return NULL;
	}
	void *go(AstEmptyC *node)
	{
		for(auto it=node->cstatements->begin();it!=node->cstatements->end();it++)
			(*it)->visit(this);
		return NULL;	
	}
	void *go(AstEmptyD *node)
	{
		for(auto i = node->statements->begin();i!=node->statements->end();i++)
		{		
			((*i)->visit(this));
		}
    cout<<"End of Declaration\n";
		return NULL;
		
	}
	void *go(AstIdentifier *node)
	{
		if(node->index!=INT_MAX)
		{
			int idx=node->index;
			if(idx<=0)
			{
				cout<<"Error\n";
				exit(-1);
			}
			for(int j=0;j<idx;j++)
			{
				string temp=node->id +"[" + to_string(j) + "]";
				vT[temp] = 0;
			}
		}
		else
			vT[node->id]=0;
		return NULL;
	}
	void *go(AstCStatement * node)
	{

		AstAssignment *assignment = dynamic_cast<AstAssignment *>(node);
		if(assignment!=NULL)
			assignment->visit(this);
		
		AstReading *reading = dynamic_cast<AstReading *>(node);
		
		if(reading!=NULL)
			reading->visit(this);
		AstWhileLoop *whileloop = dynamic_cast<AstWhileLoop *>(node);
		if(whileloop!=NULL)
			whileloop->visit(this);
		AstIfElse *ifelse = dynamic_cast<AstIfElse *>(node);
		
		if(ifelse!=NULL)
			ifelse->visit(this);
		AstForLoop *forloop =dynamic_cast<AstForLoop *>(node);
		
		if(forloop!=NULL)
			forloop->visit(this);
		AstLabel *label = dynamic_cast<AstLabel *>(node);

		if(label!=NULL)

			label->visit(this);
		AstGoToo *gotoo = dynamic_cast<AstGoToo *>(node);
		if(gotoo!=NULL)
			go(gotoo);
		AstPrinting *printing = dynamic_cast<AstPrinting *>(node);
		if(printing!=NULL)
			printing->visit(this);
		return NULL;
	}
	void *go(AstGoToo* node)
	{
		 if(lT.find(node->id)!=lT.end())
		 {
			if(node->boolexp ==NULL)
			{
				for(auto i=lT[node->id].begin();i!=lT[node->id].end();i++)	   	  
					(*i)->visit(this);
				
				exit(0);
			}
			if(*((bool *)node->boolexp->visit(this))==true)
			{
				for(auto i=lT[node->id].begin();i!=lT[node->id].end();i++)	   	  
					(*i)->visit(this);
				exit(0);
			}
		 }
		 else
		 {
			 cout<<"Error : GoTo Label not found\n" ;
			 exit(-1);
		 }
		return NULL;
	 }
	 void *go(AstAssignment *node)
	 {
	 	string id=*((string *)node->id->evaluate(this));
		vT[id]=*((int *)node->exp->visit(this));
		return NULL;
	 }
	 void *evaluate(AstIdentifier *node)
	 {
		 if(node->index==INT_MAX)
		 {
			 if(vT.find(node->id)!=vT.end())
			 {
				void *p=&node->id;

				return p;
			 }
			 else 
			 {
				 cout<<"Error Undeclared Variable Used\n";
				 exit(-1);
			 }
		 }
		 else
		 {
			int val=node->index;
			string left="[";
			string right="]";
			string temp=node->id +left + to_string(val) + right;
			if(vT.find(temp)==vT.end())
			{
				cout<<"Error Undeclared Variable Used\n";
				exit(-1);
			}
			void *p=&temp;
			return p;
		 }
	  }
	  void *go(AstReading *node)
	  {
		int x;
		for(auto i=node->id->begin();i!=node->id->end();i++)
		{
			string temp=*((string *)(*i)->evaluate(this));
			cin>>x;
			vT[temp]=x;
		}
		return NULL;
	  }  
	  void *go(AstWhileLoop *node)
	  {
		while(node->boolexp->visit(this))
		{
			node->emptyc->visit(this);
		}
		return NULL;
	  } 
	  void *go(AstIfElse *node)
	  {
		if(node->boolexp->visit(this))
			node->then_emptyc->visit(this);
		else if(node->else_emptyc!=NULL)
			node->else_emptyc->visit(this);
		return NULL;
	  } 
	  void *go(AstForLoop *node)
	  {
	 	string x=*((string *)node->id->evaluate(this));
		int step=node->step;
			
		int start=node->start;;
		vT[x]=start;
		while(start<node->end)
		{
			node->emptyc->visit(this);
			start+=step;
			vT[x]+=step;
		}
		return NULL;
	  }
	  void *go(AstPrintVals* node)
	  {
		 
		 if(node->exp==NULL)
		 
			 cout<<node->txt<<" ";
		 else
		 	cout<<node->exp->visit(this)<<" ";
		 return NULL;
	  }
	  void *go(AstPrinting* node)
	  {
		for(auto i=node->printvals->begin();i!=node->printvals->end();i++)
			(*i)->visit(this);
		
		cout<<node->last;
		return NULL;
	  } 
	  void *go(AstExp *node)
	  {
		AstBoolExp *bool_exp = dynamic_cast<AstBoolExp *>(node);
		AstBinaryExp *binary_exp = dynamic_cast<AstBinaryExp *>(node);
		AstTerm *term = dynamic_cast<AstTerm *>(node);		
		if(bool_exp!=NULL)
			return bool_exp->visit(this);
		
		
		if(binary_exp!=NULL)
			return binary_exp->visit(this);
		if(term!=NULL)
			return term->visit(this);
	  } 
	  void *go(AstLabel *node)
	  {
		 
		 if(vT.find(node->id) !=vT.end())
		 {
			 cout<<"Error\n";
			 cout<<"Label is already  used as Variable\n";
			 exit(-1);
		 }
		 return NULL;
	  }
	 void *go(AstBinaryExp *node)
	 {
		int l=*((int *)node->left->visit(this));
		int r=*((int *)node->right->visit(this));
		int exp;		
		void *p;
		switch(node->op)
		{
			case BinaryOperator::plus: 
				 				
				exp=l+r; 
				p=&exp;				
				return p;
			break;
			case BinaryOperator::minus: 
				exp= l-r;
				p=&exp;		
				return p;					
			break;
			case BinaryOperator::mul:
				exp=l*r;
				p=&exp;
				return p;
			break;
			case BinaryOperator::dv :
				exp=l/r;
				p=&exp;
				return p;
			break;
			default:
				cout<<"Error\n";
				exit(-1);

		}
		return NULL;
	 } 
	 void * go(AstBoolExp *node)
	 {

		int l=*((int *)node->left->visit(this));
		int r=*((int *)node->right->visit(this));
		void *p;
		bool res;
		switch(node->op)
		{

			case BooleanOperator::gt: 
				res=(l>r);
				p=&res;
				return p;
			break;
			case BooleanOperator::lt:  
				res=(l < r);
				p=&res;
				return p;
				break;
			case BooleanOperator::ge :
				res=(l>=r);
				p=&res;
				return 	p;
				break;
			case BooleanOperator::le :
				res = (l<=r);
				p=&res;
				return p;
				break;
			case BooleanOperator::neq:
				res=(l!=r);
				p=&res;
				return p;
			break;
			case BooleanOperator::eqeq :
				res=(l==r);
				p=&res;
				return p;
			break;
			default:
				cout<<"Error\n";
				exit(-1);


	    }
		return NULL;
	  } 
	 void *go(AstTerm *node)
	 {
		 void *p;
		if(node->identifier==NULL)
		{
			p=&node->number;
			return p;
		}
		else
		{
			string val =*((string *)node->identifier->evaluate(this));
			p=&vT[val];
			return p;
		}
	 }
};

struct cmp {
	    bool operator()(const AstIdentifier a, const AstIdentifier b) const {
			        return a.id < b.id;
				}
};

class llvmVisitor : public visitor {

	public:
	llvm::LLVMContext TheContext;
	llvm::Module *TheModule;
	llvm::BasicBlock *mainBlock;
	stack<llvm::BasicBlock*> blockStack;

	llvm::Function *mainFunction;
	llvm::Function *printFunction;
	llvm::Function *scanFunction;

	AstProgram *root;
	map<AstIdentifier, llvm::Value*,cmp> variableTable;
	map<string, llvm::BasicBlock*> labelTable;
	llvmVisitor(AstProgram *node) {
		TheModule = new llvm::Module("mainModule", TheContext);
		TheModule->setTargetTriple("x86_64-pc-linux-gnu");
		mainFunction = llvm::Function::Create(llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), false), llvm::GlobalValue::ExternalLinkage, "main", TheModule);
		mainBlock = llvm::BasicBlock::Create(TheContext, "mainFunction", mainFunction);
		printFunction = llvm::Function::Create(llvm::FunctionType::get(llvm::Type::getInt64Ty(TheContext), true), llvm::GlobalValue::ExternalLinkage, string("printf"), TheModule);
		scanFunction = llvm::Function::Create(llvm::FunctionType::get(llvm::Type::getInt64Ty(TheContext), true), llvm::GlobalValue::ExternalLinkage, string("scanf"), TheModule);
		root = node;
    root->visit(this);
	}
	void *go(AstProgram *node) {
		blockStack.push(mainBlock);
    node->emptyd->visit(this);
		node->emptyc->visit(this);
		llvm::ReturnInst::Create(TheContext, blockStack.top());
		blockStack.pop();
		TheModule->print(llvm::errs(), nullptr);
		return NULL;
	}
	void *go(AstEmptyC *node)
	{
		for(auto it=node->cstatements->begin();it!=node->cstatements->end();it++)
			(*it)->visit(this);
	}
	void *go(AstEmptyD *node)
	{
		for(auto i = node->statements->begin();i!=node->statements->end();i++)
		{		
			((*i)->visit(this));
		}
		
	}

	void *go(AstExp *node)
	{
		AstBoolExp *bool_exp = dynamic_cast<AstBoolExp *>(node);
		AstBinaryExp *binary_exp = dynamic_cast<AstBinaryExp *>(node);
		AstTerm *term = dynamic_cast<AstTerm *>(node);		
		if(bool_exp!=NULL)
			return bool_exp->visit(this);
		
		
		if(binary_exp!=NULL)
			return binary_exp->visit(this);
		if(term!=NULL)
			return term->visit(this);
	} 
	void *go(AstCStatement * node)
	{

		AstAssignment *assignment = dynamic_cast<AstAssignment *>(node);
		if(assignment!=NULL)
			assignment->visit(this);
		
		AstReading *reading = dynamic_cast<AstReading *>(node);
		
		if(reading!=NULL)
			reading->visit(this);
		AstWhileLoop *whileloop = dynamic_cast<AstWhileLoop *>(node);
		if(whileloop!=NULL)
			whileloop->visit(this);
		AstIfElse *ifelse = dynamic_cast<AstIfElse *>(node);
		
		if(ifelse!=NULL)
			ifelse->visit(this);
		AstForLoop *forloop =dynamic_cast<AstForLoop *>(node);
		
		if(forloop!=NULL)
			forloop->visit(this);
		AstLabel *label = dynamic_cast<AstLabel *>(node);

		if(label!=NULL)

			label->visit(this);
		AstGoToo *gotoo = dynamic_cast<AstGoToo *>(node);
		if(gotoo!=NULL)
			go(gotoo);
		AstPrinting *printing = dynamic_cast<AstPrinting *>(node);
		if(printing!=NULL)
			printing->visit(this);
		return NULL;
	}
	void *go(AstLabel *node)
	{
		return NULL;
	}
	void *go(AstReading *node)
	{
		return NULL;
	}
	void *go(AstIdentifier *node)
	{

		if(node->index!=INT_MAX)
		{
			int idx=node->index;
			if(idx<=0)
			{
				cout<<"Error\n";
				exit(-1);
			}
			llvm::GlobalVariable *var = new llvm::GlobalVariable(*TheModule, llvm::ArrayType::get(llvm::Type::getInt64Ty(TheContext), idx), false, llvm::GlobalValue::CommonLinkage, NULL, node->id);
				var->setInitializer(llvm::ConstantAggregateZero::get(llvm::ArrayType::get(llvm::Type::getInt64Ty(TheContext), idx)));
        variableTable.insert(make_pair(*node, var));
		}
		else
		{
			llvm::GlobalVariable *globalVar = new llvm::GlobalVariable(*TheModule,llvm::Type::getInt64Ty(TheContext), false, llvm::GlobalValue::CommonLinkage, NULL, node->id);

			globalVar->setInitializer(llvm::ConstantInt::get(llvm::Type::getInt64Ty(TheContext), 0, true));
			variableTable[*node]= globalVar;
		}
	}
	 
	 void* evaluate(AstIdentifier *node)
	 {
		 if(node->index==INT_MAX)
		 {
			 if(variableTable.find(*node)!=variableTable.end())
			 {
				void *p=(void *)variableTable[*node];
				return p;
			 }
			 else 
			 {
				 cout<<"Error Undeclared Variable Used\n";
				 exit(-1);
			 }
		 }
		 else
		 {
			std::vector <llvm::Value*> index;
			index.push_back(llvm::ConstantInt::get(TheContext, llvm::APInt(64, llvm::StringRef("0"), 10)));
			void *p=&node->index;
			index.push_back((llvm::Value *)p);
			llvm::Value *location = llvm::GetElementPtrInst::CreateInBounds(variableTable[*node], index, "tmp", blockStack.top());
            return (void *)location;
		 }
	 }
	 void *go(AstAssignment *node)
	 {
	 	llvm::Value* location=(llvm::Value *)node->id->evaluate(this);

		llvm::Value *val=(llvm::Value *)node->exp->visit(this);
		return new  llvm::StoreInst(val, location, false, blockStack.top());
	 }
	 void *go(AstPrintVals *node)
	 {
		 if(node->exp==NULL)
		 {
			pair<void *,string> x={NULL,node->txt};
			void *p=&x;
			return p;
		 }
		 else
		 {
			pair<void *,string> x={node->exp->visit(this),node->txt};
		 	void *p=&x;
			return p;
		 }
	 }
 	llvm::Value *convertToValue(string text) {
		llvm::GlobalVariable *variable = new llvm::GlobalVariable(*TheModule, llvm::ArrayType::get(llvm::IntegerType::get(TheContext, 8), text.size() + 1), true, llvm::GlobalValue::InternalLinkage, NULL, "string");
		variable->setInitializer(llvm::ConstantDataArray::getString(TheContext, text, true));
		return variable;
	}
	 void *go(AstPrinting* node)
	 {
		vector<llvm::Value*> list;
		list.push_back(convertToValue(" "));
		string FString = "";
		for(auto i=node->printvals->begin();i!=node->printvals->end();i++)
		{
			pair<void*,string> *tmp=(pair<void *,string> *)(*i)->visit(this);
			if(tmp->first==NULL)
				FString.append(tmp->second);
			else
			{
				FString.append(tmp->second);
				list.push_back((llvm::Value *)(tmp->first));
			}	
		}
		FString.append(node->last);
		list[0] = convertToValue(FString);
		llvm::CallInst::Create(printFunction, llvm::makeArrayRef(list), string("printf"), blockStack.top());
	 }
	
	void *go(AstWhileLoop *node)
	{

		llvm::BasicBlock *entry_block = blockStack.top();
		llvm::BasicBlock *header_block = llvm::BasicBlock::Create(TheContext, "loop_header", entry_block->getParent(), 0);
		llvm::BasicBlock *body_block = llvm::BasicBlock::Create(TheContext, "loop_body", entry_block->getParent(), 0);
		llvm::BasicBlock *after_loop_block = llvm::BasicBlock::Create(TheContext, "after_loop", entry_block->getParent(), 0);

		blockStack.push(header_block);
		llvm::Value *condition = static_cast<llvm::Value*>(node->boolexp->visit(this));
		llvm::ICmpInst *comparison = new llvm::ICmpInst(*header_block, llvm::ICmpInst::ICMP_NE, condition, llvm::ConstantInt::get(llvm::Type::getInt64Ty(TheContext), 0, true), "tmp");
		blockStack.pop();
		while(node->boolexp->visit(this))
		{
			node->emptyc->visit(this);
		}
		llvm::BranchInst::Create(header_block, entry_block);
		llvm::BranchInst::Create(body_block, after_loop_block, comparison, header_block);
		blockStack.push(body_block);
		node->emptyc->visit(this);
		body_block = blockStack.top();
		blockStack.pop();
		if (!body_block->getTerminator()) 
			llvm::BranchInst::Create(header_block, body_block);
												
		blockStack.push(after_loop_block);
		return NULL;
	 }
	  void *go(AstIfElse *node)
	  {
		llvm::BasicBlock *entry_block = blockStack.top();
		llvm::Value *condition = static_cast<llvm::Value *>(node->boolexp->visit(this));
		llvm::ICmpInst *comparison = new llvm::ICmpInst(*entry_block, llvm::ICmpInst::ICMP_NE, condition, llvm::ConstantInt::get(llvm::Type::getInt64Ty(TheContext), 0, true), "tmp");
		llvm::BasicBlock *if_block = llvm::BasicBlock::Create(TheContext, "if_block", entry_block->getParent());
		llvm::BasicBlock *merge_block = llvm::BasicBlock::Create(TheContext, "merge_block", entry_block->getParent());

		llvm::BasicBlock *returned_block = NULL;
		blockStack.push(if_block);
		node->then_emptyc->visit(this);
		returned_block = blockStack.top();
		blockStack.pop();
		if (!returned_block->getTerminator()) {
			llvm::BranchInst::Create(merge_block, returned_block);
		}
		if(node->else_emptyc!=NULL)
		{
			llvm::BasicBlock *else_block = llvm::BasicBlock::Create(TheContext, "else_block", entry_block->getParent());
			blockStack.push(else_block);
			node->else_emptyc->visit(this);
			returned_block = blockStack.top();
			blockStack.pop();
			if (!returned_block->getTerminator()) {
				llvm::BranchInst::Create(merge_block, returned_block);
			}
			llvm::BranchInst::Create(if_block, else_block, comparison, entry_block);
		} 
		else 
		{
			llvm::BranchInst::Create(if_block, merge_block, comparison, entry_block);
		}
		blockStack.push(merge_block);
		return NULL;
	  } 
	   void *go(AstBinaryExp *node)
	   {
		llvm::Value* l=((llvm::Value *)node->left->visit(this));
		llvm::Value* r=((llvm::Value *)node->right->visit(this));
		switch(node->op)
		{
			case BinaryOperator::plus: 
			return  llvm::BinaryOperator::Create(llvm::Instruction::Add, l, r, "tmp", blockStack.top());
			break;
			case BinaryOperator::minus: 
			return llvm::BinaryOperator::Create(llvm::Instruction::Sub, l, r, "tmp", blockStack.top());
			break;
			case BinaryOperator::mul:
			return llvm::BinaryOperator::Create(llvm::Instruction::Mul,l,r, "tmp", blockStack.top());
			break;
			case BinaryOperator::dv :
			return llvm::BinaryOperator::Create(llvm::Instruction::SDiv,l,r, "tmp", blockStack.top());
			break;
			default:
			
				cout<<"Error\n";
				exit(-1);

		}
		return NULL;
	   }
	   void *go(AstBoolExp *node)
	   {

		llvm::Value* l=((llvm::Value *)node->left->visit(this));
		llvm::Value* r=((llvm::Value *)node->right->visit(this));
		switch(node->op)
		{

			case BooleanOperator::lt: 
			return new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_SLT,l, r,"tmp", blockStack.top()), llvm::Type::getInt64Ty(TheContext), "zext", blockStack.top());
			break;
			case BooleanOperator::gt:  
			return new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_SGT,l, r,"tmp", blockStack.top()), llvm::Type::getInt64Ty(TheContext), "zext", blockStack.top());
			break;
			case BooleanOperator::ge :
			return new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_SGE,l, r,"tmp", blockStack.top()), llvm::Type::getInt64Ty(TheContext), "zext", blockStack.top());
			break;
			case BooleanOperator::le :
			return new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_SLE,l, r,"tmp", blockStack.top()), llvm::Type::getInt64Ty(TheContext), "zext", blockStack.top());
			break;
			case BooleanOperator::neq:
			return new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_NE,l, r,"tmp", blockStack.top()), llvm::Type::getInt64Ty(TheContext), "zext", blockStack.top());
			break;
			case BooleanOperator::eqeq :
			return new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_EQ,l,r,"tmp", blockStack.top()), llvm::Type::getInt64Ty(TheContext), "zext", blockStack.top());
			break;
			default:
				cout<<"Error\n";
				exit(-1);
		}
	     }
	     void *go(AstTerm *node)
	     {
			if(node->identifier==NULL)
			{
				return llvm::ConstantInt::get(llvm::Type::getInt64Ty(TheContext), node->number);
			}
			else
			{
		
				llvm::Value *offset=(llvm::Value *)node->identifier->evaluate(this);
				return new llvm::LoadInst(offset, "tmp", blockStack.top());
			}	
			return NULL;
	    }
	
	void *go(AstForLoop *node)
	{
	   llvm::BasicBlock *entry_block = blockStack.top();
	   llvm::BasicBlock *header_block = llvm::BasicBlock::Create(TheContext, "loop_header", entry_block->getParent(), 0);
	   llvm::BasicBlock *body_block = llvm::BasicBlock::Create(TheContext, "loop_body", entry_block->getParent(), 0);
	   llvm::BasicBlock *after_loop_block = llvm::BasicBlock::Create(TheContext, "after_loop", entry_block->getParent(), 0);
	   llvm::Value *location=((llvm::Value *)node->id->evaluate(this));
	   llvm::Value *val = new llvm::LoadInst(location, "load", header_block);
	   void *p=&(node->end);
	   llvm::ICmpInst *comparison = new llvm::ICmpInst(*header_block, llvm::ICmpInst::ICMP_NE, val, static_cast<llvm::Value *>(p), "tmp");
	   llvm::BranchInst::Create(body_block, after_loop_block, comparison, header_block);
	   llvm::BranchInst::Create(header_block, entry_block);
	   blockStack.push(body_block);
	   llvm::Value *step=llvm::ConstantInt::get(llvm::Type::getInt64Ty(TheContext), node->step);
	   
	   llvm::Value *x=(llvm::Value *)  llvm::BinaryOperator::Create(llvm::Instruction::Add,val, step, "tmp", blockStack.top());
		llvm::StoreInst(x, location, false, blockStack.top());
	   body_block = blockStack.top();
	   blockStack.pop();
	  if (!body_block->getTerminator()) {
		llvm::BranchInst::Create(header_block, body_block);
	  }
  	  blockStack.push(after_loop_block);
	  return NULL;
	  
	 }
	
};
#endif
	    
	    
		 
	 
	
	









