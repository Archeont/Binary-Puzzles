#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"conio2.h"
#include"conio2.cpp"
#include"restrictions.h"
#include"restrictions.cpp"
#include"drawingFunctions.h"
#include"drawingFunctions.cpp"
#include"saveAndLoad.h"
#include"saveAndLoad.cpp"
#include"resizeAndCleaning.h"
#include"resizeAndCleaning.cpp"
#include"OtherFunctions.h"
#include"OtherFunctions.cpp"

void defaultBoard(enum element **board){
    cleanBoard(board);
    board[0][3]=oneFixed;
    board[0][11]=oneFixed;
    board[1][1]=zeroFixed;
    board[1][8]=oneFixed;
    board[2][5]=zeroFixed;
    board[3][1]=zeroFixed;
    board[3][3]=oneFixed;
    board[3][5]=zeroFixed;
    board[3][7]=zeroFixed;
    board[3][9]=zeroFixed;
    board[3][11]=zeroFixed;
    board[4][0]=oneFixed;
    board[4][2]=oneFixed;
    board[4][7]=zeroFixed;
    board[4][10]=oneFixed;
    board[5][5]=zeroFixed;
    board[5][8]=oneFixed;
    board[6][2]=oneFixed;
    board[6][3]=oneFixed;
    board[6][8]=oneFixed;
    board[7][0]=zeroFixed;
    board[7][6]=zeroFixed;
    board[7][11]=zeroFixed;
    board[8][1]=oneFixed;
    board[8][4]=oneFixed;
    board[8][10]=oneFixed;
    board[9][2]=zeroFixed;
    board[9][5]=zeroFixed;
    board[9][7]=zeroFixed;
    board[10][2]=zeroFixed;
    board[10][5]=zeroFixed;
    board[10][6]=zeroFixed;
    board[10][11]=zeroFixed;
    board[11][3]=oneFixed;
    board[11][6]=zeroFixed;
    board[11][9]=oneFixed;
}

void startNewGame(enum element **board){
    if(N==12) defaultBoard(board); //defaultowa tablica istnieje tylko dla rozmiaru 12
}

void insertZeroOrOne(int zn, int X, int Y, enum element **board, char statement[]){
    if((board[Y-1][X-1]!=zeroFixed)&&(board[Y-1][X-1]!=oneFixed)){
        if(restrictionOne(board, X, Y, zn, statement)){
                if(restrictionTwo(board, X, Y, zn, statement)){
                        if(restrictionTree(board, X, Y, zn, statement)){
                            if(zn==0x30) board[Y-1][X-1]=zero;
                            if(zn==0x31) board[Y-1][X-1]=one;
                        }
                }
        }
    }
}

void communicate(char statement[], int vPosition, int hPosition){
    int k=0;
    gotoxy(hPosition, vPosition);
    while(statement[k]!='\0'){
        if(statement[k]=='\n'){ //przejscie do nawej lini
            gotoxy(hPosition, ++vPosition);
            k++;
        }
        putch(statement[k]);
        k++;
    }
}

int main() {
	int zn = 0, x = TablePozitionX+1, y = 2, attr = 8, back = 0, zero = 0;
	int X=0, Y=0;
	bool isAutomaticDetection=false;
	char txt[32];
	char statement[256];
	srand(time(NULL));
	// je¿eli program jest kompilowany w czystym jêzyku C
	// nale¿y wywo³aæ poni¿sz¹ liniê
#ifndef __cplusplus
	Conio2_Init();
#endif

    element **board;
    board=(element **)malloc(N*sizeof(element*));
    int i=0;
    while(i<N){
        board[i]=(element *)malloc(N*sizeof(element));
        i++;
    }
    cleanBoard(board);
	// settitle ustawia tytu³ okienka
	settitle("Witold Bazela 171893");
	do {
		// ustawiamy czarny kolor t³a, z którego bêdziemy
		// korzystali rysuj¹c po ekranie
		// proszê zerkn¹æ do conio2.h na listê dostêpnych kolorów
		textbackground(BLACK);
		// czyœcimy ekran: wype³niamy spacjami z ustawionym kolrem t³a
        clrscr();
		// ustawiamy kolor tekstu na jasnoszary (7 == LIGHTGRAY)
		textcolor(7);
		X=((x-(TablePozitionX-1))/2);
		Y=((y+1)/2);
		// przesuwamy kursor do kolumny 55 i wiersza 1
		// wiersze i kolumny liczymy od 1
		gotoxy(LegendPozition, 1);
		// wyœwietlamy na ekranie, w miejscu kursora napis
		// kursor przesuwa siê w prawo o d³ugoœæ napisu
		cputs("q lub esc = wyjscie");
		gotoxy(LegendPozition, 2);
		cputs("strzalki = poruszanie");
		gotoxy(LegendPozition, 3);
		cputs("0, 1 = wstawienie odpowiedniej cyfry - jesli to mozliwe");
		gotoxy(LegendPozition, 4);
		cputs("n = nowa gra");
		gotoxy(LegendPozition, 5);
		cputs("o = nowa gra z losowa plansza");
		//fun maybe
		sprintf(txt, "Obecna pozycja X : %i, Y: %i",X,Y);
		gotoxy(LegendPozition, 6);
		cputs(txt);
		//fun
		// wypisujemy na ekranie kod ostatnio naciœniêtego klawisza
		if(zero) sprintf(txt, "kod klawisza: 0x00 0x%02x", zn);
		else sprintf(txt, "kod klawisza: 0x%02x", zn);
		gotoxy(LegendPozition, 7);
		cputs(txt);
		gotoxy(LegendPozition, 8);
		cputs("p = prosta podpowiedz");
		gotoxy(LegendPozition, 9);
		cputs("r = zmien rozmiar(rozpoczna nowa gre)");
		gotoxy(LegendPozition, 10);
		cputs("k = oznacz pola ktorych nie mozna zmienic");
        gotoxy(LegendPozition, 11);
		cputs("a = tryb automatycznej detekcji ");
		gotoxy(LegendPozition+32, 11);
		if(isAutomaticDetection){
            cputs("wlaczony");
		}
		else{
            cputs("wylaczony");
		}
		gotoxy(LegendPozition, 12);
		cputs("j = podswietl pola jednoznaczne");
		gotoxy(LegendPozition, 13);
		cputs("w = wypelnij jednoznaczne pola(dzial tylko gdy sa podswietlone)");
		gotoxy(LegendPozition, 14);
		cputs("s = zapisz stan gry");
		gotoxy(LegendPozition, 15);
		cputs("l = wczytaj gre");
		if(isAutomaticDetection)   automaticDetection(board, statement);
        communicate(statement, 16, LegendPozition);
		drawTable(board);
		drawBoardFixed(board);
        if((isAutomaticDetection)&&(zn!='k')) clearFromCannotBeModified(board);
		drawUnfillableFields(board);
		paintClearCutFields(board);
        drawUserInput(board);
        bool canBeZero=false, canBeOne=false;
        if(areRestrictionsFullfiled(board,X,Y,0x30)) canBeZero=true;
        if(areRestrictionsFullfiled(board,X,Y,0x31)) canBeOne=true;
        if(!(canBeZero&&canBeOne)){
            if(canBeZero) board[X-1][Y-1]=zero;
            if(canBeOne) board[X-1][Y-1]=one;
        }
		gotoxy(x, y);
		// czekamy na naciœniêcie klawisza i odczytujemy jego kod,
		// wiêkszoœæ kodów klawiszy odpowiada ich znakom, np.
		// a to 'a', 2 to '2', + to '+', ale niektóre klawisze
		// specjalne, np. strza³ki s¹ zg³aszane jako dwa kolejne znaki,
		// z których pierwszy jest zerem, np. strza³ka w górê
		// to zero i 'H'
		zero = 0;
		zn = getch();
		if((zn!='w')&&(zn!='s')) clearClearCutFields(board);
		if(zn!='s'){
                memset(statement, 0, sizeof(statement));
                clearUnfillableFields(board);
        }
		// nie chcemy, aby klawisz 'H' dzia³a³ jako strza³ka w górê
		// wiêc sprawdzamy, czy pierwszym znakiem by³o zero
		if(zn == 0) {
			zero = 1;		// je¿eli tak, to czytamy
			zn = getch();		// kolejny znak wiedz¹c ju¿,
			if((zn == 0x48)&&(Y>1)) y-=2;	// ¿e bêdzie to znak specjalny
			else if((zn == 0x50)&&(Y<N)) y+=2;
			else if((zn == 0x4b)&&(X>1)) x-=2;
			else if((zn == 0x4d)&&(X<N)) x+=2;
		}else if((zn == 0x30)||(zn == 0x31)) insertZeroOrOne(zn, X, Y, board, statement);
		else if(zn == 'n') startNewGame(board);
		else if(zn == 'o') randomBoard(board);
		else if(zn == 'p') simpleHint(board, statement, X, Y);
		else if(zn == 'r') initBoard(board);
		else if(zn == 'k') paintUnfillableFields(board);
		else if(zn == 'a') {isAutomaticDetection=(!isAutomaticDetection);}
		else if(zn == 'j') alightClearCutFields(board);
		else if(zn == 'w') fillClearCutFields(board);
		else if(zn == 's') saveCurrentGame(board, statement);
		else if(zn == 'l') loadGame(board, statement);
	} while ((zn != 'q')&&(zn != 0x1b));

	return 0;
}
