#include <iostream>
#include <stack>
#include <math.h>
#include "b_tree.h"

using namespace std;

/*
 * NODE FUNCTIONS
 */

// NOTE: This function does not adjust the children when inserting a new kv_pair. It is the responsibility of b_tree to insert the new child.
template<typename K, typename V, size_t B>
int node<K,V,B>::insert(const K& k, const V& v){
   for(int i = 0; i<B; ++i){
      if(values[i] == nullptr) { // if we find an empty space then we should immediately insert into that space.
         values[i] = new kv_pair<K,V>(k,v);
         return i;
      }

      if(k > values[i]->key) continue; // if our key is greater than the current index's key we need to check the next key.

      // otherwise our key is less than the current index's key and we should insert the key and shuffle the values.
      kv_pair<K,V> * newValues[B];

      for(int j = 0; j<B; ++j) {
         if(j < i) { // since we haven't hit the index yet just copy the previous value.
            newValues[j] = values[j];
         } else if (j == i) {
            newValues[j] = new kv_pair<K,V>(k,v);
         } else { // we've passed the index and now need to offset.
            newValues[j] = values[j-1];
         }
      }

      // overwrite this node's values with new values.
      for(int j = 0; j<B; ++j){
         values[j] = newValues[j];
      }

      return i;
   }
   return -1;
}
// Solely for testing purposes. Helped me find some really dumb mistakes.
template<typename K, typename V, size_t B>
void node<K,V,B>::printNode(){
   std::cout << "Values: ";
   for(int i = 0; i < B; ++i){
      if(values[i] == nullptr) std::cout << "[np] ";
      else std::cout << values[i]->key << "-" << values[i]->value << " ";
   }
   std::cout << "Children: ";
   for(int i = 0; i < B; ++i){
      std::cout << ((children[i] == nullptr) ? "[np]" : "[ch]") << " ";
   }
}

template<typename K, typename V, size_t B>
void node<K,V,B>::insertChild( node<K,V,B> * child, int index){
   node<K,V,B> * newChildren[B+1];
   for(int j = 0; j <B+1; ++j){
      if(j < index) {
         newChildren[j] = children[j];
      } else if (j == index) {
         newChildren[j] = child;
      } else {
         newChildren[j] = children[j-1];
      }
   }

   for(int j = 0; j<B+1; ++j){
      children[j] = newChildren[j];
   }
}

template<typename K, typename V, size_t B>
void node<K,V,B>::replaceChild( node<K,V,B> * child, int index){
   children[index] = child;
}


template<typename K, typename V, size_t B>
int node<K,V,B>::count(){
   for(int i = 0; i<B; ++i){
      if(values[i] == nullptr) return i;
   }
   return B;
}

template<typename K, typename V, size_t B>
node<K,V,B> * node<K,V,B>::findIntervalByKey(const K& key){
   for(int i = 0; i<B+1; ++i) {
      if(values[i] == nullptr) return children[i];
      if(key < values[i]->key) return children[i];
   }
   return children[B+1]; // normally this shouldn't happen unless we check the interval of an overflowed node.
}


template<typename K, typename V, size_t B>
bool node<K,V,B>::isLeaf(){
   for(int i = 0; i<(B+1); ++i){
      if(children[i] != nullptr) return false;
   }
   return true;
}

template<typename K, typename V, size_t B>
bool node<K,V,B>::isFull(){
   for(int i = 0; i<B; ++i) {
      if(values[i] == nullptr) return false;
   }
   return true;
}

/*
 * TREE FUNCTIONS
 */

template<typename K, typename V, size_t B>
void b_tree<K,V,B>::insert(const K& key, const V& value){
   node<K,V,B> * selectedNode = root;

   stack<node<K,V,B> * > ascendingStack;

   while(!selectedNode->isLeaf()) { // descend until we find a leaf node.
      ascendingStack.push(selectedNode);
      selectedNode = selectedNode->findIntervalByKey(key);
   }

   ascendingStack.push(selectedNode);
   selectedNode->insert(key,value);
   ascendingSplit(ascendingStack);
}

/* Takes a stack filled with tree nodes and - if full - handles splitting the nodes
 * up to the root node.
 */
template<typename K, typename V, size_t B>
void b_tree<K,V,B>::ascendingSplit( stack<node<K,V,B> * > stackToRoot){
   node<K,V,B> * selectedNode = stackToRoot.top();
   stackToRoot.pop();

   if(!selectedNode->isFull()) return; // Node is not full so we do not need to split it or its parents.

   bool isLeaf = selectedNode->isLeaf();
   int median = ceil(B / 2) - 1;
   node<K,V,B> * left = new node<K,V,B>();
   node<K,V,B> * right = new node<K,V,B>();

   for(int i = 0; i < B; ++i){
      if(i == median) continue; // the median value will be getting inserted into the parent so skip over it.

      if(i < median){
         left->insert(selectedNode->values[i]->key, selectedNode->values[i]->value);
      } else {
         right->insert(selectedNode->values[i]->key, selectedNode->values[i]->value);
      }
   }

   for(int i = 0; i < B+1; ++i){
      if(i <= median){
         left->insertChild(selectedNode->children[i],i);
      } else {
         right->insertChild(selectedNode->children[i],i-(median+1));
      }
   }

   // We deal with the median value here.
   if(stackToRoot.empty()){ // We are splitting the root element so we need to make a new root node.
      node<K,V,B> * newRoot = new node<K,V,B>();
      newRoot->insert(selectedNode->values[median]->key, selectedNode->values[median]->value);
      newRoot->insertChild(left,0); // Since this is a new root element it will only have 1 value and therefore 2 children.
      newRoot->insertChild(right,1);
      root = newRoot;

      return;
   } else { // insert the median into the parent element (which might overflow it requiring another split)
      int indexInParent = stackToRoot.top()->insert(selectedNode->values[median]->key, selectedNode->values[median]->value);
      stackToRoot.top()->insertChild(right, indexInParent+1);
      stackToRoot.top()->replaceChild(left, indexInParent);
   }

   ascendingSplit(stackToRoot);
}

template<typename K, typename V, size_t B>
bool b_tree<K,V,B>::retrieve(const K& key, V& value){
   node<K,V,B> * selectedNode = root;

   while(!selectedNode->isLeaf()){
      for(int i = 0; i<B; i++){
         if(selectedNode->values[i] == nullptr) break; // stop checking values and descend to the next node.

         if(selectedNode->values[i]->key == key){
            value = selectedNode->values[i]->value;
            return true;
         }
      } // if we get here then our key is not in this node.

      selectedNode = selectedNode->findIntervalByKey(key); // this loop could be optimized.
   }

   // Check our final leaf node. (this is unneccesary replication of code but I was having issues with a bug re: leaf nodes)
   // Maybe a Do While loop could resolve this? I don't know.
   for(int i = 0; i<B; i++){
      if(selectedNode->values[i] == nullptr) break; // stop checking values and descend to the next node.

      if(selectedNode->values[i]->key == key){
         value = selectedNode->values[i]->value;
         return true;
      }
   } // if we get here then our key is not in the tree.

   return false;
}

template<typename K, typename V, size_t B>
void b_tree<K,V,B>::inorderTraversal(){
   inorder(root);
   std::cout << "\n";
}

template<typename K, typename V, size_t B>
void b_tree<K,V,B>::inorder( node<K,V,B> * n, int depth){
   if(n == nullptr) return;

   //n->printNode();

   for(int i = 0; i<(B+1); ++i){
      //if(n->children[i] == nullptr) std::cout << "[np]"; 
      if(n->children[i] != nullptr) inorder(n->children[i], depth+1);
      if(i < B && n->values[i] != nullptr) std::cout << n->values[i]->key << " "; //<< "("<< depth <<") ";
   }
}

/*
 * CONSTRUCTORS/DESTRUCTORS
 */

template<typename K, typename V>
kv_pair<K,V>::kv_pair(const K& k, const V& v){
   key = k;
   value = v;
}

template<typename K, typename V, size_t B>
node<K,V,B>::node(){
   for(int i = 0; i<B+1; ++i){
      children[i] = nullptr;
   }
   for(int i = 0; i<B; ++i){
      values[i] = nullptr;
   }
}


template<typename K, typename V, size_t B>
node<K,V,B>::~node(){
   for(int i = 0; i<B; ++i){
      if(children[i] != nullptr) delete children[i];
   }
}


template<typename K, typename V, size_t B>
b_tree<K,V,B>::b_tree(){
   root = new node<K,V,B>();
}

template<typename K, typename V, size_t B>
b_tree<K,V,B>::~b_tree(){
   delete root;
}


