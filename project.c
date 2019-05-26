#include <stdio.h>
#include <stdbool.h>

#define MAX 2415
#define STRING 10


int ** createMatrix(int *words[MAX],int **adjacencyMatrix)
{
	int i,j;
	char *word;
	
	word=(int *)malloc(sizeof(int)*STRING);
	adjacencyMatrix=(int **)malloc(sizeof(int*)*MAX);
	for(i=0; i<MAX; i++)
	{
		adjacencyMatrix[i]=(int *)malloc(sizeof(int)*MAX);
 	}
	for(i=0; i<MAX; i++)
	{
		strcpy(word,words[i]);
		for(j=0; j<MAX; j++)
		{
			  if(isOneLetter(word,words[j])==1)
			  {

	  			adjacencyMatrix[i][j]=1;
			  }
			  else
			  {
	  			adjacencyMatrix[i][j]=0;
			  }

		}
 	}
	return adjacencyMatrix;

}

int isOneLetter(char *string1,char *string2)
{
	int i=0,length,distance=0;
	length=strlen(string1);
	for(i=0; i<length; i++)
	{
		if(string1[i]-string2[i] != 0)
		{
			distance++;
		}
	}

	if(distance==1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

void checkConnection(char *words[MAX],int**adjacencyMatrix,char string1[STRING],char string2[STRING])
{
	int i=0,j=0;
	
	while((strcmp(string1,words[i]) != 0) && (i<MAX))
	{
  		i++;
	}
	while((strcmp(string2,words[j]) != 0) && (j<MAX))
	{
		j++;

	}
	
	if(adjacencyMatrix[i][j]==1)
	{
		printf("There is a connection between these two: %s and %s.", string1, string2);
	}
	else
	{
		printf("There is not a connection between these two: %s and %s.", string1, string2);
	}
}

void transition()
{
	
}

void main()
{
	FILE *file;
	char *words[MAX];
	char line[STRING],temp[STRING],string1[STRING],string2[STRING];
	int i=0,j=0;
	int **adjacencyMatrix;
	
	file=fopen("kelime.txt", "r");
	if(file==NULL)
	{
		printf("[ERROR]! File can not open.\n");
		return -1;
	}
	else
	{
		printf("[INFORMATION]! File opened with succes.\n");
	}

	while(!feof(file))
	{
		
		fgets(line,sizeof (line),file);
		words[i]=(char *)malloc(sizeof(char)*STRING);
  		strcpy(words[i],line);
		i++;
	}

	printf("Enter first string, please: ");
	scanf("%s", string1);
	strcat(string1,"\n");
	
	printf("Enter second string, please: ");
 	scanf("%s", string2);
 	strcat(string2,"\n");

	adjacencyMatrix=createMatrix(words,adjacencyMatrix);


	/*for(i=0; i<5; i++)
	{
		for(j=0; j<5; j++)
		{
			printf("%d", adjacencyMatrix[i][j]);
		}
		printf("\n");
	} */
 	checkConnection(words,adjacencyMatrix,string1,string2);
	fclose(file);
}
