#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

queue_type nQueue;

queue_type *queue_new(void){
        queue_type* newQueue = &nQueue;
        (*newQueue).queue = (char*)calloc(10, sizeof(char));
        (*newQueue).numOfElements = 0;
        (*newQueue).frontElement = 0;
        (*newQueue).size = 10;

        return newQueue;
}

int queue_enqueue(queue_type *mQueue, char newChar){
        int enqueueSuccess;

        //When the queue size is 0
        if(mQueue->numOfElements == 0){
                *((*mQueue).queue) = newChar;
                mQueue->frontElement = newChar;
                mQueue->numOfElements = 1;

                enqueueSuccess = 0;
        }
        else if(mQueue->numOfElements < mQueue->size){          //When the num of elements is within the size of the queue
                *(mQueue->queue + mQueue->numOfElements) = newChar;
                mQueue->numOfElements++;

                enqueueSuccess = 0;
        }
        else if(mQueue->numOfElements >= mQueue->size){         //When the num of elements is greater thatn the size of the queue
                mQueue->size = mQueue->size * 2;        //Double the size
                *((*mQueue).queue) = (char *)realloc((*mQueue).queue, mQueue->size * sizeof(char));
                *(mQueue->queue + mQueue->numOfElements) = newChar;
                mQueue->numOfElements++;

                enqueueSuccess = 0;
        }
        else{
                enqueueSuccess = -1;
        }

        return enqueueSuccess;
}

int queue_length(queue_type *mQueue){
        return mQueue->numOfElements;
}

char queue_dequeue(queue_type *mQueue){
        char dequeuedChar = mQueue->frontElement;
        int i = 0;

        //Moving the queue elements
        while(i < mQueue->numOfElements){
                *((*mQueue).queue + i) = *((*mQueue).queue + i + 1);
                i++;
        }

        if(mQueue->numOfElements == 0){
                mQueue->frontElement = 0;
                fprintf(stderr, "%s", "Error Queue Underflow!!");       //Queue Underflow
        }
        else{
                mQueue->frontElement = *((*mQueue).queue);
        }
        mQueue->numOfElements--;
        return dequeuedChar;
}

char queue_front(queue_type *mQueue){
        return mQueue->frontElement;
}

void queue_delete(queue_type *mQueue){
        free(mQueue);
}
