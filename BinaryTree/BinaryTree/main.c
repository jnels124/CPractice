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

void printCard ( struct card * );
int main( int argc,
          char * argv[ ] ){
    FILE *outFile = NULL;

    struct cardNode *root = NULL;
    struct card *tmpCard = NULL;
    
    int optionChar, fFlag = 0, addedToCTR = 0;

    printf ( "\n\nArgv is %s\n\n", strcat ( argv[3], "\n" ) );

    /* I am currently only accepting option but getopt is
     *   used because feature implementations will process
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
                printf ( "The file name is %s", argv[2] );
                root = createTree ( fopen ( argv[2] 
                                            ,"r"
                                          ),
                                    root
                                  );
                break;
            
            case 's': 
                //if ( fFlag ) {
                startSearch ( );
                //}
                printf ( "\n\nHere in s " );
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
        
        
        
        tmpCard = createNewCard( tmpCard );
        root = createNewCardNode( root, tmpCard, 'p' );
        
        clearBuffer ( );    // clear stdin
        addedToCTR++;
    } // end while
    
    if (root == NULL ) {
        //handle later!
    }
    
    if ( addedToCTR > 0 )
        outFile = saveData ( root, fopen ( "/Users/jessenelson/Documents"
                                           "/CodeReading/CPractice/BinaryT"
                                           "ree/BinaryTree/CardCollection.txt"
                                           , "w"
                                         )
                           );
    printCollection(root);
    fclose ( outFile );
    exit ( 0 );
}

void startSearch ( ) {
    char *input = ( char * ) malloc ( 1000 );

    while (1 == 1 ) {
        fputs ( "Would you like to search for a card?", stdout );
        fflush ( stdout );
        fgets ( input, 100, stdin );
        
        if ( strcmp ( "yes\n", input ) != 0 ) {
            break; // exit infinite loop
        }
        
        fputs ( "What player would you like to find?", stdout );
        fflush ( stdout );
        fgets ( input, 100, stdin );
        
        struct card **searchResults = searchByPlayer ( root, input );
        struct card *tmp = searchResults[0];
        
        printf ( "\n\n\nPrinting search results " );
        int loopCTR = 0;
        while ( (tmp = searchResults[loopCTR++]) != NULL ) {
            printf ( "\nType: %s"   // New line already added by fputs
                    "Series number: %d\n"
                    "Year: %d\n"
                    "Brand: %s"   // New line already added by fputs
                    "Player: %s"  // New line already added by fputs
                    "Value: $%f\n",
                    root->item->type,
                    root->item->cardSeriesNum,
                    root->item->year,
                    root->item->brand,
                    root->item->player,
                    root->item->value );
        }
    }
}

/* Creates a new card by calling methods to gather
 *  the necessary input from the user.
 *
 * @return a new card 
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

/* Creates a new card by calling the appropriate methods to read 
 * data input from file
 *
 * @param inputFile - file to be read
 *
 * @return a new card
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

/* Get type from the file
 *
 * @return type
 */
char *getTypeFromFile ( FILE *inputFile ) {
    char *type = ( char * ) malloc ( MAX_CHARS_PER_LINE );
    fgets ( type, 100, inputFile );
    printf ( "\ntype in get value %s", type );

    return type;
}

/* Get player from the file
 *
 * @return player
 */
char *getPlayerFromFile ( FILE *inputFile ) {
    char *player = ( char * ) malloc ( MAX_CHARS_PER_LINE );
    fgets ( player, 100, inputFile );
    printf ( "\nplayer in get value %s", player );

    return player;
}

/* Get brand from file
 *
 * @return brand 
 */
char *getBrandFromFile ( FILE *inputFile ) {
    char *brand = ( char * ) malloc ( MAX_CHARS_PER_LINE );
    fgets ( brand, 100, inputFile );
    
    printf ( "\nValue in get value %s", brand );

    return brand;
}

/* Gets card year from file
 *
 * @return year from the file
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

/* Gets card type from file
 *
 * @return series number from the file
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

/* Gets card value from file
 *
 * @return value from file
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
 *   when input is from the console
 */
void clearBuffer (void) {
    while ( getchar() != '\n' );
}

/* Create a binary tree by reading the provided file
 *
 * @param inputFile - File to be read
 * @param root - root of binary tree
 * @return new root to the binary tree
 */
struct cardNode *createTree (FILE *inputFile,
                             struct cardNode *root
                            ) {
    if ( inputFile == NULL ) {
        printf ( "\n\n\n The input file is null");  // Used for debugging
    }
    
    struct card *currentCard;
    int EOFFlag = 0;
    
    while ( (EOFFlag = getc ( inputFile ) ) != EOF ) { //!( feof ( inputFile ) ) ) {
        ungetc ( EOFFlag , inputFile ); // Put char back on if it is not end of file
        currentCard = createNewCardFromFile( inputFile );
        root = createNewCardNode(root, currentCard, 'P' );
    } 
        
    return root;
}

// Prints the card passed as parameter
// Used for debugging!
void printCard ( struct card *current ) {
    printf ( "PC B: %s\n", current->brand );
    printf ( "PC T: %s\n", current->type );
    printf ( "PC P: %s\n", current->player );
    printf ( "PC Y: %d\n", current->year );
    printf ( "PC CS: %d\n", current->cardSeriesNum );
    printf ( "PC V: %f\n", current->value );
}

/* This method will store data of a tree to file
 *  to be read in later.
 *
 * TODO:
 * Write file error checks and handle them
 *  Implement a true serialize method
 *
 * @return refererence to the created file (will be used in later implementation )
 */
FILE *saveData ( struct cardNode *root, FILE *outFile ) {
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

/* This method will print the cards matching the search 
 * criteria
 */
void printSearch ( struct card **found ) {
    printf ( "\nprint in print search " );
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

/* This will display usage information to the user 
 */
void usage ( ) {
}