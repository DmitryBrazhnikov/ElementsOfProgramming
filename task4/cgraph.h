#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::set;
using std::queue;
using std::vector;
using std::list;
using std::stack;
using std::map;
using std::numeric_limits;
using std::priority_queue;
using std::pair;
using std::make_pair;

template<class T>
class CGraph{
    public:
        //add an edge   
        CGraph<T>& addEdge(const T &vertex1, const T &vertex2);
        //add a bidirectinal edge   
        CGraph<T>& addDoubleEdge(const T &vertex1, const T &vertex2);
        //remove edge from graph
        CGraph<T>& rmEdge(const T &vertex1, const T &vertex2);
        //get number of vertexes
        const int getVertexCount();
        //get an array of vertexes
        const set<T> getVertexes();
        //print the graph
        void printGraph();
       
        //Algorithms 
        
        //breadth-first traversal
        list<T> goBreadth(const T &headVertex);
        //depth-first search in the entire graph
        list<T> goDepth(const T &headVertex);
        //depth-first search inside one connected component
        list<T> goDepthComponent(const T&headVertex);
        //print the traversal
        static void printWay(list<T> way);
        
        typedef DfsIterator iterator; 

    private:
        class DfsIterator {
            public:
                operator ++ () { 
            private:
                
                 
        //directed weighted graph
        map<T, vector<T> > graph;
        //auxilary function for depth-first traversal
        list<T>& visit(T &curVertex, stack<T> &lifo, map<T, int> &colors, list<T> &result);
};

//get array of vertexes 
template<class T> 
const set<T> CGraph<T>::getVertexes(){
    set<T> used;
    typename map<T, vector<T> >::iterator it;
    //go through the map
    for(it = this->graph.begin(); it != this->graph.end(); it++){
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
const int CGraph<T>::getVertexCount(){
    return getVertexes().size();
}
    
//add an edge to the graph
template<class T> 
CGraph<T>& CGraph<T>::addEdge(const T &vertex1, const T &vertex2){
    if(this->graph.count(vertex1) == 0){
        pair<T, vector<T> > newEdge;
        newEdge.first = vertex1;
        newEdge.second.push_back(vertex2);
        this->graph.insert(newEdge);
    }
    else{
        typename map<T, vector<T> >::iterator it = this->graph.find(vertex1);
        //insert this one into the list of the adjasency
        it->second.push_back(vertex2);
    }
    return *this;
}

template<class T> 
CGraph<T>& CGraph<T>::addDoubleEdge(const T &vertex1, const T &vertex2){
    addEdge(vertex1, vertex2);
    addEdge(vertex2, vertex1);
}

template<class T>
CGraph<T>& CGraph<T>::rmEdge(const T &vertex1, const T &vertex2){
    typename map<T, vector<T> >::iterator it = this->graph.find(vertex1);
    int adjSize = it->second.size();

    bool isFound = false;
    for(int i = 0; i < adjSize && isFound == false; i++){
        if(it->second.at(i) == vertex2){
            it->second.erase(it->second.begin() + i);
            isFound = true;
        }
    }
    return *this;
}

//display all edges of the graph
template<class T>
void CGraph<T>::printGraph(){
    typename map<T, vector<T> >::iterator curIt;
    typename map<T, vector<T> >::iterator endIt;
    curIt = this->graph.begin();
    endIt = this->graph.end();
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
void CGraph<T>::printWay(list<T> way){
    typename list<T>::iterator it;
    for(it = way.begin(); it != way.end(); it++){
        cout << *it << endl;
    }
}

template<class T>
list<T> CGraph<T>::goBreadth(const T &headVertex){
    list<T> result;
    map<T, int> colors; //0 - white; 1 - grey; 2 - black
    typename map<T, vector<T> >::iterator it = this->graph.begin();
    for(int i = 0; i < this->getVertexCount(); i++){
        colors.insert(it->first);
        it++;
    }
    colors[headVertex] = 1;
    queue<T> fifo;
    fifo.push(headVertex);
    T curVertex;
    while(fifo.size() != 0){
        while(fifo.size() != 0){
            curVertex = fifo.front();
            for(int i = 0; i < this->graph[curVertex].size(); i++){
                if(colors[this->graph[curVertex][i]] == 0){
                    colors[this->graph[curVertex][i]] = 1;
                    fifo.push(this->graph[curVertex][i]);
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

template<class T>
list<T>& CGraph<T>::visit(T &curVertex, stack<T> &lifo, map<T,int> &colors, list<T> &result){
    while(lifo.size() != 0){
        curVertex = lifo.top();
        bool isPresent = false;
        for(int i = 0; (i < this->graph[curVertex].size()) && (isPresent == false); i++){
            if(colors[this->graph[curVertex][i]] == 0){
                colors[this->graph[curVertex][i]] = 1;
                lifo.push(this->graph[curVertex][i]);
                isPresent = true;
            }
        }
        if(isPresent == false){
            lifo.pop();
            colors[curVertex] = 2;
            result.push_back(curVertex);
        }
    }
    return result;
}

template<class T>
list<T> CGraph<T>::goDepthComponent(const T &headVertex){
    list<T> result;
    map<T, int> colors; //0 - white; 1 - grey; 2 - black
    typename map<T, vector<T> >::iterator it = this->graph.begin();
    
    for(int i = 0; i < this->getVertexCount(); i++){
        colors.insert(pair<T, int>(it->first, 0));
        it++;
    }
    colors[headVertex] = 1;
    stack<T> lifo;
    lifo.push(headVertex);
    T curVertex;
    visit(curVertex, lifo, colors, result);
    return result;
}    

template<class T>
list<T> CGraph<T>::goDepth(const T &headVertex){
    list<T> result;
    map<T, int> colors; //0 - white; 1 - grey; 2 - black
    
    typename map<T, vector<T> >::iterator it = this->graph.begin();
    
    for(int i = 0; i < this->getVertexCount(); i++){
        colors.insert(it->first);
        it++;
    }
    
    colors[headVertex] = 1;
    stack<T> lifo;
    lifo.push(headVertex);
    T curVertex;
    
    while(lifo.size() != 0){
        visit(curVertex, lifo, colors, result);
        typename map<T, int>::iterator itColors;
        itColors = colors.begin();
        bool isPresent = false;
        //check if there are uncovered vertexes
        for(int i = 0; i < this->getVertexCount() && isPresent == false; i++){
            if(itColors->second == 0){
                lifo.push(itColors->first);
                itColors->second = 1;
                isPresent = true;
            }
            itColors++;
        }
    }
    return result;
}    

//DFS iterator
template<class T>
CGraph<T>::iterator DfsIterator (const T &headVertex){
    map<T, int> colors; //0 - white; 1 - grey; 2 - black
    
    typename map<T, vector<T> >::iterator it = this->graph.begin();
    for(int i = 0; i < this->getVertexCount(); i++){
        colors.insert(it->first);
        it++;
    }
    
    colors[headVertex] = 1;
    
    
    stack<T> lifo;
    lifo.push(headVertex);
    T curVertex;
    
    while(lifo.size() != 0){
        visit(curVertex, lifo, colors, result);
        typename map<T, int>::iterator itColors;
        itColors = colors.begin();
        bool isPresent = false;
        //check if there are uncovered vertexes
        for(int i = 0; i < this->getVertexCount() && isPresent == false; i++){
            if(itColors->second == 0){
                lifo.push(itColors->first);
                itColors->second = 1;
                isPresent = true;
            }
            itColors++;
        }
    }
    return result;
}    
