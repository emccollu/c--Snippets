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
          // Protected helper in const_iterator that returns the object
          // stored at the current position. Can be called by all
          // three versions of operator* without any type conversions.
          return current->data;
        }
        const_iterator(Node *p) : current(p) {
          // Protected constructor for const_iterator.
          // Expects a pointer that represents the current position.
        }
        friend class List;
    };
    class iterator : public const_iterator {
      public:
        iterator() {
          // Public constructor for iterator.
          // Calls the base-class constructor.
          // Must be provided because the private constructor
          // is written; otherwise zero-parameter constructor
          // would be disabled.
        }
        Object &operator* (){
          return retrieve();
        }
        const Object &operator* ( ) const{
          // Return the object stored at the current position.
          // For iterator, there is an accessor with a
          // const reference return type and a mutator with
          // a reference return type. The accessor is shown first.
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

int CharToInt(const char c) {
  switch (c){
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    default: return 0;
  }
}

int main() {
  char redChar;
  int n;
  List newLst;
/*------------------------------------
The user inputs post fix equation ending with $
Read input, both int and chars
Perform operation on last 2 nodes
Remove last node, replace next one with result
 -----------------------------------------*/
// Creating main iterator for creating list;
List::iterator charNode = newLst.begin();
// Second iterator for list operations:
List::iterator walker;
// Reading input as chars:
cout << "Enter PostFix equation: " << endl;
cin.get(redChar);
// While cin.get has not reached endpoint:
while (redChar != '$') {
  //----------------------------------------------------------
  // Condition: char is a number
  if (redChar >='0' && redChar <='9'){
    //Call to function to get int from char;
    n = CharToInt(redChar);
    walker = charNode;
    //Inserts int into list;
    charNode = newLst.insert(charNode, n);
  }
  //----------------------------------------------------------
  // Condition: char is a plus
  else if (redChar == '+' && !newLst.empty()){
    // Performs addition on n and n-1 of list:
    n = *charNode;
    walker = charNode;
    charNode++;
    n = n + *charNode;
    newLst.erase(walker);
    *charNode = n;
  }
  //----------------------------------------------------------
  // Condition: char is a asterick
  else if (redChar == '*' && !newLst.empty()){
    // Performs multiplication on n and n-1 in list:
    n = *charNode;
    walker = charNode;
    charNode++;
    n = n * *charNode;
    newLst.erase(walker);
    *charNode = n;
  }
  //----------------------------------------------------------
  // Condition: char is a asterick
  else if (redChar == '-' && !newLst.empty()){
    // Performs multiplication on n and n-1 in list:
    n = *charNode;
    walker = charNode;
    charNode++;
    n = *charNode- n;
    newLst.erase(walker);
    *charNode = n;
  }
  //----------------------------------------------------------
  // Condition: char is a divide
  else if (redChar == '/' && !newLst.empty()){
    // Performs multiplication on n and n-1 in list:
    n = *charNode;
    walker = charNode;
    charNode++;
    n = *charNode / n;
    newLst.erase(walker);
    *charNode = n;
  }
  //----------------------------------------------------------
  // Invalid Character:
  else {  } //Invalid character skipped.
  cin.get(redChar);
} //END WHILE
  /* -----------------------------------------
    If list is only result, print result.
    If list is not just result, print error.
   -----------------------------------------*/
   if (newLst.size() == 1)
     cout << endl << " Result is: " << *charNode << endl;
   else
     cout << endl << " This is not a valid postfix expression." << endl;

  return 0;
}
