#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	int n, r=3, i, j, k=0, z;
	
	FILE *inputFile;
	inputFile = fopen(argv[1], "r");
	if(inputFile == NULL)
	{
		printf("\nError in opening file in read mode.\n");
		exit(0);
	}
	fscanf(inputFile, "%d", &n);

	int available[r];

	for(i=0; i<r; i++)
		fscanf(inputFile, "%d", &available[i]);
	
	int allocation[n][r], request[n][r], max[n][r];

	for(i=0; i<n; i++)
	{
		for(j=0; j<r; j++)
			fscanf(inputFile, "%d", &allocation[i][j]);

		for(j=0; j<r; j++)
			fscanf(inputFile, "%d", &request[i][j]);

		for(j=0; j<r; j++)
			fscanf(inputFile, "%d", &max[i][j]);
	}

	int count[r];

	for(i=0; i<r; i++)
		count[i] = 0;

	while(k != r)
	{
		for(i=0; i<n; i++)
			count[k] += allocation[i][k];
		k++;
	}

	for(i=0; i<r; i++)
	         available[i] -= count[i];

	for(i=0; i<n; i++)
		for(j=0; j<r; j++)
		{
			if(max[i][j] < request[i][j])
			{
				printf("Request by P%d is greater than maximum resource.\n", i);
				exit(0);
			}
		}

	int a=0, b=1, c=2, limit=0;

	while(limit != n)
	{
		for(i=0; i<n; i++)
	        {
			if(available[a] >= request[i][a] && available[b] >= request[i][b] && available[c] >= request[i][c])
		        {
				printf("\nSafe Sequence : P%d ", i);	
		                limit++;
	                        available[a] += allocation[i][a];
	                        available[b] += allocation[i][b];
	                        available[c] += allocation[i][c];

		                request[i][a] = 999;
		                request[i][b] = 999;
		                request[i][c] = 999;

				printf("\nAvailable resources are : ");
				for(z=0; z<r; z++)
					printf("%d ", available[z]);
			}
	        }
	}

	printf("\n");

	return 0;
	
}
	





	
