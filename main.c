#include "gui.h"



//void get_file(const char *, cstring, int);
void get_title(const char *, cstring *);
void get_format(const char *, int *, QualiT **);



int main (int argc, char *argv[])
{
	gui_init(&argc, &argv);
	gui_run();

//  free(quality);
//  free(title);
    return 0;
}



//Deperecated
/*void get_file(const char * url, cstring outname, int index) {
	cstring oarg = "-o";
	cstring farg = "-f";
	cstring carg = "-c";
	cstring buffer = malloc(128*sizeof(char));
	cstring value[5];
	sprintf(*value, "%d", quality[index]->value);
	FILE * output;
	int pipes[2];
	GtkTextIter iter;
	GtkTextMark *mark;


	pipe(pipes);
	pid_t pid = fork();
	if (pid == 0) {
		dup2(pipes[1],STDOUT_FILENO);
		close(pipes[1]);
		execl(YDLPATH, YDLPATH, carg, farg, value, oarg,outname,url,NULL );
	} else if (pid > 0) {
		close(pipes[1]);
		output = fdopen(pipes[0], "r");
		while(fgets(buffer, 128, output) != NULL) {
			mark = gtk_text_buffer_get_insert(gui->txtBuffer);
			gtk_text_buffer_get_iter_at_mark(gui->txtBuffer,&iter,mark);
			gtk_text_buffer_insert(gui->txtBuffer,&iter,buffer,-1);
		}
	}
	free(buffer);
}*/


void get_title(const char * url, cstring * t) {
	cstring targ = "--get-title";
	FILE * output;
//	int status;
	int pipes[2];
	pipe(pipes);
	pid_t pid = fork();
	if (pid == 0) {
		dup2(pipes[1],STDOUT_FILENO);
		close(pipes[1]);
		execl(YDLPATH, YDLPATH, url, targ,NULL );
	} else if (pid > 0) {
		close(pipes[1]);
		output = fdopen(pipes[0], "r");
		fscanf(output,"%128[^\n]",*t);
	}
	close(pipes[0]);
}

void get_format(const char * url, int * size, QualiT ** q) {
	puts("get_format function:");
	char* farg = "-F";
	cstring buffer = malloc(1025 * sizeof(char));
	cstring * lines = malloc( 20 * sizeof(cstring));
	FILE * output;
//	int status;
	int pipes[2];
	pipe(pipes);
	pid_t pid = fork();
	if (pid == 0) {
		dup2(pipes[1],STDOUT_FILENO);
	    close(pipes[1]);
		execl(YDLPATH,YDLPATH,url,farg,NULL);
	} else if (pid>0) {
		close(pipes[1]);
		output = fdopen(pipes[0], "r");
//		wait(&status);
		fscanf(output,"%1024[^\r]",buffer);
	}

	cstring line;
	line = strtok(buffer, "\n");
	int sz = 0;
//	*size = 0;
	int printer = 0;
	puts("Available formats:");
	while(line != NULL) {
		if (strcasestr(line, "format code") != NULL) {
//		if (!strcmp(line,"Available formats:")) {
			printer = 1;
			line = strtok (NULL, "\n");
		}
		if (printer == 1 ) {
			lines[sz] = line;
			printf("%s\n", lines[sz]);
			++sz;
		}
		line = strtok (NULL,"\n");
	}

	puts("Convert to QualiT:");
	int l;
	for (l=0;l<sz;++l) {

		int k;
		cstring subs[3];
		char fline[strlen(lines[l])];

		int c, a = 0;
		for (c = 0; c < strlen(lines[l]); ++c) {
			if( (lines[l][c] != ' ' && lines[l][c+1] != ' ') ||
				(lines[l][c] != ' ' && lines[l][c+1] == ' ') ||
				(lines[l][c] == ' ' && lines[l][c+1] != ' ')) {
				if (lines[l][c] == ' ' && lines[l][c+1] != ' ' && lines[l][c-1] == ' ')
					lines[l][c] = '\t';
				fline[a++] = lines[l][c];
				fline[a] = '\0';
			}
		}
		printf("%s line: %d/%d\n", fline, l, sz);
//		exit(0);


//		puts("STROK FLINE");
		if (strcmp(fline, "")) {
			cstring ps = strtok(fline, "\t");
			for (k=0;k<3;++k) {
				subs[k] = ps;
	//			printf("%s[%d]%s", subs[k], k, (k==2 ? "\n" : " + "));
				ps = strtok(NULL, "\t");
			}

	//		QualiT * newq = malloc(sizeof(QualiT));
	//		newq->value = strtol(subs[0], NULL , 10);
	//		newq->format = subs[1];
	//		newq->size = subs[2];
	//		quality[l] = newq;
			q[l] = malloc(sizeof(QualiT));
			q[l]->format = malloc(strlen(subs[1])*sizeof(char));
			q[l]->size = malloc(strlen(subs[2])*sizeof(char));

			q[l]->value = strtol(subs[0], NULL , 10);
			sprintf(q[l]->format, "%s%c",subs[1],'\0');
			sprintf(q[l]->size, "%s%c",subs[2],'\0');
		}
		//https://www.youtube.com/watch?v=4dL_hwSfD4w
//		free(format);

	}
	*size = sz;
//	exit(0);
//	free(buffer);
//	for (l=0; l<*size;++l) printf("%s  %d\n",quality[l].format, quality[l].value);
//	*size = sz;
//	exit(0);
}

