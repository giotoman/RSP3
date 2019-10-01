#ifndef SUBSET_H
#define SUBSET_H

#include <vector>

#include "Point.h"

class Subset
{
    private:
        std::vector<Point*> v_points; //Vector containing pointers to points in ALL_POINTS global vector which form this subset.
        size_t md_pos_p1{}, md_pos_p2{}; //Indexes of the two points that form the max distance in the subset.
        float max_d = -1; //Max distance value, initialized at -1 for control.

    public:
        Subset();

        void addPoint(Point *p); //Add a pointer to a point in the subset.
        bool isHomogeneous(); //All points have the same label check.
        Point calcMeanPoint(); //Return a point with coordinates equal to the average of all the points in the subset.
        void divideByMD(Subset &D1, Subset &D2); //Divide subset into two new ones, depending if each point is closer to md_p1 or md_p2.
        void printSubset(); //STDOUT representation of subset.

        //Setters-Getters
        void setMDPOS1(size_t pos);
        void setMDPOS2(size_t pos);
        void setMAXD(float d);
        size_t getMDPOS1();
        size_t getMDPOS2();
        float getMAXD();
        size_t getSize();
        Point* getPointAt(size_t index);
};

void loadSubset(Subset &ss);
void loadSubset(Subset &ss, size_t start_index, size_t end_index);

#endif // SUBSET_H
