#include<stdio.h>
#include"resizeAndCleaning.h"
#include"conio2.h"
#include"OtherFunctions.h"

void cleanBoard(enum element **board){
    int i=0, j=0;
    while(i<N){
        while(j<N){
            board[i][j]=nothing;
            j++;
        }
        j=0;
        i++;
    }
}

void clearClearCutFields(enum element **board){
    int i=0, j=0;
    while(i<N){
        while(j<N){
            if(board[i][j]==isClearZero){
                board[i][j]=nothing;
            }
            if(board[i][j]==isClearOne){
                board[i][j]=nothing;
            }
            j++;
        }
        j=0;
        i++;
    }
}

void clearUnfillableFields(enum element **board){
    int i=0, j=0;
    while(i<N){
        while(j<N){
            if(board[i][j]==cannotBeModified){
                board[i][j]=nothing;
            }
            j++;
        }
        j=0;
        i++;
    }
}

void clearFromCannotBeModified(enum element **board){
    int i=0, j=0;
    while(i<N){
        while(j<N){
            if(board[i][j]==cannotBeModified){
                board[i][j]=nothing;
            }
            j++;
        }
        j=0;
        i++;
    }
}

void initBoard(enum element **board){
    int i=0;
    while(i<N){
		delete[] board[i];
		i++;
	}
    i=0;
    userInput();
    while(i<N){
        board[i]=(element *)malloc(N*sizeof(element));
        i++;
    }
    cleanBoard(board);
    fillNewBoard(board);
}

void fillNewBoard(enum element **board){
    FILE *file;
    char filePath[32];
    char temp;
    sprintf(filePath, "board%ix%i.txt", N, N);
    file=fopen(filePath, "r");
    if(file==NULL)
        randomBoard(board);
    int i=0, j=0;
    while(i<N)
    {
        while(j<N){
            temp=fgetc(file); // czytanie z pliku
            if(temp=='.')
                board[i][j]=nothing;
            if(temp=='1')
                board[i][j]=oneFixed;
            if(temp=='0')
                board[i][j]=zeroFixed;
            j++;
        }
        j=0;
        i++;
    }
    fclose(file);
}

void userInput(){
    int signs[3];
    char errors[32];
    memset(errors, 0, sizeof(errors));
    while(true){
        clrscr();
        gotoxy(36, 7);
        cputs(errors);
        memset(errors, 0, sizeof(errors));
        gotoxy(30, 10);
        cputs("podaj rozmiar nowej tablicy (od 2 do 12)");
        gotoxy(40, 11);
        signs[0] = getch();
        putch(signs[0]);
        if(!isNumber(signs[0])){
            strcat(errors, "nie podales cyfry\n");
            continue;
        }
        if(((signs[0]-48)%2)&&(signs[0]!=49)){   //je¿eli jest parzysta i nie równa siê jeden (49 to kod ascii liczby 1
            strcat(errors, "podaj liczbe parzysta\n");
            continue;
        }
        signs[1] = getch();
        putch(signs[1]);
        if(signs[1] == 0x0d){
            if((signs[0]-48)>1){
                N=(signs[0]-48);
                break;
            }
            else{
                strcat(errors, "za mala liczba\n");
                continue;
            }
        }
        else if(!isNumber(signs[1])){
            strcat(errors, "nie podales cyfry\n");
            signs[1]=0;
        }
        else{
            signs[0]-=48;
            signs[1]-=48;
            if((10*signs[0]+signs[1])%2){
                strcat(errors, "podaj liczbe parzysta\n");
                continue;
            }
            else if((10*signs[0]+signs[1])<=MaxBoardSize){
                N=(10*signs[0]+signs[1]);
                break;
            }
            else{
                strcat(errors, "za duza liczba\n");
                continue;
                signs[1]=0;
            }
        }
    }
}
