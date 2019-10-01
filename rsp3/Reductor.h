#ifndef REDUCTOR_H
#define REDUCTOR_H

#include "MDF.h"
#include "Point.h"
#include "Subset.h"



class Reductor
{
    private:
        double exec_time = 0; //RSP3 execution time.
        float reduction_prct = 0; //Reduction percentage achieved.
        unsigned long dist_cnt = 0; //Distances calculated.
        size_t initial_count{}; //Size of initial subset.
        size_t reduced_count = 0; //Size of reduced subset.
        unsigned long long(*MDF_func)(Subset&){}; //Pointer to MDF function used in RSP3.
        std::string MDF_name; //Name of the MDF function.
        Subset initial_ss; //Initial subset.
        std::vector<Point> reduced_pts; //Reduced subset stored as points in a vector.

    public:
        Reductor();

        void printInitialSubset(); //STDOUT representation of initial subset.
        void printReducedPoints(); //STDOUT representation of reduced subset.
        void printResults(); //STDOUT representation of RSP3 reduction results.
        void rsp3(); //Execute RSP3 on initial subset and produce the reduced subset.

        //Setters-Getters
        void setMDF(e_MDF _MDF); //Set the MDF function that will be used by RSP3.
        void setSubset(Subset &ss); //Set the initial subset to be reduced.
        Subset* getSubset();
        std::string getMDF();
        std::vector<Point>* getReducedPoints();
        size_t getInitialSize();
        size_t getReducedSize();
        float getReduction();
        double getExecTime();
        unsigned long getDistances();
};

#endif // REDUCTOR_H
