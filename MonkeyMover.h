//
//  MonkeyMover.h
//  MonkeyMover
//
//  Created by Bhatt, Nitin on 6/20/14.
//  Copyright (c) 2014 Bhatt, Nitin. All rights reserved.
//

#ifndef MonkeyMover_MonkeyMover_h
#define MonkeyMover_MonkeyMover_h

#include <iostream>
#include <set>

class Cell
{
public:
    
    Cell(int a, int b)
    : x(a)
    , y(b) {}

    int x;
    int y;
};

class CellComparator
{
public:
    bool operator()(const Cell& lhs, const Cell& rhs) const
    {
        if (lhs.x != rhs.x)
            return lhs.x < rhs.x;
        return lhs.y < rhs.y;
    }
};

// Main class for handling Monkey's movement
class MonkeyMover
{
public:
    // Default constructor
    MonkeyMover()
    : mMaxSum(19)
    , mInitialX(0)
    , mInitialY(0)
    {
        Init();
    }
    
    // Constructor for specifying distance
    // for validity of cell, start will be 0,0
    MonkeyMover(unsigned int dist)
    : mMaxSum(dist)
    , mInitialX(0)
    , mInitialY(0)
    {
        Init();
    }
    
    // Constructore to configure distance and initial
    // coordinates
    MonkeyMover(unsigned int dist,
                int x,
                int y)
    : mMaxSum(dist)
    , mInitialX(x)
    , mInitialY(y)
    {
        Init();
    }
    
    ~MonkeyMover() {}
    
    // Display all the cell that the monkey
    // can visit
    void Display()
    {
        std::cout<<"\r\n";
        std::set<Cell, CellComparator>::iterator itr = mCells.begin();
        while (itr != mCells.end())
        {
            Cell aCell = *itr;
            std::cout<<"\r\n["<<aCell.x<<"]["<<aCell.y<<"]";
            ++itr;
        }
        std::cout<<"\r\n";
    }
    
    // Get count of cells monkey can visit based on
    // distance and start coordinates specified in
    // constructor.
    size_t GetValidNeighborsCount()
    {
        mCells.clear();
        mCells.insert(Cell(mInitialX, mInitialY));
        mNewNeighbors.clear();
        mNewNeighbors.insert(Cell(mInitialX, mInitialY));

        while(true)
        {
            AddAllValidNeighbors();
   
            if (mNewNeighbors.size() == 0)
            {
                break;
            }
        }
        
        return mCells.size();
    }
    
private:
    void Init()
    {
        mCells.clear();
        mNewNeighbors.clear();
    }

    // Add all valid neighbors to mCells
    void AddAllValidNeighbors()
    {
        std::set<Cell, CellComparator> neighbors;
        
        std::set<Cell, CellComparator>::iterator itr = mNewNeighbors.begin();
        while (itr != mNewNeighbors.end())
        {
            Cell aCell = static_cast<Cell>(*itr);
            
            if (IsValidCell(Cell(aCell.x+1, aCell.y)))
            {
                neighbors.insert(Cell(aCell.x+1, aCell.y));
            }
            
            if (IsValidCell(Cell(aCell.x-1, aCell.y)))
            {
                neighbors.insert(Cell(aCell.x-1, aCell.y));
            }
            
            if (IsValidCell(Cell(aCell.x, aCell.y+1)))
            {
                neighbors.insert(Cell(aCell.x, aCell.y+1));
            }
            
            if (IsValidCell(Cell(aCell.x, aCell.y-1)))
            {
                neighbors.insert(Cell(aCell.x, aCell.y-1));
            }

            ++itr;
        }
        
        mNewNeighbors.clear();
        itr = neighbors.begin();
        
        while(itr != neighbors.end())
        {
            mInsertResult = mCells.insert(static_cast<Cell>(*itr));
            if (mInsertResult.second)
            {
                mNewNeighbors.insert(static_cast<Cell>(*itr));
            }
            ++itr;
        }
    }

    bool IsValidCell(const Cell& aCell)
    {
        return (GetSumOfDigits(aCell.x) + GetSumOfDigits(aCell.y) <= mMaxSum);
    }

    unsigned int GetSumOfDigits(int num)
    {
        unsigned int retVal = 0;
        
        num = abs(num);
        while (num > 0)
        {
            retVal += num%10;
            num = num/10;
        }
        
        return retVal;
    }
    
    unsigned int mMaxSum;
    int mInitialX;
    int mInitialY;
    
    std::set<Cell, CellComparator> mCells;
    std::set<Cell, CellComparator> mNewNeighbors;
    std::pair<std::set<Cell, CellComparator>::iterator, bool> mInsertResult;
};


#endif
