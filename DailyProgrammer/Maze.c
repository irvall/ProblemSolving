#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N;
struct nd ***maze;

struct nd {
	int visited;
	char symbol;
	struct nd *l,*r,*u,*d;
};

struct nd *new_nd() {
	struct nd *t;
	t = (struct nd*) malloc(sizeof(struct nd));
	t -> visited = 0;
	t -> symbol = '#';
	t -> l = NULL; 
	t -> r = NULL; 
	t -> u = NULL; 
	t -> d = NULL; 
	return t;
};

void reveal()
{
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			if(maze[i][j] -> visited == 1) printf(" ");
			else printf("%c", maze[i][j] -> symbol);
		}
		printf("\n");
	}
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
