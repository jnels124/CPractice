// This program will be used as a command line tool to compare two files passed as arguments,
// printing the lines where they differ.
//
//  main.c
//  CompareFiles
//
//  Created by Jesse Nelson on 2/3/13.
//  Copyright (c) 2013 Jesse Nelson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS_PER_LINE  1000            // Max number of characters for a line being read
#define MAX_DIFFERENCES_TO_TRACK  5000

void compareFiles ( FILE *file1, FILE *file2 );

int main ( int argc,
           const char * argv[]
         ) {
    
    FILE *file1,
         *file2;
    
    // There has to be three arguments. program name, first file, second file
    if ( argc != 3 ) {
        fprintf ( stderr,
                  "compare: Two files are "
                  "needed as arguments\n"
                );
        
        exit ( 1 );
    }
    
    else {
        
        if ( ( file1 = fopen ( *++argv, "r" ) ) == NULL ) {
            fprintf ( stderr,
                      "compare: Can't open file %s.\n"
                      "Please verify correct info entered",
                      *argv
                    );
            
            exit ( 1 );
        }
        
        else if ( ( file2 = fopen ( *++argv, "r" ) ) == NULL ) {
            fprintf ( stderr,
                      "compare: Can't open file %s."
                      "\nPlease verify correct info entered",
                      *argv
                    );
            
            exit ( 1 );
        }
        
        else {
            compareFiles ( file1,
                           file2
                         );
            
            // Close file streams
            fclose ( file1 );
            fclose ( file2 );
            exit ( 0 );
        }
    }
}

void compareFiles ( FILE *file1,
                    FILE *file2
                  ) {
    
    FILE *outFile = fopen ( "differencesOutput", "w" );
    
    int  lineCTR = 1,
         differencesCTR = 0;
    
    char *differences [MAX_DIFFERENCES_TO_TRACK];           // Array of character pointers
    
    
    char line1[MAX_CHARS_PER_LINE],
         line2[MAX_CHARS_PER_LINE];
    
    char *line1Pointer,
         *line2Pointer;
    
    do {
        line1Pointer = fgets ( line1,
                               MAX_CHARS_PER_LINE,
                               file1
                             );
        
        line2Pointer = fgets ( line2,
                               MAX_CHARS_PER_LINE,
                               file2
                             );
        
        if ( line1Pointer == line1 && line2Pointer == line2 ) {
            
            if ( strcmp ( line1, line2 ) != 0 ) {
                differences[differencesCTR] =
                malloc ( MAX_CHARS_PER_LINE );                 // Allocate space on the heap
                
                sprintf ( differences[differencesCTR],
                          "Line: #%d\nLine in file 1: %s"
                          "Line in file 2: %s\n",
                          lineCTR,
                          line1,
                          line2
                        );
                
                printf ( "%s\n", differences[differencesCTR] ); // Display difference to stdout
		        fputs ( differences[differencesCTR], outFile ); // Write difference to file
                
                differencesCTR++;
            }
            
            else if ( line1Pointer != line1 && line2Pointer == line2 ) {
                printf ( "end of first file at line:\n%s\n",
                         line2
                       );
            }
            
            else if ( line1Pointer == line1 && line2Pointer != line2 ) {
                printf ( "end of second file at line:\n%s\n",
                         line1
                       );
            }
        }
        
        lineCTR++;
        
    } while ( line1Pointer == line1 && line2Pointer == line2 );
    
}
