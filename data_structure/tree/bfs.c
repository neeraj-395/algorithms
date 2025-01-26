#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/queue.h"

#define NUM_VERTICES 5

void bfs(int g[][NUM_VERTICES], int start) {
    Queue q = {NULL, NULL, 0};
    int visited[NUM_VERTICES] = {0};
    enqueue(&q, start);
    visited[start] = 1;

    printf("BFS Traverse: ");
    while(q.size > 0) {
        int curr_vertex = dequeue(&q);
        printf("%d ", curr_vertex);

        int *temp = g[curr_vertex];
        for(int i = 0; i < NUM_VERTICES; i++) {
            if(temp[i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(&q, i);
            }
        }
    } printf("\n");
} 

int main() {

    int graph[][NUM_VERTICES] = {
    //   0  1  2  3  4
        {0, 0, 1, 0, 0}, // 0
        {0, 0, 0, 1, 0}, // 1
        {0, 0, 0, 0, 0}, // 2
        {0, 1, 1, 0, 1}, // 3
        {0, 0, 1, 0, 0}, // 4
    };

    bfs(graph, 1);

    return 0;
}