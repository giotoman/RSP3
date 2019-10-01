#include <iostream>
#include <math.h>
#include <string>
#include <utility>
#include <vector>

#include "Point.h"

std::vector<Point> ALL_POINTS;

Point::Point()= default;

void Point::addCoordinate(const float c)
{
    coordinates.push_back(c);
}

float Point::operator>>(const Point &p)
{
    float sum = 0;

    for (size_t i = 0; i < coordinates.size(); i++) sum += pow(this->coordinates[i] - p.coordinates[i], 2);

    return sum;
}

void Point::printPoint()
{
    for (size_t i = 0; i < coordinates.size(); i++) std::cout << "d" << i + 1 << ": " << coordinates[i] << ((i == coordinates.size() - 1) ? "" : " | ");

    std::cout << " * Class: " << label << std::endl;
}

void printAllPoints()
{
    for (auto & i : ALL_POINTS) i.printPoint();
}

void Point::setLabel(std::string lbl) { label = std::move(lbl); }
std::string Point::getLabel() { return label; }
size_t Point::getCoordsCount() { return coordinates.size(); }
void Point::setCoordAt(size_t index, float value) { coordinates[index] = value; }
float Point::getCoordAt(size_t index) { return coordinates[index]; }
