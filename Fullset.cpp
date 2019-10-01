#include <iostream>
#include <vector>

#include "Fullset.h"
#include "Point.h"
#include "Subset.h"



Fullset::Fullset(){}

void Fullset::addSubset(const Subset& ss)
{
    v_subsets.push_back(ss);
}

void Fullset::removeSubsetAt(size_t index)
{
    v_subsets.erase(v_subsets.begin() + index);
}

bool Fullset::isEmpty()
{
    return v_subsets.empty();
}

void Fullset::printSet()
{
    for (auto & v_subset : v_subsets) v_subset.printSubset();
}

size_t Fullset::getSize() { return v_subsets.size(); }
Subset* Fullset::getSubsetAt(size_t index) { return &v_subsets[index]; }
