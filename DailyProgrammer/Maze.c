#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N;
struct nd ***maze;

struct nd {
	int state; //0 - not visited, 1 - visited, 2 - wall
	struct nd *l,*r,*u,*d;
};

struct nd *new_nd() {
	struct nd *t;
	t = (struct nd*) malloc(sizeof(struct nd));
	t -> state = 2;
	t -> l = NULL; 
	t -> r = NULL; 
	t -> u = NULL; 
	t -> d = NULL; 
	return t;
};

void reveal()
{
	char not_visited = ' ';
	char wall = '#';
	char *visited = "·";
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			struct nd *n = maze[i][j];
			switch (n -> state) {
				case 0:
					printf("%c", not_visited);
					break;
				case 1:
					printf("%s", visited);
					break;
				case 2:
					printf("%c", wall);
			}
		}
		printf("\n");
	}
}

void dig()
{
	//todo: dig out maze
}

int main(int argc, char **argv)
{
	N = 10;
	maze = (struct nd***) malloc(N * N * sizeof(struct nd**));
	for(int i = 0; i < N; i++) {
		maze[i] = (struct nd**) malloc(N * sizeof(struct nd*));
		for(int j = 0; j < N; j++) {
			maze[i][j] = new_nd();
		}	
	}
	reveal();
	return 0;
}
