#include <time.h>
#include <iostream>
#include <cstdlib>
typedef int Object;

using namespace std;

class List{
  private:
    struct Node{
      /* The basic doubly linked list node. Nested inside of List,
      can be public because the Node is itself private*/
      Object  data;
      Node   *prev;
      Node   *next;
      Node(const Object &d = Object(), Node *p = NULL,
      Node *n = NULL) : data(d), prev(p), next(n) { }
    };
  public:
    class const_iterator{
      public:
        const_iterator( ) : current(NULL) {
          // Public constructor for const_iterator.
        }
        const Object &operator* ( ) const{
          // Return the object stored at the current position.
          // For const_iterator, this is an accessor with a
          // const reference return type.
          return retrieve( );
        }
        const_iterator &operator++ ( ){
          current = current->next;
          return *this;
        }
        const_iterator operator++ (int){
          const_iterator old = *this;
          ++(*this);
          return old;
        }
        const_iterator &operator-- ( ){
          current = current->prev;
          return *this;
        }
        const_iterator operator-- (int){
          const_iterator old = *this;
          --( *this );
          return old;
        }
        bool operator== (const const_iterator &rhs) const{
          return current == rhs.current;
        }
        bool operator!= (const const_iterator &rhs) const{
          return !(*this == rhs);
        }
      protected:
        Node *current;
        Object &retrieve( ) const{
          return current->data;
        }
        const_iterator(Node *p) : current(p) {
        }
        friend class List;
    };
    class iterator : public const_iterator {
      public:
        iterator() {
      }
        Object &operator* (){
          return retrieve();
        }
        const Object &operator* ( ) const{
          return const_iterator::operator*( );
        }
        iterator &operator++ ( ) {
          current = current->next;
          return *this;
        }
        iterator operator++ (int) {
          iterator old = *this;
          ++( *this );
          return old;
        }
        iterator &operator-- ( ) {
          current = current->prev;
          return *this;
        }
        iterator operator-- (int) {
          iterator old = *this;
          --(*this);
          return old;
        }
      protected:
        iterator(Node *p) : const_iterator(p) {
          // Protected constructor for iterator.
          // Expects the current position.
        }
        friend class List;
    };
  public:
    List(){
      init();
    }
    ~List() {
      clear();
      delete head;
      delete tail;
    }
    List(const List &rhs) {
      init( );
      *this = rhs;
    }
    const List &operator= (const List &rhs) {
      if(this == &rhs)
        return *this;
      clear( );
      for(const_iterator itr = rhs.begin( ); itr != rhs.end( ); ++itr)
        push_back(*itr);
      return *this;
    }
    iterator begin(){
      // Return iterator representing beginning of list.
      // Mutator version is first, then accessor version.
      return iterator(head->next);
    }
    const_iterator begin() const{
      return const_iterator(head->next);
    }
    iterator end(){
      // Return iterator representing endmarker of list.
      // Mutator version is first, then accessor version.
      return iterator(tail);
    }
    const_iterator end() const{
      return const_iterator(tail);
    }
    int size() const{
      // Return number of elements currently in the list.
      return theSize;
    }
    bool empty() const{
      // Return true if the list is empty, false otherwise.
      return size() == 0;
    }
    void clear() {
      while(!empty( ))
      pop_front();
    }
    Object &front(){
      // front, back, push_front, push_back, pop_front, and pop_back
      // are the basic double-ended queue operations.
      return *begin();
    }
    const Object &front() const{
      return *begin( );
    }
    Object &back(){
      return *--end( );
    }
    const Object &back() const{
      return *--end();
    }
    void push_front(const Object &x){
      insert( begin( ), x );
    }
    void push_back(const Object &x){
      insert( end( ), x );
    }
    void pop_front(){
      erase( begin( ) );
    }
    void pop_back(){
      erase( --end( ) );
    }
    iterator insert(iterator itr, const Object &x) {
      // Insert x before itr.
      Node *p = itr.current;
      theSize++;
      return iterator(p->prev = p->prev->next
              = new Node( x, p->prev, p) );
    }
    iterator erase(iterator itr) {
      // Erase item at itr.
      Node *p = itr.current;
      iterator retVal(p->next);
      p->prev->next = p->next;
      p->next->prev = p->prev;
      delete p;
      theSize--;
      return retVal;
    }
    iterator erase(iterator start, iterator end) {
      for(iterator itr = start; itr != end;)
      itr = erase(itr);
      return end;
    }
  private:
    int theSize;
    Node *head;
    Node *tail;
    void init() {
      theSize = 0;
      head = new Node;
      tail = new Node;
      head->next = tail;
      tail->prev = head;
    }
};

int myrand(int lower, int upper){
  return (lower + rand() % (upper - lower +1));
}

int main() {
  int n, randNum, range = 1000000;
  List newLinked;
/*-- 1. ----------------------------------
  The user inputs n, then n random numbers from 1-1mil
  are inserted into a linked list
 -----------------------------------------*/
  //User inputs size of list to create:
  cin >> n;
  //New iterator created for list:
  List::iterator plc = newLinked.begin( );
  //For loop populating list:
  for(int i=0; i<n; i++){
    //Random numbers from 1 to 1 mil created:
    randNum = myrand(1,range);
    //Random number inserted into list:
    plc = newLinked.insert(plc, randNum);
  }
/* -- 2. ----------------------------------
   Write the numbers in sorted order by repeatedly finding
   minimum, write it, and delete it until list is empty
  -----------------------------------------*/
  List::iterator hld; //Iterator to hold current min in list
  //While loop until linked list is empty
  while (!newLinked.empty()){
    //Begin each outer loop with hld = first node
    hld = newLinked.begin();
    //For loop going from beginning to end of list:
    for (plc=newLinked.begin(); plc!=newLinked.end(); plc++){
      //If condition to check if current node is new min:
      if (*plc < *hld)
        hld = plc;
    }
    //End for loop, print found min:
    cout << *hld << " ";
    //Erase that min and reloop with list size - 1:
    newLinked.erase(hld);
  }
  //End while loop/main.
  return 0;
}
