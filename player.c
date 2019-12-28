#include "consts.h"
#include "func.h"

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

vehicle *get_vehicle (char *name, char *sprite, char speed, char offx, char offy) {
	vehicle v = {name, sprite, speed, offx, offy};
	return &v;
}

void draw_player (player p, char screen[SCREENH][SCREENW], vehicle *vehicles) {
	int i, x, y;

	if (p.x > SCREENW || p.y > SCREENH || p.x < 0 || p.y < 0)
		return;

	y = p.y + vehicles[p.vehicle].offsetY;
	x = p.x + vehicles[p.vehicle].offsetX;

	for (i = 0; vehicles[p.vehicle].sprite[i]; i++) {
		if (vehicles[p.vehicle].sprite[i] == '\n') {
			x = p.x +  + vehicles[p.vehicle].offsetX;
			y++;
		}
		else if (x >= 0 && x <= SCREENW && y >= 0 && y <= SCREENH)
			screen[y][x++] = vehicles[p.vehicle].sprite[i];
	}
	return;
}

void reset_player (player *p) {
	p->x = p->y = p->vehicle = p->startx = p->starty = -1;
	p->lap = 0;
	return;
}

void move_player (player *p, char input) {
	switch (input) {
		case P1UP:
		case P2UP:
			p->y--;
			break;
		case P1DOWN:
		case P2DOWN:
			p->y++;
			break;
		case P1RIGHT:
		case P2RIGHT:
			p->x++;
	}
	return;
}

player cript_player (player p) {
	p.x ^= SAVEKEY;
	p.y ^= SAVEKEY;
	p.vehicle ^= SAVEKEY;
	return p;
}

char collision (player p, vehicle *vs, char screen[SCREENH][SCREENW], char input) {
	char w, h, x, y;
	for (w = 0, h = 1; vs[p.vehicle].sprite[w] != '\n' && vs[p.vehicle].sprite[w] != '\0'; w++) {
		if (vs[p.vehicle].sprite[w] == '\n')
			h++;
	}
	for (w = 0; vs[p.vehicle].sprite[w] != '\n' && vs[p.vehicle].sprite[w] != '\0'; w++);

	if (input == P1RIGHT || input == P2RIGHT) {
		for (x = p.x + w, y = p.y; y < p.y + h; y++) {
			if (is_in_string (WALLS, screen[y][x]))
				return WALLS[0];
			if (is_in_string (FINISHING, screen[y][x]))
				return FINISHING[0];
			if (is_in_string (BOOST, screen[y][x]))
				return BOOST[0];
			if (is_in_string (WATER, screen[y][x]) && p.vehicle != BARCO)
				return WALLS[0];
		}
	}
	else if (input == P1UP || input == P2UP) {
		for (x = p.x, y = p.y - 1; x < p.x + w; x++) {
			if (is_in_string (WALLS, screen[y][x]))
				return WALLS[0];
			if (is_in_string (FINISHING, screen[y][x]))
				return FINISHING[0];
			if (is_in_string (BOOST, screen[y][x]))
				return BOOST[0];
		}
	}
	else if (input == P1DOWN || input == P2DOWN) {
		for (x = p.x, y = p.y + h; x < p.x + w; x++) {
			if (is_in_string (WALLS, screen[y][x]))
				return WALLS[0];
			if (is_in_string (FINISHING, screen[y][x]))
				return FINISHING[0];
			if (is_in_string (BOOST, screen[y][x]))
				return BOOST[0];
			if (is_in_string (WATER, screen[y][x]) && p.vehicle != BARCO)
				return WALLS[0];
		}
	}
	return 0;
}

void reset_pos (player *p) {
	p->x = p->startx;
	p->y = p->starty;
	return;
}
