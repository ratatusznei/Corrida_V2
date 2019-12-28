#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "player.h"
#include "func.h"

/*
	Funções relacionadas com arquivos
*/
char fgoto_label (FILE *file, const char *label) {
	char 	i = 0,	//Contador
			buf;	//Buffer de caracteres

	rewind (file);

	while (buf != EOF) {
		buf = fgetc (file);

		if (i == 0)
			i = buf == ';'? 1: 0;
		else if (i > 0) {
			if (buf == label[i-1])
				i++;
			else if (buf == '\n' && label[i-1] == '\0')
				return 1;
			else
				i = 0;
		}
	}
	return 0;
}

char fprint_til_char (FILE *file, const char c) {
	char buf = fgetc (file);
	while (buf != c && buf != EOF) {
		putchar (buf);
		buf = fgetc (file);
	}
	return buf == EOF? 0: 1;
}

char fprint_block (FILE *file, const char *label) {
	if (!fgoto_label(file, label)) {
		printf ("ERRO: label \"%s\" not found on fprint_block\n\n", label);
		system ("pause");
		return 0;
	}

	char buf = fgetc (file);
	while (buf != ';' && buf != EOF) {
		putchar (buf);
		buf = fgetc (file);
	}
	return 1;
}

int fget_width (FILE *file) {
    int w;
    char buffer;
    for (w = 0, buffer = fgetc(file); buffer != '\n' && buffer != EOF; w++)
        buffer = fgetc(file);

    rewind(file);
    return w;
}

int fget_height (FILE *file) {
    int h, w;
    char buffer;

    for (h = 0, buffer = fgetc(file); buffer != ';' && buffer != EOF; h++) {
        for (w = 0; buffer != '\n' && buffer != EOF; w++)
            buffer = fgetc (file);
        buffer = fgetc (file);
    }

    rewind(file);
    return h;
}

FILE *openTrack (char *trackName) {
	FILE *file = NULL;
	char str[SCREENW];

	sprintf (str, "res\\materials\\%s.txt", trackName);
	file = fopen (str, "r");
	if (!file) {
		sprintf (str, "res\\user\\user_tracks\\%s.txt", trackName);
		file = fopen (str, "r");
	}

	return file;
}


char save_game (char *saveName, player *ps, char *trackName) {
	char sv[MAXINPUT],
		savedBytes;

	FILE *saveFile = NULL;

	player pscopy[] = {
		cript_player(ps[0]),
		cript_player(ps[1])
	};

	sprintf (sv, SAVEPATH, saveName);
	saveFile = fopen(sv, "wb");
	if (!saveFile)
		return 0;

	savedBytes =  fwrite (pscopy, sizeof (char), sizeof (pscopy)/sizeof(char), saveFile);
	savedBytes += fwrite (trackName, sizeof (char), MAXINPUT, saveFile);

	if (savedBytes != MAXINPUT + sizeof (pscopy)/sizeof(char))
		return 0;
	fclose (saveFile);
	return 1;
}

char load_game (char *saveName, player *ps, char *track) {
	FILE *saveFile = NULL;
	char sv[MAXINPUT];
	char loadedBytes;

	sprintf (sv, SAVEPATH, saveName);
	saveFile = fopen(sv, "rb");
	if (!saveFile)
		return 0;

	loadedBytes =  fread (ps, sizeof (char), 2*sizeof (player)/sizeof(char), saveFile);
	loadedBytes += fread (track, sizeof (char), MAXINPUT, saveFile);

	ps[0] = cript_player(ps[0]);
	ps[1] = cript_player(ps[1]);

	if (loadedBytes != MAXINPUT + 2*sizeof (player)/sizeof(char))
		return 0;

	return 1;
}
