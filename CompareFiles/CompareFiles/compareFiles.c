//
//  This program will receive two files as paramaters and compare
//    the files against eachother line by line displaying the
//    differences to stdout and also writing the same text to a
//    file named differencesOutput.
//
//  Pointers are stored in an array to implement features
//    not shared in this submission.
//
//  Existing bugs:
//      -Error checking against the maxline in fgets is not done
//      -Nothing is done at the moment to notify user if files
//          have the same content. Currently it will cause
//          a the code in the first if block to execute
//
//
//  compareFiles.c
//  CompareFiles
//
//  Created by Jesse Nelson on 2/10/13.
//  Copyright (c) 2013 Jesse Nelson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_CHARS_PER_LINE  1000 
#define MAX_DIFFERENCES_TO_TRACK  10000

void compareFiles ( FILE *file1,
                    FILE *file2
                  ) {
    
    FILE *outFile = fopen ( "differencesOutput", "w" );
    
    int  lineCTR = 1,
         differencesCTR = 0; // Used as indexer for *differences
    
    char *differences [MAX_DIFFERENCES_TO_TRACK]; // Array of character pointers
    
    char line1[MAX_CHARS_PER_LINE], // Holds line of input from file1
         line2[MAX_CHARS_PER_LINE]; // Holds line of input from file2
    
    char *line1Pointer,
         *line2Pointer;

    do { 
        line1Pointer = fgets ( line1,
                               MAX_CHARS_PER_LINE,
                               file1
                             ); // retuns null if error occured or at end
        
        line2Pointer = fgets ( line2,
                               MAX_CHARS_PER_LINE,
                               file2
                             ); // retuns null if error occured or at end
        
        
        if ( line1Pointer == NULL ) {
            differences[differencesCTR] =
            malloc ( MAX_CHARS_PER_LINE ); // Allocate space on the heap

            sprintf ( differences[differencesCTR],
                      "\n\nFILE ONE ENDED BEFORE FILE TWO"
                      " AT LINE %d\n",
                      lineCTR - 1
                    ); // Store formatted string
            
            printf ( "\n\nFILE ONE ENDED BEFORE FILE TWO"
                     " AT LINE %d\n",
                     lineCTR - 1
                   );
            
            fputs ( differences[differencesCTR],
                    outFile
                  ); // Write difference to file
            
            break; // Exit infinite loop
        }
        
        if ( line2Pointer == NULL ) {
            differences[differencesCTR] =
            malloc ( MAX_CHARS_PER_LINE ); // Allocate space on the heap
            
            sprintf ( differences[differencesCTR],
                      "\n\nFILE TWO ENDED BEFORE FILE ONE"
                      " AT LINE %d\n",
                      lineCTR - 1
                    ); // Store formatted string
            
            printf ( "\n\nFILE TWO ENDED BEFORE FILE ONE"
                     " AT LINE %d\n",
                     lineCTR - 1
                   );
            
            fputs ( differences[differencesCTR],
                    outFile
                  ); // Write difference to file
            
            break; // Exit infinite loop
        }
        
        if ( differencesCTR > MAX_DIFFERENCES_TO_TRACK ) {
            printf ( "!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!"
                     "\nThere are more than %d lines with "
                     "differences between the files provided."
                     "This program is not set up to handle"
                     " this situation.\n",
                     MAX_DIFFERENCES_TO_TRACK
                   );
            
            break; // Exit infinite loop
        }
        
        else if ( strcmp ( line1, line2 ) != 0 ) {
            differences[differencesCTR] =
            malloc ( MAX_CHARS_PER_LINE ); // Allocate space on the heap
            
            sprintf ( differences[differencesCTR],
                      "Line: #%d\nLine in file 1: %s"
                      "Line in file 2: %s\n",
                      lineCTR,
                      line1,
                      line2
                    ); // Store formatted string
            
            printf ( "%s\n",
                     differences[differencesCTR]
                   ); // Display difference to stdout
            
            fputs ( differences[differencesCTR],
                    outFile
                  ); // Write difference to file
            
            differencesCTR++;
        }
        
        lineCTR++;
        
    } while ( 1 == 1 ); // Infinite loop
    
    fclose ( outFile ); // Close stream
    
}