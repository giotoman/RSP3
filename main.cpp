#include <iostream>

#include "rsp3/CrossValidator.h"
#include "rsp3/DataHandler.h"

void handleArgs(int argc, char *argv[])
{
    if (argc == 1) { std::cout << "No arguments found." << std::endl; exit(EXIT_FAILURE); }

    CrossValidator cv;
    e_MDF func = e_convert(argv[2]);

    if (is_file(argv[1]))
    {
        if(argc > 4)
        {
            std::string str(argv[4]);

            DO_NORM = str.find('N') != std::string::npos;
            DO_IRR = str.find("IRR") != std::string::npos;
        }
        else
        {
            DO_NORM = false;
            DO_IRR = false;
        }

        if (argc == 6) { selectDimensions(argv[5]); DO_SELECT = true; }

        cv.createCV(argv[1], atoi(argv[3]), func);
    }
    else if (is_dir(argv[1]))
    {
        if(argc > 3)
        {
            std::string str(argv[3]);

            DO_NORM = str.find('N') != std::string::npos;
            DO_IRR = str.find("IRR") != std::string::npos;
        }
        else
        {
            DO_NORM = false;
            DO_IRR = false;
        }

        if (argc == 5) { selectDimensions(argv[4]); DO_SELECT = true; }

        cv.loadCV(argv[1], func);
    }
    else std::cout << "Path error." << std::endl;

}

int main(int argc, char *argv[])
{
    handleArgs(argc, argv);

    return 0;
}

