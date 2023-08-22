#ifndef PageTableEntry_H
#define PageTableEntry_H
//*****************************************************************************
//
//  CSCI 480 - Assignment 5 - Spring 2021
//
//  Programmer: Daniel Widing (z1838064)
//  Section:    1
//  Date Due:   4/10/2021
//
//  File:       PageTableEntry.h
//  Purpose:    Declares the PageTableEntry struct, which represents the 
//				entries in the PageTable
//
//*****************************************************************************

struct PageTableEntry
{
	bool valid;
	int physicalMemoryIndex;
};

#endif