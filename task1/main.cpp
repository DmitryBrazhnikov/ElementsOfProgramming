#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <vector>
#include <assert.h>
#include <map>

using std::cout;
using std::vector;
using std::endl;
using std::make_pair;
using std::map;

std::vector<int> addScalar (const std::vector<int> &augend, int addend){
    vector<int> result(augend.size());
    for(int i = 0; i < augend.size(); i++){
        result[i] = augend[i] + addend;
    }
    return result;
}

std::vector<int> operator + (const std::vector<int> &augend, const std::vector<int> &addend){
    assert(augend.size() == addend.size());
    
    vector<int> result(augend.size());
    for(int i = 0; i < augend.size(); i++){
        result[i] = augend[i] + addend[i];
    }
    return result;
}

std::vector<int> operator % (const std::vector<int> &dividend, int divisor){
    vector<int> result(dividend.size());
    for(int i = 0; i < dividend.size(); i++){
        result[i] = dividend[i] % divisor;
    }
    return result;
}

std::vector<int> pow(const std::vector<int> &base, int exponent = 2){
    vector<int> result(base.size());
    for(int i = 0; i < base.size(); i++){
        result[i] = pow(base[i], exponent);
    }
    return result;
}

template<class T>
class Transformation{
    public:
        virtual T operator () (const T& arg) const = 0;
        virtual int getModule() const = 0;
};        

template<class T>
class Pow : public Transformation<T> {
    public:
        explicit Pow(int module = 0) : module(module){ } 

        T operator () (const T &arg) const {
            T result = pow(arg, 2) + arg; 
            if(module != 0){
                result = result % module;
            }
            return result;
        }

        int getModule() const{
            return module;
        }
    
        void setModule(int module){
            this->module = module;
        }
    
    private:
        int module;
};

class Increment {
    public:
        int operator () (int &element){
            element++;
        }
        
        vector<int>& operator () (vector<int> &element){
            element = addScalar(element, 1);
        }
};

template<class T>
class OrbitGenerator : public Transformation<T>{
    public:
        OrbitGenerator(int cycSize, int preCycSize, const T& initValue) : module(preCycSize){
            T val = initValue;
            T arg;
            Increment inc;
            for(int i = 0; i < preCycSize; i++){
                arg = val;
                inc(val);
                orbitGraph.insert(make_pair(arg, val));
            } 
            T pointOfConnect = val;
            
            for(int i = 0; i < cycSize-1; i++){
                arg = val;
                inc(val);
                orbitGraph.insert(make_pair(arg, val));
            } 
            orbitGraph.insert(make_pair(val, pointOfConnect));
        }
        
        T operator()(const T& arg) const{
            return orbitGraph.find(arg)->second;
        }

        int getModule() const {
            return module;
        }

    private:
        int module;
        map<T, T> orbitGraph;

};
        
// find size of the orbit cycle or precycle 
template<class T>
class PreCycle{
    public:
        PreCycle(const Transformation<T> &transformation_) : transformation(transformation_) { }

        const T getElemInCycle(const T &initValue) const {
            T curValue = initValue;
            
            for(int i = 0; i <= transformation.getModule(); i++){
                curValue = transformation(curValue);
            }
            return curValue;
        }

        int getCycSize(const T &initValue) const {
            T requiredElement = getElemInCycle(initValue); 
            T curValue = requiredElement; 
            bool isCycleFound = false;
            int cycSize = 0;
            while(isCycleFound == false){
                curValue = transformation(curValue);
                cycSize++;
                
                if(requiredElement == curValue){
                    isCycleFound = true;
                }
            
            }
            return cycSize;
        }
            
        int getPreCycSize(const T &initValue) const {
            int cycSize = getCycSize(initValue);
            int preCycSize = 0;
            bool isJuncPointFound = false;
            T startPoint = initValue;

            while(!isJuncPointFound){ 
                T curPoint = startPoint;
                T checkPoint = curPoint;
               
                for(int posInCycle = 0; (posInCycle < cycSize) && !isJuncPointFound; posInCycle++){
                    curPoint = transformation(curPoint);
                    if(posInCycle == 0){
                        startPoint = curPoint;
                    }
                    if(curPoint == checkPoint){
                        isJuncPointFound = true;
                    }
                }
                
                if(!isJuncPointFound) {
                    preCycSize++;
                }
            }
            return preCycSize;
        }

    private:
        const Transformation<T>& transformation;
};

void testForInt(){
    srand(1000);
    for(int i = 0; i < 50; i++){
        int cycSize = rand() % 100 + 1;
        int preCycSize = rand() % 100 + 1;
        int initElem = rand() % 50 + 1;
         
        OrbitGenerator<int> genOrbit(cycSize, preCycSize, initElem);
        PreCycle<int> testing(genOrbit);
       
        //cout << cycSize << " " << testing.getCycSize(initElem) << "; ";
        //cout << preCycSize << " " << testing.getPreCycSize(initElem) << endl;

        assert((cycSize == testing.getCycSize(initElem)) && (preCycSize == testing.getPreCycSize(initElem)));
    }
}

void testForVector(){
    srand(1000);
    for(int i = 0; i < 50; i++){
        int cycSize = rand() % 100 + 1;
        int preCycSize = rand() % 100 + 1;
        
        int vectSize = rand() % 50 + 1;
        vector<int> initVect(vectSize);
        for(int i = 0; i < vectSize; i++){
            initVect.push_back(rand() % 50+1); 
        }
        
        OrbitGenerator<vector<int> > genOrbit(cycSize, preCycSize, initVect);
        PreCycle<vector<int> > testing(genOrbit);
        
        //cout << cycSize << " " << testing.getCycSize(initVect) << "; ";
        //cout << preCycSize << " " << testing.getPreCycSize(initVect) << endl;

        assert((cycSize == testing.getCycSize(initVect)) && (preCycSize == testing.getPreCycSize(initVect)));
    }
}

int main(){
    testForInt();
    testForVector();
    return 0;
}



