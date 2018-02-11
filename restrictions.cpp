#include<stdio.h>
#include"restrictions.h"
#include"conio2.h"

void buildStatementOne(char statement[], int zn);
void buildStatementTwo(char statement[], int zn);
void buildStatementTree(char statement[], int zn, bool line, int noValid);

bool restrictionOne(enum element **board, int X, int Y, int toInput, char statement[]){
    X--;
    Y--;
    int helpOne=0, helpTwo=0;
    if(toInput==0x30) toInput=2;
    if(toInput==0x31) toInput=3;
    if((Y-2)>=0){
        helpOne=(int)board[Y-1][X];
        helpTwo=(int)board[Y-2][X];
        if(((helpOne==toInput)||(helpOne==toInput-2)||(helpOne==toInput+4))&&((helpTwo==toInput)||(helpTwo==toInput-2)||(helpTwo==toInput+4))){
                if(statement[0]!='0') buildStatementOne(statement, toInput);
                return false;
        }
    }
    if((Y+2)<N){
        helpOne=(int)board[Y+1][X];
        helpTwo=(int)board[Y+2][X];
        if(((helpOne==toInput)||(helpOne==toInput-2)||(helpOne==toInput+4))&&((helpTwo==toInput)||(helpTwo==toInput-2)||(helpTwo==toInput+4))){
                if(statement[0]!='0') buildStatementOne(statement, toInput);
                return false;
        }
    }
    if((Y>0)&&(Y<N-1)){
        helpOne=(int)board[Y-1][X];
        helpTwo=(int)board[Y+1][X];
        if(((helpOne==toInput)||(helpOne==toInput-2)||(helpOne==toInput+4))&&((helpTwo==toInput)||(helpTwo==toInput-2)||(helpTwo==toInput+4))){
                if(statement[0]!='0') buildStatementOne(statement, toInput);
                return false;
        }
    }
    if((X-2)>=0){
        helpOne=(int)board[Y][X-1];
        helpTwo=(int)board[Y][X-2];
        if(((helpOne==toInput)||(helpOne==toInput-2)||(helpOne==toInput+4))&&((helpTwo==toInput)||(helpTwo==toInput-2)||(helpTwo==toInput+4))){
                if(statement[0]!='0') buildStatementOne(statement, toInput);
                return false;
        }
    }
    if((X+2)<N){
        helpOne=(int)board[Y][X+1];
        helpTwo=(int)board[Y][X+2];
        if(((helpOne==toInput)||(helpOne==toInput-2)||(helpOne==toInput+4))&&((helpTwo==toInput)||(helpTwo==toInput-2)||(helpTwo==toInput+4))){
                if(statement[0]!='0') buildStatementOne(statement, toInput);
                return false;
        }
    }
    if((X>0)&&(X<N-1)){
        helpOne=(int)board[Y][X-1];
        helpTwo=(int)board[Y][X+1];
        if(((helpOne==toInput)||(helpOne==toInput-2)||(helpOne==toInput+4))&&((helpTwo==toInput)||(helpTwo==toInput-2)||(helpTwo==toInput+4))){
                if(statement[0]!='0') buildStatementOne(statement, toInput);
                return false;
        }
    }
    return true;
}

void buildStatementOne(char statement[], int zn){
    strcat(statement, "wpisanie ");
    if(zn==2){
        strcat(statement, "0 ");
    }
    if(zn==3){
        strcat(statement, "1 ");
    }
    strcat(statement, "spowodowaloby pogwalcenie reguly 1\n");
}

bool restrictionTwo(enum element **board, int X, int Y, int toInput, char statement[]){
    X--;
    Y--;
    if(toInput==0x30) toInput=0;
    else toInput=1;
    int x=0, y=0, counterX=0, counterY=0, cur;
    while(x<N){
        cur=(int)board[Y][x];
        if((cur==toInput)||(cur==toInput+2)||(cur==toInput+6)) counterX++;
        if(counterX>=(N/2)){
                if(statement[0]!='0') buildStatementTwo(statement, toInput);
                return false;
        }
        x++;
    }
    while(y<N){
        cur=(int)board[y][X];
        if((cur==toInput)||(cur==toInput+2)||(cur==toInput+6)) counterY++;
        if(counterY>=(N/2)){
                if(statement[0]!='0') buildStatementTwo(statement, toInput);
                return false;
        }
        y++;
    }
    return true;
}

void buildStatementTwo(char statement[], int zn){
    strcat(statement, "wpisanie ");
    if(zn==0){
        strcat(statement, "0 ");
    }
    if(zn==1){
        strcat(statement, "1 ");
    }
    strcat(statement, "spowodowaloby pogwalcenie reguly 2\n");
}

bool restrictionTree(enum element **board, int X, int Y, int toInput, char statement[]){
    X--;
    Y--;
    element temp=board[Y][X];
    if(toInput==0x30) board[Y][X]=zero;
    if(toInput==0x31) board[Y][X]=one;
    int x=0, y=0, cur, cur2;
    while(y<N){
        if(y==Y){
            y++;
            continue;
        }
        while(x<N){
            cur=(int)board[y][x];
            cur2=(int)board[Y][x];
            if((cur==4)||(cur2==4))  x=(N+1);  // jesli jedno z pol jest puste to przerywamy sprawdzanie poniewaz wiersze nie moga byc rowne
            if(!((cur==cur2)||((cur-2)==cur2)))
                if(cur!=(cur2-2)) x=(N+1);
            x++;
            if(x==N){
                if(statement[0]!='0') buildStatementTree(statement, toInput, true, y+1);
                board[Y][X]=temp;
                return false;
            }
        }
        x=0;
        y++;
    }
    x=0; y=0;
    while(x<N){
        if(x==X){
            x++;
            continue;
        }
        while(y<N){
            cur=(int)board[y][x];
            cur2=(int)board[y][X];
            if((cur==4)||(cur2==4)) // jesli jedno z pol jest puste to przerywamy sprawdzanie poniewaz kolumny nie moga byc rowne
                if(cur!=(cur2-2)) y=(N+1);
            if(!((cur==cur2)||((cur-2)==cur2))) y=(N+1);
            y++;
            if(y==N){
                if(statement[0]!='0') buildStatementTree(statement, toInput, false, x+1);
                board[Y][X]=temp;
                return false;
            }
        }
        y=0;
        x++;
    }
    board[Y][X]=temp;
    return true;
}

void buildStatementTree(char statement[], int zn, bool line, int noValid){
    strcat(statement, "wpisanie ");
    char help[16];
    if(zn==0x30){
        strcat(statement, "0 ");
    }
    if(zn==0x31){
        strcat(statement, "1 ");
    }
    strcat(statement, "spowodowaloby pogwalcenie reguly 3\n");
    if(line){
        strcat(statement, "(wiersz bylby identyczny z ");
        sprintf(help, "%i wierszem)", noValid);
        strcat(statement, help);
    }
    else{
        strcat(statement, "(kolumna bylaby identyczna z ");
        sprintf(help, "%i kolumna", noValid);
        strcat(statement, help);
    }
}

bool areRestrictionsFullfiled(enum element **board, int X, int Y, int toInput){
    if(restrictionOne(board, X, Y, toInput, "0")){
        if(restrictionTwo(board, X, Y, toInput, "0")){
                if(restrictionTree(board, X, Y, toInput, "0")){
                    return true;
                }
        }
    }
    return false;
}
