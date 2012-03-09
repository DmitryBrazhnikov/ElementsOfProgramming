#include <iostream>

using std::cout;

template<class T>
class multiply{
    public:
        T operator() (const T &a, const T &b){
            return a * b;
        }
        T operator() (const T &a){
            return a * a;
        }
};

template<class T, template<class> class BinFunc >
T pow(const T &a, const size_t &n, BinFunc<T> &function){
    T powA = a;
    T position = 0;
    T result = 1
    while((1 << position) <= n){
        if(n & (1 << position)){
            result = result * powA;
        }
        position++;
        powA = function(powA);
    }
    return result;
}

int main(){
    multiply<int> func;
    cout << pow<int, multiply>(2, 3, func);

    return 0;
}
