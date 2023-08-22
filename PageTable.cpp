//*****************************************************************************
//
//  CSCI 480 - Assignment 5 - Spring 2021
//
//  Programmer: Daniel Widing (z1838064)
//  Section:    1
//  Date Due:   4/10/2021
//
//  File:       PageTable.cpp
//  Purpose:    Implements the methods for the PageTable class
//
//*****************************************************************************

#include <iostream>
#include "PageTable.h"

using namespace std;

/**
 * Creates a new PageTable
 *
 * @param      pmIn: pointer to the PhysicalMemory 
 * @param tableSize: size of page table
 **/
PageTable::PageTable(PhysicalMemory* pmIn, int tableSize)
{
	//Creates new invalid entries and puts them in the PageTable
	entryList = vector<PageTableEntry>(tableSize, { false, -1 });

	numFaults = 0;
	mainPhysicalMemory = pmIn;
}

/**
 * Attempts to access the page requested if it is valid, creativing a fault
 * and swaping in the given item if it is not
 *
 * @param pageID: the index of the page entry
 * @param   item: the item to be referenced
 **/
void PageTable::reference(int pageID, string item)
{
	//Checks if ID exists
	if (entryList.size() > (unsigned)pageID)
	{
		//Checks if page with pageID is valid
		if (entryList[pageID].valid == true)
		{
			//Accesses the page in physical memory
			mainPhysicalMemory->access(entryList[pageID].physicalMemoryIndex);
		}

		//If page invalid, creates a page fault and swaps in the item
		else
		{
			pageFault(pageID, item);
		}
	}
}

/**
 * Returns number of faults
 *
 * @returns int: number of faults
 **/
int PageTable::getFaults() const
{
	return numFaults;
}

/**
 * Prints the layout of the page table
 **/
void PageTable::printTable() const
{
	//Prints info for each page in the table
	for (unsigned i = 0; i < entryList.size(); i++)
	{
		cout << "PageTable: Index: " << i << " : Physical Index: " << entryList[i].physicalMemoryIndex << " : In Use: ";
		
		//Converts bool to string
		if (entryList[i].valid)
		{
			cout << "true" << endl;
		}

		else
		{
			cout << "false" << endl;
		}
	}
	
	//Prints page fault count
	cout << "PageTable: Current number of page faults: " << numFaults << endl;
}

/**
 * Resets all pages to invalid and sets faults to 0
 **/
void PageTable::reset()
{
	//Sets all pages to invalid
	for (unsigned i = 0; i < entryList.size(); i++)
	{
		entryList[i].valid = false;
	}

	numFaults = 0;
}

/**
 * Increments the numFaults and calls swapIn() of the PhysicalMemory to swap in the page 
 *
 * @param pageID: faulting page index
 * @paran   item: item to be put into physical memory
 **/
void PageTable::pageFault(int pageID, string item)
{
	cout << "PageTable: page fault occurred" << endl;
	numFaults += 1;
	int newFrameID = mainPhysicalMemory->swapIn(item);

	updateReplacedEntry(newFrameID, pageID);
}

/**
 * Puts frame index in page with ID
 *
 * @param replacedIndex: index of frame
 * @param        pageID: index of page to put frame in
 **/
void PageTable::updateReplacedEntry(int replacedIndex, int pageID)
{
	//Finds page that was linked to frame to make invalid
	for (int i = 0; (unsigned)i < entryList.size(); i++)
	{
		if (entryList[i].physicalMemoryIndex == replacedIndex)
		{
			entryList[i].physicalMemoryIndex = -1;
			entryList[i].valid = false;
		}
	}

	//Makes page that is now linked to frame valid
	entryList[pageID].physicalMemoryIndex = replacedIndex;
	entryList[pageID].valid = true;
}
