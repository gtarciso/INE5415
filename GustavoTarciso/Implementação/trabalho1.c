#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct State {
  int head_size; // amount of symbols in state's head
  char* head; // the actual state
  char **transitions; // transitions from each symbol in this state
};

struct State **states;

int n_symbols; // amount of symbols in the alphabet
int n_states; // amount of states in the FNA
int file_size;

int line_size();

void f_size();

struct State *State_create() {
  struct State *st = malloc(sizeof(struct State)); // allocate the structure
  st->head_size = 1;
  st->head = malloc(sizeof(char)*st->head_size);
  scanf("%c ", st->head); // define the head of the state (the state properly)
  int ln = line_size();
  printf("%d\n", ln);
  st->transitions = malloc(sizeof(char)*ln); // allocate the struc with the line size
  int i, j;
  if(st->transitions) {
    for(i = 0; i < n_symbols; i++) { // populate transitions vector
      j = 0;
      char aux = 'z'; // auxiliar to loop's maintenance
      char tr[ln];
      while(aux != '}') { // maintenance loop, in transition format {q0, ..., qn}
        scanf("%c", &aux); // allocate the transitions of state by the symbol
        printf("%c\n", aux);
        tr[j] = aux;
        if(aux == '-') // maintence the loop, if transitions doesn't exist, interrupt while
          aux = '}';
        j++;
      }
      st->transitions[i] = malloc(sizeof(char)*j); // allocate the transition array
      if (st->transitions[i]) {
        int k;
        // this shit doesn't work, geez :(
        for(k = 0; j < j; k++) {
          st->transitions[i][k] = tr[k]; // this fucking line is killing me
        }
      }
    }
    return st;
  }
}

void State_print(struct State *st) {
  int i, j;
  for(i = 0; i < st->head_size; i++)
    printf("%c ", st->head[i]);
  for(i = 0; i < n_symbols; i++);
    j  = 0;
    printf("{");
    while(st->transitions[i][j] != '}')
      if(st->transitions[i][j+i] == '}')
        printf("%c}", st->transitions[i][j]);
      else
        printf("%c, ", st->transitions[i][j]);
}

/*
 * get file's size
 */

void f_size() {
  fseek(stdin, 0L, SEEK_END);
  file_size = ftell(stdin);
  fseek(stdin, 0L, SEEK_SET);
}
/*
 * get line size moving a file pointer and counting
 */
int line_size() {
  int count = 0;
  while(getc(stdin) != '\n')
    count++;
  fseek(stdin, -(count+1), SEEK_CUR); // put the pointer back to line init
  return count;
}

int main() {
  scanf("%d ", &n_symbols);
  scanf("%d ", &n_states);
  int i, j;
  for(i = 0; i < n_states; i++)
    states[i] = State_create();
  for(i = 0; i < n_states; i++){
    free(states[i]->head);
    free(states[i]->transitions);
  }
  free(states);
  return 0;
}