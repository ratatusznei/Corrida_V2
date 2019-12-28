#ifndef FUNC_H
#define FUNC_H
/*
    Documentação das funções do jogo dos carrinhos
*/

char *state_to_string (int state);
/*
    Devolve uma string correspondente ao "state". Ex: MENU devolve "Menu Principal"
*/

char toupper (char *c);
/*
	Passa um char para caixa ALTA
*/

char *toupperS(char *str);
/*
    Passa uma string para caixa ALTA
*/

char is_valid (char c, char *values);
/*
	Verifica se c está em values[]
*/
char *criptS (char *s);
/*
	Criptografa e decriptografa a string s
*/
char is_in_string (char *s, char c);
/*
	Verifica se o caractere c está na string s
*/

#endif // FUNC_H
