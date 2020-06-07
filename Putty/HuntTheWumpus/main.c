#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "graph.h"
#define def 101


bool playerHint(int initialD, int distance, int* hint, int idx);

int main()
{

        char parseString[1000] = "";
        int temp;
        int door, door_counter;
        char* ptr;
        int modify = def;

        Room* playerCurrentRoom;
        Room* wumpusRoom;
        bool playerAlive = true;
        bool wumpusAlive = true;
        bool inPitRoom;

        int warmOrCold[1000];
        int WOrC = 0;


        printf("\n--- Welcome to Hunt the Wumpus ---\n");

        printf("\nLegend has it that there lives a wumpus who slaughtered hundreds of families and is heading for your tribe.\nYou, the leader of the tribe, have decided to build a cave to help evacuate your people...\n");
        printf("The workers have arrived! Direct your workers with he rooms and tunnels ou like them to construct.\n");

        printf("The following is the format to enter your commands to create rooms and tunnels\n");
        printf("<room number> ( <list of comma-seperated adjoining room numbers> ):\n");
        printf("1 (2,3)\n");
        printf("(Enter 0 (0) when finished with the cave.)\n");
        printf("Enter -2 ( <list of comma-seperated adjoining room numbers> ) for the bottomless pits cave.\n");

        /*Create the graph*/
        Cave* graph = graph_create(def);
        printf("Create:\n");

        do{
                scanf("%d (%[^)])", &temp, parseString);

                /*Modifying the size nd memory of the graph if temp is greater than the created caves*/
                if(temp >= def){
                        modify = def * 2;
                        while(temp >= modify){
                                modify = modify * 2;
                        }

                        graph = graph_realloc(graph, temp, modify);
                }

                ptr = strtok(parseString, ",");
                door_counter = 0;

                int i = 0;
                while(ptr != NULL){
                        door = atoi(ptr);

                        /*Modifying the size nd memory of the graph if door is greater than the created caves*/
                        if(door >= modify){
                                while(door >= modify){
                                        modify = modify * 2;
                                }

                                graph = graph_realloc(graph,temp, modify);
                        }

                        if(temp >  0){
                                addEdge(graph, temp, door);
                        }
                        else if(temp == -2){            /*pits location*/
                                graph->pitRooms[door] = 1;
                        }

                        door_counter++;
                        ptr = strtok(NULL, ",");
                        i++;
                }

        }while(temp > -2);


        int j;
        for(j = 1; j < modify; j++){
                addEdge(graph, j, j);   /*Create caves*/
        }


        printf("\nOH NO!! The Wumpus has arrived earlier than expected. Everyone run for your life!!!!!\n");
        printf("\nONE WEEK LATER....\n\n");
        printf("Congrats, you have survived the disaster and realized the wumpus is still living in the cave!\nHowever, what you have witnessed will haunt you for the rest of your life.\n");
        printf("You look around, finding skulls and bones scatterring around the entrance of the cave. It is your time now to get revenge!!\nSuit up cuz it's about time for someone to bury that monster once and for all...\n");
        printf("Dont forget you only have one shot at this!\n");


        int movePlayer, moveWumpus;
        printf("\n\nStarting location for the player and the Wumpus respectively: ");
        scanf("%d, %d", &movePlayer, &moveWumpus);


        /*Set the location for player and wumpus to the graph*/
        playerCurrentRoom = graph->adjList[movePlayer];
        wumpusRoom = graph->adjList[moveWumpus];



        do{
                /*First check the distnace btw player and wumpus*/
                playerAlive = wumpusKill(playerCurrentRoom, wumpusRoom);
                /*Check if the player is in the pit room*/
                inPitRoom = pitKill(graph, playerCurrentRoom);


                /*If wumpus os one room away from the plyaer and can get to the player, it would kill the plyaer*/
                if(playerAlive == false){
                        printf("AAHHHH!!!! The Wumpus got you, not a pretty sight. What happened with your revenge? It seems like your useless after all!\n");
                        printf("-- GAME OVER --\n");
                }
                else if(inPitRoom == true){
                        printf("AAHHHH!!!! Why are you flying? Oh never mind, you are actually falling to your tomb!\n");
                        printf("-- GAME OVER --\n");
                        exit(0);
                }
                else{           /*ELSE when the Wumpus is not able to kill the player*/
                        int startDistance;

                        if(playerCurrentRoom->next != NULL){
                                printf("You are in room %d, nearby rooms are ", playerCurrentRoom->room);
                                Room* nextNode;
                                nextNode = playerCurrentRoom->next;

                                /*Calls the method where it displays the nearby rooms*/
                                displayPossibleRooms(nextNode);

                                /*Get the starting distance from player to wumpus*/
                                startDistance = wumpusSearch(graph, wumpusRoom, playerCurrentRoom->room, modify);
                        }
                        else{   /*ELSE when there are no rooms connected*/
                                printf("So....the good news is you are in a room where the Wumpus cannot eat you. The bad news is YOU ARE STUCK!!\n");
                                printf("Day after day with nothing but darkness, you kept on thinking about how you let your people down and you eventually died from hunger....\n");
                                printf("!?GAME OVER?!");

                                free_graph(graph, modify);
                                exit(0);

                        }


                        /*Ask user to enter a room to travel*/
                        printf("\nTravel to which room? (Enter 0 to Shoot)\n");
                        scanf("%d", &movePlayer);


                        /*If the player wants to shoot (Enters 0)*/
                        if(movePlayer == 0){
                                wumpusAlive = playerShoot(graph, playerCurrentRoom, wumpusRoom);

                                if(wumpusAlive == false){
                                        printf("NICE! It seems like you have slain the wumpus. You have gotten your revenge and if your people were here, they will definitely be proud!\n");
                                        printf("What a great day to be alive!\n");
                                }
                                else{
                                        printf("Oh NO! Unfortunately, you have no more arrows... Also, you seemed to awaken the Wumpus!!!\n");
                                        printf("BOOM! BOOM! BOOM! You suddenly feel a blustery wind behind you.\n");
                                        printf("It was until then you realize how precious it is to be healthy and alive.... AAHHH....\n");
                                        printf("-- GAME OVER --\n");
                                }

                                break;
                        }
                        else{   /*ELSE when player moves to a new room*/
                                playerCurrentRoom = playerNewRoom(graph, movePlayer, playerCurrentRoom);

                                inPitRoom = pitKill(graph, playerCurrentRoom);
                                if(inPitRoom == true){
                                        printf("AAHHHH!!!! Why are you flying? Oh never mind, you are actually falling to your tomb!\n");
                                        printf("-- GAME OVER --\n");
                                        exit(0);
                                }



                                /*Check the distance btw player and wumpus*/
                                int wumpusDistance;
                                wumpusDistance = wumpusSearch(graph, wumpusRoom, playerCurrentRoom->room, modify);
                                warmOrCold[WOrC] = wumpusDistance;

                                /*Call hint function to give user hints about how close the player is from the wumpus*/
                                wumpusAlive = playerHint(startDistance, wumpusDistance, warmOrCold, WOrC);
                                if(WOrC != 999){        /*Check if  WOrC reaches overflow*/
                                        WOrC++;
                                }
                                else{
                                        warmOrCold[999] = warmOrCold[0];
                                        WOrC = 0;
                                }
                        }
                }

        }while(playerAlive == true && wumpusAlive == true);


        free_graph(graph,modify);

        return 0;
}


/*Display hints of wumpus location to the user*/
bool playerHint(int initialD, int distance, int* hint, int idx){
        bool wumpusDanger = true;
        int prevIdx = idx - 1;
        int d = 0;

        if(idx == 0){
                if(distance > initialD){
                        d = 1;  /*getting colder*/
                }
                else if(distance == initialD && distance != -1){
                        d = 0;  /*neither getting warmer nor colder*/
                }
                else if(distance < initialD){
                        d = -1; /*getting warmer*/
                }
        }
        else{
                if(hint[idx] > hint[prevIdx]){
                        d = 1;  /*getting colder*/
                }
                else if(hint[idx] == hint[prevIdx]){
                        d = 0;  /*neither getting warmer nor colder*/
                }
                else if(hint[idx] < hint[prevIdx] && (distance != 0 && distance != 1)){
                        d = -1; /*getting warmer*/
                }
        }


        switch(d)
        {
                case 1:         printf("You're getting colder!\n");
                        break;
                case 0:         printf("You're neither getting warmer nor colder!\n");
                        break;
                case -1:        printf("You're getting warmer!\n");
                        break;
        };


        if(distance == 0 || distance == 1){
                printf("You suddenly feel a blustery wind behind you...\n");
                printf("AAHHHH....the Wumpus got you, not a pretty sight. What happened with our revenge? It seemed like your useless after all!\n");
                printf("-- GaMe OveR --\n");
                wumpusDanger = false;
        }
        else if(distance == 2){
                printf("Aghh....the malodorous aroma from the Wumpus is nearly overpowering! You could die if you stay any longer!\n");
        }
        else if(distance == 3){
                printf("The smell of danger is close! Remember, you are revenging for your tribe.\n");
        }
        else if(distance == 4){
                printf("Your  nose can kind of detect an unpleasant smell.\n");
        }
        else if(distance >= 5){
                printf("No unpleasant smell but I promis you the Wumpus is living in this cave!\n");
        }
        else if(distance == -1){
                printf("You search for hours, days, years... It appears ou can't find any evidence of the wumpus.\n");
                wumpusDanger = false;
        }

        return wumpusDanger;
}
