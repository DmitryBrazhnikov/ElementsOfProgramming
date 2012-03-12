#include <iostream>
#include <math.h>
#include <vector>
#include <assert.h>

using std::cout;
using std::vector;
using std::endl;

// @overrading vector operators 
std::vector<int> operator + (const std::vector<int> &augend, int addend){
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
class CFunctor{
    public:
        explicit CFunctor(int module = 0) : module(module){ } 

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



// find size of the orbit cycle or precycle 
template<class T>
class PreCycle{
    public:
        PreCycle(const CFunctor<T> &functor){
            this->functor = functor;
        }

        const T getElemInCycle(const T &initValue) const {
            T curValue = initValue;
            for(int i = 0; i <= functor.getModule(); i++){
                curValue = functor(curValue);
            }
            return curValue;
        }

        int getCycSize(const T &initValue) const {
            T requiredElement = getElemInCycle(initValue); 
            T curValue = requiredElement; 
            bool isCycleFound = false;
            int cycSize = 0;
            while(isCycleFound == false){
                curValue = functor(curValue);
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
                    curPoint = functor(curPoint);
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
        CFunctor<T> functor;
};

int main(){
    CFunctor<int> func(5);
    PreCycle<int> firstOrbit(func);

    cout << firstOrbit.getPreCycSize(2) << endl;
    
    func.setModule(113);
    PreCycle<int> secondOrbit(func);
    cout << secondOrbit.getPreCycSize(3) << endl;
    
    
    vector<int> vect;
    vect.push_back(30); 
    vect.push_back(10); 
    vect.push_back(41); 
    vect.push_back(46); 
    vect.push_back(58); 
    vect.push_back(23); 
    vect.push_back(19); 
    
    CFunctor<vector<int> > vectFunc(7);
    PreCycle<vector<int> > vectOrbit(vectFunc);
    cout << vectOrbit.getPreCycSize(vect) << endl;

    return 0;
}



