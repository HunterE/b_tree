#include "b_tree.h"
#include <assert.h>
#include "iostream"


void insert(b_tree<int,int,4> * tree, int key, int value = 0){
   std::cout << "Inserting Key: "<<key <<" Value: "<< value <<"\n";
   tree->insert(key,value);
}

void inorder(b_tree<int,int,4> * tree){
   tree->inorderTraversal();
   std::cout << "\n";
}

int main(){
   node<int,int,4> * node1 = new node<int,int,4>();
   std::cout << "Test 1. Empty node is leaf.\n";
   assert(node1->isLeaf() == true);

   std::cout << "Test 2. Empty node is not full.\n";
   assert(node1->isFull() == false);

   node1->insert(1,0);
   node1->insert(2,0);

   std::cout << "Test 3. Partially full node is not full.\n";
   assert(node1->isFull() == false);


   node1->insert(3,0);
   node1->insert(4,0);

   std::cout << "Test 4. Full node is full.\n";
   assert(node1->isFull() == true);

   std::cout << "PASSED ALL TESTS.\n";

   std::cout << "START INORDER TRAVERSALS MANUAL REVIEW. \n";
   b_tree<int,int,4> * tree = new b_tree<int,int,4>();
   std::cout << "Empty Tree\nExpect: \nResult: ";
   inorder(tree);

   insert(tree,30,50);
   std::cout << "Expect: 30 \nResult: ";
   inorder(tree);

   insert(tree,50);
   insert(tree,10);
   std::cout << "Expect: 10 30 50 \nResult: ";
   inorder(tree);

   std::cout << "Inserted 4th element. Expect a split.\n";
   insert(tree,70);
   std::cout << "Expect: 10 30 50 70 \nResult: ";
   inorder(tree);


   insert(tree,20);
   insert(tree,90);
   std::cout << "Expect: 10 20 30 50 70 90 \nResult: ";
   inorder(tree);

   insert(tree,15);
   insert(tree,16);
   std::cout << "Expect: 10 15 16 20 30 50 70 90 \nResult: ";
   inorder(tree);

   insert(tree,80);
   std::cout << "Expect: 10 15 16 20 30 50 70 80 90 \nResult: ";
   inorder(tree);

   insert(tree,71);
   insert(tree,72);
   std::cout << "Expect: 10 15 16 20 30 50 70 71 72 80 90 \nResult: ";
   inorder(tree);

   insert(tree,81,100);
   insert(tree,82,500);
   insert(tree,83);
   insert(tree,84);
   std::cout << "Expect: 10 15 16 20 30 50 70 71 72 80 81 82 83 84 90 \nResult: ";
   inorder(tree);

   insert(tree,11);
   insert(tree,12);
   insert(tree,13);
   insert(tree,17);
   insert(tree,18);
   insert(tree,19);
   insert(tree,21);
   insert(tree,22);
   insert(tree,23);
   insert(tree,24);
   insert(tree,25);
   std::cout << "Expect: 10 11 12 13 15 16 17 18 19 20 21 22 23 24 25 30 50 70 71 72 80 81 82 83 84 90 \nResult: ";
   inorder(tree);

   std::cout << "TESTING RETRIEVAL\n";
   std::cout << "Expect: Found value 50 \nResult: ";
   int i;
   if(!tree->retrieve(30,i)){
      std::cout << "Couldn't find key 30.\n";
   } else {
      std::cout<<"Found value ";
      std::cout << i << "\n";
   }

   std::cout << "Expect: Found value 100 \nResult: ";
   if(!tree->retrieve(81,i)){
      std::cout << "Couldn't find key 81.\n";
   } else {
      std::cout<<"Found value ";
      std::cout << i << "\n";
   }

   std::cout << "Expect: Found value 500 \nResult: ";
   if(!tree->retrieve(82,i)){
      std::cout << "Couldn't find key 82.\n";
   } else {
      std::cout<<"Found value ";
      std::cout << i << "\n";
   }

   std::cout << "Expect: Did not find key \nResult: ";
   if(!tree->retrieve(9000,i)){
      std::cout << "Did not find key. Good!\n";
   } else {
      std::cout << "Found a value somehow...\n";
   }

   delete tree;
   /*
   tree->insert(8,0);
   tree->insert(4,0);
   std::cout << "Expect 1 2 3 4 5 8 \n";
   tree->inorderTraversal();*/
}



