//
//  BinarySearch.c
//  SearchNSort
//
//  Created by Jesse Nelson on 2/7/13.
//  Copyright (c) 2013 Jesse Nelson. All rights reserved.
//

#include <stdio.h>

int binarySearch ( int values[],
                  int searchItem,
                  int       high,
                  int        low ) {
    
    
    int mid = ( high + low ) / 2;
    
    if ( searchItem == values[mid] ) {
        
        return mid;
    }
    
    if ( low > high ) {  // Not found
        
        return -1;
    }
    
    return searchItem > values[mid] ?
    
    binarySearch ( values, searchItem, high, mid + 1 )
    :
    binarySearch ( values, searchItem, mid - 1, low );
    
}