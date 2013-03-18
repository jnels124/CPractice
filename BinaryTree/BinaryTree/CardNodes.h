//
//  This header will hold the structures and methods
//   used to create a binary tree of collector cards
//  CardNodes.h
//  BinaryTree
//
//  Created by Jesse Nelson on 3/10/13.
//  Copyright (c) 2013 Jesse Nelson. All rights reserved.
//

#ifndef BinaryTree_CardNodes_h
#define BinaryTree_CardNodes_h

struct cardNode {
    int count;
    struct cardNode *leftChild;
    struct cardNode *rightChild;
    struct card *item;
};

struct card {
    char *type; // Type of card... i.e football, basketball
    char *brand; // i.e UpperDeck, Topps, Pinnacle
    char *player; // The player on the card
    int cardSeriesNum; // Number in series
    int year; // Year card was released
    double value; // Becket price
};

int checkDuplicate ( struct cardNode *this,
                    struct card *that
                    );

struct cardNode *insertByPlayer ( struct cardNode *parent,
                                  struct card *item
                                );
struct card **searchByPlayer ( struct cardNode *root,
                               char *player
                             );
void printSearch ( struct card ** );

void printCollection ( struct cardNode * );

struct cardNode *createNewCardNode ( struct cardNode *parent,
                                    struct card *item,
                                    char option
                                    );

struct cardNode *createTree ( FILE *, struct cardNode * );
FILE *saveData ( struct cardNode *, FILE * );


char *getType ( );
char *getBrand ( );
char *getPlayer ( );
int getSeriesNumber ( );
int getYear ( );
double getValue ( );
void clearBuffer ( void );
struct card *createNewCard ( );
double getValueFromFile ( FILE * );
int getYearFromFile ( FILE * );
int getSeriesNumberFromFile ( FILE * );
char *getTypeFromFile ( FILE * );
char *getPlayerFromFile ( FILE * );
char *getBrandFromFile ( FILE * );
void startSearch ( );
void usage ( );

#endif
