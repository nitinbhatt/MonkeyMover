//
//  main.cpp
//  MonkeyMover
//
//  Created by Bhatt, Nitin on 6/20/14.
//  Copyright (c) 2014 Bhatt, Nitin. All rights reserved.
//

#include <iostream>
#include "MonkeyMover.h"

#include <time.h>

int main(int argc, const char * argv[])
{
    MonkeyMover aMonkeyMover(19);
    time_t start;
    time_t end;
    
    time(&start);
    std::cout<<"\r\nResult = "<<aMonkeyMover.GetValidNeighborsCount();
    time(&end);
    
    std::cout<<"\r\nTime ["<<difftime(end, start)<<"] Seconds\r\n";
    
    //aMonkeyMover.Display();
}

