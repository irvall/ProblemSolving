#include <string.h>
#include <stdio.h>
int main(int argc, char **argv)
{
        int i,n,sum;
        n = strlen(argv[1]);
        i = sum = 0;
        for(;i <= n;i++)
                if(argv[1][i] == argv[1][(i+1) % n])
                        sum += argv[1][i]-48;
        printf("\nResult: %d\n", sum);
        return 0;
}
