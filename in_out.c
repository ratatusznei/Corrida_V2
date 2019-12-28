#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "consts.h"
#include "player.h"
/*
    Funções de escrita e leitura do console
*/

char read_choice (char *choice) {
    fflush(stdin);
    gets (choice);
    /*
        Se o proximo char não foi uma quebra de linha no console. Ex: Foi digitado 23, então choice está com 2,
        essa não foi a escolha do jogador
    */
    if (choice[1] != '\0')
        choice[0] = '\0';
    return *choice;
}

void clear_line () {
    int i;
    putchar('\r');
    for (i = 0; i < 79; i++)
        putchar(' ');
    putchar('\r');
    return;
}

void draw_ASCII_line (char str[], int length, int pos) {
    int i;
    for (i = 0; i < pos && i < 80-1; i++)
        putchar (' ');
    for (i = 0; i < length; i++) {
        if (pos + i + 1 >= 80)      //+1 pois "pos" começa em 0
            break;
        else if (pos + i + 1 < 0)
            continue;
        putchar (str[i]);
    }
}

void no_choice () {
    system("cls");
    printf("Opção inválida!\n\n");
    system("pause");
    return;
}

void render_screen (char screen[SCREENH][SCREENW]) {
	int i, j;
	system("cls");
	for (i = 0; i < SCREENH; i++)
		for (j = 0; j < SCREENW; j++)
			putchar(screen[i][j]);
	return;
}

void clear_screen (char screen[SCREENH][SCREENW], char *track, FILE *trackFile) {
	int i, j;
	fgoto_label (trackFile, track);
	for (i = 0; i < SCREENH; i++) {
		for (j = 0; j < SCREENW; j++) {
			screen[i][j] = fgetc (trackFile);
			if (screen[i][j] == '\n') {
				screen[i][j] = '\0';
				break;
			}
			else if (screen[i][j] == ';') {
				screen[i][j] = '\0';
				i = SCREENH + 1;
				j = SCREENW + 1;
			} else if (screen[i][j] == 'P')
				screen[i][j] = ' ';
		}
	}
}

void draw_dollars (char screen[SCREENH][SCREENW], char dollars[5][2]) {
	char i, j;
	for (j = 0; j < 5; j++) {
		for (i = 0; dollars[j][i] != -1 && i < 2; i++) {
			screen[dollars[j][1]][dollars[j][0]] = '$';
		}
	}
}
