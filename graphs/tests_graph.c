#include <printf.h>
#include <stdlib.h>
#include "graph.h"

//test basic adding
int test_add() {
  printf("---Test test_add() begin: ---\n");
  graph_t * g= init_graph(5);
  add_edge(g,0,1,2);
  add_edge(g,0,2,3);
  add_edge(g,2,3,3);
  add_edge(g,3,4,3);

  if (g->adjacency_list[1]!=NULL) {
    printf("Expected null\n");
  }
  if (g->adjacency_list[4]!=NULL) {
    printf("Expected null\n");
  }
  if (g->adjacency_list[0]->destination!=1) {
    printf("Expected: %d, got: %d\n",1,g->adjacency_list[0]->destination);
    return 0;
  }
  if (g->adjacency_list[0]->next->destination!=2) {
    printf("Expected: %d, got: %d\n",2,g->adjacency_list[0]->destination);
    return 0;
  }
  if (g->adjacency_list[2]->destination!=3) {
    printf("Expected: %d, got: %d\n",3,g->adjacency_list[2]->destination);
    return 0;
  }
  if (g->adjacency_list[3]->destination!=4) {
    printf("Expected: %d, got: %d\n",4,g->adjacency_list[3]->destination);
    return 0;
  }
  delete_graph(g);
  return 1;
}

//test adding duplicates
int test_add_duplicate() {
  graph_t * g= init_graph(5);

  add_edge(g,0,1,2);
  if (g->adjacency_list[0]->weight!=2) {
    printf("Expected: %d, got: %d\n",2,g->adjacency_list[0]->weight);
    return 0;
  }

  add_edge(g,0,1,3);
  if (g->adjacency_list[0]->weight!=3) {
    printf("Expected: %d, got: %d\n",3,g->adjacency_list[0]->weight);
    return 0;
  }

  add_edge(g,0,1,4);
  if (g->adjacency_list[0]->weight!=4) {
    printf("Expected: %d, got: %d\n",4,g->adjacency_list[0]->weight);
    return 0;
  }
  delete_graph(g);
  printf("---Test test_add() end: ---\n");
  return 1;
}

int test_bad_add() {
  printf("---Test test_bad_add() begin: ---\n");
  graph_t * g= init_graph(5);
  //out of range indices
  add_edge(g,6,1,1);
  add_edge(g,1,6,1);
  add_edge(g,2,2,1);
  if (g->adjacency_list[1]!=NULL) {
    printf("Expecting NULL\n");
  }
  if (g->adjacency_list[2]!=NULL) {
    printf("Expecting NULL\n");
  }
  delete_graph(g);
  printf("---Test test_bad_add() end: ---\n");
  return 1;
}

//test adjacency
int test_is_adjacent() {
  printf("---Test test_is_adjacent() begin: ---\n");
  graph_t *g = init_graph(5);
  add_edge(g, 0, 1, 1);
  add_edge(g, 1, 2, 1);
  add_edge(g, 2, 3, 1);
  add_edge(g, 2, 1, 1);
  add_edge(g, 0, 3, 10);

  if (!is_adjacent(g,0,1)) {
    printf("Wrong adjacency.\n");
    return 0;
  }
  if (!is_adjacent(g,1,2)) {
    printf("Wrong adjacency.\n");
    return 0;
  }
  if (!is_adjacent(g,2,3)) {
    printf("Wrong adjacency.\n");
    return 0;
  }
  if (!is_adjacent(g,2,1)) {
    printf("Wrong adjacency.\n");
    return 0;
  }
  if (!is_adjacent(g,0,3)) {
    printf("Wrong adjacency.\n");
    return 0;
  }

  //not adjacent
  if (is_adjacent(g,1,0)) { //cant be reversed
    printf("Wrong adjacency.\n");
    return 0;
  }
  if (is_adjacent(g,3,0)) {
    printf("Wrong adjacency.\n");
    return 0;
  }
  if (is_adjacent(g,3,2)) {
    printf("Wrong adjacency.\n");
    return 0;
  }
  delete_graph(g);
  printf("---Test test_is_adjacent() end: ---\n");
  return 1;

}

//test BFS shortest path
int test_shortest_unweighted() {
  printf("---Test test_shortest_unweighted() begin: ---\n");
  graph_t *g = init_graph(5);
  add_edge(g, 0, 1, 1);
  add_edge(g, 1, 2, 1);
  add_edge(g, 2, 3, 1);
  add_edge(g, 2, 1, 1);
  add_edge(g, 0, 3, 10);

  int *shortest = lengths_unweighted_shortest_paths(g, 0);

  if (shortest[0] != 0) {
    printf("Expected: %d, got: %d\n",0,shortest[0]);
    return 0;
  }
  if (shortest[1] != 1) {
    printf("Expected: %d, got: %d\n",0,shortest[0]);
    return 0;
  }
  if (shortest[2] != 2) {
    printf("Expected: %d, got: %d\n",0,shortest[0]);
    return 0;
  }
  if (shortest[3] != 1) {
    printf("Expected: %d, got: %d\n",0,shortest[0]);
    return 0;
  }
  if (shortest[4] != 123456) { // unreached
    printf("Expected: %d, got: %d\n",0,shortest[0]);
    return 0;
  }
  int* temp = shortest;

  //now check vertex 2
  shortest = lengths_unweighted_shortest_paths(g, 2);
  free(temp);
  if (shortest[0] != 123456) {
    printf("Expected: %d, got: %d\n",123456,shortest[0]);
    return 0;
  }
  if (shortest[1] != 1) {
    printf("Expected: %d, got: %d\n",0,shortest[1]);
    return 0;
  }
  if (shortest[2] != 0) {
    printf("Expected: %d, got: %d\n",0,shortest[2]);
    return 0;
  }
  if (shortest[3] != 1) {
    printf("Expected: %d, got: %d\n",0,shortest[3]);
    return 0;
  }
  if (shortest[4] != 123456) { // unreached
    printf("Expected: %d, got: %d\n",0,shortest[4]);
    return 0;
  }

  free(shortest);
  delete_graph(g);
  printf("---Test test_shortest_unweighted() end: ---\n");
  return 1;
}

int test_shortest_unweighted_larger() {
  printf("---Test test_shortest_weighted_larger() begin: ---\n");
  graph_t *g = init_graph(25);
  //3 ways to go to 25th vertex, and twp of which crossed
  //route 1
  add_edge(g, 0, 1, 10);
  add_edge(g, 1, 2, 10);
  add_edge(g, 2, 24, 20);
  //route 2
  add_edge(g, 0, 5, 4);
  add_edge(g, 5, 11, 4);
  add_edge(g, 11, 16, 10);
  add_edge(g, 16, 22, 5);
  add_edge(g, 22, 23, 5);
  add_edge(g, 23, 24, 5);
  //route 3 (crossing route 2)
  add_edge(g, 0, 6, 4);
  add_edge(g, 6, 7, 4);
  add_edge(g, 7, 12, 10);
  add_edge(g, 12, 16, 5);
  int *shortest = lengths_unweighted_shortest_paths(g, 0);
  if (shortest[24] != 3) {// route 1 should be shortest
    printf("Expected: %d, got: %d\n",3,shortest[24]);
    return 0;
  }
  if (shortest[16] != 3) {// route 2
    printf("Expected: %d, got: %d\n",3,shortest[16]);
    return 0;
  }
  if (shortest[17] != 123456) { //unconnected
    printf("Expected: %d, got: %d\n",123456,shortest[17]);
    return 0;
  }

  free(shortest);
  delete_graph(g);
  printf("---Test test_shortest_unweighted_larger() end: ---\n");
  return 1;
}

int test_shortest_weighted() {
  printf("---Test test_shortest_weighted() begin: ---\n");
  graph_t *g = init_graph(5);
  add_edge(g, 0, 1, 1);
  add_edge(g, 1, 2, 2);
  add_edge(g, 2, 3, 3);
  add_edge(g, 2, 1, 4);
  add_edge(g, 0, 3, 10);
  int *shortest = lengths_weighted_shortest_paths(g, 0);
  if (shortest[0] != 0) {// test from
    printf("Expected: %d, got: %d\n",0,shortest[0]);
    return 0;
  }
  if (shortest[3] != 6) {// two alternative paths
    printf("Expected: %d, got: %d\n",3,shortest[3]);
    return 0;
  }

  int* temp = shortest;

  //now check vertex 2
  shortest = lengths_weighted_shortest_paths(g, 2);
  if (shortest[0] != 123456) {// test from
    printf("Expected: %d, got: %d\n",123456,shortest[0]);
    return 0;
  }
  if (shortest[1] != 4) {
    printf("Expected: %d, got: %d\n",4,shortest[1]);
    return 0;
  }
  if (shortest[3] != 3) {
    printf("Expected: %d, got: %d\n",3,shortest[3]);
    return 0;
  }
  free(temp);
  free(shortest);
  delete_graph(g);
  printf("---Test test_shortest_weighted() end: ---\n");
  return 1;
}

int test_shortest_weighted_larger() {
  printf("---Test test_shortest_weighted_larger() begin: ---\n");
  graph_t *g = init_graph(25);
  //3 ways to go to 25th vertex, and twp of which crossed
  //route 1
  add_edge(g, 0, 1, 10);
  add_edge(g, 1, 2, 10);
  add_edge(g, 2, 24, 20);
  //route 2
  add_edge(g, 0, 5, 4);
  add_edge(g, 5, 11, 4);
  add_edge(g, 11, 16, 10);
  add_edge(g, 16, 22, 5);
  add_edge(g, 22, 23, 5);
  add_edge(g, 23, 24, 5);
  //route 3 (crossing route 2)
  add_edge(g, 0, 6, 4);
  add_edge(g, 6, 7, 4);
  add_edge(g, 7, 12, 10);
  add_edge(g, 12, 16, 5);
  int *shortest = lengths_weighted_shortest_paths(g, 0);
  if (shortest[24] != 33) {// route 2 should be shortest
    printf("Expected: %d, got: %d\n",33,shortest[24]);
    return 0;
  }
  if (shortest[16] != 18) {// still route 2
    printf("Expected: %d, got: %d\n",18,shortest[16]);
    return 0;
  }
  if (shortest[17] != 123456) { //unconnected
    printf("Expected: %d, got: %d\n",123456,shortest[17]);
    return 0;
  }

  free(shortest);
  delete_graph(g);
  printf("---Test test_shortest_weighted_larger() end: ---\n");
  return 1;
}

int main(){
  int tested = 8;
  int success = 0;
  success += test_add();
  success += test_add_duplicate();
  success += test_is_adjacent();
  success += test_bad_add();
  success += test_shortest_unweighted();
  success += test_shortest_unweighted_larger();
  success += test_shortest_weighted();
  success += test_shortest_weighted_larger();
  printf("Ran %d tests, %d succeed, %d failed.\n",tested, success, tested-success);
}