#ifndef OTHERFUNCTIONS_H_INCLUDED
#define OTHERFUNCTIONS_H_INCLUDED

#include<stdio.h>
#include"conio2.h"

bool isNumber(int a);
void randomBoard(enum element **board);
void simpleHint(enum element **board, char statement[] ,int X, int Y);
void paintUnfillableFields(enum element **board);
void alightClearCutFields(enum element **board);
void paintClearCutFields(enum element **board);
void fillClearCutFields(enum element **board);
void automaticDetection(enum element **board, char statement[]);

#endif // OTHERFUNCTIONS_H_INCLUDED
