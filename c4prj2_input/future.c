#include "future.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
  if ((index+1) > fc->n_decks){
    fc->decks = realloc(decks, (index+1)*sizeof(*decks));
    fc->decks[index].cards[0]=ptr;
    fc->decks[index].n_cards=1;
    fc->n_decks = index+1;
  }
  else{
    fc->decks[index].cards = realloc(fc->decks[index].cards, (fc->decks[index].n_cards +1)*sizeof(*(fc->decks[index].cards)));
    fc->decks[index].n_cards += 1;
    fc->decks[index].cards[fc->decks[index].n_cards -1]=ptr;
  }
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
  if (deck->n_cards < fc->n_decks){
    printf("there is not enough cards\n");
  }
  else{
    for (int i=0; i < fc->n_decks ; i++){
      for (int j=0; j<fc->decks[i].n_cars;j++){
	fc->decks[i].cards[j] = deck->cards[i];
      }
    }
  }
}
