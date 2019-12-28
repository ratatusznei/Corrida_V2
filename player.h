#ifndef PLAYER_H
#define PLAYER_H
#include "consts.h"
/*
	Header com declaração relacionadas aos jogadores
*/
typedef struct player {
    char vehicle;
	char x, y, startx, starty, lap;
	char moves;
} player;

typedef struct vehicle {
	char *name;
	char *sprite;
	char speed;
	char offsetX, offsetY;
} vehicle;

vehicle *get_vehicle (char *name, char *sprite, char speed, char offx, char offy);
/*
	Devolve uma struct veiculo com os parametros especificados
*/

void draw_player (player p, char screen[SCREENH][SCREENW], const vehicle *vehicles);
/*
	Desenha um carro na matriz screen
*/

void reset_player (player *p);
/*
	Reseta os valores de p
*/

void move_player (player *p, char dir);
/*
	Move o jogador na direção dir
*/
player cript_player (player p);
/*
	Criptografa e decriptografa as informações de p
*/
char collision (player p, const vehicle *vs, char screen[SCREENH][SCREENW], char input);
/*
	Checa colisão
*/
void reset_pos (player *p);
/*
	Manda o jogador para o inicio da pista
*/

#endif // PLAYER_H
