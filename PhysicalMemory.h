#ifndef PhysicalMemory_H
#define PhysicalMemory_H
//*****************************************************************************
//
//  CSCI 480 - Assignment 5 - Spring 2021
//
//  Programmer: Daniel Widing (z1838064)
//  Section:    1
//  Date Due:   4/10/2021
//
//  File:       PhysicalMemory.h
//  Purpose:    Declares the PhysicalMemory class, which works with the PageTable
//              class to make up the simulated memory
//
//*****************************************************************************

#include <string>
#include <vector>

using namespace std;

class PhysicalMemory
{
public:
    PhysicalMemory(int memorySize, int algorithmIn); //Initialize all the data and data structure in the class (e.g. set clock to 0). 
                                                     //The second argument is for testing different page replacement algorithms if you will implement the bonus credits for LRU.
    void access(int frameID);                        //access the frame, update the time stamp and time list 
    void printMemory() const;                        //print out the physical memory layout
    int swapIn(string item);                         //returns the frame ID of the item just swapped in

private:
    vector <string> memoryList;  //The physical memory!
    vector <int> timeList;       //data structure for the replacement algorithm
    int currentTimeIndex;        //current clock for timestamp
    int algorithmFlag;           //indicate if using FIFO or LRU
    int getNextAvailableFrame(); //get a frame, either available or via replacement
    bool isFull();               //check if the memory is full
};

#endif
