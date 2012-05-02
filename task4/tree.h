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
        Tree<T>& addEdge(const T &vertex1, const T &vertex2);
        int getTreeOrder() const;
        void printTree();
       
        vector<T> depthFirstSearch(const T &root);
        vector<T> breadthFirstSearch(const T &root);
        static void printPath(const vector<T> &path);
        T& getParent(const T& vertex) throw (HasNoParentException);
        
    private:
        map<T, vector<T> > tree;
        T root;
        map<T, T> parents;
        int order;
        //forward iterator functions
        T& nextVertex(const T& vertex) throw (OutOfRangeException); 
};

template<class T>
class Tree<T>::DfsIterator {
    public:
        DfsIterator(){
            tree = 0;
            curVertex = 0;
        }
        
        DfsIterator(Tree<T>* tree_, T* curVertex_) : tree(tree_), curVertex(curVertex_) { }

        DfsIterator& operator = (const DfsIterator& it){
            this->tree = it.tree;
            this->curVertex = it.curVertex;
        }
        
        bool operator == (const DfsIterator& it) const {
            return (tree == it.tree && curVertex == it.curVertex)? true : false;
        }
        
        bool operator != (const DfsIterator& it) const {
            return (!(*this == it))? true : false;
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
        
        DfsIterator operator + (int increment) const {
            DfsIterator result = *this;
            for(int i = 0; i < increment; i++){
                result++;
            }
            return result;
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
    DfsIterator it(this, &root);
    return it;
}

template<class T>
typename Tree<T>::DfsIterator Tree<T>::end() {
    DfsIterator endit(this, 0);
    return endit;
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

    T previousVertex = root;
    T currentVertex = root;

    bool isFound = false;
    while(!isFound){
        if(tree.count(currentVertex) > 0){
            typename vector<T>::iterator childNodeIt = find(tree[currentVertex].begin(), tree[currentVertex].end(), previousVertex);
            if(childNodeIt == tree[currentVertex].end()){
                next = &tree[currentVertex][0];
                isFound = true;
            }
            else{
                if((childNodeIt + 1) != tree[currentVertex].end()){
                    next = &(*(childNodeIt+1));
                    isFound = true;
                }
                else {
                    try {
                        previousVertex = getParent(*childNodeIt);
                        currentVertex = getParent(previousVertex);
                    }
                    catch(HasNoParentException& exception){
                        throw OutOfRangeException();
                    }
                }
            }
        } 
        else {
            try {
                previousVertex = currentVertex;
                currentVertex = getParent(currentVertex);
            }
            catch(HasNoParentException& exception){
                throw OutOfRangeException();
            }
        }
    }
    return *next;
}

//get a cardinal number
template<class T> 
int Tree<T>::getTreeOrder() const {
    return order;
}
    
//add an edge to the tree
template<class T> 
Tree<T>& Tree<T>::addEdge(const T &vertex1, const T &vertex2){
    tree[vertex1].push_back(vertex2);
    parents[vertex2] = vertex1;
    order = parents.size();
    return *this;
}

//display all edges of the tree
template<class T>
void Tree<T>::printTree(){
    typename map<T, vector<T> >::iterator curIt;
    typename map<T, vector<T> >::iterator endIt;
    curIt = this->tree.begin();
    endIt = this->tree.end();
    while(curIt != endIt){
        int i = 0;
        //show the adjasent vertexes
        while(i < curIt->second.size()){
            cout << curIt->first << " -> ";
            cout << curIt->second.at(i);
            cout << endl;
            i++;
        }
        curIt++;
    }
}

//print a traversal
template<class T>
void Tree<T>::printPath(const vector<T> &path){
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
        for(int i = 0; (i < this->order) && (isPresent != true); i++){
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


