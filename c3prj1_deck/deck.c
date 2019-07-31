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

void add_card_to (deck_t * deck, card_t c){
  deck->cards = realloc(deck->cards, (deck->n_cards + 1)*sizeof(*(deck->cards)));
  deck->cards[deck->n_cards] = malloc(sizeof(*c));
  deck->cards[deck->n_cards]->value = c.value;
  deck->cards[deck->n_cards]->suit = c.suit;
}

card_t * add_empty_card(deck_t * deck){
  card_t * empty_card = malloc(sizeof(*empty_card));
  empty_card->value = 0;
  empty_card->suit = 0;
  add_card_to(deck,*empty_card);
  return empty_card;
}

deck_t * make_deck_exclude (deck_t * excluded_cards){
  deck_t * deck_excluded = malloc(sizeof(*(deck_excluded)));
  size_t num = 52 - excluded_cards->n_cards;
  deck_excluded->n_cards = num;
  deck_excluded->cards = malloc(num*sizeof(*(deck_excluded->cards)));
  for (int i=0; i<52 ; i++){
    if (!deck_contains(excluded_cards, card_from_num(i))){
      add_card_to(deck_excluded,card_from_num(i));
    }
  }
  return deck_excluded;
}

deck_t * build_remaining_deck (deck_t ** hands, size_t n_hands){
  deck_t * tailored_deck = malloc(sizeof(*tailored_deck));
  tailored_deck->n_cards = 0;
  tailored_deck->cards = NULL;
  for (int i=0; i < n_hands ; i++){
    for (int j=0; j < hands[i]->n_cards; j++){
      add_card_to(tailored_deck, hands[i]->cards[j]);
    }
  }
  return make_deck_exclude(tailored_deck);
}

void free_deck(deck_t * deck){
  free(deck->cards);
  free(deck);
}

