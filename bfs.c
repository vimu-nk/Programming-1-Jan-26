#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX 100
#define MAX_NODE_LEN 10

int adjMat[MAX][MAX];
int visited[MAX];
char nodes[MAX][MAX_NODE_LEN];
int n, type; //if type == 1 then directed, and if type == 0 then undirected

typedef struct
{
    int data[MAX];
    int front;
    int rear;
} Queue;

void initQ(Queue *q)
{
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q)
{
    return q->rear == -1;
}

int isFull(Queue *q)
{
    return q->front == MAX - 1;
}

void enqueue(Queue *q, int value)
{
    if(isFull(q))
    {
        printf("Queue is full. Cannot enqueue %d\n", value);
        exit(1);
    }

    if(isEmpty(q))
    {
        q->front = 0;
    }

    q->rear++;
    q->data[q->rear] = value;
    printf("Enqueued %d\n", value);
}

int dequeue(Queue *q)
{
    if(isEmpty(q))
    {
        printf("Queue is empty. Cannot dequeue.\n");
        exit(1);
    }

    int value = q->data[q->front];

    if(q->front == q->rear)
    {
        q->front = -1;
        q->rear = -1;
    }
    else
    {
        q->front++;
    }

    printf("Dequeued %d\n", value);

    return value;
}

int maxNum()
{
    int max = adjMat[0][0];

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(max < adjMat[i][j])
            {
                max = adjMat[i][j];
            }
        }
    }

    return log10(max) + 1;
}

int maxChars()
{
    int count = 0;
    int max = 0;

    for(int i = 0; i < n; i++)
    {
        while(nodes[i] != '\0')
        {
            count++;
        }

        if(max < count)
        {
            max = count;
        }
    }

    return max;
}

int findNode(char c[10])
{
    for(int x = 0; x < n; x++)
    {
        if(strcmp(c, nodes[x]) == 0)
        {
            return x;
        }
    }

    printf("Invalid node name.\n");
    exit(1);
}

void printMatrix()
{
    int l = maxNum();
    int cl = maxChars();

    for(int i = 0; i < cl + 2; i++)
    {
        printf(" ");
    }

    
}

void readFile(FILE *file)
{
    fscanf(file, "%d\n", &n); //input node count

    printf("Number of Nodes : %d\n", n);

    printf("Nodes :");

    for(int i = 0; i < n; i++) //input nodes
    {
        fscanf(file, "%s", nodes[i]);

        printf(" %s", nodes[i]);
    }


    printf("\n");

    char temp[15];

    fscanf(file, "%s\n", temp); //input graph type

    if(strcmp(temp, "undirected") == 0)
    {
        type = 0;
    }
    else if(strcmp(temp, "directed") == 0)
    {
        type = 1;
    }
    else
    {
        printf("Invalid graph type.\n");
        exit(1);
    }

    printf("Graph Type : %s\n", type == 0 ? "Undirected" : "Directed");

    for(int i = 0; i < MAX; i++) //initializing adjacency matrix to all zeros
    {
        for(int j = 0; j < MAX; j++)
        {
            adjMat[i][j] = 0;
        }
    }

    char node1[10], node2[10];
    int weight, idn1, idn2;

    while(fscanf(file, "%s %s %d", node1, node2, &weight) != EOF) //input edges and their corresponding weight
    {
        idn1 = findNode(node1);
        idn2 = findNode(node2);

        adjMat[idn1][idn2] = weight;

        if(type == 0)
        {
            adjMat[idn2][idn1] = weight;
        }

        printf("%s %s %s : %d\n", node1, type == 0 ? "-" : "->", node2, weight);
    }

    printf("\n");
}

int main()
{
    FILE *file = fopen("graph.txt", "r");

    if(!file)
    {
        printf("Failed to open the file.\n");
        exit(1);
    }

    readFile(file);

    fclose(file);

    return 0;
}