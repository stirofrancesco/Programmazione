#include <iostream>

using namespace std;

template <class H> class Nodo{

  private:
    Nodo<H>* left, *right, *parent;
    H* key;

  public:

    Nodo(H key, Nodo<H>* parent = NULL, Nodo<H>* left = NULL, Nodo<H>* right = NULL){
      this->left = left;
      this->right = right;
      this->parent = parent;
      this->key = new H(key);
    }

    void setLeft(Nodo<H>* left){ this->left = left; }
    void setRight(Nodo<H>* right){ this->right = right; }
    void setParent(Nodo<H>* parent){ this->parent = parent; }
    H getKey(){ return *key; }
    Nodo<H>* getLeft(){ return left; }
    Nodo<H>* getRight(){ return right; }
    Nodo<H>* getParent(){ return parent; }
};



template <class H> class BST{

  private:
    Nodo<H>* root, *current;
    int n;


    Nodo<H>* _search(H x){
      Nodo<H>* tmp = root;
      while (tmp && tmp->getKey!=x)
        if (x<tmp->getKey()) tmp = tmp->getLeft();
        else tmp = tmp->getRight();

      return tmp;
    }

    Nodo<H>* _rsearch(Nodo<H>* tmp, H x){
      if (!tmp) return NULL;
      if (tmp->getKey()==x) return tmp;
      if (x<tmp->getKey()) return _rsearch(tmp->getLeft(),x);
      return _rsearch(tmp->getRight(),x);
    }

    Nodo<H>* _rminimo(Nodo<H>* tmp){
      if (!tmp) return NULL;
      return _rminimo(tmp->getLeft());
      if (!tmp->getRight() && !tmp->getLeft())
        return tmp;
    }

    Nodo<H>* _minimo(Nodo<H>* tmp){
      while (tmp->getLeft())
        tmp = tmp->getLeft();
      return tmp;
    }

    Nodo<H>* _rmassimo(Nodo<H>* tmp){
      if (!tmp) return NULL;
      return _rmassimo(tmp->getRight());
      if (!tmp->getRight() && !tmp->getLeft())
        return tmp;
    }

    Nodo<H>* _massimo(Nodo<H>* tmp){
      while (tmp->getRight())
        tmp = tmp->getRight();
      return tmp;
    }

    Nodo<H>* _successore(Nodo<H>* tmp) {
			if(tmp->getRight())
				return _minimo(tmp->getRight());
			Nodo<H> *p = tmp->getParent();
			while(p!=NULL && p->getKey()<tmp->getKey())
				p = p->getParent();
			return p;
		}

		Nodo<H>* _predecessore(Nodo<H>* tmp) {
			if(tmp->getLeft())
				return _massimo(tmp->getLeft());
			Nodo<H> *p = tmp->getParent();
			while(p!=NULL && p->getKey()>tmp->getKey())
				p = p->getParent();
			return p;
		}

    void _inorder(Nodo<H> *x) {
			if(!x) return;
			_inorder(x->getLeft());
			cout << x->getKey() << " ";
			_inorder(x->getRight());
		}

		void _preorder(Nodo<H> *x) {
			if(!x) return;
			cout << x->getKey() << " ";
			_preorder(x->getLeft());
			_preorder(x->getRight());
		}

		void _postorder(Nodo<H> *x) {
			if(!x) return;
			_postorder(x->getLeft());
			_postorder(x->getRight());
			cout << x->getKey() << " ";
		}

    int _altezza(Nodo<H> *tmp) {
			if(!tmp) return 0;
			return max(_altezza(tmp->getLeft()),_altezza(tmp->getRight()))+1;
		}


    public:

     BST(){
        root = NULL;
        current = NULL;
        n=0;
      }

      BST* ins(H x){
        Nodo<H> *p = NULL;
        Nodo<H> *t = root;

        while (t){
          p=t;
          if (t->getKey()>x)
            t = t->getLeft();
          else
            t = t->getRight();
        }

        Nodo<H> *newn = new Nodo<H>(x,p);
        if (!p){
          root = newn;
          return this;
        }
        if (p->getKey()>=x)
          p->setLeft(newn);
        else
          p->setRight(newn);

        n++;
        return this;
      }


      void inorder(){
        _inorder(root);
      }



};





















int main(){

  BST<int>* b1 = new BST<int>();
  b1->ins(5)->ins(7)->ins(10)->ins(8)->ins(14)->inorder();

}
