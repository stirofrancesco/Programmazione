#include <iostream>

using namespace std;

template<class H> class Nodo{

  private:
    Nodo<H>* next, *prev;
    H* key;


  public:
    Nodo(H key, Nodo<H>* prev = NULL, Nodo<H>* next = NULL){
      this->next = next;
      this->prev = prev;
      this->key = new H(key);
    }

    Nodo<H>* getNext(){ return next; }
    Nodo<H>* getPrev(){ return prev; }
    H getKey(){ return *key; }
    void setNext(Nodo<H>* next){ this->next = next; }
    void setPrev(Nodo<H>* prev){ this->prev = prev; }
    void setKey(H key){ this->key = new H(key); }
};


template <class H> class OList{

  private:
    Nodo<H>* head, *tail, *current;
    int n;

    Nodo<H>* _search(H x){
      Nodo<H>* tmp = head;
      while (tmp){
        if (tmp->getKey()==x)
          return tmp;
        tmp = tmp->getNext();
      }
      return NULL;
    }

    Nodo<H>* recursive_search(H x, Nodo<H>* node){
      if (!node)
        return NULL;
      if (node->getKey()==x)
        return node;
      return recursive_search(x, node->getNext());
    }

    void _recursive_print(Nodo<H>* x){
      if (!x)
        return;
      cout << x->getKey();
      if (x->getNext())
        cout << " ";
      else
        cout << endl;

      _recursive_print(x->getNext());
    }

  public:

    OList(){
      head = tail = NULL;
      n=0;
    }

    OList* ins(H x){

      if (!head){
        head = tail = new Nodo<H>(x);
        n++;
        return this;
      }

      if (x>=head->getKey()){
        head = new Nodo<H>(x,NULL,head);
        head->getNext()->setPrev(head);
        n++;
        return this;
      }

      Nodo<H>* tmp = head->getNext();
      while (tmp){
        if (x>=tmp->getKey()){
          Nodo<H>* aux = new Nodo<H>(x,tmp->getPrev(),tmp);
          tmp->getPrev()->setNext(aux);
          tmp->setPrev(aux);
          n++;
          return this;
        }
        tmp = tmp->getNext();
      }

      Nodo<H>* aux = new Nodo<H> (x,tail);
      tail->setNext(aux);
      tail = tail->getNext();
      n++;
      return this;
    }

    void stampa(){
      Nodo<H>* tmp = head;
      while (tmp){
        cout << tmp->getKey() << " ";
        tmp = tmp->getNext();
      }
      cout << endl;
    }

    void recursive_print(){
      _recursive_print(head);
    }

    int getSize(){
      return n;
    }

    bool search(H x){
      return (_search(x)!=NULL);
    }

    OList<H>* canc (H x){

      Nodo<H>* aux = _search(x);

      if (!aux)
        return this;

      if (n==1){
        delete head;
        head = tail = NULL;
        n--;
      }

      if (aux == head){
        head = head->getNext();
        head->setPrev(NULL);
        delete aux;
        n--;
        return this;
      }

      if (aux == tail){
        tail = tail->getPrev();
        tail->setNext(NULL);
        delete aux;
        n--;
        return this;
      }

      aux->getPrev()->setNext(aux->getNext());
      aux->getNext()->setPrev(aux->getPrev());
      delete aux;
      n--;
      return this;
  }

  OList<H>* truncate(){

    if (!head)
      return this;

    if (n==1){
      delete head;
      head = tail = NULL;
      n--;
      return this;
    }

    Nodo<H>* aux = tail;
    tail = tail->getPrev();
    tail->setNext(NULL);
    delete aux;
    n--;
    return this;
  }

  OList<H>* canc2 (H x){
    while (_search(x)!=NULL)
      canc(x);
    return this;
  }

  void reset() {
    // inizializzazione dell'iteratore
    current = head;
  }

  H *next() {
      // funzione di iterazione:
      // restituisce l'elemento successivo della lista
    if(current) {
        Nodo<H> *tmp = current;
        current = current->getNext();
        return tmp->getKey();
    }
    return NULL;
  }

  int has_next() {
      // funzione di iterazione:
      // restituisce un valore booleano indicante la presenza o meno di un elemento successivo nella lista
      return (current->getNext()!=NULL);
  }



};

int main(){
  OList<int>* l1 = new OList<int>();
  l1->ins(2)->ins(8)->ins(10)->ins(1)->ins(10)->ins(4)->ins(1)->ins(4)->stampa();
  l1->truncate()->truncate()->truncate()->ins(6)->canc2(4)->canc2(8)->canc2(10)->canc2(80)->stampa();
  cout << l1->getSize();
  cout << endl;
}
