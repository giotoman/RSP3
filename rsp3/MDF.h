#ifndef MDF_H
#define MDF_H

#include "Subset.h"



extern std::vector<size_t> RANKS;
extern size_t DIMS;

enum e_MDF
{
    GRID = 0,
    MH = 1,
    QH = 2,
    HH = 3,
    CONV = 4
};

unsigned long long MDF_GRID(Subset &ss);
unsigned long long MDF_MHULL(Subset &ss);
unsigned long long MDF_QHULL(Subset &ss);
unsigned long long MDF_HHULL(Subset &ss);
e_MDF e_convert(const std::string &str);

#endif // MDF_H
