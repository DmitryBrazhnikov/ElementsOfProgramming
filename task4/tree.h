#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <limits>
#include <algorithm>

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
        int getTreeOrder();
        void printTree();
       
        vector<T> depthFirstSearch(const T &root);
        vector<T> breadthFirstSearch(const T &root);
        static void printPath(const vector<T> &path);
        
    private:
        map<T, vector<T> > tree;
        T root;
        map<T, T> parents;
        int order;
        //forward iterator functions
        T* getParent(const T vertex);
        T* nextVertex(const T& vertex, const T& prev); 
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
            curVertex = (tree->nextVertex(*curVertex, *curVertex));
            return result;
        }
        
        DfsIterator operator ++ () {
            curVertex = (tree->nextVertex(*curVertex, *curVertex));
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
T* Tree<T>::getParent(const T vertex){
    T* parent;
    if(vertex == root){
        parent = 0;
    }
    else{
        parent = &parents[vertex];
    }
    return parent;
}

template<class T>
T* Tree<T>::nextVertex(const T& vertex, const T& prev){
    T* next;
    if(tree.count(vertex) > 0){
        typename vector<T>::iterator childNodeIt = find(tree[vertex].begin(), tree[vertex].end(), prev);
        if(childNodeIt == tree[vertex].end()){
            next = &(tree[vertex][0]);
        }
        else{
            if((childNodeIt + 1) != tree[vertex].end()){
                next = &(*(childNodeIt+1));
            }
            else {
                T* ancestor = getParent(*childNodeIt);
                T* greatAncestor = getParent(*ancestor);
                if(greatAncestor == 0){
                    next = 0;
                }
                else{
                    next = nextVertex(*greatAncestor, *ancestor);
                }
            }
        }
    } 
    else {
        T* parent = getParent(vertex);
        if(parent == 0){
            next = 0;
        }
        else {
            typename vector<T>::iterator childNodeIt = find(tree[*parent].begin(), tree[*parent].end(), vertex);
            if((childNodeIt + 1) == tree[*parent].end()){
                T* ancestor = getParent(*childNodeIt);
                T* greatAncestor = getParent(*ancestor);
                if(greatAncestor == 0){
                    next = 0;
                }
                else{
                    next = nextVertex(*greatAncestor, *ancestor);
                }
            }
            else{
                next = &(*(childNodeIt+1));
            }
        }
    }
    return next;
}

//get a cardinal number
template<class T> 
int Tree<T>::getTreeOrder(){
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


