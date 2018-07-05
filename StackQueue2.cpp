#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>

using namespace std;

template <class H> class Queue{

  private:
    H** v;
    int len, head, tail, current, n;

  public:

    Queue(int len){
      this->len = len;
      head = tail = 0;
      n = 0;
      v = new H* [len];
    }

    Queue<H>* enqueue(H x){
      if (n==len)
        return this;

      v[tail] = new H(x);
      tail = (tail+1)%len;
      n++;
      return this;
    }

    H dequeue (){
      if (isEmpty())
        return -1;

      H out = *v[head];
      head = (head+1)%len;
      n--;
      return out;
    }

    int size(){ return n; }
    int isEmpty(){ return n==0; }

    void reset(){ current = 0; }

    H* next(){
      if (current == n)
        return NULL;

      H* out = v[(head+current)%len];
      current++;
      return out;
    }

    bool has_next(){
      return (current<n);
    }
};


template <class H> ostream &operator<<(ostream& out, const Queue<H>& q1) {
	Queue<H> q = q1;
	q.reset();
	out << "{";
	while(H *i = q.next()) {
		out << *i;
		if(q.has_next()) out << ", ";
	}
	out << "}";
	return out;
}


template <class H> class Stack{

  private:
    H** v;
    int n,len,current,top;


  public:

    Stack(int len){
      this->len = len;
      v = new H*[len];
      n=0;
      top=0;
    }

    Stack* push(H x){
      if (top==len)
        return this;

      v[top++] = new H(x);
      n++;
      return this;
    }

    H pop(){
      if (n==0)
        return -1;

      return *v[--top];
    }

    void reset(){ current = top-1; }

    H* next(){
      if (current < 0)
        return NULL;

      H* out = v[current--];
      return out;
    }

    bool has_next(){
      return (current>=0);
    }

    int size() {return n;}
		int isEmpty() { return (n==0); }
};

template <class H> ostream &operator<<(ostream& out, const Stack<H>& s1) {
	Stack<H> s = s1;
	s.reset();
	out << "{";
	while(H *i = s.next()) {
		out << *i;
		if(s.has_next()) out << ", ";
	}
	out << "}";
	return out;
}

int main(){

  Queue<int>* q1 = new Queue<int>(5);
  q1->enqueue(2)->enqueue(3)->enqueue(10)->enqueue(8);
//  q1->dequeue();
  cout << *q1 << endl;

Stack<int>* s1 = new Stack<int>(5);
s1->push(2)->push(3)->push(10)->push(8);
//s1->pop();
cout << *s1;


}
