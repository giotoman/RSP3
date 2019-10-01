#include <iostream>
#include <vector>

#include "Point.h"
#include "Subset.h"



Subset::Subset(){}

void Subset::addPoint(Point *p)
{
    v_points.push_back(p);
}

bool Subset::isHomogeneous()
{
    if (v_points.size() == 1) return true;

    for (size_t i = 1; i < v_points.size(); i++) if (v_points[0]->getLabel() != v_points[i]->getLabel()) return false;

    return true;
}

Point Subset::calcMeanPoint()
{
    if (v_points.size() == 1) return *v_points[0];

    Point mean_p;
    mean_p.setLabel(v_points[0]->getLabel());

    for (size_t i = 0; i < v_points[0]->getCoordsCount(); i++)
    {
        float sum = 0;

        for (auto & v_point : v_points) sum += v_point->getCoordAt(i);

        mean_p.addCoordinate(sum / v_points.size());
    }

    return mean_p;
}

void Subset::divideByMD(Subset &D1, Subset &D2)
{
    for (auto & v_point : v_points)
    {
        float md_1 = *v_point>>*v_points[md_pos_p1];
        float md_2 = *v_point>>*v_points[md_pos_p2];

        if (md_1 < md_2) D1.addPoint(v_point);
        else if (md_1 > md_2) D2.addPoint(v_point);
        else
        {
            if (D1.v_points.size() == 0) D1.addPoint(v_point);
            else D2.addPoint(v_point);
        }
    }
}

void Subset::printSubset()
{
    for (auto & v_point : v_points) v_point->printPoint();

    if(max_d >= 0)
    {
        std::cout << "Subset max distance is: " << max_d << " between points:" << std::endl;
        std::cout << "Index: " << md_pos_p1 << " -> "; v_points[md_pos_p1]->printPoint();
        std::cout << "Index: " << md_pos_p2 << " -> "; v_points[md_pos_p2]->printPoint();
    }

    std::cout << "Subset is homogeneous: " << ((isHomogeneous() == 1) ? "true" : "false") << std::endl <<  std::endl;
}

void loadSubset(Subset &ss)
{
    for (auto & i : ALL_POINTS) ss.addPoint(&i);
}

void loadSubset(Subset &ss, size_t start_index, size_t end_index)
{
    for (size_t i = start_index; i < end_index; i++) ss.addPoint(&ALL_POINTS[i]);
}

void Subset::setMDPOS1(size_t pos) { md_pos_p1 = pos; }
void Subset::setMDPOS2(size_t pos) { md_pos_p2 = pos; }
size_t Subset::getMDPOS1() { return md_pos_p1; }
size_t Subset::getMDPOS2() { return md_pos_p2; }
void Subset::setMAXD(float d) { max_d = d; }
float Subset::getMAXD() { return max_d; }
size_t Subset::getSize() { return v_points.size(); }
Point* Subset::getPointAt(size_t index) { return v_points[index]; }
