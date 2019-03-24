#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0
#define UNDIRECTED 1

#if DEBUG
#define debug(...)                    \
    do {                              \
        fprintf(stderr, __VA_ARGS__); \
    } while (0)
#else
#define debug(...) \
    do {           \
    } while (0)
#endif

struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode *next;
};

struct AdjList {
    struct AdjListNode *head;
};

struct Graph {
    int V;
    struct AdjList *array;
};

struct AdjListNode *newAdjListNode(int dest, int weight) {
    struct AdjListNode *newNode = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;

    return newNode;
}

struct Graph *newGraph(int V) {
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array = (struct AdjList *)malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

void addEdge(struct Graph *graph, int src, int dest, int weight) {
    struct AdjListNode *newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

#if UNDIRECTED
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
#endif
}

struct MinHeapNode {
    int v;
    int dist;
};

struct MinHeap {
    int size;
    int capacity;
    int *pos;
    struct MinHeapNode **array;
};

struct MinHeapNode *newMinHeapNode(int v, int dist) {
    struct MinHeapNode *minHeapNode =
        (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;

    return minHeapNode;
}

struct MinHeap *newMinHeap(int capacity) {
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode **)malloc(capacity * sizeof(struct MinHeapNode *));

    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b) {
    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap *minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        struct MinHeapNode *smallestNode = minHeap->array[smallest];
        struct MinHeapNode *idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

int isEmpty(struct MinHeap *minHeap) {
    return minHeap->size == 0;
}

struct MinHeapNode *extractMin(struct MinHeap *minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    struct MinHeapNode *root = minHeap->array[0];

    struct MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;

    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(struct MinHeap *minHeap, int v, int dist) {
    int i = minHeap->pos[v];

    minHeap->array[i]->dist = dist;

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

int isInMinHeap(struct MinHeap *minHeap, int v) {
    return minHeap->pos[v] < minHeap->size;
}

void printArr(int dist[], int n) {
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

int prev[2000000];

void printPath(int parent[], int j, int cols, int graphSize) {
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j], cols, graphSize);

    debug("node: %d -> ", j);

    if (j == parent[j] + 1) {
        printf("%c", 'R');
    } else if (j == parent[j] - 1) {
        printf("%c", 'L');
    } else if (j == parent[j] + cols) {
        printf("%c", 'D');
    } else if (j == parent[j] - cols) {
        printf("%c", 'U');
    } else if (j == parent[j] + graphSize || j == parent[j] - graphSize) {
        printf("%c", 'W');
    }
}

void printSolution(int parent[], int src, int dest, int cols, int graphSize) {
    printPath(parent, dest, cols, graphSize);
}

int dijkstra(struct Graph *graph, int src, int dest, int cols, int graphSize) {
    int V = graph->V;
    int dist[V];

    struct MinHeap *minHeap = newMinHeap(V);

    for (int v = 0; v < V; ++v) {
        prev[src] = -1;
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        struct MinHeapNode *minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;

        struct AdjListNode *pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;

            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + pCrawl->weight;

                prev[v] = u;
                if (v == dest) {
                    printf("%d ", dist[dest]);
                    printSolution(prev, src, dest, cols, graphSize);
                    printf("\n");
                    return 1;
                }
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
#if DEBUG
    printArr(dist, V);
#endif

    return dist[dest];
}

int getCols(FILE *fp) {
    int ret = 0;

    char n;
    while (fscanf(fp, "%c", &n)) {
        if (n == '\n')
            break;
        ret++;
    }
    rewind(fp);
    return ret;
}

struct MapSquare {
    char symbol;
    int vertex;
} map[2002][1002];

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("%s\n", "Usage: ./spacedeli <infile>");
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("%s\n", "File not found.");
        exit(1);
    }

    debug("Debugging mode is ON.\n");
#if UNDIRECTED
    debug("Graph is undirected.\n");
#endif

    char n;
    int i = 0;
    int j = 0;
    int rows = 0;
    int cols = 0;
    int vertex = 0;

    cols = getCols(fp);

    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    rewind(fp);

    rows = filesize / (cols + 1);  // Assuming newline at the end of file

    int graphSize = rows * cols;
    struct Graph *graph = newGraph(graphSize * 2);

    int src_vertex = 0;
    int end_vertex = 0;

    debug("rows: %d, cols: %d\n\n", rows, cols);

    for (i = 0; i <= rows; i++) {
        for (j = 0; j <= cols; j++) {
            fscanf(fp, "%c", &n);
            if (n != '\n') {
                map[i][j].symbol = n;
                map[i][j].vertex = vertex;
                map[rows + i][j].symbol = n;
                map[rows + i][j].vertex = vertex + graphSize;

                debug("map[%d][%d].vertex: %d\n", i, j, map[i][j].vertex);
                debug("map[%d][%d].vertex: %d\n\n", rows + i, j, map[i + rows][j].vertex);

                if (n == 'W') {
                    addEdge(graph, map[i][j].vertex, map[i + rows][j].vertex, 1);
                    debug("Added special edge from %d to %d with weight %d\n", map[i][j].vertex, map[i + rows][j].vertex, 1);
                }

                if (n == 'E')
                    end_vertex = vertex;

                if (n == 'S')
                    src_vertex = vertex;

                vertex++;
            }
        }
    }

    fclose(fp);

    // At this point we have our map.
#if DEBUG
    debug("Input: \n");
    for (i = 0; i < 2 * rows; i++) {
        for (j = 0; j < cols; j++) {
            debug("(%c %d) ", map[i][j].symbol, map[i][j].vertex);
        }
        debug("\n");
    }
    debug("\n");
#endif

    int weight;
    int index;
    for (weight = 2; weight >= 1; weight--) {
        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                index = (weight == 2 ? i : i + rows);

                if (map[index][j].vertex % cols != 0 && map[index][j].symbol != 'X' && map[index][j - 1].symbol != 'X') {
                    addEdge(graph, map[index][j].vertex, map[index][j - 1].vertex, weight);
                    debug("Added edge from %d to %d with weight %d\n", map[index][j].vertex, map[index][j - 1].vertex, weight);
                }
                if (map[index][j].vertex % graphSize >= cols && map[index][j].symbol != 'X' && map[index - 1][j].symbol != 'X') {
                    addEdge(graph, map[index][j].vertex, map[index - 1][j].vertex, weight);
                    debug("Added edge from %d to %d with weight %d\n", map[index][j].vertex, map[index - 1][j].vertex, weight);
                }
            }
        }
    }

    dijkstra(graph, src_vertex, end_vertex, cols, graphSize);

    free(graph);

    return 0;
}
