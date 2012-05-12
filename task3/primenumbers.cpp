#include "primenumbers.h"

PrimeNumbers::PrimeNumbers(int count){
    primeSieve.push_back(false);
    
    for(int i = 2; i <= count; i++){
        primeSieve.push_back(true);
    }

    for(int i = 2; i*i <= count; i++){
        if(primeSieve[i]){ 
            for(int j = i*i; j <= count; j += i){
                primeSieve[j] = false;
            }
        }
    }
}

std::vector<int> PrimeNumbers::getPrimeNumbers() const {
    std::vector<int> primes;
    for(int i = 0; i < primeSieve.size(); i++){
        if(primeSieve[i]){
            primes.push_back(i);
        }
    }
    return primes;
}

bool PrimeNumbers::isPrime(int number) const {
    return primeSieve[number];
}
