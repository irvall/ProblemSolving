#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_STRING_LENGTH 25

float COMMISION;
int NPERSONS, NPRODUCTS;

struct Person {
	char *name;
	int *expenses; 
        int *revenue;
};

struct Person new_person(char *pname)
{
	struct Person p;
	p.name= pname;
	p.expenses = (int*)malloc(NPRODUCTS * sizeof(int));
	p.revenue  = (int*)malloc(NPRODUCTS * sizeof(int));
	return p;
};

int array_sum(int *a)
{
	int i,out;
	for(i = 0, out = 0; i < NPRODUCTS; i++) 
		out += a[i];
	return out;
}

void calculate_commisions(struct Person *persons)
{
	int i,j;
	printf("\t\t");
	for(i = 0; i < NPERSONS; i++) 
		printf("%s\t", persons[i].name);
	
	printf("\nCommisions\t");
	for(i = 0; i < NPERSONS; i++) 
		printf("%.2f\t", (array_sum(persons[i].revenue) - array_sum(persons[i].expenses)) * (COMMISION / 100.0));
	printf("\n");	
}

int main(int argc, char **argv)
{
	NPRODUCTS 	= atoi(argv[1]);
	NPERSONS	= atoi(argv[2]);
	COMMISION	= atof(argv[3]);
	printf("%d \n", NPRODUCTS);
	printf("%d \n", NPERSONS);
	printf("%f \n", COMMISION);
	int i,j,n;
	struct Person *persons;
	persons = (struct Person*)malloc(NPERSONS * sizeof(struct Person));
	char t[DEFAULT_STRING_LENGTH], p[DEFAULT_STRING_LENGTH];
	scanf("%s", t);
	for(i = 0; i < NPERSONS; i++) {
		scanf("%s", t);
		persons[i] = new_person(t);
		printf("Name: %s\n", persons[i].name);
	}
	for(j = 0; j < NPRODUCTS; j++) {	
		scanf("%s", p);
		printf("P %s\n", p);
		for(i = 0; i < NPERSONS; i++) {
			scanf("%d", &persons[i].revenue[j]);
			printf("%d ", persons[i].revenue[j]);
		}
		printf("\n");
	}
	for(i = 0; i <= NPRODUCTS; ++i) {
		scanf(" %s", t);
		printf("t %s\n", t);
	}
	for(j = 0; j < NPRODUCTS; j++) {	
		scanf("%s", p);
		for(i = 0; i < NPERSONS; i++) {
			scanf("%d", &persons[i].expenses[j]);
		}
	}
	calculate_commisions(persons);
	return 0;
}
