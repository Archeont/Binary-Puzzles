#ifndef SAVEANDLOAD_H_INCLUDED
#define SAVEANDLOAD_H_INCLUDED

#include<stdio.h>
#include"conio2.h"

bool userInputWhereToSave(char filePath[]);
bool userInputFromWhereLoad(char filePath[]);
void saveCurrentGame(enum element **board, char statement[]);
void loadGame(enum element **board, char statement[]);
#endif // SAVEANDLOAD_H_INCLUDED
