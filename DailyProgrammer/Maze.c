#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int N;
struct nd ***maze;

void set_mode(int want_key)
{
	static struct termios old, new;
	if (!want_key) {
		tcsetattr(STDIN_FILENO, TCSANOW, &old);
		return;
	}

	tcgetattr(STDIN_FILENO, &old);
	new = old;
	new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
}

int get_key()
{
	int c = 0;
	struct timeval tv;
	fd_set fs;
	tv.tv_usec = tv.tv_sec = 0;

	FD_ZERO(&fs);
	FD_SET(STDIN_FILENO, &fs);
	select(STDIN_FILENO + 1, &fs, 0, 0, &tv);

	if (FD_ISSET(STDIN_FILENO, &fs)) {
		c = getchar();
		set_mode(0);
	}
	return c;
}

struct nd {
	int state; //0- not visited, 1- visited, 2- wall, 3- player
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

int rand_range(int a, int b)
{
	int r = rand() % (b-a);
	return r + a;
}

int outer_wall(struct nd *n)
{
	if((n -> d == NULL || n -> u == NULL 
	|| n -> l == NULL || n -> r == NULL)
	&& n -> state == 2) 
		return 1;
	return 0;	
}

void reveal()
{
	char visited = '-';
	char not_visited = ' ';
	char wall = '#';
	char player = '@';
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			switch (maze[i][j] -> state) {
				case 0:
					printf("%c", not_visited);
					break;
				case 1:
					printf("%c", visited);
					break;
				case 2:
					printf("%c", wall);
					break;
				case 3:
					printf("%c", player);
					break;
			}
		}
		printf("\n");
	}
	printf("\n");
}

void visit(struct nd *n) 
{
	n -> state = 1;
}

int visited(struct nd *n) 
{
	return n -> state == 1 ? 1 : 0;
}

void set_player(struct nd *n)
{
	n -> state = 3;
}

struct nd *up(struct nd *n) {
	if(n -> u == NULL || outer_wall(n -> u))
		return NULL;
	else return n -> u;
}

struct nd *down(struct nd *n) {
	if(n -> d == NULL || outer_wall(n -> d))
		return NULL;
	else return n -> d;
}

struct nd *left(struct nd *n) {
	if(n -> l == NULL || outer_wall(n -> l))
		return NULL;
	else return n -> l;
}

struct nd *right(struct nd *n) {
	if(n -> r == NULL || outer_wall(n -> r))
		return NULL;
	else return n -> r;
}

void dig()
{
	char m;
	int start[2] 	= {rand_range(1,N-1),0};
	int end[2]	= {rand_range(1,N-1),N-1}; 
	struct nd *start_nd = maze[start[0]][start[1]];
	struct nd *end_nd = maze[end[0]][end[1]];
	struct nd *current_nd = start_nd;
	visit(end_nd);	
	set_player(start_nd);
	reveal();
	int c;
	for(;;) {
		set_mode(1);
		while (!(c = get_key())) usleep(10000);
		visit(current_nd);
		switch(c) {
			case 'w': {
				struct nd *tmp = up(current_nd);
				if(tmp == NULL) continue;
				if(tmp == start_nd || tmp == end_nd)
					current_nd = tmp;
				if(!outer_wall(tmp))
					current_nd = tmp;	
				break;
				  }
			case 'a': {
				struct nd *tmp = left(current_nd);
				if(tmp == NULL) continue;
				if(tmp == start_nd || tmp == end_nd)
					current_nd = tmp;
				if(!outer_wall(tmp))
					current_nd = tmp;
				break;
				  }
			case 's': {
				struct nd *tmp = down(current_nd);
				if(tmp == NULL) continue;
				if(tmp == start_nd || tmp == end_nd)
					current_nd = tmp;
				if(!outer_wall(tmp))
					current_nd = tmp;
				break;
				  }			
			case 'd': {
				struct nd *tmp = right(current_nd);
				if(tmp == NULL) continue;
				if(tmp == start_nd || tmp == end_nd)
					current_nd = tmp;
				if(!outer_wall(tmp))
					current_nd = tmp;
				break;
				  }
			default: continue;
		}
		set_player(current_nd);
		reveal();	
		if(current_nd == end_nd) {
			printf("Your winner ,'o)\n");
			return;
		}
	}
}

void show_neighbours(struct nd *n)
{
	if(n -> u != NULL) printf("UP;");
	if(n -> d != NULL) printf("DOWN;");
	if(n -> l != NULL) printf("LEFT;");
	if(n -> r != NULL) printf("RIGHT;");
	printf("\n");			
}

int main(int argc, char **argv)
{
		
	srand(time(NULL));
	N = 10;
	maze = (struct nd***) malloc(N * N * sizeof(struct nd**));
	for(int i = 0; i < N; i++) {
		maze[i] = (struct nd**) malloc(N * sizeof(struct nd*));
		for(int j = 0; j < N; j++) {
			maze[i][j] = new_nd();
		}	
	}
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			if(j > 0) 	maze[i][j] -> l = maze[i][j-1];
			if(j < N-1) 	maze[i][j] -> r = maze[i][j+1];
			if(i > 0) 	maze[i][j] -> u = maze[i-1][j];
			if(i < N-1) 	maze[i][j] -> d = maze[i+1][j];
		}
	}
	dig();
	return 0;
}
