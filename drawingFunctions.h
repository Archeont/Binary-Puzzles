#ifndef DRAWINGFUNCTIONS_H_INCLUDED
#define DRAWINGFUNCTIONS_H_INCLUDED

#include<stdio.h>
#include"conio2.h"

int countYZeros(enum element **board, int Y);
int countYOnes(enum element **board, int Y);
int countXZeros(enum element **board, int X);
int countXOnes(enum element **board, int X);
void drawTable(enum element **board);
void drawBoardFixed(enum element **board);
void drawUnfillableFields(enum element **board);
void drawUserInput(enum element **board);
#endif // DRAWINGFUNCTIONS_H_INCLUDED
