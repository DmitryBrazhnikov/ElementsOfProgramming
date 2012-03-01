#include <iostream>
#include <math.h>

using std::cout;

template<class T>
class Function{
    public:
        T operator () (T &x_arg){
            return pow(x_arg, 2);
        }
};

template<class T>
class PreCycle{
    public:
        PreCycle(const Function<T> &funcToExec){
            this->funcToExec = funcToExec;
        }

        int getCycSize(const int &module, const T &initValue){
            T value = initValue;
            for(int i = 0; i <= module; i++){
                value = funcToExec(value);
                value = value % module;
            }

            T lookForNumber = value; 
            bool isCycleFound = false;
            int cycSize = 0;
            while(isCycleFound == false){
                value = funcToExec(value);
                value = value % module;
                cycSize++;
                
                if(lookForNumber == value){
                    isCycleFound = true;
                }
            }
            return cycSize;
        }
            
        int getPreCycSize(const int &module, const T &initValue){
            int cycSize = getCycSize(module, initValue);
            T value = initValue;
            T result;
            int preCycSize = 0;
            while(value != result){ 
                for(int i = 0; i < preCycSize; i++){
                    value = funcToExec(value);
                    value = value % module;
                }
                                    
                result = value;
                for(int i = 0; i < cycSize; i++){
                    result = funcToExec(result);
                    result = result % module;
                }
                
                if(value != result) {
                    preCycSize++;
                }
            }
            return preCycSize;
        }
    private:
        Function<T> funcToExec;
};

int main(){
    Function<int> func;
    PreCycle<int> cyc(func);
    cout << cyc.getPreCycSize(5, 2);
    
    return 0;
}



