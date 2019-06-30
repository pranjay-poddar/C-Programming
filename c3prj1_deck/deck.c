#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  for (int i=0; i<hand->n_cards ; i++){
    card_t ** cards_array = hand->cards;
    print_card(*cards_array[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  size_t n = d->n_cards;
  for (int j=0; j < n; j++){
    card_t ** array = d->cards;
    if ((array[j])->value == c.value && (array[j])->suit == c.suit){
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  card_t * dum_address;
  card_t ** array= d->cards;
  for (int i=0; i<d->n_cards; i++){
    int n1 = rand()% d->n_cards;
    // int n2 = rand()% d->n_cards;
    dum_address = array[i];
    array[i]=array[n1];
    array[n1] = dum_address;
  }

}

void assert_full_deck(deck_t * d) {
  for (unsigned c=0; c<52; c++){
    assert(deck_contains(d,card_from_num(c)));
  }
}
