#include<stdio.h>
#include<stdlib.h>

struct node
{
	int process;
	int arrival;
	int burst;
};

//Function for swapping structures.
void swap(struct node *p, struct node *q)
{
	struct node temp = *p;
	*p = *q;
	*q = temp;
}

int main(int argc, char const *argv[])
{
	int n, t, i, j, limit=0, count=0, min, k=0;
	FILE *inputFile, *outputFile;

	//Input is taken from FILE.
	inputFile = fopen(argv[1], "r");
	if(inputFile == NULL)
	{
		printf("\nError in reading file in read  mode.\n");
		exit(0);
	}

	fscanf(inputFile, "%d", &n); //Number of processes
	fscanf(inputFile, "%d", &t); //Time Quantum

	struct node round[n];
	int p[n], at[n], bt[n];

	for(i=0; i<n; i++)
	{
		fscanf(inputFile, "%d", &round[i].process);
		fscanf(inputFile, "%d", &round[i].arrival);
		fscanf(inputFile, "%d", &round[i].burst);
	}
	fclose(inputFile);

	//Sorting array of structures in order of arrival time.
	for(i=0; i<n-1; i++)
	{
		min = i;
		for(j=i+1; j<n; j++)
			if(round[j].arrival < round[min].arrival)
				min = j;
		swap(&round[min], &round[i]);
	}

	//Duplicating Arrival and Burst time in arrays.
	for(i=0; i<n; i++)
	{
		p[i] = round[i].process;
		at[i] = round[i].arrival;
		bt[i] = round[i].burst;
	}

	for(i=0; i<n; i++)
		limit += bt[i];
	
	if(round[0].arrival != 0)   // Condition to check if arrival time is not starting with '0'.
		limit += round[0].arrival;

	int num = n*3;
	int queue[num], ct[n];
	int front=0, rear=-1;
	for(i=0; i<=t; i++)
		if(round[i].arrival <= t)
		{
			queue[++rear] = round[i].process;
			k++;
		}

	for(i=0; i<n; i++)
		ct[i] = 0;

	//Output is taken in FILE.
	outputFile = fopen(argv[2], "w+");

	//GANTT Chart
	fprintf(outputFile, "Gantt Chart\n\n");
	while(count != limit)
	{
		if(round[queue[front]].burst >= t)
		{
			fprintf(outputFile, "(%d, P%d) ", count, queue[front]+1);
                        round[queue[front]].burst -= t;
                        count += t;

			ct[queue[front]] = count;

			if(round[queue[front]].burst != 0)
				queue[++rear] = queue[front];

			front++;
		}
		else if(round[queue[front]].burst > 0 && round[queue[front]].burst < t)
		{
			fprintf(outputFile, " (%d, P%d) ", count, queue[front]+1);
			count += round[queue[front]].burst;

			ct[queue[front]] = count;
			round[queue[front]].burst = 0;
			front++;
		}

		if(round[k].arrival < (t*2) && k != n)
			queue[++rear] = round[k++].process;
	}

	int wt[n], tat[n];

	//Calculating Turn Around Time and Waiting Time
	for(i=0; i<n; i++)
	{
		tat[i] = ct[i] - at[i];
		wt[i] = tat[i] - bt[i];
	}

	fprintf(outputFile, "\n\n   AT  BT  CT  TAT  WT\n");

	for(i=0; i<n; i++)
		fprintf(outputFile, "P%d  %d  %d   %d   %d   %d\n", p[i]+1, at[i], bt[i], ct[i], tat[i], wt[i]);

	fclose(outputFile);
	return 0;
}	       
