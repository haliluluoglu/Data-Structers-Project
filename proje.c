#include <stdio.h>
#include <stdbool.h>

#define MAX 2415
#define STRING 10

int top=0;
int queue[MAX];
int front=-1,rear=-1;


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

void checkConnection(char *words[MAX],int**adjacencyMatrix,char string1[STRING],char string2[STRING]
					,int *firstIndex,int *secondIndex)
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
		printf("\nThere is a connection between these two: %s and %s\n", string1, string2);
	}
	else
	{
		printf("\nThere is not a connection between these two: %s and %s\n", string1, string2);
	}

	*firstIndex=i;
	*secondIndex=j;
}

int *transition(int *firstIndex,int *secondIndex,int **adjacencyMatrix,
					int *words[MAX])
{
	int control,counter=0,found=0;
	int backupArray[MAX];

  	enqueue(*firstIndex);
  	
	while(isEmpty()!=1)
	{
  		control=dequeue();
  		counter++;
		if(control==*secondIndex)
  		{
  			printf("-->%s", words[*secondIndex]);
			printf("---->%d changed with.", counter);
			return;
		}
		else
		{
			printf("-->%s", words[control]);
			addQueue(adjacencyMatrix,control,backupArray);	
		}
	}
	printf("[INFO]! Could not find any path.\n");
}

void addQueue(int **adjacencyMatrix,int control,int backupArray[MAX])
{
	int i;
	for(i=0; i<MAX; i++)
	{
		if(adjacencyMatrix[control][i]==1)
		{
			if(backupArray[i] != adjacencyMatrix[control][i])
			{
				backupArray[i] = adjacencyMatrix[control][i];
				enqueue(i);
			}
		}
	}
}

int isEmpty()
{
	if(top==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int isFull()
{
	if(top==MAX)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void enqueue(int value)
{
	if(!isFull())
	{
		if(isEmpty())
		{
			queue[0]=value;
			rear=0; front=0;
			top=1;
		}
		else
		{
			rear++;
			queue[rear]=value;
			top++;
		}
	}
	else
	{
		printf("[ERROR]! Queue is full.\n");
	}
}
int dequeue()
{
	int value;
	if(!isEmpty())
	{
		value=queue[front];
		front++;
		top--;
		return value;
	}
	else
	{
		printf("[ERROR]! Queue is empty.\n");
	}
}

void main()
{
	FILE *file;
	char *words[MAX];
	char line[STRING],temp[STRING],string1[STRING],string2[STRING];
	int i=0,j=0,k;
	int **adjacencyMatrix;
	int *firstIndex,*secondIndex;
	int backupArray[MAX];

	firstIndex=(int *)malloc(sizeof(int));
	secondIndex=(int *)malloc(sizeof(int));

	file=fopen("kelime.txt", "r");
	if(file==NULL)
	{
		printf("[ERROR]! File can not open.\n");
		return -1;
	}
	else
	{
		printf("[INFO]! File opened with succes.\n");
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

 	checkConnection(words,adjacencyMatrix,string1,string2,firstIndex,secondIndex);

 	transition(firstIndex,secondIndex,adjacencyMatrix,words);

	fclose(file);
}
