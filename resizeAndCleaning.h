#ifndef RESIZEANDCLEANING_H_INCLUDED
#define RESIZEANDCLEANING_H_INCLUDED

#include<stdio.h>
#include"conio2.h"
#include"OtherFunctions.h"

void clearClearCutFields(enum element **board);
void clearUnfillableFields(enum element **board);
void clearFromCannotBeModified(enum element **board);
void initBoard(enum element **board);
void fillNewBoard(enum element **board);
void userInput();
void cleanBoard(enum element **board);

#endif // RESIZEANDCLEANING_H_INCLUDED
