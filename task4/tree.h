#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <limits>
#include <algorithm>
#include <exception>

using std::cout;
using std::cin;
using std::endl;
using std::queue;
using std::vector;
using std::stack;
using std::map;
using std::numeric_limits;
using std::priority_queue;
using std::pair;
using std::make_pair;
using std::find;
using std::exception;
using std::ostream;

class HasNoParentException : public exception { };
class OutOfRangeException : public exception { };

template<class T>
class Tree{
    private:
        class DfsIterator; 
    public:
        //nested private forward iterator support
        typedef DfsIterator iterator;
        friend class DfsIterator;
        DfsIterator begin();
        DfsIterator end();
        
        Tree(const T& root_) : root(root_) { }; 
        Tree<T>& addEdge(const T &fromVertex, const T &toVertex);
        int getVerticesNumber() const;
        
        template <typename Type>
        friend std::ostream& operator << (std::ostream& out, const Tree<Type>& tree);
            
        vector<T> depthFirstSearch(const T &root);
        vector<T> breadthFirstSearch(const T &root);
        T& getParent(const T& vertex) throw (HasNoParentException);
    private:
        map<T, vector<T> > tree;
        T root;
        map<T, T> parents;
        int verticesNumber;
        //forward iterator functions
        T& nextVertex(const T& vertex) throw (OutOfRangeException); 
        ostream& printTree(ostream& out);
};

template<class T>
class Tree<T>::DfsIterator {
    public:
        
        DfsIterator(Tree<T>* treePtr = 0, T* curVertexPtr = 0) : tree(treePtr), curVertex(curVertexPtr) { }

        DfsIterator& operator = (const DfsIterator& it){
            this->tree = it.tree;
            this->curVertex = it.curVertex;
        }
        
        bool operator == (const DfsIterator& it) const {
            return (tree == it.tree && curVertex == it.curVertex);
        }
        
        bool operator != (const DfsIterator& it) const {
            return !(*this == it);
        }

        DfsIterator operator ++ (int) {
            DfsIterator result = *this;
            try{
                curVertex = &(tree->nextVertex(*curVertex));
            }
            catch(OutOfRangeException& exception){
                curVertex = 0;
            }
            return result;
        }
        
        DfsIterator& operator ++ () {
            try{
                curVertex = &(tree->nextVertex(*curVertex));
            }
            catch(OutOfRangeException& exception){
                curVertex = 0;
            }
            return *this;
        }
        
        const T& operator * () const {
            return *curVertex;
        }
        
    private:
        Tree<T>* tree; 
        T* curVertex;
};

template<class T>
typename Tree<T>::DfsIterator Tree<T>::begin() {
    return DfsIterator(this, &root);
}

template<class T>
typename Tree<T>::DfsIterator Tree<T>::end() {
    return DfsIterator(this, 0);
}

template<class T>
T& Tree<T>::getParent(const T& vertex) throw (HasNoParentException) {
    T* parent;
    if(parents.count(vertex) > 0){
        parent = &parents[vertex];
    }
    else{
        throw HasNoParentException();
    }
    return *parent;
}

template<class T>
T& Tree<T>::nextVertex(const T& root) throw (OutOfRangeException) {
    T* next;

    try {
        T previousVertex = root;
        T currentVertex = root;

        bool isFound = false;
        while(!isFound){
            if(tree.count(currentVertex) > 0){
                vector<T>& childNodes = tree[currentVertex];
                typename vector<T>::iterator childNodeIt = find(childNodes.begin(), childNodes.end(), previousVertex);
                if(childNodeIt == childNodes.end()){
                    next = &childNodes[0];
                    isFound = true;
                }
                else if((childNodeIt + 1) != childNodes.end()){
                    next = &(*(childNodeIt + 1));
                    isFound = true;
                }
                else {
                    previousVertex = getParent(*childNodeIt);
                    currentVertex = getParent(previousVertex);
                }
            } 
            else {
                previousVertex = currentVertex;
                currentVertex = getParent(currentVertex);
            }
        }
    }
    catch(HasNoParentException& exception){
        throw OutOfRangeException();
    }
    return *next;
}

//get a cardinal number
template<class T> 
int Tree<T>::getVerticesNumber() const {
    return verticesNumber;
}
    
//add an edge to the tree
template<class T> 
Tree<T>& Tree<T>::addEdge(const T &fromVertex, const T &toVertex){
    tree[fromVertex].push_back(toVertex);
    parents[toVertex] = fromVertex;
    verticesNumber = parents.size();
    return *this;
}

//display all edges of the tree
template<class T>
ostream& Tree<T>::printTree(ostream& out){
    typename map<T, vector<T> >::iterator curIt;
    typename map<T, vector<T> >::iterator endIt;
    curIt = this->tree.begin();
    endIt = this->tree.end();
    while(curIt != endIt){
        int i = 0;
        //show the adjasent vertexes
        while(i < curIt->second.size()){
            out << curIt->first << " -> ";
            out << curIt->second.at(i);
            out << endl;
            i++;
        }
        curIt++;
    }
    return out;
}

template<class T>
ostream& operator << (ostream& out, const Tree<T>& tree){
    out << tree.verticesNumber;
    return out; 
}

//print a traversal
template<class T>
void printPath(const vector<T> &path){
    for(int i = 0; i < path.size(); i++){
        cout << path[i] << " ";
    }
}

template<class T>
vector<T> Tree<T>::depthFirstSearch(const T& root){
    vector<T> result;
    Tree<T>::iterator it;
    for(it = this->begin(); it != this->end(); it++){
        result.push_back(*it);
    }
    return result;
}


template<class T>
vector<T> Tree<T>::breadthFirstSearch(const T &root){
    vector<T> result;
    map<T, int> colors; //0 - white; 1 - grey; 2 - black
    typename map<T, T >::iterator it = parents.begin();
    for(; it != parents.end(); it++){
        colors[it->first] = 0;
    }

    colors[root] = 1;
    queue<T> fifo;
    fifo.push(root);
    T curVertex;
    while(fifo.size() != 0){
        while(fifo.size() != 0){
            curVertex = fifo.front();
            if(tree.count(curVertex) > 0){
                for(int i = 0; i < this->tree[curVertex].size(); i++){
                    if(colors[this->tree[curVertex][i]] == 0){
                        colors[this->tree[curVertex][i]] = 1;
                        fifo.push(this->tree[curVertex][i]);
                    }
                }
            }
            fifo.pop();
            result.push_back(curVertex);
        }
        typename map<T, int>::iterator itColors;
        itColors = colors.begin();
        bool isPresent = false;
        //check if there are uncovered vertexes
        for(int i = 0; (i < this->getVerticesNumber()) && !isPresent; i++){
            if(itColors->second == 0){
                fifo.push(itColors->first);
                itColors->second = 1;
                isPresent = true;
            }
            itColors++;
        }
    }
    return result;
}    

//template<class T>
//Tree<T> Type<T>::treeRestore(Tree<T>::iterator dfsIt, const vector<T> bfs){
    













