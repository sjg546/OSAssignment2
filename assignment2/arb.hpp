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

void ARB(std::vector<std::string> traces, int pageSize, int pagecount, int shiftbitnumber, int length)
{
    Timing *timer = new Timing();
    int count = 0;

    Printer *printer = new Printer();
    std::vector<MemoryItem *> memory;

    int curr = 0;
    int i = 0;
    int recTime = 1;

    while (i < traces.size())
    {
        if ((recTime - 1) % (length) == 0)
        {
            Utilities::shiftBits(memory);
        }

        std::string temp = traces[i];
        std::string value = Utilities::hexConverter(temp.erase(0, 2), pageSize);

        if (traces[i][0] != '#')
        {
            printer->pushBackEmpty();
            curr = printer->times.size() - 1;
            // std::cout<<curr<<std::endl;
            timer->events++;
            printer->times[curr] = "Time:  " + std::to_string(recTime);
            recTime++;

            if (Utilities::checkIsInMemory(memory, pagecount, value) == -1)
            {
                timer->diskReads++;
                timer->pageFaults++;
                printer->hit_miss[curr] = " MISS:  ";
            }
            else
            {
                printer->hit_miss[curr] = " HIT:  ";
            }
            printer->page[curr] = printer->page[curr] + "page   " + value;
            MemoryItem *tempMemoryItem = new MemoryItem(value, shiftbitnumber);

            tempMemoryItem->arbBits[0] = '1';

            if (memory.size() < pagecount)
            {
                if (Utilities::checkIsInMemory(memory, pagecount, traces[i]) == -1)
                {
                    if (traces[i][0] == 'W')
                    {
                        tempMemoryItem->memoryBit = 1;
                    }
                    memory.push_back(tempMemoryItem);
                }
            }
            else
            {
                int inMemory = Utilities::checkIsInMemory(memory, pagecount, tempMemoryItem->value);
                if (inMemory != -1)
                {
                    memory[inMemory]->arbBits[0] = '1';
                    if (traces[i][0] == 'W')
                    {
                        memory[inMemory]->memoryBit = 1;
                    }
                }
                else
                {

                    int oldestItem = Utilities::arbReplacementFind(memory);

                    printer->page[curr] = printer->page[curr] + "    REPLACE:  page  " + memory[oldestItem]->value;
                    if (traces[i][0] == 'W')
                    {
                        tempMemoryItem->memoryBit = 1;
                    }
                    if (memory[oldestItem]->memoryBit == 1)
                    {
                        timer->diskWrites++;
                        printer->page[curr] = printer->page[curr] + " (DIRTY)";
                    }
                    memory[oldestItem] = tempMemoryItem;
                }
            }
            printer->frames[curr] = " Frames: ";

            for (int j = 0; j < memory.size(); j++)
            {
                printer->frames[curr] = printer->frames[curr] + " " + memory[j]->value + " " + "(" + memory[j]->arbBits + ")";
            }
            Utilities::incrementAge(memory);
        }
        else
        {
        }
        i++;
    }
    printer->printTiming();
    // timer->printOutput();
}
