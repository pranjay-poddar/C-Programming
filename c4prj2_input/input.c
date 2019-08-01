#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "input.h"
#include "deck.h"
#include "future.h"


deck_t * hand_from_string(const char * str, future_cards_t * fc){
  size_t L = strlen(str);
  char hand [L+1];
  char * cursor = strcpy(hand, str);
  //printf("%lu\n",strlen(cursor));
  //printf("%s\n",cursor);
  deck_t * dummy_deck = malloc(sizeof(* dummy_deck));
  char * card_end = NULL;
  dummy_deck->n_cards = 0;
  dummy_deck->cards = NULL;
  int k =0;
  while((k<(L-1)) && (*cursor !='\n')){
    card_end = strchr(cursor,' ');/*
    if (card_end == NULL){
      card_end = strchr(cursor, '\n');
    }
				  */
    if (cursor == card_end){
      cursor++;
      k++;
      // card_end = strchr(cursor, ' ');
    }
    else{
      // check for future card
      if (*cursor == '?'){
	cursor++;
	add_future_card(fc, atoi(cursor), add_empty_card(dummy_deck));
	k += (card_end - cursor+1);
	cursor = card_end + 1;
      }
      else{
	//printf("%c %c\n",*cursor,*(cursor+1));
	add_card_to(dummy_deck, card_from_letters(*cursor,*(cursor+1)));
	cursor += 2;
	k += 2;
      }
    }
  }
  if (dummy_deck->n_cards < 5){
    fprintf(stderr,"the hand must be at least 5\n");
    return EXIT_FAILURE;
  }
  return dummy_deck;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
  char * buffer = NULL;
  size_t sz = 0;
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
