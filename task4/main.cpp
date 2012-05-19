#include <iostream>
#include "tree.h"
#include <cassert>
#include <algorithm>

template<class T>
void arbitraryTreeTest(const std::vector<T>& _vertices){
    srand(1000);
    for(int i = 0; i < 100; i++){
        std::vector<T> vertices = _vertices;
        std::vector<T> childs;
        
        int parentIndex = rand() % vertices.size();
        T parent = vertices[parentIndex];
        vertices.erase(vertices.begin() + parentIndex);
        Tree<T> tree(parent);
        
        while(vertices.size() > 0){
            int childsCount = rand() % vertices.size();
            if(childsCount == 0){
                childsCount++;
            }
            for(int i = 0; i < childsCount; i++){
                int childIndex = rand() % vertices.size();
                T child = vertices[childIndex];
                vertices.erase(vertices.begin() + childIndex);
                childs.push_back(child);
                tree.addEdge(parent, child);
            }
            parentIndex = rand() % childs.size();
            parent = childs[parentIndex];
            childs.erase(childs.begin() + parentIndex);
        }
        assert(tree.depthFirstSearchThroughIterator(tree.getRoot()) == tree.depthFirstSearch(tree.getRoot()));
    }

}

template<class T> 
T inc(){
    static T value = 1;
    return value++;
}
 
int main(){
    std::vector<char> charVertices(10);
    for(int i = 0; i < charVertices.size(); i++){
        charVertices[i] = i + 65;
    }
    arbitraryTreeTest(charVertices);

    std::vector<int> intVertices(10);
    generate(intVertices.begin(), intVertices.end(), inc<int>);
    arbitraryTreeTest(intVertices);
   
   return 0;
}
