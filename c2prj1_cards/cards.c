#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(c.value >= 2 && c.value <= VALUE_ACE);
  assert(c.suit>=0 && c.suit <= 3);
}

const char * ranking_to_string(hand_ranking_t r) {
  const char *handName[]={
    "STRAIGHT_FLUSH",
    "FOUR_OF_A_KIND",
    "FULL_HOUSE",
    "FLUSH",
    "STRAIGHT",
    "THREE_OF_A_KIND",
    "TWO_PAIR",
    "PAIR",
    "NOTHING"};
  return handName[r];
}

char value_letter(card_t c) {
  switch (c.value){
  case 10 :
    return '0';
  case 11 :
    return 'J';
  case 12 : 
    return 'Q';
  case 13 :
    return 'K';
  case 14 :
    return 'A';
  default : ;
    char dum1 = '0';
    char dum = dum1 + c.value;
    return dum;
  }
  //return 'x';
}


char suit_letter(card_t c) {
  return 'x';
  
}

void print_card(card_t c) {

}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  return temp;
}
