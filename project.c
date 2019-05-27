#include <stdio.h>
#include <stdbool.h>

#define MAX 2415
#define STRING 10

int top=0;
int stack[MAX*MAX];

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

void transition(int *firstIndex,int *secondIndex,int **adjacencyMatrix,int *words[MAX])
{
	int path[MAX];
	int pathIndex=0,connection=0,control;
	int founded=0;
	
	push(*firstIndex);
	path[pathIndex++]=*firstIndex;
	while(!isEmpty())
	{
		//printf("\ngirdi1");

		while((adjacencyMatrix[*firstIndex][connection] != 1)
				&& (connection<MAX))
				{
					//printf("%d\n", adjacencyMatrix[*firstIndex][connection]);
	 				connection++;
				}

		if(connection<MAX && (*secondIndex != connection))
		{
			//printf("\ngirdi3");

				if(controlPath(connection,path,pathIndex)==false)
				{
					//printf("\ngirdi5");
				//	printf("check:%d\n", controlPath(connection,path,pathIndex));

						push(connection);
						//printf("%d\n", peek());
				}
				connection++;
			
		}
		else if(connection<MAX && (*secondIndex == connection) )
		{
				printf("\n%d",pathIndex);
				printPath(path,pathIndex,words);
				founded=1;
				connection++;
		}
		else
		{
			//printf("\ngirdi7");
			control=pop();
			while(  (controlPath(control,path,pathIndex)==true)
					&& (isEmpty()!=1))
					{
						pathIndex--;
						control=pop();
					}
			if(!isEmpty())
			{
				*firstIndex=control;
				push(*firstIndex);
				path[pathIndex++]=*firstIndex;
				connection=0;
			}
			
		}
	}
	
	while(isEmpty() != 1);
	if(founded==0)
	{
		printf("There is no path for these words.b");
	}
	


}

int controlPath(int connection,int path[MAX],int pathIndex)
{
	int i=0;
 	while((connection != path[i]) && (i<pathIndex))
	{
		i++;
	}
	if(i<pathIndex)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void printPath(int path[MAX],int size,int *words[MAX])
{
	int i;
	printf("%d ",size);
	for(i=0; i<size; i++)
	{
		printf("%s-->", words[path[i]]);
	}
	printf("%d words changed.", size);
}

int isEmpty()
{
	if(top==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isFull()
{
	if(top==MAX)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int pop()
{
	int data;
	if(!isEmpty())
	{
		data=stack[top--];
 		//printf("\n[INFO]! This is the pop value: %d\n", data);
		return data;
	}
	else
	{
		printf("[ERROR]! Empty stack.\n");
		return -1;
	}
}

void push(int data)
{
	if(!isFull())
	{
		top++;
		stack[top]=data;
	}
	else
	{
		printf("[ERROR]! Stack is full.\n");
	}
	//printf("[INFO]! Data pushed succesfully %d.\n", data);
}

int peek()
{
	if(!isEmpty())
	{
		return stack[top];
	}
}

void main()
{
	FILE *file;
	char *words[MAX];
	char line[STRING],temp[STRING],string1[STRING],string2[STRING];
	int i=0,j=0;
	int **adjacencyMatrix;
	int *firstIndex,*secondIndex;
	
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


	/*for(i=0; i<5; i++)
	{
		for(j=0; j<5; j++)
		{
			printf("%d", adjacencyMatrix[i][j]);
		}
		printf("\n");
	} */
 	checkConnection(words,adjacencyMatrix,string1,string2,firstIndex,secondIndex);
 	
 	transition(firstIndex,secondIndex,adjacencyMatrix,words);
	fclose(file);
}
