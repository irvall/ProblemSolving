#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char alphabet[37] = "#_23456789abcdefghijklmnopqrstuvwxyz";

int rand_range(int a, int b)
{
	return a + rand() % (b-a);;
}

void swap(char *a, char *b)
{
	char t = *a;
	*a = *b;
	*b = t;
}

char* new_state()
{
	int i;
	char *out;
	out = (char*) malloc(37 * sizeof(char));
	memcpy(out, alphabet, 37);
	for(i = 0; i < 36; i++) {
		char *c = out + rand_range(i,36);
		swap(out+i, c);
	}
	return out;
}

void shift_row(int row, int n)
{
	char temp[7];
	memcpy(temp, alphabet+(row*6)+(6-n), n);
	memcpy(temp+n, alphabet+(row*6), 6-n);
	memcpy(alphabet+(row*6), temp, 6);
}

void shift_col(int col, int n)
{
	int i,j;
	char temp[7];
	for(i = col+((6-n)*6), j = 0; j < n; i += 6, j++)
		temp[j] = alphabet[i];
	for(i = col; j < 6; i += 6, j++)
		temp[j] = alphabet[i];
	for(i = col, j = 0; j < 6; i += 6, j++)
		alphabet[i] = temp[j];
}

int* find(char c)
{
	int i, *out;
	out = (int*) malloc(2 * sizeof(int));
	for(i = 0; i < 36; i++)
		if(alphabet[i] == c) break;
	out[0] = i / 6;
	out[1] = i % 6;
	return out;
}

void view_matrix(char *s)
{
	int i;
	for(i = 0; i < 36; i++) {
		if(i > 0 && i % 6 == 0)
			printf("\n");
		printf("%c ", s[i]);
	}
	printf("\n");
}

void decrypt_message(char *ciphertext)
{
	//todo
}
int main(int argc, char **argv)
{
	srand(time(NULL));
	char *s = new_state();
	*alphabet = s;
	int *k = find('#');	
	printf("(%d,%d)\n", k[0], k[1]);
	view_matrix(alphabet);
	return 0;
}
