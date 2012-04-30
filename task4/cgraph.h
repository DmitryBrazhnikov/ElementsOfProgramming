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
using std::set;
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
        class DfsIterator {
            public:
                DfsIterator(){
                    tree = 0;
                    curVertex = 0;
                }
                
                DfsIterator(Tree<T>* tree_, T* curVertex_) : tree(tree_) {
                    curVertex = curVertex_;
                }

                DfsIterator& operator = (const DfsIterator& it){
                    this->tree = it.tree;
                    this->curVertex = it.curVertex;
                }
                
                bool operator == (const DfsIterator& it){
                    if(tree == it.tree && curVertex == it.curVertex){
                        return true;
                    }
                    return false;
                }
                
                bool operator != (const DfsIterator& it){
                    if(!(*this == it)){
                        return true;
                    }
                    return false;
                }
        
                DfsIterator operator ++ (int) {
                    DfsIterator result = *this;
                    curVertex = (tree->nextVertex(*curVertex, *curVertex));
                    return result;
                }
                
                T& operator * () {
                    return *curVertex;
                }
            private:
                Tree<T>* tree; 
                T* curVertex;
        };
    
    public:
        typedef DfsIterator iterator;
        
        Tree(const T& root_) : root(root_) { }; 
        
        //add an edge   
        Tree<T>& addEdge(const T &vertex1, const T &vertex2);
        //get number of vertexes
        set<T> getVertexes();
        int getTreeOrder();
        //print the tree
        void printTree();
       
        //Algorithms 
        T* nextVertex(const T& vertex, const T& prev); 
        //breadth-first traversal
        vector<T> goBreadth(const T &headVertex);
        //print the traversal
        static void printPath(const vector<T> &path);
        void printParents();

        DfsIterator begin();
        DfsIterator end();
        
    private:
        //directed weighted tree
        map<T, vector<T> > tree;
        T root;
        int order;
        
        map<T, T> parents;
};


template<class T>
typename Tree<T>::DfsIterator Tree<T>::begin(){
    DfsIterator it(this, &root);
    return it;
}

template<class T>
typename Tree<T>::DfsIterator Tree<T>::end(){
    DfsIterator endit(this, 0);
    return endit;
}

template<class T>
T* Tree<T>::nextVertex(const T& vertex, const T& prev){
    T* next = 0;
    if(vertex == 0){
        return 0;
    }
    if(tree.count(vertex) > 0 && !(tree[vertex].size() == 1 && tree[vertex][0] == prev)){
        if(prev != 0){
        typename vector<T>::iterator childIterator = find(tree[vertex].begin(), tree[vertex].end(), prev);
            if(childIterator == tree[vertex].end()){
                next = &(tree[vertex][0]);
            }
            else{
                if(childIterator+1 != tree[vertex].end()){
                    next = &(*(childIterator+1));
                }
                else {
                    next = 0;
                }
            }
        }
        else{
            next = &(tree[vertex][0]);
        }
    } 
    else {
        T parent = parents[vertex];
        vector<T> children = tree[parent];
        typename vector<T>::iterator childIterator = find(children.begin(), children.end(), vertex);
        if(childIterator + 1 == children.end()){
            next = nextVertex(parents[parents[*childIterator]],parents[*childIterator]);
        }
        else{
            next = &(*(childIterator+1));
        }
    }
    return next;
}


template<class T>
void Tree<T>::printParents(){
    typename map<T, T>::iterator it = parents.begin();
    for(; it != parents.end(); it++){
        cout << it->first << " " << it->second << endl;
    }
}

//get array of vertexes 
template<class T> 
set<T> Tree<T>::getVertexes(){
    set<T> used;
    typename map<T, vector<T> >::iterator it;
    //go through the map
    for(it = tree.begin(); it != tree.end(); it++){
        if(used.count(it->first) == 0){
            used.insert(it->first);
        }
        //check every element of the adjasency list
        for(int i = 0; i < it->second.size(); i++){
            T curVertex = it->second.at(i);
            if(used.count(curVertex) == 0){
                used.insert(curVertex);
            }
        }
    }
    return used;
}

//get a cardinal number
template<class T> 
int Tree<T>::getTreeOrder(){
    return parents.size();
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

//dispay the traversal
template<class T>
void Tree<T>::printPath(const vector<T> &path){
    for(int i = 0; i < path.size(); i++){
        cout << path[i] << " ";
    }
}

template<class T>
vector<T> Tree<T>::goBreadth(const T &headVertex){
    vector<T> result;
    map<T, int> colors; //0 - white; 1 - grey; 2 - black
    typename map<T, vector<T> >::iterator it = this->tree.begin();
    for(int i = 0; i < this->getVertexCount(); i++){
        colors.insert(make_pair(it->first, 0));
        it++;
    }
    colors[headVertex] = 1;
    queue<T> fifo;
    fifo.push(headVertex);
    T curVertex;
    while(fifo.size() != 0){
        while(fifo.size() != 0){
            curVertex = fifo.front();
            for(int i = 0; i < this->tree[curVertex].size(); i++){
                if(colors[this->tree[curVertex][i]] == 0){
                    colors[this->tree[curVertex][i]] = 1;
                    fifo.push(this->tree[curVertex][i]);
                }
            }
            fifo.pop();
            result.push_back(curVertex);
        }
        typename map<T, int>::iterator itColors;
        itColors = colors.begin();
        bool isPresent = false;
        //check if there are uncovered vertexes
        for(int i = 0; (i < this->getVertexCount()) && (isPresent != true); i++){
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


