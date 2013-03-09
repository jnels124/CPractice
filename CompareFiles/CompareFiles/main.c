//
// This program will be used as the driver for
//   a command line tool that compares two files
//   passed as arguments, printing the lines where they differ.
//
// Additional features will be added to manipulate the files,
//   beyond dispaying differences, at a later date.
//
//
//  main.c
//  CompareFiles
//
//  Execution:
//    From command line, while in project directory, type:
//    make
//    make run ( make must be installed on your machine! )
//    make clean ( removes output files ) 
//    or
//    gcc main.c compareFiles.c then,
//    ./a.out file1, file2
//
//  Created by Jesse Nelson on 2/3/13.
//  Copyright (c) 2013 Jesse Nelson. All rights reserved.
//
//  Hosted at https://github.com/jnels124/CPractice
//

#include <stdio.h>
#include <stdlib.h>


void compareFiles ( FILE *file1,
                    FILE *file2
                  );

int main ( int argc,
           const char * argv [ ]
         ) {
    
    FILE *file1,
         *file2;
    
    // There has to be three arguments.
    // program name, first file, second file
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
