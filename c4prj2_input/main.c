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
  FILE * f1 = fopen("d.txt","r");
  if (f1 == NULL){
    fprintf(stderr,"could not open the file\n");
    return EXIT_FAILURE;
  }
  
  size_t n_hands =0;
  size_t n_deck =0;
  future_cards_t * fc = malloc(sizeof(*fc));
  future_cards_t * fc1 = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;
  deck_t ** hands_array = read_input(f, &n_hands, fc);
  //  deck_t ** deck_array = read_input(f1, &n_deck, fc1);
  printf("no of cards in the deck is %lu\n",hands_array[0]->n_cards);
  printf("no of unknown cards %lu\n",fc->n_decks);
  future_cards_from_deck(hands_array[0],fc);
  print_hand(hands_array[1]);
  printf("\n");
  /*
  for (int i=0; i<n_hands; i++){
    print_hand(hands_array[i]);
  }
  */
  return EXIT_SUCCESS;
}
