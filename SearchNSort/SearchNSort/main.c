//
//  main.c
//  SearchNSort
//
//  Created by Jesse Nelson on 2/7/13.
//  Copyright (c) 2013 Jesse Nelson. All rights reserved.
//

#include <stdio.h>

int binarySearch(int someValues[], int searchingFor, int high, int low);

int main(int argc, const char * argv[]) {
    
    int val[] = {5, 10, 15, 20, 25, 27,
                30, 50, 100, 150, 200, 899, 900  };
    
    int returnValue = binarySearch(val, 899, 12, 0);
    
    if ( returnValue != -1 ) {
        printf ("Found it at %d ", returnValue);
    }
    
    else {
        printf ("Unable to find item.");
    }
   
}

