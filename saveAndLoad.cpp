#include<stdio.h>
#include"saveAndLoad.h"
#include"conio2.h"

bool userInputWhereToSave(char filePath[]){
    int i=0;
    clrscr();
    gotoxy(36, 7);
    cputs("podaj nazwe pliku wynikowego");
    gotoxy(39, 10);
    while(i<32){
        filePath[i] = getch();
        if(filePath[i]==0x0d){
                filePath[i]='.';
                filePath[i+1]='t';
                filePath[i+2]='x';
                filePath[i+3]='t';
                break;
        }
        putch(filePath[i]);
        i++;
        if(i==28){
            gotoxy(36, 5);
            cputs("nazwa zbyt dluga!");
            memset(filePath, 0, sizeof(filePath));
            return false;
        }
    }
    return true;
}

bool userInputFromWhereLoad(char filePath[]){
    int i=0;
    clrscr();
    gotoxy(36, 7);
    cputs("podaj nazwe pliku do wczytania");
    gotoxy(39, 10);
    while(i<32){
        filePath[i] = getch();
        if(filePath[i]==0x0d){
                filePath[i]='.';
                filePath[i+1]='t';
                filePath[i+2]='x';
                filePath[i+3]='t';
                break;
        }
        putch(filePath[i]);
        i++;
        if(i==28){
            gotoxy(36, 5);
            cputs("nazwa zbyt dluga!");
            memset(filePath, 0, sizeof(filePath));
            return false;
        }
    }
    return true;
}

void saveCurrentGame(enum element **board, char statement[]){
    FILE *file;
    char filePath[32];
    memset(filePath, 0, sizeof(filePath));
    char temp;
    int help;
    while(!userInputWhereToSave(filePath)){};
    file=fopen(filePath, "a");
    char n=(char)N;
    fputc(n, file);
    int i=0, j=0;
    while(i<N)
    {
        while(j<N){
            help=(int)board[i][j];
            help+=48;
            temp=(char)help;
            fputc(temp, file); // zapisywanie do pliku cyfry
            j++;
        }
        j=0;
        i++;
    }
    fputc('?', file); //separator komunikatow i stanu gry
    i=0, j=0;
    while(statement[i]!='\0')
    {
        fputc(statement[i], file); // zapisywanie do pliku komunikatow
        i++;
    }
    fclose(file);
}

void loadGame(enum element **board, char statement[]){
    FILE *file;
    char filePath[32];
    memset(filePath, 0, sizeof(filePath));
    char temp;
    int help;
    while(!userInputFromWhereLoad(filePath)){};
    int i=0, j=0;
    file=fopen(filePath, "r");
    while(i<N){
		delete[] board[i];
		i++;
	}
    i=0;
    temp=fgetc(file);
    N=(int)temp;
    while(i<N){
        board[i]=(element *)malloc(N*sizeof(element));
        i++;
    }
    i=0;
    temp=fgetc(file);
    while(i<N){
        while(j<N){
            help=(int)temp;
            help-=48;
            board[i][j]=(element)help;
            j++;
            temp=fgetc(file);
        }
        j=0;
        i++;
    }
    i=0;
    temp=fgetc(file);
    while(temp!=EOF){
        statement[i]=temp;
        i++;
        temp=fgetc(file);
    }
}
