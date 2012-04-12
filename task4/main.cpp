#include <iostream>
#include "cgraph.h"


int main() {
    cout << "TEST\n";
    CGraph<char> myGraph1;
    myGraph1.addEdge('u','v');
    myGraph1.addEdge('u','x');
    myGraph1.addEdge('x','v');
    myGraph1.addEdge('v','y');
    myGraph1.addEdge('y','x');
    myGraph1.addEdge('w','y');
    myGraph1.addEdge('z','z');
    myGraph1.rmEdge('z','z');
    myGraph1.addEdge('z','z');
    myGraph1.addEdge('w','z');
    myGraph1.printGraph();
    cout << myGraph1.getVertexCount();
    
    return 0;
}
