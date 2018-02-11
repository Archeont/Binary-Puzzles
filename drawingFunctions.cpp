#include<stdio.h>
#include"drawingFunctions.h"
#include"conio2.h"

int countYZeros(enum element **board, int Y){
    int sum=0, i=0;
    while(i<N){
        if((board[Y][i]==zero)||(board[Y][i]==zeroFixed))  sum++;
        i++;
    }
    return sum;
}

int countYOnes(enum element **board, int Y){
    int sum=0, i=0;
    while(i<N){
        if((board[Y][i]==one)||(board[Y][i]==oneFixed))  sum++;
        i++;
    }
    return sum;
}

int countXZeros(enum element **board, int X){
    int sum=0, i=0;
    while(i<N){
        if((board[i][X]==zero)||(board[i][X]==zeroFixed))  sum++;
        i++;
    }
    return sum;
}

int countXOnes(enum element **board, int X){
    int sum=0, i=0;
    while(i<N){
        if((board[i][X]==one)||(board[i][X]==oneFixed))  sum++;
        i++;
    }
    return sum;
}

void drawTable(enum element **board){
    int i=0,j=0,k=0;
    char howMany[5];
    while(i<N){
        while(j<2*N+1){
            gotoxy(TablePozitionX+j,1+2*i);
            cputs("-");
            j++;
        }
        howMany[0]='|';
        howMany[1]=(char)(countYZeros(board, i)+48); //zamieniamy na kod ASCII i przypisujemy
        howMany[2]=';';
        howMany[3]=(char)(countYOnes(board, i)+48);
        howMany[4]='|';
        gotoxy(TablePozitionX-10, (2*i)+2);
        cputs(howMany);
        while(k<N+1){
            gotoxy(TablePozitionX+2*k,(2*i)+2);
            cputs("|");
            k++;
        }
        j=0;
        k=0;
        i++;
    }
    while(j<2*N+1){
            gotoxy(TablePozitionX+j,1+2*i);
            cputs("-");
            j++;
        }
    i=0;
    while(i<N){
        howMany[0]='-';
        howMany[1]=(char)(countXZeros(board, i)+48);
        howMany[2]='.';
        howMany[3]=(char)(countXOnes(board, i)+48);
        howMany[4]='-';
        gotoxy(TablePozitionX+1+(2*i), 2*(N+1));
        putch(howMany[0]);
        gotoxy(TablePozitionX+1+(2*i), 2*(N+1)+1);
        putch(howMany[1]);
        gotoxy(TablePozitionX+1+(2*i), 2*(N+1)+2);
        putch(howMany[2]);
        gotoxy(TablePozitionX+1+(2*i), 2*(N+1)+3);
        putch(howMany[3]);
        gotoxy(TablePozitionX+1+(2*i), 2*(N+1)+4);
        putch(howMany[4]);
        i++;
    }
}

void drawBoardFixed(enum element **board){
    int i=0, j=0, x=0, y=0;
    while(i<N){
        while(j<N){
            if(board[i][j]!=nothing){
                x=(TablePozitionX+1+2*j);
                y=(2+2*i);
                gotoxy(x,y);
                if(board[i][j]==oneFixed){
                    cputs("1");
                }
                else if(board[i][j]==zeroFixed){
                    cputs("0");
                }
            }
            j++;
        }
        j=0;
        i++;
    }
}

void drawUserInput(enum element **board){
    int i=0, j=0, x=0, y=0;
    textbackground(BLUE);
    while(i<N){
        while(j<N){
            if(board[i][j]!=nothing){
                x=(TablePozitionX+1+2*j);
                y=(2+2*i);
                gotoxy(x,y);
                if(board[i][j]==one){
                    cputs("1");
                }
                else if(board[i][j]==zero){
                    cputs("0");
                }
            }
            j++;
        }
        j=0;
        i++;
    }
}

void drawUnfillableFields(enum element **board){
    int i=0, j=0, x, y;
    textbackground(WHITE);
    while(i<N){
        while(j<N){
            if(board[i][j]==cannotBeModified){
                x=(TablePozitionX+1+2*j);
                y=(2+2*i);
                gotoxy(x,y);
                cputs("*");
            }
            j++;
        }
        j=0;
        i++;
    }
}
