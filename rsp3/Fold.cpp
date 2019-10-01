#include <iostream>

#include "Fold.h"
#include "Reductor.h"
#include "Subset.h"



Fold::Fold()= default;

void Fold::createFold(size_t id, size_t ts_start, size_t ts_end, e_MDF func)
{
    this->id = id;
    this->ts_start = ts_start;
    this->ts_end = ts_end;

    rd.setMDF(func);
}

void Fold::execFold()
{
    Subset tr_ss, ts_ss;

    for (size_t i = 0; i < ALL_POINTS.size(); i++)
    {
        if (i >= ts_start && i <= ts_end) ts_ss.addPoint(&ALL_POINTS[i]);
        else tr_ss.addPoint(&ALL_POINTS[i]);
    }

    rd.setSubset(tr_ss);

    if(!rd.getMDF().compare("CONV")) { prediction_prct = classify(); }
    else { rd.rsp3(); prediction_prct = rd_classify(); }

    printFold();
}

float Fold::rd_classify()
{
    size_t correct_count = 0;

    std::vector<Point> *reduced_pts = rd.getReducedPoints();

    for (size_t i = ts_start; i <= ts_end; i++)
    {
        float min_d = reduced_pts->at(0) >> ALL_POINTS[i];
        std::string label = reduced_pts->at(0).getLabel();

        for (size_t j = 1; j < reduced_pts->size(); j++)
        {
            float curr_d = reduced_pts->at(j) >> ALL_POINTS[i];

            if (curr_d < min_d)
            {
                min_d = curr_d;
                label = reduced_pts->at(j).getLabel();
            }
        }

        if (!label.compare(ALL_POINTS[i].getLabel())) correct_count++;
    }

    return (float)correct_count / (ts_end - ts_start) * 100;
}

float Fold::classify()
{
    size_t correct_count = 0;

    Subset* initial_ss = rd.getSubset();

    for (size_t i = ts_start; i <= ts_end; i++)
    {
        float min_d = *initial_ss->getPointAt(0) >> ALL_POINTS[i];
        std::string label = initial_ss->getPointAt(0)->getLabel();

        for (size_t j = 1; j < initial_ss->getSize(); j++)
        {
            float curr_d = *initial_ss->getPointAt(j) >> ALL_POINTS[i];

            if (curr_d < min_d)
            {
                min_d = curr_d;
                label = initial_ss->getPointAt(j)->getLabel();
            }
        }

        if (!label.compare(ALL_POINTS[i].getLabel())) correct_count++;
    }

    return (float)correct_count / (ts_end - ts_start) * 100;
}

void Fold::printFold()
{
    std::cout << std::endl << "Fold id: " << (id < 10 ? "0" : "") << id << std::endl << "===========" << std::endl;
    std::cout << "  Train subset size: " << rd.getInitialSize() << std::endl;
    std::cout << "   Test subset size: " << ts_end - ts_start + 1 << std::endl;
    std::cout << "       Test Indexes: " << ts_start << " - " << ts_end << std::endl;
    std::cout << "Reduced subset size: " << rd.getReducedSize() << std::endl << std::endl;
    rd.printResults();
    std::cout << std::endl << "Prediction accuracy: " << prediction_prct << "%" << std::endl;
}

Reductor* Fold::getReductor() { return &rd; }
float Fold::getPrediction() { return prediction_prct; }
