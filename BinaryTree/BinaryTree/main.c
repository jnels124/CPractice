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
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "CardNodes.h"



int main( int argc,
          char * argv[ ] ){

    struct cardNode *root = NULL;
    struct card *tmpCard = NULL;
    
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
        
    } // end while
    
    printCollection( root );
} // end of main 
/*********************************TEST************************************
    struct card **searchResults = searchByPlayer ( root, "dan marino\n" );
    int loopCTR = 0;
    if ( searchResults == NULL ) {
        printf ( "RESULTS ARE NULL " );
    }
    struct card *tmp;// = searchResults[0]->player;
   
    printf ( "\n\n\nPrinting search results " );
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
                 root->item->value
               );
    }
} // end of main 
************************************************************************/

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
 *  * I am currently only accepting one option but getopt is
 *    *   used because feature implementations will process
     *   multiple options
     *
     * Currently passing multiple options at run time
     * is likely to produce unexpected results.
     *
     */
    /*while ( ( optionChar = getopt ( argc,
                                    argv,
                                    "inf" ) ) != -1 ) {
        switch ( optionChar ) {
            case 'i':
                printf ( "hello%d", 10 );
                break;
            
            case 'n':
                printf ( "N %d", 20 );
                break;
                
            default:
                break;
        }
    }
} */

// Having problems with scanf taking all info at once
// so a separate method was created to obtain each
// piece of data.

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

/* Gets card type from user
 *
 * @return the input entered by the user
 */
char *getType ( ) {
    char *type = ( char * ) malloc ( 1000 );
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
