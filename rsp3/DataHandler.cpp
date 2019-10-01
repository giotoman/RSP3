#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sys/stat.h>

#include "CrossValidator.h"
#include "DataHandler.h"
#include "MDF.h"
#include "Point.h"

std::string DELIMETER;

size_t parse_import(const std::string& path)
{
    std::ifstream file(path.c_str());

    std::string line;

    if (!getline(file, line)) { std::cout << "\nCould not import dataset at: " + path << std::endl; file.close(); exit(EXIT_FAILURE); }

    size_t point_cnt = 0;

    if (line.at(0) == '@') { DELIMETER = ","; do { getline(file, line); } while(line.find("@data") == std::string::npos && line.find("@DATA") == std::string::npos); }
    else DELIMETER = "	";

    while(getline(file, line)) { insertPoint(line); point_cnt++; }

    file.close();

    std::cout << "\nSuccessfully imported dataset at: " + path << std::endl;

    return point_cnt;
}

void insertPoint(const std::string& data_line)
{
    Point p;

    size_t start = 0U;
    size_t end = data_line.find(DELIMETER);

    while (end != std::string::npos)
    {
        std::string value = data_line.substr(start, end - start);
        p.addCoordinate(stof(value));

        start = end + DELIMETER.length();
        end = data_line.find(DELIMETER, start);
    }

    p.setLabel(data_line.substr(start, end));

    ALL_POINTS.push_back(p);
}

void normalize()
{
    size_t d = ALL_POINTS[0].getCoordsCount();

    float min_max_vals[d][2];

    for (size_t i = 0; i < d; i++) min_max_vals[i][0] = min_max_vals[i][1] = ALL_POINTS[0].getCoordAt(i);

    for (size_t i = 1; i < ALL_POINTS.size(); i++)
    {
        for (size_t j = 0; j < d; j++)
        {
            if(min_max_vals[j][0] > ALL_POINTS[i].getCoordAt(j)) min_max_vals[j][0] = ALL_POINTS[i].getCoordAt(j);
            else if(min_max_vals[j][1] < ALL_POINTS[i].getCoordAt(j)) min_max_vals[j][1] = ALL_POINTS[i].getCoordAt(j);
        }
    }

    for (auto & i : ALL_POINTS)
    {
        for (size_t j = 0; j < d; j++)
        {
            float xi = i.getCoordAt(j);
            float xmin = min_max_vals[j][0];
            float xmax = min_max_vals[j][1];

            if(xmax != xmin) i.setCoordAt(j, (xi - xmin) / (xmax - xmin));
            else i.setCoordAt(j, 0);
        }
    }
}

struct Indexed_IR
{
    float ir;
    size_t index;

    inline bool operator() (const Indexed_IR &ir1, const Indexed_IR &ir2) { return (ir1.ir > ir2.ir); }
};

void irr()
{
    if (DO_SELECT) return;

    size_t d = ALL_POINTS[0].getCoordsCount();

    if(!DO_IRR) { for (size_t i = 0; i < d; i++) RANKS.push_back(i); DIMS = d; std::cout << "\nNo interquartile range ranking applied." << std::endl; return; }

    float curr_d_vals[ALL_POINTS.size()];
    Indexed_IR irs[d];

    for (size_t i = 0; i < d; i++)
    {
        for (size_t j = 0; j < ALL_POINTS.size(); j++) curr_d_vals[j] = ALL_POINTS[j].getCoordAt(i);

        std::sort(&curr_d_vals[0], &curr_d_vals[0] + ALL_POINTS.size());

        irs[i].ir = calcIR(&curr_d_vals[0], ALL_POINTS.size());

        irs[i].index = i;
    }

    std::sort(&irs[0], &irs[0] + d, Indexed_IR());

    std::cout << "\nApplied interquartile range ranking:" << std::endl;

    for (size_t i = 0; i < d; i++) { RANKS.push_back(irs[i].index); std::cout << "D: " << irs[i].index + 1 << " -> IR: " << irs[i].ir << ((i < 3) ? " *" : "") << std::endl; }
    DIMS = (d < 4) ? d : 3;
}

float calcIR(float *f_arr, size_t f_size)
{
    size_t q1, q3, q2_lower, q2_upper, token;

    token = (f_size / 2 == 1) ? 0 : 1;

    q2_lower = (f_size / 2) - token;
    q2_upper = q2_lower + 1;

    q1 = q2_lower / 2;
    q3 = (q2_upper + f_size) / 2;

    return f_arr[q3] - f_arr[q1];
}

bool is_file(const char* path)
{
    struct stat buf{};
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

bool is_dir(const char* path)
{
    struct stat buf{};
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

void selectDimensions(std::string dims)
{
    std::cout << "Selected dimensions: " << dims << std::endl;

    size_t pos = 0;
    std::string delimiter = ",", token;
    DIMS = 0;

    while ((pos = dims.find(delimiter)) != std::string::npos)
    {
        token = dims.substr(0, pos);
        RANKS.push_back(atoi(token.c_str()) - 1);
        DIMS++;
        dims.erase(0, pos + delimiter.length());
    }

    RANKS.push_back(atoi(dims.c_str()) - 1);
    DIMS++;
}

