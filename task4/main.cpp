#include <iostream>
#include "tree.h"

using std::cout;
using std::cin;
using std::endl;

int main() {
    int edgesNumber;
    cin >> edgesNumber;
    int root;
    cin >> root;
    
    Tree<int> tree(root);
    for(int i = 0; i < edgesNumber; i++){
        int from;
        int to;
        cin >> from >> to;
        tree.addEdge(from,to);
    }
    
   cout << tree << endl;
   std::vector<int> path = tree.breadthFirstSearch(root);
   cout << "bfs: ";
   printPath(path);
   cout << endl;
   path = tree.depthFirstSearch(root);
   cout << "dfs: ";
   printPath(path);
   cout << endl;
 
   return 0;
}
