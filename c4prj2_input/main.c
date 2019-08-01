#include <stdlib.h>
#include <stdio.h>

#include "input.h"
#include "future.h"
#include "deck.h"

int main (){
  FILE * f = fopen("hand.txt","r");
  if (f == NULL){
    fprintf(stderr,"could not open the fiel\n");
    return EXIT_FAILURE;
  }
  size_t n_hands =0;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;
  deck_t ** hands_array = read_input(f, &n_hands, fc);
  /*
  for (int i=0; i<n_hands; i++){
    print_hand(hands_array[i]);
  }
  */
  return EXIT_SUCCESS;
}
