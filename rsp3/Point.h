#ifndef POINT_H
#define POINT_H

#include <string>
#include <vector>



class Point
{
    private:
        std::vector<float> coordinates; //Vector containing coordinates of point.
        std::string label; //Label aka class name of point.

    public:
        Point();

        void addCoordinate(float c); //Add a coordinate to a point.
        float operator>>(const Point &p); //Operator overload for calculating the Euclid distance between two points. (Not including root for speed)
        void printPoint(); //STDOUT representation of a point.

        //Setters-Getters
        void setLabel(std::string lbl);
        std::string getLabel();
        size_t getCoordsCount();
        void setCoordAt(size_t index, float value);
        float getCoordAt(size_t index);
};

extern std::vector<Point> ALL_POINTS; //Global vector containing all points of imported dataset / folds.
void printAllPoints(); //STDOUT representation of global vector.

#endif // POINT_H
