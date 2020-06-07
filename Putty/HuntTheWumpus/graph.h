#include <stdbool.h>

struct Graph{
        int numOfRooms;
        int* visited;
        int* pitRooms;
        struct Node** adjList;
};
typedef struct Graph Cave;

struct Node{
        int room;
        struct Node* next;
};
typedef struct Node Room;

/*Creates a graph with adjacency list*/
struct Graph* graph_create(int rooms);

/*Connects the edges of two nodes in the graph*/
void addEdge(struct Graph* graph, int source, int dest);

/*Creates a new node*/
struct Node* createNode(int num);

/*Modify (reallocate) the graph and the memory*/
struct Graph* graph_realloc(struct Graph* graph, int oldRooms, int total);

/*Print the graph*/
void printGraph(struct Graph* graph);

/*Prints the nearby rooms player can visit*/
void displayPossibleRooms(struct Node* nextRoom);

/*Set the player to the new cave*/
struct Node* playerNewRoom(struct Graph* cave, int moveP, struct Node* playerCurrentR);

/*Determine whether the new cave is a valid move for the player*/
bool isValidMove(struct Node* playerRoom, int futureRoom);

/*Scan if player is either one room apart or same room from wumpus*/
bool wumpusKill(struct Node* playerR, struct Node* wumpusR);

/*Scan if player is at a bottomless pit room*/
bool pitKill(struct Graph* graph, struct Node* playerR);

/*Player shoots an arrow which travels at most two rooms apart from the player's room  and checks if the wumpus is killed*/
bool playerShoot(struct Graph* cave, struct Node* playerR, struct Node* wumpusR);

/*Recursive method to find the wumpus*/
void recursiveSearch(struct Graph* cave, struct Node* wumpusR, int room, struct Node* neighborNode, int wLevel);

/*Setting default values and finding the shortest level to get to the wumpus for all the neighbor nodes*/
int wumpusSearch(struct Graph* cave, struct Node* wumpusR, int room, int total);

/*free the graph from memory*/
void free_graph(struct Graph* graph, int totalR);

/*free the nodes from memory*/
void free_vertex(struct Graph* graph, struct Node* vertex);
