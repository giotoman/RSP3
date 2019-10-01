#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <string>

extern std::string DELIMETER;

size_t parse_import(const std::string& path);
void insertPoint(const std::string& data_line);
void normalize();
void irr();
float calcIR(float *f_arr, size_t s);
bool is_file(const char* path);
bool is_dir(const char* path);
void selectDimensions(std::string dims);

#endif // DATAHANDLER_H
