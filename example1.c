//Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
}
NODE;

/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa    
    
typedef struct g
{
    int vertices;
    int *visited;
    struct Node **head;
} 
GRAPH;

typedef struct s
{
    int top;
    int stackCap;
    int *arr;
}
STACK;

NODE *createNode(int x)
{
    NODE *newNode = (NODE *) malloc(sizeof(NODE));
    newNode->data = x;
    newNode->next = NULL;
    
    return newNode;
}

void addEdge(GRAPH *graph , int src , int dest)
{
    NODE *newNode = createNode(dest);
    newNode->next = graph->head[src];
    graph->head[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->head[dest];
    graph->head[dest] = newNode;
}

GRAPH *createGraph(int v)
{
    GRAPH *graph = (GRAPH *) malloc(sizeof(GRAPH));
    graph->vertices = v;
    graph->head = (NODE **) malloc(sizeof(NODE *) * v);
    graph->visited = (int *) malloc(sizeof(int) * v);

    for (int i = 0 ; i < v ; i++)
    {
        graph->head[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

STACK *createStack(int scap)
{
    STACK *s = malloc(sizeof(STACK));
    s->arr = malloc(scap * sizeof(int));
    s->top = -1;
    s->stackCap = scap;

    return s;
}

void push(int value , STACK *s)
{
    s->top = s->top + 1;
    s->arr[s->top] = value;
}

void DFS(GRAPH *graph , STACK *s , int v_nr)
{
    NODE *aux = graph->head[v_nr];
    
    graph->visited[v_nr] = 1;
    printf("%d " , v_nr);
    push(v_nr , s);

    while (aux != NULL)
    {
        int con_ver = aux->data;
        if (graph->visited[con_ver] == 0)
        {
            DFS(graph , s , con_ver);
        }
        aux = aux->next;
    }
}

void insertEdges(GRAPH *g , int edgeNr , int nrv)
{
    int src , dest , i;
    printf("adauga %d munchii (de la 1 la %d)\n" , edgeNr , nrv);
    for (i = 0 ; i < edgeNr ; i++)
    {
        scanf("%d%d" , &src , &dest);
        addEdge(g , src , dest);
    }
}

void wipe(GRAPH *g , int nrv)
{
    for (int i = 0 ; i < nrv ; i++)
    {
        g->visited[i] = 0;
    }
}    

int isPath(GRAPH *g , int nrv , STACK *s1 , STACK *s2 , int vertex1 , int vertex2)// 0 sau 1 daca poate fi sau nu ajuns
{
    DFS(g, s1, vertex1);
    printf("\n");

    wipe(g, nrv);

    DFS(g, s2, vertex2);
    printf("\n");

    for (int i = 0; i <= s1->top ; i++) // aici i tine loc de numar adica de restaurant
    {
        for (int j = 0; j <= s2->top ; j++)
        {
            if (s1->arr[i] == s2->arr[j])
            {
                return 1;
            }
        }
    }
    return 0;
}          

int main(void)
{
    int nrv , edgeNr , vertex1 , vertex2 , ans;

    printf("cate noduri are graful?");
    scanf("%d", &nrv);

    printf("cate muchii are graful?");
    scanf("%d", &edgeNr);

    GRAPH *g = createGraph(nrv);

    STACK *s1 = createStack(2 * nrv);
    STACK *s2 = createStack(2 * nrv);

    insertEdges(g , edgeNr , nrv);

    vertex1 = 5;
    vertex2 = 3;

    ans = isPath(g , nrv , s1 , s2 , vertex1 , vertex2);

    if (ans)
    {
        printf("Da\n");
    }
    else
    {
        printf("Nu\n");
    }

    return 0;
}