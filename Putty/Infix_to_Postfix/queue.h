/*Queue.h*/
struct queue{
        char* queue;
        int numOfElements;
        int size;
        int frontElement;
};

typedef struct queue queue_type;

/*Create a new empty queue of characters
 * RETURN VALUE: a pointer to a queue upon success; NULL if failure
 */
queue_type *queue_new(void);

/*add a char onto an existing queue at the end
 * RETURN VALUE: 0 upon success and -1 upon failure
 */
int queue_enqueue(queue_type *, char);

/*Query the number of elements on a given queue*/
int queue_length(queue_type *);

/*remove the front char from a queue; queue_dequeue(s) can only be
 * called if queue_length(s) > 0 */
char queue_dequeue(queue_type *);

/*return the front char from a queue without altering the queue;
 * queue_front(s) can only be called if queue_length(s) > 0
 */
char queue_front(queue_type *);

/*Free all memory associated with this queue.*/
void queue_delete(queue_type *);
