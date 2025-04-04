#include "queue.h"
#include "tile_game.h"

#define VISITED_SIZE 1000003 //needs to be prime
char visited[VISITED_SIZE] = {0};

void enqueue(struct queue *q, struct game_state state) 
{
    size_t temp = serialize(state);
    insert_at_head(&q->data,temp);
}

struct game_state dequeue(struct queue *q) 
{ 
    size_t temp = remove_from_tail(&q->data);
    return deserialize(temp); 
}

bool match(uint8_t tiles[4][4])
{
    int exp = 1;
    for(int r = 0; r<4;r++)
    {
        for(int c = 0; c<4; c++)
        {
            if(r == 3 && c == 3)
            {
                return (tiles[r][c] == 0);
            }
            if(tiles[r][c] != exp++)
            {
                return false;
            }
        }
    }
    return true;
}

int number_of_moves(struct game_state start) 
{ 
    struct queue q;
    q.data.head = NULL;
    enqueue(&q,start);
    while (q.data.head != NULL) 
    {
        struct game_state cur = dequeue(&q);

        if (match(cur.tiles)) 
        {
            free_list(q.data);
            return cur.num_steps;
        }

        struct game_state next;

        next = cur;
        move_up(&next);
        uint64_t key = serialize(next);
        size_t index = key % VISITED_SIZE;
        if (!visited[index]) 
        {
            visited[index] = 1;
            enqueue(&q, next);
        }

        next = cur;
        move_down(&next);
        key = serialize(next);
        index = key % VISITED_SIZE;
        if (!visited[index]) 
        {
            visited[index] = 1;
            enqueue(&q, next);
        }

        next = cur;
        move_left(&next);
        key = serialize(next);
        index = key % VISITED_SIZE;
        if (!visited[index]) 
        {
            visited[index] = 1;
            enqueue(&q, next);
        }

        next = cur;
        move_right(&next);
        key = serialize(next);
        index = key % VISITED_SIZE;
        if (!visited[index]) 
        {
            visited[index] = 1;
            enqueue(&q, next);
        }
    }
    free_list(q.data);
    return -1;
}
