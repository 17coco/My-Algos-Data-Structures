#include <stdlib.h>
#include "graph.h"

//create a graph of the given number of vertices. Once created, the number of vertices
//will not change, but one can add edges to the list
graph_t *init_graph(int num_vertices) {
  if (num_vertices<0) {
    return NULL;
  }
  //assign memory for the graph
  graph_t *new_graph = (graph_t *) malloc(sizeof(graph_t));
  //assign memory for the adjacency list
  dnode_t **new_adjacency_list = (dnode_t **) malloc(num_vertices * sizeof(dnode_t *));
  //initialize adjacency list
  int i;
  for (i = 0; i < num_vertices; i++) {
    new_adjacency_list[i] = NULL;
  }
  new_graph->num_vertices = num_vertices;
  new_graph->num_edges = 0;
  new_graph->adjacency_list = new_adjacency_list;

  return new_graph;
}

//delete the specified graph
void delete_graph(graph_t *g) {
  int i;
  for (i = 0; i < g->num_vertices; i++) {
    dnode_t *prev = NULL;
    dnode_t *curr = g->adjacency_list[i];
    while (curr != NULL) {
      prev = curr;
      curr = curr->next;
      free(prev);
    }
  }
  free(g->adjacency_list);
  free(g);
}


//add a new edge from u to v of the specified graph with the specified weight.
//the graph cannot have multiple edges from u to v.
//if an edge already exists then its weight will be replaced with this specified weight.
//this function can insert the vertices in each other's adjacency lists in any order
void add_edge(graph_t *graph, int u, int v, int weight) {
  if (v >= graph->num_vertices || u >= graph->num_vertices
      || v < 0 || u < 0 || u == v) { // index out of range
    return;
  }
  dnode_t *new_node = (dnode_t *) malloc(sizeof(dnode_t));
  new_node->weight = weight;
  new_node->destination = v;
  new_node->prev = NULL;
  new_node->next = NULL;
  // if adjacency list is empty
  if (graph->adjacency_list[u] == NULL) {
    graph->adjacency_list[u] = new_node;
    graph->num_edges++;
  } else { //if not empty
    dnode_t *curr = graph->adjacency_list[u];
    dnode_t *prev = NULL;
    while (curr != NULL) { //traverse once to update weight or add edge
      // didn't use curr->next here
      // to make sure the check below will be applied to the tail of the list
      if (curr->destination == v) { //if already exist
        curr->weight = weight; //update weight
        free(new_node); //new node should be freed
        return;//get out if edge is found and updated
      }
      //advance
      prev = curr;
      curr = curr->next;
    }
    if (prev != NULL) { //if got to the end and edge doesn't exist
      new_node->prev = prev;
      prev->next = new_node;
      graph->num_edges++;
    }
  }
}

// determine if there is an edge from u to v in the specified graph
bool is_adjacent(graph_t *graph, int u, int v) {
  if (graph->adjacency_list[u] == NULL
      || v >= graph->num_vertices || u >= graph->num_vertices
      || v < 0 || u < 0) {
    return false;
  } else {
    dnode_t *curr = graph->adjacency_list[u];
    while (curr != NULL) {
      if (curr->destination == v) {
        return true;
      }
      //advance
      curr = curr->next;
    }
    return false;
  }
}

// find the lengths of the unweighted shortest paths from the given vertex to all the vertices of this graph
int *lengths_unweighted_shortest_paths(graph_t *graph, int from) {
  if (from<0||from>=graph->num_vertices||graph->num_vertices<=0) { //input limiting
    return NULL;
  }
  int *visited = (int *) malloc(sizeof(int) * graph->num_vertices); //array to track whether a vertex is visited
  int *shortest = (int *) malloc(sizeof(int) * graph->num_vertices); //array to track the shortest distance
  queue_t *queue = init_queue();
  int i;
  for (i = 0; i < graph->num_vertices; i++) { //initialize
    shortest[i] = 123456; // to infinity
    visited[i] = 0; // not visited
  }
  shortest[from] = 0;
  push(queue, from);
  while (queue->length > 0) {
    int now_visit_from = pop(queue); //get from the queue
    visited[now_visit_from] = 1; //mark as visited
    dnode_t *curr = graph->adjacency_list[now_visit_from];
    while (curr != NULL) { //traverse every vertex
      int visiting = curr->destination;
      if (!visited[visiting]) { //if not visited
        visited[visiting] = 1;
        shortest[visiting] = shortest[now_visit_from] + 1;
        push(queue, visiting);
      }
      curr = curr->next;
    }
  }
  //free memory
  free(visited);
  delete_queue(queue);
  return shortest;
}


// find the lengths of the weighted shortest paths from the given vertex to all the vertices of this graph
/*
This can be determined by using the Dijkstra's shortest path algorithm from the "from" vertex.

If v cannot be reached from the "from" vertex, the length of its shortest path should be 123456, an arbitrary number that represents infinity.
*/
int *lengths_weighted_shortest_paths(graph_t *graph, int from) {
  if (from<0||from>=graph->num_vertices||graph->num_vertices<=0) {
    return NULL;
  }
  int *visited = (int *) malloc(sizeof(int) * graph->num_vertices); //array to track whether a vertex is visited
  int *shortest = (int *) malloc(sizeof(int) * graph->num_vertices); //array to track the shortest distance
  //int shortest[100];
  queue_t *priority_queue = init_queue();
  int i;
  for (i = 0; i < graph->num_vertices; i++) { //initialize
    shortest[i] = 123456; // to infinity
    visited[i] = 0; // not visited
  }
  shortest[from] = 0;
  for (i = 0; i < graph->num_vertices; i++) { //push into the priority queue
    push_pq(priority_queue, i, 123456);
  }
  push_pq(priority_queue, from, 0);
  while (priority_queue->length > 0) {
    int now_visit_from = pop(priority_queue); //lowest priority
    visited[now_visit_from] = 1; // mark as visited
    dnode_t *curr = graph->adjacency_list[now_visit_from];
    while (curr != NULL) { //traverse every vertex
      int visiting = curr->destination;
      if (!visited[visiting] //if not visited
          //and new path is shorter than the current shortest
          && shortest[visiting] > shortest[now_visit_from] + curr->weight) {
        shortest[visiting] = shortest[now_visit_from] + curr->weight;
        //change priority
        push_pq(priority_queue, visiting, shortest[visiting]);
      }
      curr = curr->next;
    }
  }
  free(visited);
  delete_queue(priority_queue);
  return shortest;
}

//create an empty queue
queue_t *init_queue() {
  queue_t *queue = (queue_t *) malloc(sizeof(queue_t));
  queue->head = NULL;
  queue->tail = NULL;
  queue->length = 0;
  return queue;
}

//push to the queue
void push(queue_t *q, int element) {
  dnode_t *node = (dnode_t *) malloc(sizeof(dnode_t));
  node->destination = element; //use destination to hold value
  node->weight = 0;//this doesn't get used
  node->next = NULL;
  node->prev = NULL;
  if (q->head == NULL) { // empty queue
    q->head = node;
    q->tail = node;
  } else {
    //add in front, pop from back
    node->next = q->head;
    q->head->prev = node;
    q->head = node;
  }
  q->length++;
}

//push to the queue as a priority queue
//the smallest priority at bottom to be compatible with pop();
void push_pq(queue_t *q, int element, int priority) {
  dnode_t *node = (dnode_t *)malloc(sizeof(dnode_t));

  node->destination = element; // use destination to hold value
  node->weight = priority;     // this is the priority
  node->next = NULL;
  node->prev = NULL;
  q->length++;

  if (q->head == NULL) { // empty queue
    q->head = node;
    q->tail = node;
  } else {
    dnode_t *curr = q->head;
    // find insertion point
    // since it's already sorted just find first smaller priority
    while (curr != NULL && priority < curr->weight) {
      curr = curr->next;
    }
    if (curr == NULL) { // insert at end
      q->tail->next = node;
      node->prev = q->tail;
      q->tail = node;
    } else if (curr == q->head) { // insert at head
      node->next = q->head;
      q->head->prev = node;
      q->head = node;
    } else { // insert before curr (middle)
      node->next = curr;
      node->prev = curr->prev;
      curr->prev->next = node;
      curr->prev = node;
    }
  }
}

//pop from the queue (-1 means no element to pop)
int pop(queue_t *q) {
  if (q->tail == NULL) {
    return -1;
  } else {
    dnode_t *temp = q->tail; // store current tail
    int element = q->tail->destination; // get the element
    if (q->tail->prev == NULL) { //if only one
      q->head = NULL;
      q->tail = NULL;
    } else {
      q->tail->prev->next = NULL;
      q->tail = q->tail->prev; // move tail ahead
    }
    q->length--;
    free(temp);

    return element;
  }
}

//delete queue
void delete_queue(queue_t *q) {
  if (q->length > 0) {
    dnode_t *curr = q->head;
    dnode_t *prev = NULL;
    while (curr != NULL) {
      prev = curr;
      curr = curr->next;
      free(prev);
    }
  }
  free(q);
}

