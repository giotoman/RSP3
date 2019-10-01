#include <string>

#include "MDF.h"
#include "Point.h"
#include "Subset.h"
#include "qhull/QuickHull.hpp"

std::vector<size_t> RANKS;
size_t DIMS;

unsigned long long MDF_GRID(Subset &ss)
{
    unsigned long long d_count = 0;
    float max_d = 0;
    size_t pos1 = 0, pos2 = 0;

    for (size_t i = 0; i < ss.getSize(); i++)
    {
        for (size_t j = i + 1; j < ss.getSize(); j++)
        {
            float curr_d = *ss.getPointAt(i) >> *ss.getPointAt(j);
            d_count++;

            if (curr_d > max_d) { max_d = curr_d; pos1 = i; pos2 = j; }
        }
    }

    ss.setMDPOS1(pos1);
    ss.setMDPOS2(pos2);
    ss.setMAXD(max_d);

    return d_count;
}

unsigned long long MDF_MHULL(Subset &ss)
{
    std::vector<float> max_values;
    std::vector<float> min_values;
    std::vector<size_t> max_indexes;
    std::vector<size_t> min_indexes;

    size_t dimensions = DIMS;

    for (size_t i = 0; i < dimensions; i++)
    {
        max_values.push_back(ss.getPointAt(0)->getCoordAt(RANKS[i]));
        max_indexes.push_back(0);
        min_values.push_back(ss.getPointAt(0)->getCoordAt(RANKS[i]));
        min_indexes.push_back(0);
    }

    for (size_t i = 1; i < ss.getSize(); i++)
    {
        for (size_t j = 0; j < dimensions; j++)
        {
            if (ss.getPointAt(i)->getCoordAt(RANKS[j]) > max_values[j])
            {
                max_values[j] = ss.getPointAt(i)->getCoordAt(RANKS[j]);
                max_indexes[j] = i;
            }
            else if (ss.getPointAt(i)->getCoordAt(RANKS[j]) < min_values[j])
            {
                min_values[j] = ss.getPointAt(i)->getCoordAt(RANKS[j]);
                min_indexes[j] = i;
            }
        }
    }

    Subset m_hull;
    std::vector<size_t> ss_indexes;

    for (size_t i = 0; i < dimensions; i++)
    {
        ss_indexes.push_back(max_indexes[i]);
        ss_indexes.push_back(min_indexes[i]);
    }

    for (size_t i = 0; i < ss_indexes.size(); i++)
    {
        size_t j = i + 1;

        while(j < ss_indexes.size())
        {
            if (ss_indexes[i] == ss_indexes[j]) ss_indexes.erase(ss_indexes.begin() + j);
            else j++;
        }

        m_hull.addPoint(ss.getPointAt(ss_indexes[i]));
    }

    unsigned long long d_count = MDF_GRID(m_hull);

    ss.setMDPOS1(ss_indexes[m_hull.getMDPOS1()]);
    ss.setMDPOS2(ss_indexes[m_hull.getMDPOS2()]);
    ss.setMAXD(m_hull.getMAXD());

    return d_count;
}

unsigned long long MDF_QHULL(Subset &ss)
{
    if (ss.getSize() < 6) return MDF_GRID(ss);

    using namespace quickhull;
    QuickHull<float> qh;
    std::vector<Vector3<float>> pointCloud;

    Subset m_hull;

    for (size_t i = 0; i < ss.getSize(); i++)
    {
        Vector3<float> v3_point{};

        v3_point.x = ss.getPointAt(i)->getCoordAt(RANKS[0]);
        v3_point.y = ss.getPointAt(i)->getCoordAt(RANKS[1]);
        v3_point.z = (ss.getPointAt(i)->getCoordsCount() > 2) ? ss.getPointAt(i)->getCoordAt(RANKS[2]) : 0;

        pointCloud.push_back(v3_point);
    }

    auto hull = qh.getConvexHull(pointCloud, false, true);
    auto indexBuffer = hull.getIndexBuffer();

    for (size_t i = 0; i < indexBuffer.size(); i++)
    {
        size_t j = i + 1;

        while(j < indexBuffer.size())
        {
            if(indexBuffer[i] == indexBuffer[j]) indexBuffer.erase(indexBuffer.begin() + j);
            else j++;
        }

        m_hull.addPoint(ss.getPointAt(indexBuffer[i]));
    }

    unsigned long long d_count = MDF_GRID(m_hull);

    ss.setMDPOS1(indexBuffer[m_hull.getMDPOS1()]);
    ss.setMDPOS2(indexBuffer[m_hull.getMDPOS2()]);
    ss.setMAXD(m_hull.getMAXD());

    return d_count;
}

unsigned long long MDF_HHULL(Subset &ss)
{
    if (ss.getSize() < 4) return MDF_GRID(ss);

    std::vector<float> max_values;
    std::vector<float> min_values;
    std::vector<size_t> max_indexes;
    std::vector<size_t> min_indexes;

    size_t dimensions = ss.getPointAt(0)->getCoordsCount();

    for (size_t i = 0; i < dimensions; i++)
    {
        max_values.push_back(ss.getPointAt(0)->getCoordAt(i));
        max_indexes.push_back(0);
        min_values.push_back(ss.getPointAt(0)->getCoordAt(i));
        min_indexes.push_back(0);
    }

    for (size_t i = 1; i < ss.getSize(); i++)
    {
        for (size_t j = 0; j < dimensions; j++)
        {
            if (ss.getPointAt(i)->getCoordAt(j) > max_values[j])
            {
                max_values[j] = ss.getPointAt(i)->getCoordAt(j);
                max_indexes[j] = i;
            }
            else if (ss.getPointAt(i)->getCoordAt(j) < min_values[j])
            {
                min_values[j] = ss.getPointAt(i)->getCoordAt(j);
                min_indexes[j] = i;
            }
        }
    }

    Subset m_hull;
    std::vector<size_t> ss_indexes;

    for (size_t i = 0; i < dimensions; i++)
    {
        ss_indexes.push_back(max_indexes[i]);
        ss_indexes.push_back(min_indexes[i]);
    }

    for (size_t i = 0; i < ss_indexes.size(); i++)
    {
        for (size_t j = i + 1; j < ss_indexes.size(); j++) if (ss_indexes[i] == ss_indexes[j]) ss_indexes.erase(ss_indexes.begin() + j);

        m_hull.addPoint(ss.getPointAt(ss_indexes[i]));
    }

    unsigned long long d_count = MDF_QHULL(m_hull);

    ss.setMDPOS1(ss_indexes[m_hull.getMDPOS1()]);
    ss.setMDPOS2(ss_indexes[m_hull.getMDPOS2()]);
    ss.setMAXD(m_hull.getMAXD());

    return d_count;
}

e_MDF e_convert(const std::string &str)
{
    if(str == "GRID") return GRID;
    else if(str == "MH") return MH;
    else if(str == "QH") return QH;
    else if (str == "HH") return HH;
    else return CONV;
}
