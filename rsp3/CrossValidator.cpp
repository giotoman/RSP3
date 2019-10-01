#include <dirent.h>
#include <iostream>

#include "CrossValidator.h"
#include "DataHandler.h"
#include "Fold.h"

bool DO_NORM;
bool DO_IRR;
bool DO_SELECT;

CrossValidator::CrossValidator()= default;

void CrossValidator::createCV(const std::string& file_path, size_t folds, e_MDF func)
{
    parse_import(file_path);

    if (DO_NORM) { normalize(); std::cout << "\nApplied normalization" << std::endl; }
    else std::cout << "\nNo normalization applied" << std::endl;

    if (func == QH || func == HH || func == MH) irr();

    size_t crop = ALL_POINTS.size() / folds;
    size_t leftovers = ALL_POINTS.size() % folds;

    for (size_t i = 0; i < folds; i++)
    {
        size_t ts_start = crop * i;
        size_t ts_end = (crop * (i + 1)) - 1;

        if (i == folds - 1) ts_end += leftovers;

        Fold f;
        f.createFold(i + 1, ts_start, ts_end, func);
        f.execFold();

        avg_dist_cnt += f.getReductor()->getDistances();
        avg_exec_time += f.getReductor()->getExecTime();
        avg_reduction_prct += f.getReductor()->getReduction();
        avg_prediction_prct += f.getPrediction();

        v_folds.push_back(f);
    }

    avg_dist_cnt /= folds;
    avg_exec_time /= folds;
    avg_reduction_prct /= folds;
    avg_prediction_prct /= folds;

    printAnalysis();
}

void CrossValidator::loadCV(const std::string& dir_path, e_MDF func)
{
    int f_cnt = 0;

    DIR* dirp = opendir(dir_path.c_str());

    struct dirent * dp;
    while ((dp = readdir(dirp)) != nullptr)
    {
        const std::string curr_path = dir_path + "/" + dp->d_name;

        if (is_file(curr_path.c_str()))
        {
            Fold f;
            f_cnt++;

            size_t ts_start = ALL_POINTS.size();
            size_t ts_end = ts_start + parse_import(dir_path + "/" + dp->d_name) - 1;

            f.createFold(f_cnt, ts_start, ts_end, func);
            v_folds.push_back(f);
        }
    }

    closedir(dirp);

    if (DO_NORM) { normalize(); std::cout << "\nApplied normalization" << std::endl; }
    else std::cout << "\nNo normalization applied" << std::endl;

    if (func == QH || func == HH || func == MH) irr();

    for (auto & v_fold : v_folds)
    {
        v_fold.execFold();

        avg_dist_cnt += v_fold.getReductor()->getDistances();
        avg_exec_time += v_fold.getReductor()->getExecTime();
        avg_reduction_prct += v_fold.getReductor()->getReduction();
        avg_prediction_prct += v_fold.getPrediction();
    }

    avg_dist_cnt /= v_folds.size();
    avg_exec_time /= v_folds.size();
    avg_reduction_prct /= v_folds.size();
    avg_prediction_prct /= v_folds.size();

    printAnalysis();
}

void CrossValidator::printAnalysis()
{
    std::cout << std::endl << "Cross validation results:" << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << " Average accuracy: " << avg_prediction_prct << "%" << std::endl;
    std::cout << "Average reduction: " << avg_reduction_prct << "%" << std::endl;
    std::cout << "Average distances: " << avg_dist_cnt << std::endl;
    std::cout << "Average fold time: " << avg_exec_time << " sec(s)" << std::endl;
}
