/*parcurgere  graf cu DFS/BFS*/

//Imi cer scuze in avans. E ok..

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
}
NODE;

typedef struct Graph
{
    int vertices;
    int *visited;
    struct Node **head;
}
GRAPH;
/// utils

NODE* createNode(int v)
{
    NODE *newNode = (NODE *) malloc(sizeof(NODE));
    newNode->data = v;
    newNode->next = NULL;

    return newNode;
}

GRAPH* createGraph(int vertices)
{
    GRAPH *graph = (GRAPH *) malloc(sizeof(GRAPH));
    graph->vertices = vertices;
    graph->head = (NODE **) malloc(vertices * sizeof(NODE *));
    graph->visited = (int *) malloc(sizeof(int) * vertices);

    for (int i = 0 ; i < vertices ; i++)
    {
        graph->head[i] = NULL;
        graph->visited[i] = 0;
    }
    
    return graph;
}

void addEdge(GRAPH *graph, int src, int dest)
{
    NODE *newNode = createNode(dest);
    newNode->next = graph->head[src];
    graph->head[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->head[dest];
    graph->head[dest] = newNode;
}

void insertEdge(int nr_of_vertices, int nr_of_edges, GRAPH *graph)
{
    int src , dest , i;
    printf("Adauga %d muchii (de la 0 la %d)\n", nr_of_edges, nr_of_vertices - 1);
    for (i = 0; i < nr_of_edges; i++)
    {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

/// bfs utils
int isEmpty(NODE *queue)
{
    if (queue == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void enqueue(NODE **queue, int data)
{
    NODE *newNode = createNode(data);

    if (isEmpty(*queue)) 
    {
        *queue = newNode;
    }
    else
    {
        NODE *temp = *queue;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int dequeue(NODE **queue)
{
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;

    free(temp);
    return data;
}

void printGraph(GRAPH *graph)
{
    int i;
    
    for (i = 0 ; i < graph->vertices ; i++)
    {
        NODE *temp = graph->head[i];
        while (temp != NULL)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void printQueue(NODE *queue)
{
    while (queue != NULL)
    {
        printf("%d ", queue->data);
        queue = queue->next;
    }
}


void wipeVisitedList(GRAPH *graph, int nr_of_vertices)
{
    for (int i = 0 ; i < nr_of_vertices ; i++)
    {
        graph->visited[i] = 0;
    }
}

// parcurgeri
void DFS(GRAPH *graph, int vertex_nr)
{
    NODE *temp =  graph->head[vertex_nr];
    graph->visited[vertex_nr] = 1;
    printf("%d->", vertex_nr);

    while (temp != NULL)
    {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(GRAPH *graph, int start)
{
    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!isEmpty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->head[current];
        while (temp != NULL)
        {
            int con_vertex = temp->data;

            if (graph->visited[con_vertex] == 0)
            {
                graph->visited[con_vertex] = 1;
                enqueue(&queue, con_vertex);
            }
            temp = temp->next;
        }
    }
}

int main(void)
{
    int nr_of_vertices , nr_of_edges , starting_vertex;
    
    printf("cate noduri are graful?");
    scanf("%d", &nr_of_vertices);

    printf("cate muchii are graful?");
    scanf("%d", &nr_of_edges);

    GRAPH *graph = createGraph(nr_of_vertices);
    insertEdge(nr_of_vertices, nr_of_edges, graph);
    printGraph(graph);

    printf("de unde plecam in DFS?");
    scanf("%d", &starting_vertex); // =)))
    printf("parcurgere cu DFS:");
    DFS(graph, starting_vertex);
    
    wipeVisitedList(graph, nr_of_vertices);
    printf("\n");

    printf("de unde plecam in BFS?");
    scanf("%d", &starting_vertex);
    printf("parcurgere cu BFS:");
    BFS(graph, starting_vertex);

    return 0;
}
