#include<stdio.h>
#include"OtherFunctions.h"
#include"conio2.h"

bool isNumber(int a){
    if((a>47)&&(a<58))
        return true;
    return false;
}

void randomBoard(enum element **board){
    cleanBoard(board);
    float floatN=(float)N;
    float help=((floatN*floatN)/100)*maxFill;
    int maxToFill=(int)help;
    help=((floatN*floatN)/100)*minFill;
    int minToFill=(int)help;
    int toFill=(rand()%(maxToFill-minToFill))+minToFill;
    int maxAttempts=N*N*N*N;
    int i=0, attempts=0, randomN, randomX, randomY;
    while(i<toFill){
         while(true){
                randomN=rand()%2;
                randomY=rand()%N;
                randomX=rand()%N;
                if(randomN==0) {randomN=0x30;}
                if(randomN==1) {randomN=0x31;}
                if(board[randomY][randomX]==nothing){
                    if(areRestrictionsFullfiled(board, randomX+1, randomY+1, randomN)){
                            if(randomN==0x30){
                                board[randomY][randomX]=zeroFixed;
                            }
                            if(randomN==0x31){
                                board[randomY][randomX]=oneFixed;
                            }
                            i++;
                            break;
                    }
                }
                attempts++;
                if(attempts>=maxAttempts){
                    break;
                }
         }
         if(attempts>=maxAttempts){
            cleanBoard(board);
            break;
         }
         attempts=0;
    }
}

void simpleHint(enum element **board, char statement[] ,int X, int Y){
    char canBeInputed[10];
    canBeInputed[0]='\0';
    bool canBe=true;
    int code=(int)(board[Y-1][X-1]);
    if(code<2){
        strcat(statement, "pole niemodyfikowale!");
        return;
    }
    else{
        if(!restrictionOne(board, X, Y, 0x30, statement)){
            canBe=false;
        }
        if(!restrictionTwo(board, X, Y, 0x30, statement)){
            canBe=false;
        }
        if(!restrictionTree(board, X, Y, 0x30, statement)){
            canBe=false;
        }
        if(canBe){
            strcat(canBeInputed,"(0");
        }
        canBe=true;
        if(!restrictionOne(board, X, Y, 0x31, statement)){
            canBe=false;
        }
        if(!restrictionTwo(board, X, Y, 0x31, statement)){
            canBe=false;
        }
        if(!restrictionTree(board, X, Y, 0x31, statement)){
            canBe=false;
        }
        if(canBe){
            if(canBeInputed[0]!='\0'){
                strcat(canBeInputed,";1)\n");
            }
            else{
                strcat(canBeInputed, "(1)\n");
            }
        }
        else if(canBeInputed[0]!='\0'){
            strcat(canBeInputed,")\n");
        }
    }
    strcat(statement, canBeInputed);
}

void paintUnfillableFields(enum element **board){
    int i=0, j=0;
    while(i<N){
        while(j<N){
            if(board[i][j]==nothing){
                if(!areRestrictionsFullfiled(board, j+1, i+1, 0x30)){
                    if(!areRestrictionsFullfiled(board, j+1, i+1, 0x31)){
                        board[i][j]=cannotBeModified;
                    }
                }
            }
            j++;
        }
        j=0;
        i++;
    }
}

void alightClearCutFields(enum element **board){
    int i=0, j=0;
    bool isClearCutZero=false;
    bool isClearCutOne=false;
    while(i<N){
        while(j<N){
            if(board[i][j]==nothing){
                if(areRestrictionsFullfiled(board, j+1, i+1, 0x30)){
                        isClearCutZero=true;
                }
                if(areRestrictionsFullfiled(board, j+1, i+1, 0x31)){
                        if(!isClearCutZero){
                                isClearCutOne=true;
                        }
                        else{
                            isClearCutZero=false;
                        }
                }
                if(isClearCutZero){
                        board[i][j]=isClearZero;
                }
                if(isClearCutOne){
                        board[i][j]=isClearOne;
                }
                isClearCutZero=false;
                isClearCutOne=false;
            }
            j++;
        }
        j=0;
        i++;
    }
}

void paintClearCutFields(enum element **board){
    int i=0, j=0, x, y;
    textbackground(RED);
    while(i<N){
        while(j<N){
            if(board[i][j]==isClearZero){
                x=(TablePozitionX+1+2*j);
                y=(2+2*i);
                gotoxy(x,y);
                cputs("0");
            }
            if(board[i][j]==isClearOne){
                x=(TablePozitionX+1+2*j);
                y=(2+2*i);
                gotoxy(x,y);
                cputs("1");
            }
            j++;
        }
        j=0;
        i++;
    }
}

void fillClearCutFields(enum element **board){
    int i=0, j=0;
    while(i<N){
        while(j<N){
            if(board[i][j]==isClearZero){
                board[i][j]=zero;
            }
            if(board[i][j]==isClearOne){
                board[i][j]=one;
            }
            j++;
        }
        j=0;
        i++;
    }
}

void automaticDetection(enum element **board, char statement[]){
    paintUnfillableFields(board);
    bool breaker=false;
    int i=0, j=0;
    while(i<N){
            while(j<N){
                if(board[i][j]==cannotBeModified){
                    strcat(statement, "nie mozna skonczyc gry!\n");
                    breaker=true;
                    break;
                }
                j++;
            }
        if(breaker) break;
        j=0;
        i++;
    }
}
