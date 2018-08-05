#include <stdio.h>
#include <stdlib.h>

int find_placing(int score, int *arr, int l, int h)
{
	int i = (l + h) >> 1, k = arr[i];
	if (i == 0 && score >= k)
		return 1;
	if ((h - l) <= 1)
		return i + 2;
	if (score > k)
		return find_placing(score, arr, l, i);
	if (k > score)
		return find_placing(score, arr, i, h);
	return i + 1;
}

int main()
{
	int *arr, i, p, n, m, t;
	scanf("%d", &n);
	arr = (int *)malloc(n * sizeof(int));
	p = -1;
	for (i = 0; i < n; i++)
	{
		scanf("%d", &t);
		if (t == p)
		{
			--i;
			--n;
			continue;
		}
		else
		{
			arr[i] = t;
			p = t;
		}
	}
	scanf("%d", &m);
	for (i = 0; i < m; i++)
	{
		scanf("%d", &t);
		printf("%d\n", find_placing(t, arr, 0, n));
	}
	return 0;
}
