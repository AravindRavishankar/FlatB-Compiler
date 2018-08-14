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
using namespace llvm;
enum BinaryOp
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
		int start,step=1,end;
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
		BinaryOp op;
		AstBinaryExp(AstExp *left,AstExp *right,BinaryOp op)
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
		AstExpr *exp;
		AstIdentifier(string id)
		{
			this->id=id;
			this->exp=NULL;
			
		}
		AstIdentifier(string id,AstExp *exp)
		{
			this->id=id;
			this->exp=exp;
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
struct cmp {
	    bool operator()(const AstIdentifier a, const AstIdentifier b) const {
			        return a.id < b.id;
				}
};

class llvmVisitor : public visitor {

	public:
	LLVMContext Context_Main;
	Module *Module_Main;
	BasicBlock *Block_Main;
	stack<BasicBlock*> Stack_Block;

	Function *Function_Main;
	Function *Function_Print;
	Function *Function_scan;

	AstProgram *root;
	map<AstIdentifier, Value*,cmp> vT;
	map<string, BasicBlock*> labelTable;
	llvmVisitor(AstProgram *node) {
		Module_Main = new Module("MainModule", Context_Main);
		Module_Main->setTargetTriple("x86_64-pc-linux-gnu");
		Function_Main = Function::Create(FunctionType::get(Type::getVoidTy(Context_Main), false), GlobalValue::ExternalLinkage, "main", Module_Main);
		Block_Main = BasicBlock::Create(Context_Main, "Function_Main", Function_Main);
		Function_Print = Function::Create(FunctionType::get(Type::getInt64Ty(Context_Main), true), GlobalValue::ExternalLinkage, string("printf"), Module_Main);
		Function_scan = Function::Create(FunctionType::get(Type::getInt64Ty(Context_Main), true), GlobalValue::ExternalLinkage, string("scanf"), Module_Main);
		root = node;
    root->visit(this);
	}
	void *go(AstProgram *node) {
		Stack_Block.push(Block_Main);
    node->emptyd->visit(this);
		node->emptyc->visit(this);
		ReturnInst::Create(Context_Main, Stack_Block.top());
		Stack_Block.pop();
		Module_Main->print(errs(), nullptr);
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
      void *p=node->exp->visit(this);

			GlobalVariable *var = new GlobalVariable(*Module_Main, ArrayType::get(Type::getInt64Ty(Context_Main), idx), false, GlobalValue::CommonLinkage, NULL, node->id);
				var->setInitializer((Constant *)p);
        	vT[*node]=var;
		}
		else
		{
			GlobalVariable *var = new GlobalVariable(*Module_Main,Type::getInt64Ty(Context_Main), false, GlobalValue::CommonLinkage, NULL, node->id);

			var->setInitializer(ConstantInt::get(Type::getInt64Ty(Context_Main), 0, true));
			vT[*node]= var;
		}
	}
	 
	 void* evaluate(AstIdentifier *node)
	 {
		 if(node->index==INT_MAX)
		 {
			 if(vT.find(*node)!=vT.end())
			 {
				void *p=(void *)vT[*node];
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
			vector <Value*> indices;
			indices.push_back(ConstantInt::get(Context_Main, APInt(64, StringRef("0"), 10)));
			void *p=&node->index;
			indices.push_back((Value *)p);
			Value *location = GetElementPtrInst::CreateInBounds(vT[*node], indices, "tmp", Stack_Block.top());
      return (void *)location;
		 }
	 }
	 void *go(AstAssignment *node)
	 {
	 	Value* location=(Value *)node->id->evaluate(this);

		Value *val=(Value *)node->exp->visit(this);
		return new  StoreInst(val, location, false, Stack_Block.top());
	 }
	 void *go(AstPrintVals *node)
	 {

		pair<void *,string> *x=new pair<void  *,string>;
		 if(node->exp==NULL)
		 {
      x->first=NULL;
      x->second="%d";
      void *p=(void *)x;
			return p;
		 }
		 else
		 {
			x->first=node->exp->visit(this);
      x->second=node->txt;
		 	void *p=(void *)x;
			return p;
		 }
	 }
 	Value *convert(string text) {
		GlobalVariable *var = new GlobalVariable(*Module_Main, ArrayType::get(IntegerType::get(Context_Main, 8), text.size() + 1), true, GlobalValue::InternalLinkage, NULL, "string");
		var->setInitializer(ConstantDataArray::getString(Context_Main, text, true));
		return var;
	}
	 void *go(AstPrinting* node)
	 {
		vector<Value*> list;
		list.push_back(convert(" "));
		string FString = "";
		for(auto i=node->printvals->begin();i!=node->printvals->end();i++)
		{
			pair<void*,string> *tmp=(pair<void *,string> *)(*i)->visit(this);
			if(tmp->first==NULL)
				FString.append(tmp->second);
			else
			{
				FString.append(tmp->second);
				list.push_back((Value *)(tmp->first));
			}	
      delete tmp;
		}
		FString.append(node->last);
		list[0] = convert(FString);
		CallInst::Create(Function_Print, makeArrayRef(list), string("printf"), Stack_Block.top());
	 }
	
	void *go(AstWhileLoop *node)
	{

		BasicBlock *Entry = Stack_Block.top();
		BasicBlock *Header = BasicBlock::Create(Context_Main, "loop_header", Entry->getParent(), 0);
		BasicBlock *body_block = BasicBlock::Create(Context_Main, "loop_body", Entry->getParent(), 0);
		BasicBlock *after_loop_block = BasicBlock::Create(Context_Main, "after_loop", Entry->getParent(), 0);

		Stack_Block.push(Header);
		Value *cond = static_cast<Value*>(node->boolexp->visit(this));
		ICmpInst *compare = new ICmpInst(*Header, ICmpInst::ICMP_NE, cond, ConstantInt::get(Type::getInt64Ty(Context_Main), 0, true), "tmp");
		Stack_Block.pop();
		BranchInst::Create(Header, Entry);
		BranchInst::Create(body_block, after_loop_block, compare, Header);
		Stack_Block.push(body_block);
		node->emptyc->visit(this);
		body_block = Stack_Block.top();
		Stack_Block.pop();
		if (!body_block->getTerminator()) 
			BranchInst::Create(Header, body_block);
												
		Stack_Block.push(after_loop_block);
		return NULL;
	 }
	  void *go(AstIfElse *node)
	  {
		BasicBlock *Entry = Stack_Block.top();
		Value *cond = static_cast<Value *>(node->boolexp->visit(this));
		ICmpInst *compare = new ICmpInst(*Entry, ICmpInst::ICMP_NE, cond, ConstantInt::get(Type::getInt64Ty(Context_Main), 0, true), "tmp");
		BasicBlock *if_block = BasicBlock::Create(Context_Main, "IF_BLOCK", Entry->getParent());
		BasicBlock *merge_block = BasicBlock::Create(Context_Main, "MERGE_BLOCK", Entry->getParent());

		BasicBlock *returned_block = NULL;
		Stack_Block.push(if_block);
		node->then_emptyc->visit(this);
		returned_block = Stack_Block.top();
		Stack_Block.pop();
		if (!returned_block->getTerminator()) {
			BranchInst::Create(merge_block, returned_block);
		}
		if(node->else_emptyc!=NULL)
		{
			BasicBlock *else_block = BasicBlock::Create(Context_Main, "ELSE_BLOCK", Entry->getParent());
			Stack_Block.push(else_block);
			node->else_emptyc->visit(this);
			returned_block = Stack_Block.top();
			Stack_Block.pop();
			if (!returned_block->getTerminator()) {
				BranchInst::Create(merge_block, returned_block);
			}
			BranchInst::Create(if_block, else_block, compare, Entry);
		} 
		else 
		{
			BranchInst::Create(if_block, merge_block, compare, Entry);
		}
		Stack_Block.push(merge_block);
		return NULL;
	  } 
	   void *go(AstBinaryExp *node)
	   {
		Value* l=((Value *)node->left->visit(this));
		Value* r=((Value *)node->right->visit(this));
		switch(node->op)
		{
			case BinaryOp::plus: 
			return  BinaryOperator::Create(Instruction::Add, l, r, "tmp", Stack_Block.top());
			break;
			case BinaryOp::minus: 
			return BinaryOperator::Create(Instruction::Sub, l, r, "tmp", Stack_Block.top());
			break;
			case BinaryOp::mul:
			return BinaryOperator::Create(Instruction::Mul,l,r, "tmp", Stack_Block.top());
			break;
			case BinaryOp::dv :
			return BinaryOperator::Create(Instruction::SDiv,l,r, "tmp", Stack_Block.top());
			break;
			default:
			
				cout<<"Error\n";
				exit(-1);

		}
		return NULL;
	   }
	   void *go(AstBoolExp *node)
	   {

		Value* l=((Value *)node->left->visit(this));
		Value* r=((Value *)node->right->visit(this));
		switch(node->op)
		{

			case BooleanOperator::lt: 
			return new ZExtInst(CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_SLT,l, r,"tmp", Stack_Block.top()), Type::getInt64Ty(Context_Main), "zext", Stack_Block.top());
			break;
			case BooleanOperator::gt:  
			return new ZExtInst(CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_SGT,l, r,"tmp", Stack_Block.top()), Type::getInt64Ty(Context_Main), "zext", Stack_Block.top());
			break;
			case BooleanOperator::ge :
			return new ZExtInst(CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_SGE,l, r,"tmp", Stack_Block.top()), Type::getInt64Ty(Context_Main), "zext", Stack_Block.top());
			break;
			case BooleanOperator::le :
			return new ZExtInst(CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_SLE,l, r,"tmp", Stack_Block.top()), Type::getInt64Ty(Context_Main), "zext", Stack_Block.top());
			break;
			case BooleanOperator::neq:
			return new ZExtInst(CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_NE,l, r,"tmp", Stack_Block.top()), Type::getInt64Ty(Context_Main), "zext", Stack_Block.top());
			break;
			case BooleanOperator::eqeq :
			return new ZExtInst(CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_EQ,l,r,"tmp", Stack_Block.top()), Type::getInt64Ty(Context_Main), "zext", Stack_Block.top());
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
				return ConstantInt::get(Type::getInt64Ty(Context_Main), node->number);
			}
			else
			{
		
				Value *off=(Value *)node->identifier->evaluate(this);
				return new LoadInst(off, "tmp", Stack_Block.top());
			}	
			return NULL;
	    }
	
	void *go(AstForLoop *node)
	{
	   BasicBlock *Entry = Stack_Block.top();
	   BasicBlock *Header = BasicBlock::Create(Context_Main, "LoopHeader", Entry->getParent(), 0);
	   BasicBlock *body_block = BasicBlock::Create(Context_Main, "LoopBody", Entry->getParent(), 0);
	   BasicBlock *after_loop_block = BasicBlock::Create(Context_Main, "AfterLoop", Entry->getParent(), 0);
	   Value *location=((Value *)node->id->evaluate(this));
	   Value *val = new LoadInst(location, "load", Header);
	   void *p=&(node->end);
	   ICmpInst *compare = new ICmpInst(*Header, ICmpInst::ICMP_NE, val, static_cast<Value *>(p), "tmp");
	   BranchInst::Create(body_block, after_loop_block, compare, Header);
	   BranchInst::Create(Header, Entry);
	   Stack_Block.push(body_block);
	   Value *step=ConstantInt::get(Type::getInt64Ty(Context_Main), node->step);
	   
	   Value *x=(Value *)  BinaryOperator::Create(Instruction::Add,val, step, "tmp", Stack_Block.top());
		StoreInst(x, location, false, Stack_Block.top());
//    Stack_Block.pop();
	   body_block = Stack_Block.top();
	   Stack_Block.pop();
	  if (!body_block->getTerminator()) {
		BranchInst::Create(Header, body_block);
	  }
  	  Stack_Block.push(after_loop_block); 
	  return NULL;
	  
	 }
	
};
#endif
	    
	    
		 
	 
	
	









