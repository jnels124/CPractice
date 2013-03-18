//
//  This program currently takes information from the user
//    to create a card object and store it in a binary tree.
//
//  Later implementations will process command line arguments
//    to specify action to perform such as insert, search,
//    remove, create new, readfrom file, read serialized tree
//       etc..
//
//  To do:
//    Implement serilization so trees can be stored to disk
//    Implement deserialiation so obects can be read from disk
//
//    Currently, all data entered by the user is lost after program
//    terminates. This data needs to be serialized for later use!
//
//    Also, error checking is minimal, if existent at all, in most places
//
//    process command line options
//    implement a delete function to remove cards no longer owned
//
//  main.c
//  BinaryTree
//
//  Created by Jesse Nelson on 3/1/13.
//  Copyright (c) 2013 Jesse Nelson. All rights reserved.
//
//  Hosted at https://github.com/jnels124/CPractice

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "CardNodes.h"
#define MAX_CHARS_PER_LINE 300

static FILE *outFile;
void printCard ( struct card * );
char *getTypeFromFile ( FILE * );
char *getPlayerFromFile ( FILE * );
char *getBrandFromFile ( FILE * );
int getYearFromFile ( FILE * );
int getSeriesNumberFromFile ( FILE * );
double getValueFromFile ( FILE * );
int main( int argc,
          char * argv[ ] ){

    struct cardNode *root = NULL;
    //( struct cardNode * ) malloc ( sizeof ( struct cardNode ) );
    struct card *tmpCard = NULL;
    int optionChar, fFlag = 0;


/***IGNORE THIS SECTION OF CODE IT IS THE START OF ANOTHER VERSION***
 *  fputs ( "Type in the year of card and hit enter.\n", stdout);
 *   scanf ( "%d", &seriesNumber );
 *  "Type: %s "
 *   "Series number: %d "
 *   "Year: %d "
 *   "Brand: %s "
 *   "Player: %s "
 *   "Value: $%f\n"
 *
 *  
 *
 *  int optionChar;
 *
 *
 *   * I am currently only accepting option but getopt is
 *   *   used because feature implementations will process
     *   multiple options
     *
     * Currently passing multiple options at run time
     * is likely to produce unexpected results.
     * You can only pass the s (search) option if f is
     * passed first-> Error checking isn't written yet 
     *
     */
    while ( ( optionChar = getopt ( argc,
                                    argv,
                                    "fsS" ) ) != -1 ) {
        switch ( optionChar ) {
            case 'f':  // Create tree from file
                fFlag = 1;
                printf ( "The file name is %s", argv[2]);
                root = createTree ( fopen ( "/Users/jessenelson/Documents/CodeReading/CPractice/BinaryTree/BinaryTree/CardCollection.txt", "r" ),
                                    root
                                  );
                //printf ( "root type: %s", root->item->type );
                
                break;
            
            case 's': 
                if ( fFlag ) {
                    printSearch ( searchByPlayer( root, argv[3] ) );
                }
                break;
                
            case '?': default: // invalid option
                usage ();
                //saveData ( root, "CardCollection.txt" );
        }
    }
    // Add additonal cards if userWishes
    while ( 1 == 1 ) {
        char *input = ( char * ) malloc ( 1000 );
        fputs ( "Would you like to enter another card? yes or no\n", stdout );
        fflush ( stdout );
        fgets ( input, 100, stdin );
        
        if ( strcmp ( "yes\n", input ) != 0 ) {
            
            break; // exit infinite loop
            
        }
        
        tmpCard = createNewCard( tmpCard );
        root = createNewCardNode( root, tmpCard, 'p' );
        
        clearBuffer ( );
        
    } // end while*/
    if (root == NULL ) {
        printf ("root is fucking null");
    }
    printCollection(root);
    outFile = saveData ( root, fopen ( "/Users/jessenelson/Documents/CodeReading/CPractice/BinaryTree/BinaryTree/CardCollection.txt" , "a+" ) );
    fclose ( outFile );
    exit ( 0 );
}

/* Creates a new card by gathrering necessary input from the user
 */
struct card *createNewCard (  ) {
    struct card *newCard = ( struct card * ) malloc ( sizeof ( struct card ) );
    
    newCard->type = getType ( ); 
    newCard->player = getPlayer ( );
    newCard->brand = getBrand ( );
    newCard->year = getYear ( );
    newCard->cardSeriesNum = getSeriesNumber ( );
    newCard->value = getValue ( );
    
    return newCard;
}

/* Creates a new card by gathrering necessary input from the user
 */
struct card *createNewCardFromFile ( FILE *inputFile ) {
    struct card *newCard = ( struct card * ) malloc ( sizeof ( struct card ) );
    
    newCard->type = getTypeFromFile ( inputFile );
    newCard->cardSeriesNum = getSeriesNumberFromFile ( inputFile );
    newCard->year = getYearFromFile ( inputFile );
    newCard->brand = getBrandFromFile ( inputFile );
    newCard->player = getPlayerFromFile ( inputFile );
    newCard->value = getValueFromFile ( inputFile );
    
    return newCard;
}

char *getTypeFromFile ( FILE *inputFile ) {
    char *type = ( char * ) malloc ( MAX_CHARS_PER_LINE );
    fgets ( type, 100, inputFile );
    printf ( "\ntype in get value %s", type );

    return type;
}

char *getPlayerFromFile ( FILE *inputFile ) {
    char *player = ( char * ) malloc ( MAX_CHARS_PER_LINE );
    fgets ( player, 100, inputFile );
    
    printf ( "\nplayer in get value %s", player );

    return player;
}

char *getBrandFromFile ( FILE *inputFile ) {
    char *brand = ( char * ) malloc ( MAX_CHARS_PER_LINE );
    fgets ( brand, 100, inputFile );
    
    printf ( "\nValue in get value %s", brand );

    return brand;
}

/* Gets card year from user
 *
 * @return the input entered by the user
 */
int getYearFromFile ( FILE *inputFile ) {
    int year = 0;
    char yearInput[10];
    year = atoi ( fgets ( yearInput,
                         MAX_CHARS_PER_LINE,
                         inputFile
                         )// strtok ( NULL, "," )
                 );
    printf ( "\nyear in get value %d", year );

    
    return year;
}

/* Gets card type from user
 *
 * @return the input entered by the user
 */
int getSeriesNumberFromFile ( FILE *inputFile ) {
    int seriesNum = 0;
    char seriesNumInput[10];
    seriesNum = atoi ( fgets ( seriesNumInput,
                         MAX_CHARS_PER_LINE,
                         inputFile
                         )// strtok ( NULL, "," )
                 );
    printf ( "\nseries in get value %d", seriesNum );

    
    return seriesNum;
}

/* Gets card value from user
 *
 * @return the input entered by the user
 */
double getValueFromFile ( FILE *inputFile ) {
    double value = 0.0;
    char valueInput[15];
    value = atoi ( fgets ( valueInput,
                              MAX_CHARS_PER_LINE,
                              inputFile
                              )// strtok ( NULL, "," )
                      );
    printf ( "\nValue in get value %f", value );
    
    return value;
}

/* Gets card type from user
 *
 * @return the input entered by the user
 */
char *getType ( ) {
    char *type = ( char * ) malloc ( MAX_CHARS_PER_LINE );
    fputs ( "Type in the type of card and hit enter.\n", stdout );
    fflush( stdout );
    fgets ( type, 100, stdin );
    
    return type;
}


/* Gets card brand from user
 *
 * @return the input entered by the user
 */
char *getBrand ( ) {
    char *brand = ( char * ) malloc ( 1000 );
    fputs ( "Type in the brand of card and hit enter.\n", stdout );
    fflush( stdout );
    fgets ( brand, 100, stdin );
    
    return brand;
}

/* Gets card player from user
 *
 * @return the input entered by the user
 */
char *getPlayer( ) {
    char *player = ( char * ) malloc ( 1000 );
    fputs ( "Type in the player on card and hit enter.\n", stdout );
    fflush( stdout );
    fgets ( player, 100, stdin );
    
    return player;
}

/* Gets card year from user
 *
 * @return the input entered by the user
 */
int getYear ( ) {
    int year = 0;
    fputs ( "Type in the year of the card and hit enter.\n", stdout);
    scanf ( "%d", &year );
    
    return year;
}

/* Gets card type from user
 *
 * @return the input entered by the user
 */
int getSeriesNumber ( ) {
    int seriesNumber = 0;
    fputs ( "Type in the series number of the card and hit enter.\n", stdout);
    scanf ( "%d", &seriesNumber );
    
    return seriesNumber;
}

/* Gets card value from user
 *
 * @return the input entered by the user
 */
double getValue ( ) {
    double value = 0.0;
    fputs ( "Type in the value of the card and hit enter.\n", stdout);
    scanf ( "%lf", &value );
    
    return value;
}


/* This method is used to clear the input 
 *   buffer after each card is entered
 */
void clearBuffer (void) {
    while ( getchar() != '\n' );
}

struct cardNode *createTree (FILE *inputFile,
                             struct cardNode *root ) {
    if ( inputFile == NULL ) {
        printf ( "\n\n\n The input file is null");
    }
    printf ("inside create tree ");
    char lineInput[MAX_CHARS_PER_LINE];
    char *linePointer;
    struct card *currentCard;
    
    int i = 0;
    
    
    while (i < 2 ) {//!( feof ( inputFile ) ) ) {
        currentCard = createNewCardFromFile( inputFile );
        root = createNewCardNode(root, currentCard, 'P' );
        /*printf ( "\ntype after card %s\n", currentCard->type );
        printf ( "\nbrand after card %s\n", currentCard->brand );
        printf ( "\nplayer after card %s\n", currentCard->player );
        printf ( "\nyear after card %d\n", currentCard->year );
        printf ( "\nvalue after card %f\n", currentCard->value );
        printf ( "\nseries number after card %d\n", currentCard->cardSeriesNum );*/
        i++;
        //root = createNewCardNode( root, currentCard, 'p' );
        /*char type[MAX_CHARS_PER_LINE],
        player[MAX_CHARS_PER_LINE],
        brand[MAX_CHARS_PER_LINE];
        currentCard = ( struct card * ) malloc ( sizeof ( struct card ) );
        /*linePointer = fgets ( lineInput,
                              MAX_CHARS_PER_LINE,
                              inputFile
                            );*/ // retuns null if error occured or at end
        //copy = strdup ( linePointer );
        //printf ("\n\nLine input %s", copy );
        
        /*if ( linePointer == NULL ) {
            break;
        }*/
        
        //strtok ( linePointer, " " ); //Parse to next meaningful value
        /*printf ( "MADE IT BEFORE ");
        currentCard->type =fgets ( type,
                                    MAX_CHARS_PER_LINE,
                                    inputFile
                                  );//strtok ( copy, "," );
        printf ( "MADE IT AFTER ");
        //printf ("\n The type is %s", currentCard->type);
        //printf ( "%s", currentCard->type );
        //lineInput = NULL;
        
        /*linePointer = fgets ( lineInput,
                             MAX_CHARS_PER_LINE,
                             inputFile
                             );*/ // retuns null if error occured or at end
        
        /*currentCard->cardSeriesNum = atoi ( fgets ( lineInput,
                                                   MAX_CHARS_PER_LINE,
                                                   inputFile
                                                  )
                                          );//)strtok ( NULL, "," ) );
        printf ( "%d\n", currentCard->cardSeriesNum );
        
        /*linePointer = fgets ( lineInput,
                             MAX_CHARS_PER_LINE,
                             inputFile
                             );*/ // retuns null if error occured or at end
        
        /*currentCard->year = atoi ( fgets ( lineInput,
                                          MAX_CHARS_PER_LINE,
                                          inputFile
                                         )// strtok ( NULL, "," )
                                 );
        printf ( "%d\n", currentCard->year );
        printf ( "the value of type 1 is %s  ", currentCard->type );
        
        /*linePointer = fgets ( lineInput,
                             MAX_CHARS_PER_LINE,
                             inputFile
                             ); // retuns null if error occured or at end*/
       /* currentCard->brand = fgets ( brand,
                                    MAX_CHARS_PER_LINE,
                                    inputFile
                                    ); // retuns null if error occured or at end//linePointer;// strtok ( NULL, "," );
        printf ( "%s", currentCard->brand );
        printf ( "the value of type 2 is %s  ", currentCard->type );
        
        currentCard->player = fgets ( player,
                                      MAX_CHARS_PER_LINE,
                                      inputFile
                                    ); // retuns null if error occured or at end
        printf ( "%s", currentCard->player );
        printf ( "the value of type 3 is %s  ", currentCard->type );
        
        currentCard->value = atof ( fgets ( lineInput,
                                           MAX_CHARS_PER_LINE,
                                           inputFile
                                          )
                                  );
        printf ( "%f\n", currentCard->value );
        i++;
        printf ( "the value of type 4 is %s  ", currentCard->type );
        root = createNewCardNode( root, currentCard, 'p' );
        printf ( "the value of type after root is %s  ", currentCard->type );*/
        
        //printCard ( currentCard );
    } 
        
    return root;
}

void printCard ( struct card *current ) {
    printf ( "PC B: %s\n", current->brand );
    printf ( "PC T: %s\n", current->type );
    printf ( "PC P: %s\n", current->player );
    printf ( "PC Y: %d\n", current->year );
    printf ( "PC CS: %d\n", current->cardSeriesNum );
    printf ( "PC V: %f\n", current->value );
}

// TODO:
//    Write file error checks
//    Implement a true serialize method
FILE *saveData ( struct cardNode *root, FILE *outFile ) {
    printf ("Save was called");
    //
    printf ("Was able to open the file");
    if ( root != NULL ) {
        saveData ( root->leftChild, outFile );
        
        char *contentBuffer =
        ( char * ) malloc ( sizeof ( struct card ) );
        
        sprintf ( contentBuffer,
                  "%s"   // New line already added by fputs
                  "%d\n"
                  "%d\n"
                  "%s"   // New line already added by fputs
                  "%s"  // New line already added by fputs
                  "%f\n",
                  root->item->type,
                  root->item->cardSeriesNum,
                  root->item->year,
                  root->item->brand,
                  root->item->player,
                  root->item->value
                );
        
        fputs ( contentBuffer, outFile );
        
        saveData ( root->rightChild, outFile );
    }

    return NULL;
}

void printSearch ( struct card **found ) {
    int loopCTR = 0;
    struct card *tmp;
    while ( ( tmp = found[loopCTR++] ) != NULL ) {
        printf ( "\nType: %s"   // New line already added by fputs
                 "Series number: %d\n"
                 "Year: %d\n"
                 "Brand: %s"   // New line already added by fputs
                 "Player: %s"  // New line already added by fputs
                 "Value: $%f\n",
                 tmp->type,
                 tmp->cardSeriesNum,
                 tmp->year,
                 tmp->brand,
                 tmp->player,
                 tmp->value
               );
    }
}

void usage ( ) {
}