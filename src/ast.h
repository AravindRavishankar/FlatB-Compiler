#ifndef _AST_H
#define _AST_H
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
		virtual void go(AstProgram* node) = 0;
		virtual void go(AstEmptyD* node) = 0; 
		virtual void go(AstEmptyC* node) = 0;
		virtual void go(AstIdentifier* node) = 0;
		virtual void go(AstCStatement* node) = 0;
		virtual void go(AstAssignment* node) = 0;
		virtual void go(AstPrinting* node) = 0;
		virtual void go(AstForLoop* node) = 0;
		virtual void go(AstIfElse* node) = 0;
		virtual void go(AstWhileLoop* node) = 0;
		virtual void go(AstReading* node) = 0;
		virtual void go(AstPrintVals* node)=0;
		virtual int go(AstExp* node) = 0;
		virtual bool go(AstBoolExp* node) = 0;
		virtual int go(AstBinaryExp* node) = 0;
		virtual int go(AstTerm* node) = 0;
		virtual void go(AstLabel *node)=0;
		virtual string evaluate(AstIdentifier * node)=0;
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
		 void visit(visitor* _visitor) 
		{
			_visitor->go(this);
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
		 void visit(visitor* _visitor) 
		{
			_visitor->go(this);
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
		void visit(visitor* _visitor) 
		{
			_visitor->go(this);
		}
};
class AstCStatement : public AstNode
{
	public:
		virtual ~AstCStatement()
		{
		}
		 void visit(visitor* _visitor) 
		{
			_visitor->go(this);
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

		 void visit(visitor *_visitor) 
		{
			_visitor->go(this);
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

		 void visit(visitor* _visitor) 
		{
			_visitor->go(this);
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

	 void visit(visitor* _visitor) 
	{
		_visitor->go(this);
	}

};
class AstForLoop :public AstCStatement 
{
	public :
		AstIdentifier *id;
		AstEmptyC *emptyc;
		int start,step=-1,end;
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

		 void visit(visitor* _visitor) 
		{
			_visitor->go(this);
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

		 void visit(visitor* _visitor) 
		{
			_visitor->go(this);
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
		 void visit(visitor* _visitor) 
		{
			_visitor->go(this);
		}
		
		
};
class AstLabel:public AstNode{
	public:
		string id;
		AstLabel(string id)
		{
			this->id=id;
		}
		 void visit(visitor* _visitor) 
		{
			_visitor->go(this);
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
		void visit(visitor* _visitor) 
		{
			_visitor->go(this);
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

		 void visit(visitor* _visitor) 
		{
			_visitor->go(this);
		}
};
class AstExp : public AstNode
{
	public:
	virtual ~AstExp()
	{
	}

	 int  visit(visitor* _visitor) 
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

		 int visit(visitor* _visitor) 
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

		 bool visit(visitor* _visitor) 
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

	 int visit(visitor* _visitor) 
	{
		return _visitor->go(this);
	}
};
class AstIdentifier :public AstNode
{
	public :
		string id;
		AstExp *exp;
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
		 void visit(visitor* _visitor) 
		{
			return _visitor->go(this);
		}
		 string evaluate(visitor* _visitor)
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
	void go(AstProgram *node)
	{
		if(node->emptyd!=NULL)
		node->emptyd->visit(this);
		if(node->emptyc!=NULL)
		node->emptyc->visit(this);
	}
	void go(AstEmptyC *node)
	{
		for(auto it=node->cstatements->begin();it!=node->cstatements->end();it++)
			(*it)->visit(this);
	}
	void go(AstEmptyD *node)
	{
		for(auto i = node->statements->begin();i!=node->statements->end();i++)
		{		
			((*i)->visit(this));
		}
		
	}
	void go(AstIdentifier *node)
	{
		if(node->exp!=NULL)
		{
			int idx=node->exp->visit(this);
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
	}
	void go(AstCStatement * node)
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
	}
	void go(AstGoToo* node)
	{
		 if(lT.find(node->id)!=lT.end())
		 {
			if(node->boolexp ==NULL)
			{
				for(auto i=lT[node->id].begin();i!=lT[node->id].end();i++)	   	  
					(*i)->visit(this);
				
				exit(0);
			}
			if(node->boolexp->visit(this)==true)
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
	 }
	 void go(AstAssignment *node)
	 {
	 	string id=node->id->evaluate(this);
		vT[id]=node->exp->visit(this);
	 }
	 string  evaluate(AstIdentifier *node)
	 {
		 if(node->exp==NULL)
		 {
			 if(vT.find(node->id)!=vT.end())
			 {
				 return node->id;
			 }
			 else 
			 {
				 cout<<"Error Undeclared Variable Used\n";
				 exit(-1);
			 }
		 }
		 else
		 {
			int val=node->exp->visit(this);
			string left="[";
			string right="]";
			string temp=node->id +left + to_string(val) + right;
			if(vT.find(temp)==vT.end())
			{
				cout<<"Error Undeclared Variable Used\n";
				exit(-1);
			}
			return temp;
		 }
	  }
	  void go(AstReading *node)
	  {
		int x;
		for(auto i=node->id->begin();i!=node->id->end();i++)
		{
			string temp=(*i)->evaluate(this);
			cin>>x;
			vT[temp]=x;
		}
	  }  
	  void go(AstWhileLoop *node)
	  {
		while(node->boolexp->visit(this))
		{
			node->emptyc->visit(this);
		}
	  } 
	  void go(AstIfElse *node)
	  {
		if(node->boolexp->visit(this))
			node->then_emptyc->visit(this);
		else if(node->else_emptyc!=NULL)
			node->else_emptyc->visit(this);
	  } 
	  void go(AstForLoop *node)
	  {
	 	string x=node->id->evaluate(this);

		int step;
		if(node->step==-1)
			step=1;
		else
			step=node->step;
			
		int start=node->start;;
		vT[x]=start;
		while(start<node->end)
		{
			node->emptyc->visit(this);
			start+=step;
			vT[x]+=step;
		}
	  }
	  void go(AstPrintVals* node)
	  {
		 
		 if(node->exp==NULL)
		 
			 cout<<node->txt<<" ";
		 else
		 	cout<<node->exp->visit(this)<<" ";
	  }
	  void go(AstPrinting* node)
	  {
		for(auto i=node->printvals->begin();i!=node->printvals->end();i++)
			(*i)->visit(this);
		
		cout<<node->last;
	  } 
	  int go(AstExp *node)
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
	  void go(AstLabel *node)
	  {
		 
		 if(vT.find(node->id) !=vT.end())
		 {
			 cout<<"Error\n";
			 cout<<"Label is already  used as Variable\n";
			 exit(-1);
		 }
	  }
	 int go(AstBinaryExp *node)
	 {
		int l=node->left->visit(this);
		int r=node->right->visit(this);
		switch(node->op)
		{
			case BinaryOperator::plus: 
				return l+r;
			break;
			case BinaryOperator::minus: return l-r;
						break;
			case BinaryOperator::mul:
						return l * r;
						break;
			case BinaryOperator::dv :
						return l / r;
				break;
			default:
				cout<<"Error\n";
				exit(-1);

		}
	 } 
	 bool go(AstBoolExp *node)
	 {

		int l=node->left->visit(this);
		int r=node->right->visit(this);
		switch(node->op)
		{

			case BooleanOperator::gt: 
				return l > r;
			break;
			case BooleanOperator::lt:  return l < r;
						break;
			case BooleanOperator::ge :
					return 	l >= r;
						break;
			case BooleanOperator::le :
						return l <= r;
		break;
			case BooleanOperator::neq: 
				return l != r;
			break;
			case BooleanOperator::eqeq :
				return l  == r;
		break;
			default:
				cout<<"Error\n";
				exit(-1);


	    }
	  } 
	 int go(AstTerm *node)
	 {
		if(node->identifier==NULL)
			return node->number;
		else
		{
			string val =node->identifier->evaluate(this);
			return vT[val];
		}
	 }
};
#endif
	









