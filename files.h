#ifndef FILES_H
#define FILES_H
#include "player.h"
/*
	Fun��es relacionadas com arquivos
*/

char fgoto_label (FILE *file, const char *label);
/*
	Posiciona o ponteiro file para o caractere imediatamente ap�s a label
*/

char fprint_til_char (FILE *file, const char c);
/*
	Print file na tela at� o caractere indicado
*/

char fprint_block (FILE *file, const char *label);
/*
	Printa na tela um bloco de caracteres de file que come�a com
	";label" e termina em ";"
*/

int fget_width (FILE *file);
/*
    Devolte a largura da linha de file
*/

int fget_height (FILE *file);
/*
    Devolte a altura de file
*/

FILE *openTrack (char *trackName);
/*
	Abre o arquivo com a pista selecionada e retorna ele
*/
char save_game (char *saveName, player *ps, char *trackName);
/*
	Salva o jogo em um arquivo
*/
char load_game (char *saveName, player *ps, char *track);
/*
	Abre o jogo em um arquivo
*/
#endif FILE_H
