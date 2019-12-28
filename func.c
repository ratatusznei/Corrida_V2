#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "consts.h"
/*
	Funções úteis genéricas
*/

char *state_to_string (int state) {
    switch (state) {
        case SAIR:
            return "Sair";
        case SPLASH:
            return "Splash";
        case MENU:
            return "Menu Principal";
        case SOBRE:
            return "Sobre";
        case AJUDA:
            return "Ajuda";
        case OPCOES:
            return "Opções";
        case SELCARROS:
            return "Seleção de Carros";
		case SELPISTA:
			return "Seleção de Pistas";
        case JOGO:
            return "Jogo";
        case LOADGAME:
            return "Carregar Jogo Salvo";
        case FIMDEJOGO:
            return "Fim de Jogo";
        default:
            return "Estado desconhecido";
    }
}

char toupper (char *c) {
	*c = *c >= 'a' && *c <= 'z'? *c - 'a' + 'A' : *c;
	return *c;
}

char *toupperS (char *str) {
    int i;
    for (i = 0; str[i]; i++)
        toupper (&str[i]);
    return str;
}

char is_valid (char c, char *values) {
	while (*values)
		if (c == *(values++))
			return 1;
	return 0;
}

char *criptS (char *s) {
	char str[MAXINPUT];
	int i;

	for (i = 0; s[i]; i++)
		str[i] ^= SAVEKEY;

	return str;
}

char is_in_string (char *s, char c) {
	char *p = s;
	while (*p) {
		if (*(p++) == c)
			return 1;
	}
	return 0;
}
