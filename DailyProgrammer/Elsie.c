#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char alphabet[37] = "#_23456789abcdefghijklmnopqrstuvwxyz";

//Shift row n times right.
void shift_row(int row, int n)
{
	char temp[7];
	memcpy(temp, alphabet+(row*6)+(6-n), n);
	memcpy(temp+n, alphabet+(row*6), 6-n);
	memcpy(alphabet+(row*6), temp, 6);
}

//Shift column n times downwards.
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

// Find given char and return its position [row,col]. 
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

//Print string as a 6x6 matrix.
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
	return 0;
}
