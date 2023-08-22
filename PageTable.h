#ifndef PageTable_H
#define PageTable_H
//*****************************************************************************
//
//  CSCI 480 - Assignment 5 - Spring 2021
//
//  Programmer: Daniel Widing (z1838064)
//  Section:    1
//  Date Due:   4/10/2021
//
//  File:       PageTable.h
//  Purpose:    Declares the PageTable class, which represents the page table
//              which contains the PageTableEntrys
//
//*****************************************************************************

#include <string>
#include <vector>
#include "PhysicalMemory.h"
#include "PageTableEntry.h"

using namespace std;

class PageTable
{
public:
    PageTable(PhysicalMemory* pmIn, int tableSize); //initialize all entries to invalid
    void reference(int pageID, string item);        //reference a logical page,  if not in memory,  call pageFault() 
    int getFaults() const;                          //return number of faults
    void printTable() const;                        //print the layout of page table
    void reset();                                   //reset the validity flag to false, and  numberoffaults  to 0.

private:
    vector<PageTableEntry> entryList;                        //the page table!
    int numFaults;
    PhysicalMemory* mainPhysicalMemory;
    void pageFault(int pageID, string item);                 //increment numFaults;  need to swap in the item into physical memory by calling the swapIn() of the PhysicalMemory class 
    void updateReplacedEntry(int replacedIndex, int pageID); //after page replacement, update the page table correspondingly by making the original mapping for the frame invalid
};

#endif
