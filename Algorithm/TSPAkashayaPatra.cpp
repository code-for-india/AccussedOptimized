// A C / C++ program for Prim's Minimum Spanning Tree (MST) algorithm.
// The program is for adjacency matrix representation of the graph

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

// Number of vertices in the graph
#define V 6
int done[V]={0};
typedef struct list{
    int num;
    struct list *next;
} Node;

typedef struct stack{
    int num;
    struct stack *next;
    struct stack *prev;
} Stack;



Stack *head = NULL;

Node *child[V]={NULL};
// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
    
    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    
    return min_index;
}
// A utility function to print the constructed MST stored in parent[]
int printMST(int parent[], int n, int graph[V][V])
{
    printf("Edge   Weight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
    return 1;
}
// A utility function to print the constructed MST stored in parent[]
void printMSTpath(int parent[], int n, int graph[V][V])
{
    
        Node *current=child[n];
    Stack *pointing=head;
        if(done[n]==0){
            if(current==NULL)
                return;
            while(current->next!=NULL){
                printMSTpath(parent,current->num,graph);
                
                while(pointing->next!=NULL){
                    pointing=pointing->next;
                }
                pointing->next=(Stack *)malloc(sizeof(Stack));
                pointing->next->prev=pointing;
                pointing->next->next=NULL;
                pointing->next->num=current->num;
               // printf("%d-->",current->num);
                current=current->next;
            }
            pointing=head;
            while(pointing->next!=NULL){
                pointing=pointing->next;
            }
            pointing->next=(Stack *)malloc(sizeof(Stack));
            pointing->next->prev=pointing;
            pointing->next->next=NULL;
            pointing->next->num=current->num;
           // printf("%d-->",current->num);
            
        }
        done[n]=1;
        //printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
    
    }
    
    



// Function to construct and print MST for a graph represented using adjacency
// matrix representation
void primMST(int graph[V][V])
{
    int parent[V]; // Array to store constructed MST
    int key[V];   // Key values used to pick minimum weight edge in cut
    bool mstSet[V];  // To represent set of vertices not yet included in MST
    
    Node *current;
    
    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
    
    // Always include first 1st vertex in MST.
    key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST
    
    // The MST will have V vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick thd minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet);
        
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
        
        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < V; v++)
            
            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v]){
                parent[v]  = u, key[v] = graph[u][v];
                if(child[u]==NULL){
                    child[u]=(Node *)malloc(sizeof(Node));
                    child[u]->num=v;
                    child[u]->next=NULL;
                }else{
                    current=child[u];
                    while(current->next!=NULL){
                        current=current->next;
                    }
                    current->next=(Node *)malloc(sizeof(Node));
                    current->next->num=v;
                    current->next->next=NULL;
                }
            }
    }
    
    // print the constructed MST
    printMST(parent, V, graph);
    //printf("0--->");
    head=(Stack *)malloc(sizeof(Stack));
    head->prev=NULL;
    head->next=NULL;
    
    printMSTpath(parent, 0, graph);
    
   // printf("0\n");
    Stack *currentp=head;
    while(currentp->next!=NULL){
        currentp=currentp->next;
    }
    printf("0--->");
    while(currentp->prev!=NULL){
        printf("%d--->",currentp->num);
        currentp=currentp->prev;
    }
    printf("0\n");
}


// driver program to test above function
int main()
{
    int graph[V][V];
    char line[4096];
    int rowCounter=0;
    int colCounter=0;
    FILE *stream = fopen("/Users/admin/Desktop/prim.txt", "r");
   // fgets(line, 1024, stream);
    //memset(routes,0,sizeof(struct route)*128);
    while (fgets(line, 1024, stream))
    {
        const char* tok;
        for (tok = strtok(line, ",");
             tok && *tok;
             tok = strtok(NULL, ",\n"))
        {
            graph[rowCounter][colCounter++]=atoi(tok);
        }
        rowCounter++;
        colCounter=0;
        
    }
    // Print the solution
    primMST(graph);
    
    return 0;
}