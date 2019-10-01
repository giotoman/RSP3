#ifndef FULLSET_H
#define FULLSET_H

#include <vector>

#include "Subset.h"



class Fullset
{
    private:
        std::vector<Subset> v_subsets;

    public:
        Fullset();

    void addSubset(const Subset& ss);
    void removeSubsetAt(size_t index);
    bool isEmpty();
    void printSet();

    size_t getSize();
    Subset* getSubsetAt(size_t index);

};

#endif // FULLSET_H
