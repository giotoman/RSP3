#include <ctime>
#include <iostream>
#include <string>

#include "MDF.h"
#include "Reductor.h"
#include "Fullset.h"
#include "Subset.h"

Reductor::Reductor(){}

void Reductor::printInitialSubset()
{
    initial_ss.printSubset();
}

void Reductor::printReducedPoints()
{
    for (size_t i = 0; i < reduced_pts.size(); i++) reduced_pts[i].printPoint();
}

void Reductor::rsp3()
{
    dist_cnt = 0;
    clock_t begin = clock();

    Fullset S;
    S.addSubset(initial_ss);

    do
    {
        //Select the subset in S with the highest max distance value
        float highest_md = 0;
        size_t highest_index = 0;

        for (size_t i = 0; i < S.getSize(); i++)
        {
            if(S.getSubsetAt(i)->getMAXD() == -1)
            {
                dist_cnt += MDF_func(*S.getSubsetAt(i));
            }

            if(S.getSubsetAt(i)->getMAXD() > highest_md)
            {
                highest_md = S.getSubsetAt(i)->getMAXD();
                highest_index = i;
            }
        }

        if(S.getSubsetAt(highest_index)->isHomogeneous())
        {
            Point r = S.getSubsetAt(highest_index)->calcMeanPoint();
            reduced_pts.push_back(r);
        }
        else
        {
            Subset D1, D2;
            S.getSubsetAt(highest_index)->divideByMD(D1, D2);
            S.addSubset(D1);
            S.addSubset(D2);
        }

        S.removeSubsetAt(highest_index);
    }
    while(!S.isEmpty());

    clock_t end = clock();

    exec_time = double(end - begin) / CLOCKS_PER_SEC;
    reduced_count = reduced_pts.size();
    reduction_prct = (1 - ((float)reduced_count / initial_count)) * 100;
}

void Reductor::printResults()
{
    std::cout << "        Method used: " << MDF_name << std::endl;
    std::cout << "          Reduction: " << reduction_prct << "%" << std::endl;
    std::cout << "          Distances: " << dist_cnt << std::endl;
    std::cout << "     Execution time: " << exec_time << " sec(s)" << std::endl;
}

void Reductor::setMDF(e_MDF _MDF)
{
    switch(_MDF)
    {
        case 0 : MDF_name = "GRID"; MDF_func = MDF_GRID; return;
        case 1 : MDF_name = "MARGIN_HULL"; MDF_func = MDF_MHULL; return;
        case 2 : MDF_name = "QUICK_HULL"; MDF_func = MDF_QHULL; return;
        case 3 : MDF_name = "HYBRID_HULL"; MDF_func = MDF_HHULL; return;
        default : MDF_name = "CONV";
    }
}
void Reductor::setSubset(Subset &ss){ initial_ss = ss; initial_count = ss.getSize(); }
Subset* Reductor::getSubset(){ return &initial_ss; }
std::string Reductor::getMDF(){ return MDF_name; }
std::vector<Point>* Reductor::getReducedPoints() { return &reduced_pts; }
size_t Reductor::getInitialSize() { return initial_count; }
size_t Reductor::getReducedSize() { return reduced_count; }
float Reductor::getReduction() { return reduction_prct; }
double Reductor::getExecTime() { return exec_time; }
unsigned long Reductor::getDistances() { return dist_cnt; }
