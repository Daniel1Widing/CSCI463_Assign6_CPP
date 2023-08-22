//*****************************************************************************
//
//  CSCI 480 - Assignment 5 - Spring 2021
//
//  Programmer: Daniel Widing (z1838064)
//  Section:    1
//  Date Due:   4/10/2021
//
//  File:       PhysicalMemory.cpp
//  Purpose:    Implements the methods for the PhysicalMemory class
//
//*****************************************************************************

#include <iostream>
#include "PhysicalMemory.h"

/**
 * Initilizes the PhysicalMemory elements and data
 * 
 * @param  memorySize: size of phyical memory
 * @oaran algorithmIn: algoithm to use
 **/
PhysicalMemory::PhysicalMemory(int memorySize, int algorithmIn)
{
	//Creates empty phyiscal memory of given size
	memoryList = vector<string>(memorySize, "");

	//Creates an empty time list for the physical memory
	timeList = vector<int>(memorySize, 0);
	
	currentTimeIndex = 0;
	algorithmFlag = algorithmIn;
}

/**
 * Accesses data in passed frame ID and then updates time stamp and list
 *
 * @param frameID: frame ID of frame to access
 **/
void PhysicalMemory::access(int frameID)
{
	cout << "Physical: Accessed frameID: " << frameID << " contains: " << memoryList[frameID] << endl;
	currentTimeIndex += 1;

	//Updates time list if using LRU
	if (algorithmFlag == 0)
	{
		timeList[frameID] = currentTimeIndex;
	}
}

/**
 * Prints data in physical memory
 **/
void PhysicalMemory::printMemory() const
{
	//Prints contents of each frame in memory
	for (unsigned i = 0; i < memoryList.size(); i++)
	{
		cout << "Physical: Memory Frame: " << i << " contains: " << memoryList[i] << endl;
	}
}

/**
 * Puts data into the next available frame and then updates time stamp and list
 *
 * @param item: data to put in next available frame
 * 
 * @returns int: ID of frame swapped into
 **/
int PhysicalMemory::swapIn(string item)
{
	//Gets available frame
	int newID = getNextAvailableFrame();
	
	//Puts item into frame
	memoryList[newID] = item;
	cout << "Physical: Stored: " << item << endl;
	
	//Updates time stamp and list
	currentTimeIndex += 1;
	timeList[newID] = currentTimeIndex;

	//Returns frame ID
	return newID;
}

/**
 * Gets the ID of the next frame to store info in when there is a page fault
 *
 * @returns int: ID of next available frame
 **/
int PhysicalMemory::getNextAvailableFrame()
{
	//Finds victim frame when memory is full
	if (isFull())
	{
		//Victim is frame with lowest timeList number for both FIFO and LRU
		int lowestTime = 0;
		int lowestID = 0;

		for (unsigned i = 0; i < timeList.size(); i++)
		{
			if (lowestTime == 0 || timeList[i] < lowestTime)
			{
				lowestTime = timeList[i];
				lowestID = i;
			}
		}

		return lowestID;
	}
	
	//Finds first empty frame if memory not full
	else
	{
		//Chcks frames in order
		for (unsigned i = 0; i < timeList.size(); i++)
		{
			//Returns ID of empty frame
			if (timeList[i] == 0)
			{
				return i;
			}
		}
	}

	return 0;
}

/**
 * Returns if the memory is full or empty
 *
 * @returns  true: memory full
 *			false: memory empty
 **/
bool PhysicalMemory::isFull()
{
	//Checks all frames in memory to see if any are empty
	for (unsigned i = 0; i < timeList.size(); i++)
	{
		//Returns true if any frame is empty
		if (timeList[i] == 0)
		{
			return false;
		}
	}

	//Returns true if no frames are empty
	return true;
}