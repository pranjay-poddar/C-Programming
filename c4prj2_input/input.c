#include <stdlib.h>
#include <stdio.h>
#include "deck.h"
//#include "card.h"
#include "future.h"

deck_t * hand_from_string(const char * str, futrue_cards_t * fc){
  char * cursor = str;
  deck_t * dummy_deck = malloc(sizeof(* dummy_deck));
  char * card_end = NULL;
  dummy_deck->n_cards = 0;
  dummy_deck->cards = NULL;
  while(*cursor != '\n'){
    card_end = strchr(cursor,' ');
    if (card_end == NULL){
      card_end = strchr(cursor, '\n');
    }
    if (cursor == card_end){
      cursor++;
      // card_end = strchr(cursor, ' ');
    }
    else{
      // check for future card
      if (*cursor == '?'){
	add_future_card(fc, atoi(cursor+1), add_empty_card(dummy_deck));
	cursor = card_end + 1;
      }
      else{
	add_card_to(dummy_deck, card_from_letters(*cursor,*(cursor+1)));
	cursor += 2;
      }
    }
  }
  return dummy_deck;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
  char * buffer = NULL;
  sz = 0;
  unsigned hand_count = 0;
  deck_t ** deck_array = NULL;
  deck_t * deckPtr = NULL;
  while(getline(&buffer,&sz,f)>0){
    deckPtr = hand_from_string(buffer,fc);
    deck_array = realloc(deck_array, (hand_count+1)*sizeof(*deck_array));
    deck_array[hand_count] = deckPtr;
    hand_count++;
  }
  *n_hands = hand_count;
  return deck_array;
}
