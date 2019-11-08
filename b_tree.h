#ifndef B_TREE_H
#define B_TREE_H

#include <functional>
#include <stack>
#include "ticket.h"

using namespace std;

template<typename K,typename V>
struct kv_pair {
   K key;
   V value;

   kv_pair(const K&, const V&);
};

template<typename K, typename V, size_t B>
struct node {
   public:
      kv_pair<K,V> * values[B];
      node<K,V,B> * children[B+1];

      node();
      ~node();

      bool isLeaf(); // returns true if node has 0 children.
      bool isFull(); // returns true if node has B values.

      /* Stores the kv_pair into the node.
       * RETURNS index that kv_pair was inserted into.
       */
      int insert(const K&, const V&);
      int count();
      void insertChild(node<K,V,B> *, int);
      void printNode();
      void replaceChild(node<K,V,B> *, int);
      node<K,V,B> * findIntervalByKey(const K&);
};

template<typename K, typename V, size_t B>
class b_tree {
static_assert(B >= 3, "B must be greater than or equal to 3.");
   public:
      b_tree();
      ~b_tree();
      void insert(const K&, const V&);
      //bool remove(const K&);
      bool retrieve(const K&, V&);
      void inorderTraversal();
   private:
      void inorder(node<K,V,B>*,int depth=1);
      void ascendingSplit(stack<node<K,V,B> * >);
      node<K,V,B> * root;
};

template class kv_pair<int,int>;
template class node<int,int,4>;
template class b_tree<int,int,4>;

template class kv_pair<int,ticket*>;
template class node<int,ticket*,4>;
template class b_tree<int,ticket*,4>;

#endif
