#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <bitset>

#ifndef PRINTER_H
#define PRINTER_H

class Printer
{
public:
    std::vector<std::string> times;
    std::vector<std::string> page;
    std::vector<std::string> hit_miss;
    std::vector<std::string> frames;

    Printer()
    {
        times = {};
        page = {};
        frames = {};
        hit_miss = {};
    }

    void pushBackEmpty()
    {
        times.push_back("");
        page.push_back("");
        frames.push_back("");
        hit_miss.push_back("");
    }
    
    void printTiming()
    {
        for (int i = 0; i < times.size(); i++)
        {
            std::cout << std::setw(12) << std::left << times[i] << std::setw(12) << std::left << hit_miss[i] << std::setw(40) << std::left << page[i] << std::setw(20) << std::left << frames[i] << std::endl;
        }
    }
};
#endif //Timing Definition

#ifndef TIMING_H
#define TIMING_H

class Timing
{
public:
    int events;
    int diskWrites;
    int diskReads;
    int pageFaults;
    Timing()
    {
        events = 0;
        diskWrites = 0;
        diskReads = 0;
        pageFaults = 0;
    }
    void printOutput()
    {
        std::cout << std::setw(20) << std::left << "events in trace: " << std::setw(6) << std::left << events << std::endl;
        std::cout << std::setw(20) << std::left << "total disk reads: " << std::setw(6) << std::left << diskReads << std::endl;
        std::cout << std::setw(20) << std::left << "total disk writes: " << std::setw(6) << std::left << diskWrites << std::endl;
        std::cout << std::setw(20) << std::left << "page faults: " << std::setw(6) << std::left << pageFaults << std::endl;
    }
};
#endif //Timing Definition

#ifndef MEMORYITEM_H
#define MEMORYITEM_H

class MemoryItem
{
public:
    int memoryBit;
    std::string value;
    int age;
    int worked;
    std::string arbBits;
    std::string wsarbBits;
    MemoryItem(std::string valueIn)
    {
        value = valueIn;
        memoryBit = 0;
        age = 0;
        worked = 0;
        wsarbBits = "00000";
    }
    MemoryItem(std::string valueIn, int arbBitsIn)
    {
        value = valueIn;
        memoryBit = 0;
        age = 0;
        worked = 0;
        arbBits = "";
        wsarbBits = "00000";
        for (int i = 0; i < arbBitsIn; i++)
        {
            arbBits = arbBits + "0";
        }
    }
};
#endif //MemoryItem Definition
