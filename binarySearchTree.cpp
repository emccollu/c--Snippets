#include <iostream>    // For NULL
using namespace std;

//From dsexceptions.h:
class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

//From BinarySearchTree.h:
template <typename Comparable>
class BinarySearchTree{
  public:
  BinarySearchTree():root(NULL){}
  BinarySearchTree(const BinarySearchTree &rhs):root(NULL){*this = rhs;}
  ~BinarySearchTree(){ makeEmpty(); }/* Destructor for the tree */
  const Comparable &findMin() const{
    /*Find the smallest item in the tree. Throw UnderflowException if empty.*/
    if(isEmpty())
      throw UnderflowException();
    return findMin(root)->element;
  }
  const Comparable &findMax() const{
    /*Find the largest item in the tree. Throw UnderflowException if empty.*/
    if(isEmpty())
      throw UnderflowException();
    return findMax(root)->element;
  }
  bool contains(const Comparable &x) const{return contains(x, root);}/*Returns true if x is found in the tree.*/
  bool isEmpty() const{return root == NULL;}/*Test if the tree is logically empty. Return true if empty, false otherwise.*/
  void printTree(ostream &out = cout) const{
    /*Print the tree contents in sorted order.*/
    if(isEmpty())
      out << "Empty tree" << endl;
    else
      printTree(root, out);
  }
  void makeEmpty(){makeEmpty(root);}/*Make the tree logically empty.*/
  void insert(const Comparable &x){insert(x, root);}/*Insert x into the tree; duplicates are ignored.*/
  void remove(const Comparable &x){remove(x, root);}/*Remove x from the tree. Nothing is done if x is not found. */
  const BinarySearchTree &operator=(const BinarySearchTree &rhs){
    /*Deep copy.*/
    if(this != &rhs){
      makeEmpty();
      root = clone(rhs.root);
    }
    return *this;
  }
  private:
  struct BinaryNode{
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
      : element(theElement), left(lt), right(rt) {}
  };
  BinaryNode *root;
  void insert(const Comparable &x, BinaryNode * &t){
    /*Internal method to insert into a subtree.
    x is the item to insert.
    t is the node that roots the subtree.
    Set the new root of the subtree.*/
    if(t == NULL)
      t = new BinaryNode(x, NULL, NULL);
    else if(x < t->element)
      insert(x, t->left);
    else if(t->element < x)
      insert(x, t->right);
    else
      ;// Duplicate; do nothing
  }
  void remove(const Comparable &x, BinaryNode * &t){
    /*Internal method to remove from a subtree.
    x is the item to remove.
    t is the node that roots the subtree.
    Set the new root of the subtree.*/
    if(t == NULL)
      return;   // Item not found; do nothing
    if(x < t->element)
      remove(x, t->left);
    else if(t->element < x)
      remove(x, t->right);
    else if(t->left != NULL && t->right != NULL){// Two children
      t->element = findMin(t->right)->element;
      remove(t->element, t->right);
    }
    else{
      BinaryNode *oldNode = t;
      t = (t->left != NULL) ? t->left : t->right;
      delete oldNode;
    }
  }
  BinaryNode * findMin(BinaryNode *t) const{
    /*Internal method to find the smallest item in a subtree t. Return node containing the smallest item.*/
    if(t == NULL)
      return NULL;
    if(t->left == NULL)
      return t;
    return findMin(t->left);
  }
  BinaryNode * findMax(BinaryNode *t) const{
    /*Internal method to find the largest item in a subtree t. Return node containing the largest item.*/
    if(t != NULL)
      while(t->right != NULL)
    t = t->right;
    return t;
  }
  bool contains(const Comparable &x, BinaryNode *t) const{
    /*Internal method to test if an item is in a subtree.
    x is item to search for.
    t is the node that roots the subtree.*/
    if(t == NULL)
      return false;
    else if(x < t->element)
      return contains(x, t->left);
    else if(t->element < x)
      return contains(x, t->right);
    else
      return true;    // Match
  }
  void makeEmpty(BinaryNode * &t){
    /*Internal method to make subtree empty.*/
    if(t != NULL){
      makeEmpty(t->left);
      makeEmpty(t->right);
      delete t;
    }
    t = NULL;
  }
  //Altered to print numbers in reverse:
  void printTree(BinaryNode *t, ostream &out) const{
    /*Internal method to print a subtree rooted at t in sorted order.*/
    if(t!=NULL){
      //Swapped right and left for reverse order:
      printTree(t->right, out);
      out << t->element << endl;
      printTree(t->left, out);
    }
  }
  BinaryNode * clone(BinaryNode *t) const{
    /*Internal method to clone subtree.*/
    if(t==NULL)
      return NULL;
    else
      return new BinaryNode(t->element, clone(t->left), clone(t->right));
  }
};

//Previously provided random number generator:
int myrand(int lower, int upper){
  return (lower + rand() % (upper - lower +1));
}

int main(){
  //-------Variables------------------------
    int n, randNum, range = 1000000;
    BinarySearchTree<int> thisTree;
  //----------------------------------------
    //Prompts user for input:
    cout << "Enter number: " << endl;
    //Sets input to n:
    cin >> n;
    //Loop to create n random numbers and insert them into BST:
    for(int i=0; i<n; i++){
      //Random numbers between 1 to 1 mil created:
      randNum = myrand(1,range);
      //Random number inserted into tree:
      thisTree.insert(randNum);
    }
    //Prints completed tree:
    thisTree.printTree();
  return 0;
}
