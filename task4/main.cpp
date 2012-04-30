#include <iostream>
#include "cgraph.h"


int main() {
    Tree<int> t(1);
    t.addEdge(1,2);
    t.addEdge(1,7);
    t.addEdge(1,8);
    t.addEdge(2,3);
    t.addEdge(2,6);
    t.addEdge(3,4);
    t.addEdge(3,5);
    t.addEdge(8,9);
    t.addEdge(8,12);
    t.addEdge(9,10);
    t.addEdge(9,11);
    //t.printTree();
    //cout << t.nextVertex(5,4) << endl; 
cout << "order" << t.getTreeOrder() << endl;
   t.printTree(); 
    //cout << t.nextVertex(1,1) << endl; 
  //t.printParents(); 
   Tree<int>::iterator it;

   for(it = t.begin(); it != t.end(); it++){
       cout << *it << endl;
   } 
  cout << "fffffffffffffffffffFF" << endl;     
    Tree<int> t2(4);
    t2.addEdge(4,5);
    t2.addEdge(5,1);
    t2.addEdge(1,2);
    t2.addEdge(6,3);
    t2.addEdge(1,6);
    t2.addEdge(3,9);
    t2.addEdge(8,10);
    t2.addEdge(2,8);
    t2.addEdge(10,11);
   Tree<int>::iterator it2;

   for(it2 = t2.begin(); it2 != t2.end(); it2++){
       cout << *it2 << endl;
   } 
    
    Tree<int> t3(1);
    t3.addEdge(1,2);
    t3.addEdge(2,3);
    t3.addEdge(3,4);
    t3.addEdge(4,5);
    t3.addEdge(5,6);
    t3.addEdge(6,7);
   Tree<int>::iterator it3;
  cout << "fffffffffffffffffffFF" << endl;     

   for(it3 = t3.begin(); it3 != t3.end(); it3++){
       cout << *it3 << endl;
   } 
    return 0;
}
