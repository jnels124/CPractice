//
//  This file contains the methods needed to
//   insert, delete and print a binary tree
//
//  BTNode.c
//  BinaryTree
//
//  TODO:
//    Error checking
//
//  Created by Jesse Nelson on 2/27/13.
//  Copyright (c) 2013 Jesse Nelson. All rights reserved.
//
//  Hosted at https://github.com/jnels124/CPractice
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CardNodes.h"

struct card *searchResults[sizeof (struct card)];

/* Checks the option to determine how 
 * cards should be inserted and calls
 * the appropriate insertion method
 *
 * @return pointer to parent
 *
 */
struct cardNode *createNewCardNode ( struct cardNode *parent,
                                     struct card *item,
                                     char option
                                   ) {
    switch ( option ) {
        case 'b':
            // insert by brand// To be implemented later
            
            break;
            
        case 't':
            // insert by type// To be implemented later
            
            break;
            
        case 's':
            // insert by series number// To be implemented later
            
            break;
            
        case 'y':
            // insert by year// To be implemented later
            
            break;
            
        case 'v':
            // insert by value// To be implemented later
            
            break;
            
            // insert by player
        case 'p':
            return insertByPlayer ( parent, item );
            
        default: // just insert by player
            return insertByPlayer ( parent, item );
    }

    return NULL; // ERROR OCCURED
}

// Print all nodes in tree
void printCollection ( struct cardNode *root ) {
    if ( root != NULL ) {
        printCollection ( root->leftChild );
        
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
        
        printCollection ( root->rightChild );
    }
}

/* This method is called as a new node is reached
 * to determine if this card is a duplicate to one
 * already in the tree.
 *
 * To be considered a duplicate all attributes defined
 * in the card structure must be identical.
 * 
 * @return 0 if any attribue in card differs, else 1
 *
 */
int checkDuplicate ( struct cardNode *this,
                     struct card *that
                   ) {
    int brandCMP = strcmp ( this->item->brand, that->brand ),
        playerCMP = strcmp ( this->item->player, that->player ),
        seriesNumCMP = ( this->item->cardSeriesNum == that->cardSeriesNum ),
        yearCMP = ( this->item->year == that->year ),
        valueCMP = ( this->item->value == that->value );
    
    return seriesNumCMP == 1 &&
           yearCMP == 1 &&
           valueCMP == 1 &&
           playerCMP == 0 &&
           brandCMP == 0;
}

//*******************************BY_PLAYER**********************************

/* Inserts card in binary true in order by player
 *
 * @return pointer to parent
 *
 */
struct cardNode *insertByPlayer ( struct cardNode *parent,
                                  struct card *item
                                ) {
    int strcmpCND;
    
    // New tree, or inserting at leaf node
    if ( parent == NULL ) {
        parent = ( struct cardNode * ) malloc ( sizeof ( struct cardNode ) );
        parent->item = item; 
        parent->leftChild = NULL;
        parent->rightChild = NULL;
    }
    
    else if ( checkDuplicate( parent, item ) ) {
        parent->count++; // duplicate card
    }
    
    /* Found correct location for player.
     * The new node will be inserted to the left
     * of the first node encountered that contains
     * the same player.
     */
    else if ( ( strcmpCND = strcmp
            ( parent->item->player, item->player ) ) == 0 ) {
        
        struct cardNode *tmp =
        ( struct cardNode * ) malloc ( sizeof ( struct cardNode ) );
        
        tmp->item = item;
        tmp->count = 1;
        tmp->leftChild = parent->leftChild;

        parent->leftChild = tmp;
    }
    
    else if ( strcmpCND < 0 ) {
        parent->leftChild = insertByPlayer ( parent->leftChild, item );
    }
    
    else {
        parent->rightChild = insertByPlayer ( parent->rightChild, item );
    }
    
    return parent; // Return updated parent with all pointers
}

/* This method will search the binary tree for the specified
 *   player and returns a pointer to an array of card structures
 *   that contains a pointer to every card matching the criteria
 */
struct card **searchByPlayer ( struct cardNode *root,
                               char *player
                             ) {
    static int foundCTR = 0; // Initialized only once on first call

    int strcmpCND;
    
    if ( root == NULL && foundCTR == 0) {
        return NULL;
    }
    
    if ( root == NULL ) {
        
        //return searchResults;
    }
    /* Performance in this block can be improved by
     * calling another method to finish checking the
     * tree until we no longer have cards of the same
     * player. This block only adds the card to the 
     * array. The program will continue checking the 
     * tree even after the first non-player is found
     * This can drastically effect execution time if 
     * you have a BIG struture and the player
     * being searched for is at the top of the tree.
     */
    else if ( ( strcmpCND = strcmp ( root->item->player, player ) ) == 0 ) {
        searchResults[foundCTR] =
        ( struct card * ) malloc ( sizeof ( struct card ) );
        
        searchResults[foundCTR] = root->item;
        
        foundCTR++;
        
        searchByPlayer ( root->rightChild, player );
        searchByPlayer ( root->leftChild, player );
    }
    
    else if ( strcmpCND < 0 ) {
        searchByPlayer( root->leftChild, player );
    }
    
    else {
        searchByPlayer (root->rightChild, player );
    }
    
    return searchResults; 
}
//****************************END_BY_PLAYER**********************************

//*******************************BY_PLAYER**********************************

/* Inserts card in binary true in order by player
 *
 * @return pointer to parent
 *
 *
struct cardNode *insertByPlayer ( struct cardNode *parent,
                                 struct card *item
                                 ) {
    int strcmpCND;
    
    // New tree, or inserting at leaf node
    if ( parent == NULL ) {
        parent = ( struct cardNode * ) malloc ( sizeof ( struct cardNode ) );
        parent->item = item;
        parent->leftChild = NULL;
        parent->rightChild = NULL;
    }
    
    else if ( checkDuplicate( parent, item ) ) {
        parent->count++; // duplicate card
    }
    
    /* Found correct location for player.
     * The new node will be inserted to the left
     * of the first node encountered that contains
     * the same player.
     *
    else if ( ( strcmpCND = strcmp
               ( parent->item->player, item->player ) ) == 0 ) {
        
        struct cardNode *tmp =
        ( struct cardNode * ) malloc ( sizeof ( struct cardNode ) );
        
        tmp->item = item;
        tmp->count = 1;
        tmp->leftChild = parent->leftChild;
        
        parent->leftChild = tmp;
    }
    
    else if ( strcmpCND < 0 ) {
        parent->leftChild = insertByPlayer ( parent->leftChild, item );
    }
    
    else {
        parent->rightChild = insertByPlayer ( parent->rightChild, item );
    }
    
    return parent; // Return updated parent with all pointers
}

/* This method will search the binary tree for the specified
 *   player and returns a pointer to an array of card structures
 *   that contains a pointer to every card matching the criteria
 *
struct card **searchByPlayer ( struct cardNode *root,
                              char *player
                              ) {
    static int foundCTR = 0; // Initialized only once on first call
    
    int strcmpCND;
    
    if ( root == NULL && foundCTR == 0) {
        return NULL;
    }
    
    if ( root == NULL ) {
        
        //return searchResults;
    }
    /* Performance in this block can be improved by
     * calling another method to finish checking the
     * tree until we no longer have cards of the same
     * player. This block only adds the card to the
     * array. The program will continue checking the
     * tree even after the first non-player is found
     * This can drastically effect execution time if
     * you have a BIG struture and the player
     * being searched for is at the top of the tree.
     *
    else if ( ( strcmpCND = strcmp ( root->item->player, player ) ) == 0 ) {
        searchResults[foundCTR] =
        ( struct card * ) malloc ( sizeof ( struct card ) );
        
        searchResults[foundCTR] = root->item;
        
        foundCTR++;
        
        searchByPlayer ( root->rightChild, player );
        searchByPlayer ( root->leftChild, player );
    }
    
    else if ( strcmpCND < 0 ) {
        searchByPlayer( root->leftChild, player );
    }
    
    else {
        searchByPlayer (root->rightChild, player );
    }
    
    return searchResults;
}*/
//****************************END_BY_PLAYER**********************************


