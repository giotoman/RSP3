//
// Created by thomas on 12/2/21.
//

#ifndef RSP3_RANDOMITERATOR_H
#define RSP3_RANDOMITERATOR_H

#include <vector>
#include <random>
#include <iostream>
#include <stdexcept>

class RandomIterator
{
    public:
        RandomIterator(const unsigned long long &amount, const unsigned long long &min, const unsigned long long &max);

        bool has_next() const;
        unsigned long long next();

private:
        unsigned long long floor;
        unsigned long long n;
        unsigned long long last_k;
        unsigned long long num_left;
        std::mt19937_64 gen;
};


#endif //RSP3_RANDOMITERATOR_H
