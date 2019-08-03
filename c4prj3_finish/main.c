#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

int determine_winner(deck_t ** hands, size_t num_hands){
  int player_ind = 0;
  unsigned tie = 0;
  int result =0;
  for (int j=1; j < num_hands; j++){
    result = compare_hands(hands[j], hands[player_ind]);
    //    printf("%d ",result);
    if (result > 0){
      player_ind = j;
      tie = 0;
    }
    else if (result == 0){
      tie = 1;
    }
    else{}
  }
  if (tie != 0){
    return -1;
  }
  else{
    return player_ind;
  }
}

int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
  if (argc < 2){
    fprintf(stderr,"not enough arguments\n");
    printf("Usage: ./progName InputFile Trials(optional)\n");
    return EXIT_FAILURE;
  }
  if (argc > 3){
    printf("Usage: ./progName InputFile Trials(optional)\n");
    return EXIT_FAILURE;
  }
  unsigned num_trial = 10000;
  if (argc == 3){
    num_trial = atoi(argv[2]);
  }
  FILE * f = fopen(argv[1], "r");
  // check for opening the file
  if (f == NULL){
    fprintf(stderr, "could not open the file\n");
    return EXIT_FAILURE;
  }
  size_t n_hands =0;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;
  deck_t ** hands_array = read_input(f, &n_hands, fc);
  deck_t * remaining_deck = build_remaining_deck(hands_array, n_hands);
  // count winning array
  unsigned score[n_hands + 1];
  for (int c = 0; c <= n_hands; c++){
    score[c]=0;
  }
  int winner = -2;
  // monte carlo simulation loop
  for (int i=0; i < num_trial; i++){
    shuffle(remaining_deck);
    future_cards_from_deck(remaining_deck, fc);
    winner = determine_winner(hands_array, n_hands);
    //    printf("%d ",winner);
    if (winner >= 0){
      score[winner] += 1;
    }
    else{
      score[n_hands] += 1;
    }
  }
  double ratio = 0;
  for (size_t k=0; k < n_hands; k++){
    ratio = ((double) score[k]) / num_trial;
    printf("Hand %zu won %u / %u times (%.2f%%)\n", k,score[k], num_trial, ratio);
  }
  printf("And there were %u ties\n", score[n_hands]);
  //  printf("%d\n",compare_hands(hands_array[0],hands_array[1]));
  return EXIT_SUCCESS;
}
