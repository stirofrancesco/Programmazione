#include <iostream>

using namespace std;

template <class H> class MSTree{
  public:
    virtual void printInput()=0;
    virtual void printOutput()=0;
    virtual int height()=0;
    virtual int calls()=0;
};

template <class H> class Nodo{

  private:
    Nodo<H>* left, *right, *parent;
    int nin,nout;
    H* in;
    H* out;

  public:
    Nodo(H* in, int nin=0, Nodo<H>* left = NULL, Nodo<H>* right = NULL, Nodo<H>* parent = NULL){
      this->left = left;
      this->right = right;
      this->parent = parent;
      this->nout = 0;
      this->in = in;
      this->nin = nin;
      this->out = NULL;
    }

    int getNin(){ return nin; }
    int getNout(){ return nout; }

    H* getIn(){ return in; }
    H* getOut(){ return out; }

    Nodo<H>* getRight(){ return right; }
    Nodo<H>* getLeft(){ return left; }
    Nodo<H>* getParent(){ return parent; }

    void setIn(H* in){ this->in = in; }
    void setOut(H* out){ this->out = out; }
    void setNin(int nin){ this-> nin = nin; }
    void setNout(int nout){ this->nout = nout; }

    void setRight(Nodo<H>* right){ this->right = right; }
    void setLeft(Nodo<H>* left){ this->left = left; }
    void setParent(Nodo<H>* parent){ this->parent = parent; }

};


template <class H> class MyMSTree: public MSTree<H>{


  private:
    Nodo<H>* root = NULL;


    void _inOrder(Nodo<H>* node){
      if (!node)
        return;

      _inOrder(node->getLeft());
      for (int i=0;i<node->getNout();i++)
        cout << node->getOut()[i] << " ";
      cout << endl;
      _inOrder(node->getRight());
    }

    void Merge(H* A, int na, H* B, int nb, H* &C, int &nc)
    {
    	nc=na+nb;
    	C=new H[nc];

    	int ia=0;
    	int ib=0;
    	int ic=0;

    	while((ia<na) && (ib<nb))
    	{
    		if(A[ia]<B[ib])
    			C[ic++]=A[ia++];
    		else
    			C[ic++]=B[ib++];
    	}

    	if (ia<na)
    	{
    		while(ia<na)
    			C[ic++]=A[ia++];
    	}
    	else
    	{
    		while(ib<nb)
    			C[ic++]=B[ib++];
    	}
    }



    void split(H* A, int na, H* &B, int& nb, H* &C, int& nc){

      int mid = (na/2);
      nb = mid;
      nc = na-mid;

      B = new H[nb];
      C = new H[nc];

      for (int i=0;i<nb;i++)
        B[i] = A[i];

      int j=0;
      for (int i=mid;i<na;i++)
        C[j++] = A[i];
    }


    Nodo<H>* buildInputTree(H* A, int na){

      if (na>1){
        H* B;
        H* C;
        int nb=0,nc=0;

        split(A,na,B,nb,C,nc);

        Nodo<H>* left_subtree = buildInputTree(B,nb);
        Nodo<H>* right_subtree = buildInputTree(C,nc);

        Nodo<H>* r = new Nodo<H>(A,na,left_subtree,right_subtree);
        left_subtree->setParent(r);
        right_subtree->setParent(r);

        return r;
      }
      else
        return new Nodo<H>(A,na);
    }

    void fillOutputs(Nodo<H>* r){
      if (!r)
        return;

      if (r->getRight() && r->getLeft()){

        fillOutputs(r->getLeft());
        fillOutputs(r->getRight());
        H* out;
        int nc;
        Merge(r->getLeft()->getOut(),r->getLeft()->getNout(),r->getRight()->getOut(),r->getRight()->getNout(),out,nc);
        r->setOut(out);
        r->setNout(r->getNin());
      }
      else{
        r->setOut(r->getIn());
        r->setNout(r->getNin());
      }

  }

  public:

    MyMSTree(H* input, int length){
      root = buildInputTree(input,length);
      fillOutputs(root);
    }

    void printInput(){
      H* tmp = root->getIn();
      int l = root->getNin();

      for (int i=0;i<l;i++)
        cout << tmp[i] << " ";

      cout << endl;
    }


    void printOutput(){
      for (int i=0;i<root->getNout();i++)
       cout << root->getOut()[i] << " ";
      cout << endl;
    }

    int height(){}
    int calls(){

    }





};



int main(){

  int array[] = {5,8,1,4,20,15,18};
  int length = 7;

  MyMSTree<int>* ms = new MyMSTree<int>(array,length);
  cout<<"input:"<<endl;
  ms->printInput();
  cout<<endl;
  cout<<"output:"<<endl;
  ms->printOutput();
  cout<<endl;

}
