#include <iostream>
#include <math.h>
#include <vector>
#include <assert.h>

using std::cout;
using std::vector;
using std::endl;

// @overrading vectors operators 
std::vector<int> operator + (const std::vector<int> &v1, const int &n){
    vector<int> result(v1.size());
    for(int i = 0; i < v1.size(); i++){
        result[i] = v1[i] + n;
    }
    return result;
}

std::vector<int> operator + (const std::vector<int> &v1, const std::vector<int> &v2){
    assert(v1.size() == v2.size());
    
    vector<int> result(v1.size());
    for(int i = 0; i < v1.size(); i++){
        result[i] = v1[i] + v2[i];
    }
    return result;
}

std::vector<int> operator % (const std::vector<int> &v1, const int &n){
    vector<int> result(v1.size());
    for(int i = 0; i < v1.size(); i++){
        result[i] = v1[i] % n;
    }
    return result;
}

std::vector<int> pow(const std::vector<int> &v1, const int &n){
    vector<int> result(v1.size());
    for(int i = 0; i < v1.size(); i++){
        result[i] = pow(v1[i], n);
    }
    return result;
}

template<class T>
class CFunctor{
    public:
        CFunctor(){
            this->module = 0;
        }

        CFunctor(const int &module){
            this->module = module;
        }

        T operator () (T &arg){
            T result = pow(arg,2);
            if(module != 0){
                result = result % module;
            }
            return result;
        }

        const int& getMod() const{
            return module;
        }
    private:
        int module;
};


// find size of the orbit cycle or precycle 
template<class T>
class PreCycle{
    public:
        PreCycle(const CFunctor<T> &funcToExec){
            this->funcToExec = funcToExec;
        }

        int getCycSize(const T &initValue){
            T value = initValue;
            for(int i = 0; i <= funcToExec.getMod(); i++){
                value = funcToExec(value);
            }

            T lookForNumber = value; 
            bool isCycleFound = false;
            int cycSize = 0;
            while(isCycleFound == false){
                value = funcToExec(value);
                cycSize++;
                
                if(lookForNumber == value){
                    isCycleFound = true;
                }
            }
            return cycSize;
        }
            
        int getPreCycSize(const T &initValue){
            int cycSize = getCycSize(initValue);
            T value = initValue;
            T result;
            int preCycSize = 0;
            while(value != result){ 
                for(int i = 0; i < preCycSize; i++){
                    value = funcToExec(value);
                }
                                    
                result = value;
                for(int i = 0; i < cycSize; i++){
                    result = funcToExec(result);
                }
                
                if(value != result) {
                    preCycSize++;
                }
            }
            return preCycSize;
        }
    private:
        CFunctor<T> funcToExec;
};

int main(){
    CFunctor<int> func(5);
    PreCycle<int> cyc(func);
    cout << cyc.getPreCycSize(2) << endl;
    
    vector<int> v1;
    v1.push_back(0); 
    v1.push_back(1); 
    v1.push_back(4); 
    
    CFunctor<vector<int> > funcV(5);
    PreCycle<vector<int> > cycV(funcV);
    cout << cycV.getPreCycSize(v1) << endl;

    return 0;
}



