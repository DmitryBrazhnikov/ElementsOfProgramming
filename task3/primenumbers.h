#pragma once
#include <vector>

class PrimeNumbers {
    public:
        explicit PrimeNumbers(int count);
        bool isPrime(int number) const;
        std::vector<int> getPrimeNumbers() const;

    private:
        std::vector<bool> primeSieve;
};
