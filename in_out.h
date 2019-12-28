#ifndef IN_OUT_H
#define IN_OUT_H
#include "consts.h"
/*
	Funções de escrita e leitura do console
*/

void no_choice ();
/*
    Exibe na tela uma mensagem de erro
*/

void draw_ASCII_line (char str[], int length, int pos);
/*
    "Desenha" uma string a "pos" espacos do inicio do console
    Aceita posições negativas e maiores que  80
    O cursor deve estar no inicio da linha para funcionar corretamente
*/

void clear_line ();
/*
    Apaga o conteudo da linha atual
*/

char read_choice (char *choice);
/*
    Leitura utilizada em menus, fflush interno
*/

void render_screen (char screen[SCREENH][SCREENW]);
/*
	Atualiza a tela mostrada aos jogadores
*/

void clear_screen (char screen[SCREENH][SCREENW], char *track, FILE *trackFile);
/*
	Preenche screen só com a pista atual
*/
void draw_dollars (char screen[SCREENH][SCREENW], char dollars[5][2]);
/*
	Imprime os dolares em screen
*/
#endif // IN_OUT_H
