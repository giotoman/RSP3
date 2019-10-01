#ifndef FOLD_H
#define FOLD_H

#include "Reductor.h"

class Fold
{
    private:
        size_t id{}; //Fold cross-validation id.
        size_t ts_start{}; //Starting reference index on ALL_POINTS vector.
        size_t ts_end{}; //Ending reference index on ALL_POINTS vector.
        Reductor rd; //RSP3 Reductor.
        float prediction_prct{}; //Prediction percentage achieved with KNN-1

        float rd_classify(); //KNN-1 classification. (test subset -> reduced subset)
        float classify(); //KNN-1 classification. (test subset -> train subset)

    public:
        Fold();

        void createFold(size_t id, size_t ts_start, size_t ts_end, e_MDF func);
        void execFold();
        void printFold();

        //Setters-Getters
        Reductor* getReductor();
        float getPrediction();
};

#endif // FOLD_H
