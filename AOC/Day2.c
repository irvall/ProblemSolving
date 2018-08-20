#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int calc_row(char *row)
{
	int i,j,n,v,min,max;
	n = strlen(row);
	min = INT_MAX;
	max = INT_MIN;
	for(i=j=0;i<n;i++,j=0) {
		char tmp[8];
		while(i < n && row[i] != ' ' && row[i] != '\t') 
			tmp[j++] = row[i++];
		tmp[j] = '\0';
		v = atoi(tmp);
		if(v > max) max = v;
		if(min > v) min = v;
	}
	return max - min;
}

int main(int argc, char **argv)
{
	int checksum = 0;
	char const* const filename = argv[1];
	FILE* file = fopen(filename, "r");
	char line[256];
	while(fgets(line, sizeof(line), file))
		checksum += calc_row(line);
	printf("Checksum: %d\n", checksum);
	fclose(file);
	return 0;
}
