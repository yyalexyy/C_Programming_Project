#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "graph.h"

static int wumpusFound = 0;     /*Sets to one when Wumpus is found (Variable used in wumpusSearch and recursiveSearch function)*/
static int level = 0;           /*Sets to the level from player to wumpus (Variable used in wumpusSearch and recursvieSearch function)*/
static int firstCall = 0;       /*sets to 1 when recursiveSearch function is called (Variable used in wumpusSearch and recursvieSearch function)*/


struct Graph* graph_create(int rooms){
        Cave* graph = (struct Graph*)malloc(sizeof(struct Graph));
        graph->numOfRooms = rooms;
        graph->adjList = (struct Node**)malloc(rooms*sizeof(struct Node*));
        graph->visited = (int*)malloc(rooms*sizeof(int));
        graph->pitRooms =(int*)malloc(rooms*sizeof(int));

        int i;
        for(i = 0; i < rooms; i++){             /*Setting each node in adjacency list and visited to default values*/
                graph->adjList[i] = NULL;
                graph->visited[i] = 0;
                graph->pitRooms[i] = 0;
        }

        return graph;
}



void addEdge(struct Graph* graph, int source, int dest){
        Room* newNode = createNode(dest);

        //point new node to current head
        newNode->next = graph->adjList[source];

        //point head pointer to new node
        graph->adjList[source] = newNode;
}


struct Node* createNode(int num){
        Room* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->room = num;
        newNode->next = NULL;
        return newNode;
}

struct Graph* graph_realloc(struct Graph* graph, int prevTotal, int total){
        graph = (struct Graph*)realloc(graph, total*sizeof(struct Graph));
        graph->numOfRooms = total;
        graph->adjList = (struct Node**)realloc(graph->adjList, total*sizeof(struct Node*));
        graph->visited = (int*)realloc(graph->visited, total*sizeof(int));
        graph->pitRooms = (int*)realloc(graph->visited, total*sizeof(int));

        int i;
        for(i = prevTotal; i < total; i++){             /*Setting new  nodes in adjacency list and visited to default values*/
                graph->adjList[i] = NULL;
                graph->visited[i] = 0;
                graph->pitRooms[i] = 0;
        }

        return graph;
}


void printGraph(struct Graph* graph){
        int i;
        for(i = 0; i < graph->numOfRooms; i++){
                Room* temp = graph->adjList[i];
                printf("\n Adjacency list of Vertex %d\n", i);
                while(temp){
                        printf("%d, ", temp->room);
                        temp = temp->next;
                }
                printf("\n");
        }
}


void displayPossibleRooms(struct Node* nextRoom){
        do{
                printf("%d",nextRoom->room);    /*Display the room number*/
                nextRoom = nextRoom->next;      /*Head to the neighbor node*/
                if(nextRoom != NULL){
                        printf(", ");
                }
        }while(nextRoom != NULL);
}


struct Node* playerNewRoom(struct Graph* cave, int moveP, struct Node* playerCurrentR){
        bool isValid;

        do{
                isValid = isValidMove(playerCurrentR, moveP);           /*Check if future move is valid*/
                if(isValid == true){
                        playerCurrentR = cave->adjList[moveP];          /*Set player to the new room*/
                }
                else{
                        printf("You cannot move there. Re-enter room? (Enter 0 to Shoot)\n");
                        scanf("%d", &moveP);
                }
        }while(isValid == false);

        return playerCurrentR;
}


bool isValidMove(struct Node* playerRoom, int futureRoom){
        bool isValid = false;
        Room* nextNode = playerRoom->next;

        if(nextNode != NULL){
                do{     /*Traverse through the neighbor nodes to check if the number user entered is one of the neighbor rooms*/
                        if(nextNode->room  == futureRoom){
                                isValid = true;
                                break;
                        }
                        else{           /*Set nextNode to the neighbor node*/
                                nextNode = nextNode->next;
                        }
                }while(nextNode != NULL);
        }

        return isValid;
}


bool wumpusKill(struct Node* playerR, struct Node* wumpusR){
        bool playerAlive = true;
        Room* wNeighborNode;

        if(wumpusR->next != NULL){              /*If wumpus can head to neighbor cave*/
                wNeighborNode = wumpusR->next;
        }
        else{                                   /*Player is still alive because wumpus can't move anywhere*/
                return true;
        }


        if(wNeighborNode != NULL){
                do{     /*Check if player room is either in wumpus room or wumpus's neighbor room*/
                        if(wNeighborNode->room == playerR->room || wumpusR->room == playerR->room){
                                playerAlive = false;            /*player dies*/
                                break;
                        }
                        else{
                                wNeighborNode = wNeighborNode->next;
                        }
                }while(wNeighborNode != NULL);
        }

        return playerAlive;
}


bool pitKill(struct Graph* graph, struct Node* playerR){
        bool inPitR = false;

        if((graph->pitRooms[playerR->room]) == 1){
                inPitR = true;
        }

        return inPitR;
}


bool playerShoot(struct Graph* cave, struct Node* playerR, struct Node* wumpusR){
        bool wumpusAlive = true;
        Room* pNeighborNode = playerR->next;


        while(pNeighborNode != NULL){
                if(pNeighborNode->room == wumpusR->room){               /*If wumpus is located next to one of the player's room*/
                        wumpusAlive = false;                            /*wumpus killed*/
                        break;
                }
                else{
                        Room* neighborNode = cave->adjList[pNeighborNode->room];

                        while(neighborNode != NULL){
                                if(neighborNode->room == wumpusR->room){        /*If wumpus is located two rooms from the player*/
                                        wumpusAlive = false;                    /*Wumpus is killed*/
                                        break;
                                }
                                else{
                                        neighborNode = neighborNode->next;
                                }
                        }
                }


                if(wumpusAlive == true){                /*If wumpus is alive, check the nexxt neighbor room*/
                        pNeighborNode = pNeighborNode->next;
                }
                else{
                        break;                          /*End the loop when wumpus is already killed*/
                }
        }

        return wumpusAlive;
}


void recursiveSearch(struct Graph* cave, struct Node* wumpusR, int room, struct Node* neighborNode, int wLevel){
        struct Node* adjList = cave->adjList[room];
        struct Node* temp;

        if(firstCall == 1){             /*If the function is called the first time*/
                temp = neighborNode;    /*Set temp to one of the neighbor node*/
        }
        else{
                temp = adjList->next;   /*Set temp to the first node in the linked list*/
        }

        cave->visited[room] = 1;        /*Set the current room as one to represent visited*/

        while(temp != NULL){
                int connectedRoom = temp->room;

                if(cave->visited[connectedRoom] == 0){          /*Checks if the room is visited*/
                        if(wumpusFound == 0){                   /*If wumpus is not found*/
                                if(wumpusR->room == connectedRoom){     /*If temp node is in the same node as wumpus*/
                                        level = wLevel + 1;             /*Set global variable level to the level wumpus was found*/
                                        wumpusFound = 1;                /*Set wumpus to 1 as found*/
                                }
                                else{
                                        level = -1;             /*Set global variable to -1 as wumpus was never found*/
                                }
                        }

                        firstCall = 0;          /*Set firstCall to 0 because we already called the function once*/
                        recursiveSearch(cave,wumpusR, connectedRoom, neighborNode, wLevel+1);   /*Recursive Case*/
                }

                temp = temp->next;
        }
}


int wumpusSearch(struct Graph* cave, struct Node* wumpusR, int room, int totalR){
        wumpusFound = 0;        /*Setting the values back to default*/
        level = 0;
        int i;
        for(i = 0; i < totalR; i++){
                cave->visited[i] = 0;
        }


        int colNum = 0;
        Room* temp = cave->adjList[room];
        while(temp->next != NULL){      /*Counting the number of columns in one specific row*/
                colNum += 1;
                temp = temp->next;
        }


        if(colNum != 0){                /*If coulumn isn't 0, meaning there are rooms you can move to*/
                Room* neighbor = cave->adjList[room];
                int wumpusLevels[colNum+1];     /*Start at index 1*/
                int counter = 1;

                int e;
                for(e = 1; e <= colNum; e++){
                        firstCall = 1;          /*Set firstCall to 1 because you are about to call the recursive method*/
                        neighbor = neighbor->next;

                        recursiveSearch(cave, wumpusR, room, neighbor, level);

                        wumpusLevels[counter] = level;          /*Save the level wumpus was found from the player for eah neighbor nodes*/
                        counter++;                              /*Increment counter*/

                        wumpusFound = 0;                        /*Setting the values back to default*/
                        level = 0;
                        int i;
                        for(i = 0; i < totalR; i++){
                                cave->visited[i] = 0;
                        }
                }


                int l;
                int shortest = wumpusLevels[1];
                for(l = 1; l < colNum+1; l++){                  /*Loop through the levels that was found and find the smallest one*/
                        if(wumpusLevels[l] != 0){               /*If wumpus was found*/
                                if(shortest > wumpusLevels[l] && wumpusLevels[l] != -1){
                                        shortest = wumpusLevels[l];
                                }
                        }
                }

                return shortest;
        }
        else{           /*You are stuck in a room where there are no neighbor rooms you can move to*/
                printf("So....you want to hear the good news or the bad news first?\n");
                printf("The bad news is you can't get out of the room. The good news is .... there are none XD\n");
                printf("Day after day with nothing but darkness, you kept on thinking about how you let your people down and eventually you starve to death....\n");
                printf("GAME OVER!!!\n");

                //free memory
                free_graph(cave, totalR);
                exit(0);
        }
}


void free_graph(struct Graph* graph, int totalR){
        if (graph != NULL) {
                int i;
                for (i = 0; i < totalR; i++) {
                        free_vertex(graph, graph->adjList[i]);
                }


                free(graph->adjList);
                free(graph->visited);
                free(graph);
        }
}


void free_vertex(struct Graph* graph, struct Node* vertex) {
    if (vertex) {

        while (vertex->next != NULL) {
            Room* edge = vertex->next;
            vertex->next = vertex->next->next;
            free(edge);
        }

        free(vertex);

    }
}
