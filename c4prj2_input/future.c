#include <stdio.h>
#include "future.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
  size_t n =0;
  if ((index+1) > fc->n_decks){
    fc->decks = realloc(fc->decks, (index+1)*sizeof(*(fc->decks)));
    fc->decks[index].cards=malloc(sizeof(*(fc->decks[index].cards)));
    fc->decks[index].cards[0]=ptr;
    fc->decks[index].n_cards=1;
    fc->n_decks = index+1;
  }
  else{
    if (fc->decks[index].cards == NULL){
      fc->decks[index].n_cards = 0;
      //      printf("yes cards is null\n");
    }
    n = fc->decks[index].n_cards;
    fc->decks[index].cards = realloc(fc->decks[index].cards,(n+1)*sizeof(card_t));
    //printf("%lu\n",fc->decks[index].n_cards);
    fc->decks[index].cards[n]=ptr;
    n++;
    fc->decks[index].n_cards = n;
  }
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
  if (deck->n_cards < fc->n_decks){
    printf("there is not enough cards in the deck\n");
    exit(EXIT_FAILURE);
  }
  else{
    //    print_hand(deck);
    for (int i=0; i < fc->n_decks ; i++){
      for (int j=0; j<fc->decks[i].n_cards;j++){
	//print_card(*(deck->cards[i]));
	//printf("\n");
	fc->decks[i].cards[j]->value =5/* deck->cards[i]->value*/;
      }
    }
  }
}
