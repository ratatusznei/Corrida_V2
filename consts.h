#ifndef CONSTS_H
#define CONSTS_H
/*
	Atribui��o aos estados do jogo
*/
#define SAIR		-1
#define SPLASH		0
#define MENU		1
#define SOBRE		2
#define AJUDA		3
#define OPCOES		4
#define SELCARROS	5
#define SELPISTA	6
#define SEMAFORO	7
#define JOGO		8
#define LOADGAME	9
#define FIMDEJOGO	10
/*
	Atribui��o de constantes
*/
#define SPLASHSTEPS 80
#define SEQELEFANTE	"RIPBALEIA"
#define SEQCORREDOR	"WWSSADADBA"
#define SEQDRAGAO	"AHHH!"
#define MAXINPUT	54			//N�mero de caracteres m�ximo que o usu�rio pode entrar
#define SCREENW		80
#define SCREENH		20
#define NVEHICLES	3
#define SAVEKEY		124
/*
	M�scaras de Colis�o
*/
#define WALLS		"-|+$"
#define FINISHING	"#@"
#define BOOST		">"
#define BOOSTPOW    20
#define WATER		"~^"
/*
	Dire��es
*/
#define	UP			0
#define	DOWN		1
#define	RIGHT		2
#define P1CONTROLS	"WSDBY "
#define	P1UP		'W'
#define	P1DOWN		'S'
#define	P1RIGHT		'D'
#define P2CONTROLS	"IKLBY "
#define	P2UP		'I'
#define	P2DOWN		'K'
#define	P2RIGHT		'L'
#define SALVAJOGO	'Y'
#define SAIRJOGO	'B'
/*
	Ve�culos
*/
#define BRUXA		0
#define MOTO		1
#define BARCO		2
#define ELEFANTE	3
#define CORREDOR	4
#define DRAGAO		5
/*
	Game Flag Masks
*/
#define COLOR_ON	0b00000001	//Colorir as letras para os jogadores?
#define NIGHT_ON	0b00000010	//Modo noturno ativo?
#define PLY_TURN	0b00000100	//'0' -> Turno do J1; '1' -> Turno do J2
#define PLY1_TURN	0b00000000
#define PLY2_TURN	0b00000100
#define LANGUAGE	0b00001000	//'0' -> Portugu�s; '1' -> Ingl�s
/*
	Files paths
*/
#define	PORTPATH	"res\\lang\\portuguese.txt"
#define	ENGPATH		"res\\lang\\english.txt"
#define LOGOPATH	"res\\materials\\logo.txt"
#define TRCKPATH	"res\\materials\\tracks.txt"
#define SAVEPATH	"res\\user\\saves\\%s.sv"

#endif // CONSTS_H
