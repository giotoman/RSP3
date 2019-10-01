#ifndef CROSSVALIDATOR_H
#define CROSSVALIDATOR_H

#include <vector>

#include "Fold.h"

extern bool DO_NORM;
extern bool DO_IRR;
extern bool DO_SELECT;

class CrossValidator
{
    private:
        std::vector<Fold> v_folds; //Vector holding cross validation folds.
        float avg_reduction_prct = 0; //Average reduction percentage.
        float avg_prediction_prct = 0; //Average prediction percentage.
        unsigned long avg_dist_cnt = 0; //Average distances calculated.
        double avg_exec_time = 0; //Average execution time.


    public:
        CrossValidator();

        void createCV(const std::string& file_path, size_t folds, e_MDF func); //Create cross-validation from file.
        void loadCV(const std::string& dir_path, e_MDF func); //Load cross-validation from directory.
        void printAnalysis();
};

#endif // CROSSVALIDATOR_H
