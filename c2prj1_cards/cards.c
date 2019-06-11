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
  switch (c.suit){
  case 0 :
    return 's';
  case 1 :
    return 'h';
  case 2 :
    return 'd';
  case 3 :
    return 'c';
  default :
    return '0';
  }
}

void print_card(card_t c) {
  printf("%c%c",value_letter(c),suit_letter(c));

}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  switch (suit_let){
  case 's' :
    temp.suit = SPADES;
    break;
  case 'h':
    temp.suit = HEARTS;
    break;
  case 'd' :
    temp.suit = DIAMONDS;
    break;
  case 'c' :
    temp.suit = CLUBS;
    break;
  default :
    printf("please enter a valid suit\n");
    break;
  }
  switch (value_let){
  case 'A' :
    temp.value = 14;
    break;
  case 'K' :
    temp.value = 13;
    break;
  case 'Q' :
    temp.value = 12;
    break;
  case 'J' :
    temp.value = 11;
    break;
  case '0':
    temp.value = 10;
    break;
  default  :;
    int dd = value_let - '0';
    temp.value = dd;
    break;
  }
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  int ddd = c/13;
  int remainder = c % 13;
  temp.value = remainder + 2;
  switch (ddd){
  case 0 :
    temp.suit = SPADES;
    break;
  case 1 :
    temp.suit = HEARTS;
    break;
  case 2 :
    temp.suit = DIAMONDS;
    break;
  case 3:
    temp.suit = CLUBS;
    break;
  }
  return temp;
}
