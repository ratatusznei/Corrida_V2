#define STARTINGSTATE SPLASH
#define VERSAO      "Beta 2"
#define LASTUPDATE  "06/12/2016"
/*  TO DO:
        Escrever as instruções
        Carregar jogos salvos
        Organizar as funções de forma racional
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include "files.h"
#include "func.h"
#include "in_out.h"
#include "player.h"
#include "consts.h"

int main() {
	//Inicializações
	setlocale(LC_ALL, "Portuguese");

	//Contadores genéricos e variaveis auxiliares
	int i, j;

	//Char (1 byte) pois ocupa menos espaço na memória que short int (2 bytes)
	//Variaveis de controle
	char gameState = STARTINGSTATE,
		 flags = 0b00000010,
		 strInput[MAXINPUT],
		 track[30] = "\0";


	//Inicialização de arquivos
	FILE *file = fopen (LOGOPATH, "r");
	if (!file) {
		printf ("ERRO: logo.txt não encontrado!\n");
		system ("pause");
	}
	FILE *lang = fopen(PORTPATH, "r");
	FILE *trackFile = NULL;

	//inicializa a matriz que vai conter a logo
	const short int	LOGOHEIGHT = fget_height(file),
					LOGOWIDTH = fget_width(file);

    //Frame Buffer, contém a próxima tela a ser desenhada
	char frameBuf[SCREENH][SCREENW];

	//Preenche a matriz frameBuf com o conteúdo do arquivo logo.txt
	for (i = 0; i < LOGOHEIGHT; i++)
		fgets (frameBuf[i], 100, file);
	fclose (file);

	//Matriz com a aparencia dos veículos
	const vehicle vehicles[] = {
		//*get_vehicle ( nome, sprite, speed, offsetX, offsetY )
		*get_vehicle("A bruxa", "}--", 3, 0, 0),
		*get_vehicle("A moto de luz", "o=o", 4, 0, 0),
		*get_vehicle("O barco da terra", "\\_/", 3, 0, 0),
		*get_vehicle("ELEFANTÃO",   " O°~\n"
                                    "^ ^", 3, 0, -1),
		*get_vehicle("Corredor", "\x2\n\x86\n^", 2, 0, -2),
		*get_vehicle("\"Quero p-p-peixe agora!\"", 	" } \n"
													"~O°<", 6, 0, -1),
		*get_vehicle("Tá pegando fogo bixo!", " \\\n//", 0, 0, -1)
	};


	char dollarcount = 0;
	char dollars[5][2];//Posição dos dollars
	//vehilce, x, y, startx, starty, lap, moves
	player fire = {6, SCREENW+1, SCREENH+1, 0, 0, 0, 0};

	//Vetor com as structs dos jogadores
	player players[2];
	players[0].x = players[1].x = -1;

	do {
		switch (gameState) {
			case SPLASH:
				system("cls");
				//Para toda linha na matriz frameBuf:
				for (i = 0; i < LOGOHEIGHT; i++) {
				    if (i % 2 == 0) {   //Se linha Par
				        for (j = 0; j <= SPLASHSTEPS; j++) {
				            //<-- Linha se move nessa direção
				            clear_line();
				            //Calcular nova posição e desenhar linha
				            draw_ASCII_line (frameBuf[i], LOGOWIDTH, (int) floor(60 - LOGOWIDTH/4 + (20 + LOGOWIDTH/4) * cos ((j) * M_PI/ SPLASHSTEPS)) );
				        }
				    }
				    else {
				        for (j = 0; j <= SPLASHSTEPS; j++) {
				            //--> Linha se move nessa direção
				            clear_line();
				            //Calcular nova posição e desenhar linha
				            draw_ASCII_line(frameBuf[i], LOGOWIDTH, (int) floor(20 - 3*LOGOWIDTH/4 - (20 + LOGOWIDTH/4) * cos ((j) * M_PI/ SPLASHSTEPS)) );
				        }
				    }
				    putchar('\n');
				    Sleep(1000/SPLASHSTEPS);
				}
				gameState = MENU;
				Sleep(2000);
				break;

			case MENU:
				system("cls");
				fprint_block (lang, "MENUPRINCIPAL");

				strInput[0] = getch ();
				gameState = strInput[0] == '1'? SELCARROS:
							strInput[0] == '2'? LOADGAME:
							strInput[0] == '3'? OPCOES:
							strInput[0] == '4'? AJUDA:
							strInput[0] == '5'? SOBRE:
							strInput[0] == '0'? SAIR:
												MENU;
				if (gameState == MENU)
				    no_choice ();
				break;

			case SOBRE:
				system("cls");
				fprint_block (lang, "MENUSOBRE");
				printf ("%s", VERSAO);
				fprint_til_char (lang, ';');
				printf ("%s", LASTUPDATE);
				fprint_til_char (lang, ';');
				system ("pause");
				gameState = MENU;
				break;

			case AJUDA:
				system("cls");
				fprint_block (lang, "MENUAJUDA");

				strInput[0] = getch ();
				system("cls");
				switch (strInput[0]) {
				    case '1':
				    case '2':
					case '3':
				        fprint_block (lang, strInput[0] == '1'? "REGRAS":
											strInput[0] == '2'?	"CONTROLES":
																"CRIARPISTA");
				        system ("pause");
				        break;
				    case '0':
				        gameState = MENU;
				        break;
				    default:
				        no_choice ();
				}
				break;

			case OPCOES:
				system ("cls");

				fprint_block (lang, "MENUOPCOES");
				printf ("[%s]", flags&COLOR_ON? "ON": "OFF");
				fprint_til_char (lang, ';');
				printf ("[%s]", flags&NIGHT_ON? "ON": "OFF");
				fprint_til_char (lang, ';');
				printf ("[%s]", flags&LANGUAGE? "English": "Português");
				fprint_til_char (lang, ';');

				strInput[0] = getch ();
				switch (strInput[0]) {
					//Cor das letras
				    case '1':
				        flags = flags^COLOR_ON;
				    break;
				    //Modo noturno
				    case '2':
				        flags = flags^NIGHT_ON;
				        system(flags&NIGHT_ON? "color 07": "color F0");
				    break;
				    //Traduções
				    case '3':
						flags = flags^LANGUAGE;
						if (lang)
							fclose (lang);
						if (!freopen (flags&LANGUAGE? ENGPATH: PORTPATH, "r", lang)) {
							printf("ERRO: Lang file not found!\n");
							system("pause");
						}
						break;
					//Voltar
				    case '0':
				        gameState = MENU;
				    break;
				    default:
				        no_choice ();
				}
				break;

			case SELCARROS:
				system("cls");
				//i = jogador atual, 0 = p1, 1 = p2
				i = 0;

				while (i >= 0 && i <= 1) {
				    //Reseta as escolhas anteriores do jogador
				    reset_player(&players[i]);
				    if (flags&COLOR_ON)
				        system(flags&NIGHT_ON? ((i == 0? "color 0B": "color 0C")): (i == 0? "color F9": "color FC"));

				    system ("cls");
				    fprint_block (lang, "SELCARRO");
				    printf ("%d", i+1);
				    fprint_til_char (lang, ';');
				    for (j = 0; j < NVEHICLES; j++)
						if (players[0].vehicle != j)
							printf ("\t(%d) %s: %s\n", j+1, vehicles[j].name, vehicles[j].sprite);

				    fprint_til_char (lang, ';');

				    strInput[0] = getche ();
				    if (strInput[0] == '>') {
						//Ler string caso '>'
                        gets (strInput);
                        toupperS(strInput);
				    }

				    system("cls");
				    if (strInput[0] != '0') {
				        //Se J1 não escolheu a bruxa
				        if (strInput[0] == '1' && players[0].vehicle != BRUXA) {
							//Escrever sobre a bruxa
				            fprint_block (lang, "BRUXALORE");
							//Ler e confirmar
				            strInput[0] = getch ();
				            if (strInput[0] == 'C' || strInput[0] == 'c') {
								players[i].vehicle = BRUXA; //Seleciona veiculo
								i++;    //Próximo jogador
				            }
				        }
				        //Se J1 não escolheu a moto
				        else if (strInput[0] == '2' && players[0].vehicle != MOTO) {
							//Escrever sobre a moto
				            fprint_block (lang, "MOTOLORE");
							//Ler e confirmar
                            strInput[0] = getch ();
				            if (strInput[0] == 'C' || strInput[0] == 'c') {
								players[i].vehicle = MOTO; //Seleciona veiculo
								i++;    //Próximo jogador
				            }
				        }
				        //Se J1 não escolheu o barco
				        else if (strInput[0] == '3' && players[0].vehicle != BARCO) {
							//Escrever sobre o barco
				            fprint_block (lang, "BOATLORE");
				            //Ler e confirmar
				            strInput[0] = getch ();
				            if (strInput[0] == 'C' || strInput[0] == 'c') {
								players[i].vehicle = BARCO; //Seleciona veiculo
								i++;    //Próximo jogador
				            }
				        }
				        else if (strcmp(strInput, SEQELEFANTE) == 0 && players[0].vehicle != ELEFANTE) {
				            printf (
								"Você escolheu nada!\n"
								"\n\t\tParabéns!\n"
								"\n\t(C) Confirmar?\n"
				            );
				            strInput[0] = getch ();
				            if (strInput[0] == 'C' || strInput[0] == 'c') {
								players[i].vehicle = ELEFANTE; //Seleciona veiculo
								i++;    //Próximo jogador
				            }
				        }
						else if (strcmp(strInput, SEQCORREDOR) == 0 && players[0].vehicle != CORREDOR) {
				            printf (
								"Você escolheu Q?!\n"
								"\n\t\tParabéns!\n"
								"\n\t(C) Confirmar?\n"
				            );
				            strInput[0] = getch ();
				            if (strInput[0] == 'C' || strInput[0] == 'c') {
								players[i].vehicle = CORREDOR; //Seleciona veiculo
								i++;    //Próximo jogador
				            }
				        }
				        else if (strcmp(strInput, SEQDRAGAO) == 0 && players[0].vehicle != DRAGAO) {
				            printf (
								"Mestre malvado!\n"
								"\n\t(C) Confirmar?\n"
				            );
				            strInput[0] = getch ();
				            if (strInput[0] == 'C' || strInput[0] == 'c') {
								players[i].vehicle = DRAGAO; //Seleciona veiculo
								i++;    //Próximo jogador
				            }
				        }
				        else
				            no_choice ();
				    }
				    else    //Se foi digitado 0: volte um jogador
				        i -= 1;
				}//Fim while
				//Resetar cores
				system(flags&NIGHT_ON? "color 07": "color F0");

				if (i < 0)	//Se jogador 1 digitou 0, volte ao menu
				    gameState = MENU;
				else if (i > 1)	//Se não, iniciar jogo
				    gameState = SELPISTA;
				break;

			case SELPISTA:
				system("cls");
				//Reabre file com o arquivo contendo a lista das pistas
				freopen (TRCKPATH, "r", file);
				//Salva em frameBuf 9 nomes de pistas do arquivo tracks.txt
				fprint_block(lang, "SELPISTA");
                fgoto_label (file, "LISTA");
				for (i = 0; i < 9; i++) {
					for (j = 0; j < SCREENW; j++){
						frameBuf[i][j] = fgetc(file);
						if (frameBuf[i][j] == '\n') {
							frameBuf[i][j] = '\0';
							break;
						} else if (frameBuf[i][j] == ';') {
							frameBuf[i][0] = '\0';
							i = SCREENH + 1;
							break;
						}
					}
				}
				//Imprime o nome das pistas salvo em frameBuf
				for (i = 0; frameBuf[i][0] != ';' && frameBuf[i][0] != '\0' && i < 9; i++)
					printf ("\t(%d) %s\n", i+1, frameBuf[i]);
				printf ("\n\t(0) Voltar\n");

				strInput[0] = getch ();
				//Se 0 voltar ao menu de seleção de carros
				if (strInput[0] == '0')
					gameState = SELCARROS;
				//Se em [0, 9], escolher a pista
				else if (strInput[0] > '0' && strInput[0] - '0' <= i) {
					//Copiar o nome de pista correspondente para o vetor track, char para int e então -1, pois vetor começa em indice 0
					strcpy(track, frameBuf[strInput[0] - '0' - 1]);
					toupperS(track);

					//Procura o nome da pista no arquivo
					trackFile = openTrack (track);
                    if (!trackFile) {
						printf ("ERRO: Track not found!\n");
						system ("pause");
						gameState = MENU;
                    }
                    else {
						//Limpa a matriz
						for (i = 0; i < SCREENH; i++)
							for (j = 0; j < SCREENW; j++)
								frameBuf[i][j] = '\0';

						//Preenche a matriz com a pista
						fgoto_label (trackFile, track);
						for (i = 0; i < SCREENH; i++) {
							for (j = 0; j < SCREENW; j++) {
								frameBuf[i][j] = fgetc (trackFile);
								//Se == '\n' passa para a próxima linha, i++ e j = 0
								if (frameBuf[i][j] == '\n') {
									frameBuf[i][j] = '\0';
									break;
								}
								//Se == ';' sair dos 2 loops
								else if (frameBuf[i][j] == ';' || frameBuf[i][j] == EOF) {
									frameBuf[i][j] = '\0';
									i = SCREENH + 1;
									j = SCREENW + 1;
								}
								//Se P posicionar jogadores
								else if (frameBuf[i][j] == 'P') {
									frameBuf[i][j] = ' ';
								}
							}//end for (j = 0; j < SCREENW; j++)
						}//end for (i = 0; i < SCREENH; i++)

						render_screen(frameBuf);
						printf ("\nVocê escolheu a pista %s!\n\n\t(C) Confirmar? ", track);
						strInput[0] = getch ();
						if (strInput[0] == 'c' || strInput[0] == 'C')
							gameState = SEMAFORO;
					}//end if (!trackFile)
				}//end else if (strInput[0] > '0' && strInput[0] - '0' <= i), entre '0' e '9'
				else
					no_choice ();
				break;

			case SEMAFORO:
				system("cls");
				//i = bool para colorir o semáforo, localizada no arquivo
				i = fgoto_label (trackFile, "COLOR");
				//Não estava ocorrendo rewind sem a linha abaixo
				rewind (trackFile);

				//Se achar a primeira tela de semaforo
				if (fgoto_label(trackFile, "S0")) {
					fprint_til_char (trackFile, ';');
					if (i) //Se cor = on
						system (flags&NIGHT_ON? "color 0C": "color FC");
					else
						system (flags&NIGHT_ON? "color 07": "color F0");
					Sleep (1000);
					strcpy (strInput, track);

					//Se achar a segunda tela de semaforo
					if (fgoto_label(trackFile, "S1")) {
						system("cls");
						fprint_til_char (trackFile, ';');
						if (i) //Se cor = on
							system (flags&NIGHT_ON? "color 0E": "color F6");
						else
							system (flags&NIGHT_ON? "color 07": "color F0");
						Sleep (1000);
						strcpy (strInput, track);

						//Se achar a terceira tela de semaforo
						if (fgoto_label(trackFile, "S2")) {
							system("cls");
							fprint_til_char (trackFile, ';');
							if (i) //Se cor = on
								system (flags&NIGHT_ON? "color 0A": "color F2");
							else
								system (flags&NIGHT_ON? "color 07": "color F0");
							Sleep (1000);
						}
					}
				}

				//Posiciona jogadores
				fgoto_label (trackFile, track);
				for (i = 0; i < SCREENH; i++) {
					for (j = 0; j < SCREENW; j++) {
						frameBuf[i][j] = fgetc (trackFile);

						if (frameBuf[i][j] == 'P') {
							if (players[0].startx == -1) {
								players[0].startx = j;
								players[0].starty = i;
							}
							else if (players[1].startx == -1) {
								players[1].startx = j;
								players[1].starty = i;
							}

							if (players[0].x == -1) {
								players[0].x = j;
								players[0].y = i;
							}
							else if (players[1].x == -1) {
								players[1].x = j;
								players[1].y = i;
							}
						}
					}
				}
				//Reset dollars
				for (i = 0; i < 5; i++)
					dollars[i][0] = -1;

				clear_screen (frameBuf, track, trackFile);
				draw_player (players[0], frameBuf, vehicles);
				draw_player (players[1], frameBuf, vehicles);
				render_screen(frameBuf);
				gameState = JOGO;
				break;

			case JOGO:
				//Update
				flags &= ~PLY_TURN;	//Turno = Jog. 1, clear na flag PLY_TURN
				printf ("\nP1 Lap = %d\tP2 Lap = %d\n", players[0].lap+1, players[1].lap+1);
				do {
					//Colore de acordo com as flags
					if (flags&COLOR_ON)
				        system(flags&NIGHT_ON? (( (flags&PLY_TURN) == PLY1_TURN? "color 0B": "color 0C")): ((flags&PLY_TURN) == PLY1_TURN? "color F9": "color FC"));
					else
						system(flags&NIGHT_ON? "color 07": "color F0");

					printf ("Turno do Jogador %d: ", (flags&PLY_TURN) == PLY1_TURN? 1: 2);

					//Input do jogador 1 no indice 2 e input do jogador 2 no indide 4
					strInput[(flags&PLY_TURN) == PLY1_TURN? 2: 4] = getche ();
					putchar ('\n');
					toupper (&strInput[(flags&PLY_TURN) == PLY1_TURN? 2: 4]);

					//Se a entrada for válida
					if (is_valid (strInput[(flags&PLY_TURN) == PLY1_TURN? 2: 4], (flags&PLY_TURN) == PLY1_TURN? P1CONTROLS: P2CONTROLS)) {
						//Se digitou sair, volte ao menu
						if (strInput[(flags&PLY_TURN) == PLY1_TURN? 2: 4] == SAIRJOGO) {
							system(flags&NIGHT_ON? "color 07": "color F0");
							gameState = MENU;
							break;
						}
						//Se digitou salvar, salve o jogo
						else if (strInput[(flags&PLY_TURN) == PLY1_TURN? 2: 4] == SALVAJOGO) {
                            printf("Digite um nome para o jogo a salvar: ");
                            gets (frameBuf[0]);
							if (save_game (frameBuf[0], players, track)) {
								printf("Jogo salvo com sucesso em ");
								printf(SAVEPATH, frameBuf[0]);
								putchar('\n');
							}
							else
								printf("Erro ao salvar o jogo!\n");
						}
						//Se estiver no turno do J1, passe para o J2
						else if ((flags&PLY_TURN) == PLY1_TURN)
							flags |= PLY_TURN; //Set na flag ply_turn

						//Se estiver no turno do J2, confirmar as entradas anteriores
						else {
							printf ("\t(C) Confirmar? ");
							system(flags&NIGHT_ON? "color 07": "color F0");
							strInput[0] = getch ();
							//Se confirmou, sair
							if (strInput[0] == 'c' || strInput[0] == 'C')
								break;
							//Se não confirmou, volte ao turno do J1
							else {
								flags &= ~PLY_TURN;
								system ("cls");
								render_screen(frameBuf);
							}
						}
					}
					//Se input não for válido
					else
						printf ("Comando não conhecido!\n");

				} while (1);


				//Se jogadores não quiserem sair
				if (gameState == JOGO) {
					players[0].moves = vehicles[players[0].vehicle].speed;
					players[1].moves = vehicles[players[1].vehicle].speed;

					while (players[0].moves > 0 || players[1].moves > 0) {
						if (players[0].moves > 0) {
							i = collision (players[0], vehicles, frameBuf, strInput[2]);//i = P1 colidiu?

							if (i == BOOST[0] && (players[0].vehicle == BRUXA || players[0].vehicle == DRAGAO))
								players[0].moves += BOOSTPOW;

							if (i == 0 || i == BOOST[0]) {
								if (players[0].vehicle == MOTO) {
									dollars[dollarcount][0] = players[0].x;
									dollars[dollarcount][1] = players[0].y;
									dollarcount = (dollarcount + 1) % 5;
								}

								move_player (&players[0], strInput[2]);
								players[0].moves--;

							}
							else if (i == WALLS[0]) {
								fire.x = players[0].x;
								fire.y = players[0].y;
                                reset_pos (&players[0]);
								players[0].moves = 0;
							}
							else if (i == FINISHING[0]) {
								players[0].lap++;
								reset_pos (&players[0]);
								if (players[0].lap > 2) {
									flags &= ~PLY_TURN;//JOG1 VENCEU
									gameState = FIMDEJOGO;
								}
							}
						}

						if (players[1].moves > 0) {
							i = collision (players[1], vehicles, frameBuf, strInput[4]);//i = P2 colidiu?

							if (i == BOOST[0] && (players[1].vehicle == BRUXA || players[1].vehicle == DRAGAO))
								players[1].moves += BOOSTPOW;

							if (i == 0 || i == BOOST[0]) {
								if (players[1].vehicle == MOTO) {
									dollars[dollarcount][0] = players[1].x;
									dollars[dollarcount][1] = players[1].y;
									dollarcount = (dollarcount + 1) % 5;
								}
								move_player (&players[1], strInput[4]);
								players[1].moves--;

							}
							else if (i == WALLS[0]) {
								fire.x = players[1].x;
								fire.y = players[1].y;
                                reset_pos (&players[1]);
								players[1].moves = 0;
							}
							else if (i == FINISHING[0]) {
								players[1].lap++;
								reset_pos (&players[1]);
								if (players[1].lap > 2) {
									flags |= PLY2_TURN;//JOG2 VENCEU
									gameState = FIMDEJOGO;
								}
							}
						}
					}

					//Render
					clear_screen (frameBuf, track, trackFile);
					draw_player (fire, frameBuf, vehicles);
					draw_dollars (frameBuf, dollars);
					draw_player (players[0], frameBuf, vehicles);
					draw_player (players[1], frameBuf, vehicles);
					render_screen(frameBuf);
				}
				break;

			case LOADGAME:
				system("cls");
				printf ("Digite o nome do jogo salvo: ");
				gets (strInput);

				//Se achar arquivo .sv
				if (load_game (strInput, players, track)) {
					trackFile = openTrack (track);
					//Se não achar o arquivo da pista salva no .sv
					if (!trackFile) {
						printf ("Track file not found!\n");
						system ("pause");
						gameState = MENU;
					}
					//Se achar o arquivo da pista salva no .sv
					else {
						//Limpa o buffer da tela
						for (i = 0; i < SCREENH; i++)
							for (j = 0; j < SCREENW; j++)
								frameBuf[i][j] = '\0';

						printf ("Jogo carregado com sucesso!\n\tPista: %s\n\t(C) Confirmar?\n", track);
						strInput[0] = getch();
						gameState = strInput[0] == 'c'? SEMAFORO:
									strInput[0] == 'C'? SEMAFORO:
									MENU;
					}
				}
				//Se não achar .sv
				else {
					printf ("Erro ao carregar jogo (save corrompido ou inexistente)!\n");
					system ("pause");
					gameState = MENU;
				}
				break;

			case FIMDEJOGO:
				system("cls");
				//Limpa a matriz
				for (i = 0; i < SCREENH; i++)
					for (j = 0; j < SCREENW; j++)
						frameBuf[i][j] = '\0';

				//Preenche a matriz com a pista
				if (fgoto_label (trackFile, "FIM")) {
					for (i = 0; i < SCREENH; i++) {
						for (j = 0; j < SCREENW; j++) {
							frameBuf[i][j] = fgetc (trackFile);
							//Se == '\n' passa para a próxima linha, i++ e j = 0
							if (frameBuf[i][j] == '\n') {
								frameBuf[i][j] = '\0';
								break;
							}
							//Se == ';' sair dos 2 loops
							else if (frameBuf[i][j] == ';' || frameBuf[i][j] == EOF) {
								frameBuf[i][j] = '\0';
								i = SCREENH + 1;
								j = SCREENW + 1;
							}
							//Se P posicionar jogadores
							else if (frameBuf[i][j] == 'P') {
								players[flags&PLY_TURN == PLY1_TURN? 0: 1].x = j;
								players[flags&PLY_TURN == PLY1_TURN? 0: 1].y = i;
							}
							else if (frameBuf[i][j] == 'p') {
								players[flags&PLY_TURN == PLY1_TURN? 1: 0].x = j;
								players[flags&PLY_TURN == PLY1_TURN? 1: 0].y = i;
							}
						}//end for (j = 0; j < SCREENW; j++)
					}//end for (i = 0; i < SCREENH; i++)

					//Render
					draw_player (players[0], frameBuf, vehicles);
					draw_player (players[1], frameBuf, vehicles);
					render_screen(frameBuf);
				}
				printf ("Parabéns! Jogador %d venceu!\n\n", flags&PLY_TURN == PLY1_TURN? 1: 2);

                reset_player (&players[0]);
                reset_player (&players[1]);
				system ("pause");
				gameState = MENU;
				break;

			default:
				system("cls");
				printf(
					"Erro: Estado desconhecido!\n\n"
					"(1) Reiniciar Jogo\n"
					"(0) Fechar Jogo\n"
				);
				read_choice (strInput);
				gameState = strInput[0] == 1? MENU: SAIR;
		}
	} while (gameState != SAIR);

	system("cls");
	printf ("\nAdeus e obrigado por jogar!\n\n\t:D\n\n");

	//Fechando arquivos, se abertos
	if (file)
        fclose(file);
	if (trackFile)
		fclose(trackFile);
	if (lang)
		fclose (lang);

	return 0;
}
