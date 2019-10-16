#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "helperClasses.hpp"

#ifndef UTILITIES_H
#define UTILITIES_H

class Utilities
{
    public:

    /**
     * Converts a hexidecimal value to decimal (base 10).
     * 
     * @param   std::string in
     * @param   int pagesize
     * 
     * @return  std::string
     */
    static std::string hexConverter(std::string in, int pagesize)
    {
        int y;
        std::stringstream stream;

        stream << in;
        stream >> std::hex >> y;

        return std::to_string(y / pagesize);
    }

    /**
     * Increment the age of the memory vector provided.
     * 
     * @param   std::vector<MemoryItem *> memory
     * 
     * @return  void
     */
    static void incrementAge(std::vector<MemoryItem *> memory)
    {
        for (int i = 0; i < memory.size(); i++)
        {
            memory[i]->age++;
        }
    }

    /**
     * Increment the WSARB bits.
     * 
     * @param   std::vector<MemoryItem *> memory
     * 
     * @return  void
     */
    static void incrementWorked(std::vector<MemoryItem *> memory)
    {
        for (int i = 0; i < memory.size(); i++)
        {
            memory[i]->worked++;
        }
    }

    /**
     * Find the oldest memory item in the vector.
     * 
     * @param   std::vector<MemoryItem *> memory
     * 
     * @return  int
     */
    static int getOldest(std::vector<MemoryItem *> memory)
    {
        int max = 0;
        int ret = 0;

        for (int i = 0; i < memory.size(); i++)
        {
            if (memory[i]->age > max)
            {
                max = memory[i]->age;
                ret = i;
            }
        }

        return ret;
    }

    /**
     * Find the oldest memory item that has been worked on.
     * 
     * @param   std::vector<MemoryItem *>
     * 
     * @return  int
     */
    static int getOldestWorked(std::vector<MemoryItem *> memory)
    {
        int max = 0;
        int ret = 0;
        for (int i = 0; i < memory.size(); i++)
        {
            if (memory[i]->worked > max)
            {
                max = memory[i]->worked;
                ret = i;
            }
        }
        return ret;
    }

    /**
     * Find a specific page size in the specified memory.
     * 
     * @param   std::vector<MemoryItem *> memory
     * @param   int pageSize
     * @param   std::string trace
     * 
     * @return  int
     */
    static int checkIsInMemory(std::vector<MemoryItem *> memory, int pageSize, std::string trace)
    {
        for (int i = 0; i < memory.size(); i++)
        {
            if (memory[i]->value == trace)
            {
                return i;
            }
        }
        return -1;
    }

    /**
     * Shift all of the bits in memory to the right by 1 spot.
     * 
     * @param   std::vector<MemoryItem *> memory
     * 
     * @return  void
     */
    static void shiftBits(std::vector<MemoryItem *> memory)
    {
        for (int i = 0; i < memory.size(); i++)
        {
            for (int j = memory[0]->arbBits.size() - 1; j > 0; j--)
            {
                memory[i]->arbBits[j] = memory[i]->arbBits[j - 1];
            }
            memory[i]->arbBits[0] = '0';
        }
    }

    /**
     * Shift the bits to the right in accordance to the WSARB algorithm.
     * 
     * @param   std::vector<MemoryItem *> memory
     * 
     * @return  void
     */
    static void wsarbShiftBits(std::vector<MemoryItem *> memory)
    {
        for (int i = 0; i < memory.size(); i++)
        {
            for (int j = memory[0]->wsarbBits.size() - 1; j > 0; j--)
            {
                memory[i]->wsarbBits[j] = memory[i]->wsarbBits[j - 1];
            }
            memory[i]->wsarbBits[0] = '0';
        }
    }

    /**
     * Replace memory in accordance to the ARB algorithm.
     * 
     * @param   std::vector<MemoryItem *> memory
     * 
     * @return  int
     */
    static int arbReplacementFind(std::vector<MemoryItem *> memory)
    {
        std::vector<int> references = {};
        std::vector<MemoryItem *> item;

        unsigned long long int min = 1000000000000000;
        unsigned long long output;

        for (int i = 0; i < memory.size(); i++)
        {
            output = std::stoull(memory[i]->arbBits, 0, 2);
            // std::cerr<<output<<" ";

            if (output < min)
            {
                min = output;
                item.clear();
                references.clear();
                item.push_back(memory[i]);
                references.push_back(i);
            }
            else if (output == min)
            {
                item.push_back(memory[i]);
                references.push_back(i);
            }
        }

        if (references.size() == 1)
        {
            return references[0];
        }
        else
        {
            int oldref = 0;
            int oldest = 0;
            for (int i = 0; i < item.size(); i++)
            {
                if (memory[references[i]]->age > oldest)
                {
                    oldest = memory[references[i]]->age;
                    oldref = references[i];
                }
            }
            return oldref;
        }
    }

    /**
     * Replace memory in accordance to the WSARB algorithm.
     * 
     * @param   std::vector<MemoryItem *> memory
     * @param   std::vector<MemoryItem *> workingset
     * 
     * @return  int
     */
    static int wsarbReplacementFind(std::vector<MemoryItem *> memory, std::vector<MemoryItem *> workingset)
    {
        std::cout << "hit";

        for (int i = 0; i < workingset.size(); i++)
        {
            std::cout << workingset[i]->value << " " << workingset[i]->wsarbBits << " ";
        }

        std::cout << std::endl;

        return 1;
    }
};

#endif
