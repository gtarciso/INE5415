#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct State {
  int head_size; // amount of symbols in state's head
  char *head; // the actual state
  char **transitions; // transitions from each symbol in this state
};

struct State **states;

int n_symbols; // amount of symbols in the alphabet
int n_states; // amount of states in the FNA
int file_size;

int line_size();

void f_size();

void the_walking_file();

void generate_FNA(int n);

struct State *State_create(int _hs) {
  struct State *st = malloc(sizeof(struct State)); // allocate the structure
  st->head_size = _hs;
  int i, j;
  char aux; // auxiliar to loop's maintenance
  st->head = malloc(sizeof(char)*(st->head_size));
  for (i = 0; i < _hs; i++){
    scanf("%c", &aux); // define the head of the state (the state properly)
    st->head[i] = aux;
  }
  int ln = line_size();
  st->transitions = malloc(sizeof(char)*ln); // allocate the struc with the line size
  if(st->transitions) {
    for(i = 0; i < n_symbols; i++) { // populate transitions vector
      j = 0;
      aux = 'z'; // maintenance while's loop
      char tr[ln+1];
      while(aux != '}') { // maintenance loop, in transition format {q0, ..., qn}
        scanf("%c", &aux); // allocate the transitions of state by the symbol
        tr[j] = aux;
        if(aux == '-') { // maintence the loop, if transitions doesn't exist, interrupt while
          aux = '}';
        }
        j++;
      }
      st->transitions[i] = malloc(sizeof(char)*j); // allocate the transition array
      if (st->transitions[i]) {
        int k;
        for(k = 0; k < j; k++) {
          st->transitions[i][k] = tr[k];
        }
      }
    }
    the_walking_file();
    return st;
  }
}

/*
 * print the automata
 */

void State_print(struct State *st) {
  int i, j;
  for(i = 0; i < st->head_size; i++)
    printf("%c ", st->head[i]);
  for(i = 0; i < n_symbols; i++) {
    j  = 0;
    while(st->transitions[i][j] != '}') {
      if(st->transitions[i][j+1] == '}')
        printf("%c}", st->transitions[i][j]);
      else if(st->transitions[i][j]== '{' )
        printf("{");
      else if (st->transitions[i][j] == '-') {
        printf("-");
        break;
      }
      else
        printf("%c", st->transitions[i][j]);
      j++;
    }
  }
  printf("\n");
}

/*
 * get file's size
 */

void f_size() {
  fseek(stdin, 0L, SEEK_END);
  file_size = ftell(stdin);
  fseek(stdin, 0L, SEEK_SET);
  rewind(stdin);
}

/*
 * a method to move the pointer to the next line
 * avoiding some bugs with scanf
 */

void the_walking_file() {
  while(getc(stdin) != '\n')
    continue;
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

void generate_FNA(int n) {
  int i;
  for(i = 0; i < n; i++) {
    int ln = line_size();
    struct State *st = malloc(sizeof(struct State));
    st = malloc(sizeof(char)*ln);
    st = State_create(1);
    states[i] = st;
  }
}

int main() {
  f_size();
  /*
   * Allocate the States array 
   */
  states = malloc(sizeof(struct State));
  states = malloc(sizeof(char)*file_size);
  scanf("%d", &n_symbols);
  scanf("%d", &n_states);
  the_walking_file();
  generate_FNA(n_states); 
  int i = 0;
  for(i = 0; i < n_states; i++)
    State_print(states[i]);
  return 0;
}