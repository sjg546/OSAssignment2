#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <bitset>

#include "helperClasses.hpp"
#include "Utilities.hpp"

#include "fifo.hpp"
#include "wsarb.hpp"
#include "lru.hpp"
#include "arb.hpp"

int main(int argc, char *argv[])
{
    std::vector<std::string> traces = {};
    std::string str;
    std::ifstream in(argv[1]);

    while (std::getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if (str.size() > 0)
            traces.push_back(str);
    }
    //Close The File
    in.close();

    int pagesize = atoi(argv[2]);
    int pagecount = atoi(argv[3]);
    std::string method = argv[4];
    int a = 3;

    if (method == "FIFO")
    {
        FIFO(traces, pagecount, pagesize);
    }
    else if (method == "WSARB")
    {
        int shiftbitnumber = atoi(argv[5]);
        int length = atoi(argv[6]);
        int size = atoi(argv[7]);
        
        WSARB(traces, pagesize, pagecount, shiftbitnumber, length, size);
    }
    else if (method == "ARB")
    {
        int shiftbitnumber = atoi(argv[5]);
        int length = atoi(argv[6]);

        ARB(traces, pagesize, pagecount, shiftbitnumber, length);
    }
    else if (method == "LRU")
    {
        LRU(traces, pagecount, pagesize);
    }

    return 1;
}
