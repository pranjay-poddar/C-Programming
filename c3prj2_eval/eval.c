#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const * cp1 = vp1;
  const card_t * const * cp2 = vp2;
  const card_t * c1 = *cp1;
  const card_t * c2 = *cp2;
  int dum;
  if (c1->value == c2->value){
    dum = c2->suit - c1->suit;
    return dum;
  }
  else{
    dum = c2->value - c1->value;
    return dum;
  }
}

suit_t flush_suit(deck_t * hand) {
  int suit_count[4]={0,0,0,0};
  for (int i=0; i< hand->n_cards;i++){
    suit_t dum = hand->cards[i]->suit;
    suit_count[dum]+=1;
  }
  suit_t j;
  for (j=SPADES; j <= CLUBS; j++){
    if (suit_count[j]>=5){
      return j;
    }
  }
  return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned largest=0;
  for (int i=0; i<n; i++){
    if (arr[i]>largest){
      largest = arr[i];
    }
  }
  return largest;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  for (size_t i=0; i<n ; i++){
    if (match_counts[(int)i]== n_of_akind){
      return i;
    }
  }
  assert(0);
  return 0;
}
ssize_t find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  for (ssize_t i=0; i< hand->n_cards;i++){
    if (match_counts[i]>1 && (hand->cards[i]->value != hand->cards[match_idx]->value)){
      return i;
    }
  }
  /*
  for (ssize_t j = match_idx + match_counts[match_idx];j<hand->n_cards;j++){
    if (match_counts[j]>1){
      return j;
    }
  }
  */
  return -1;
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  //checking if the no of remaining cards is less than 5
  /*if (hand->n_cards - index < 5){
    return 0;
    }*/
  if (hand->cards[index]->value == VALUE_ACE){
    unsigned ref = 5;
    unsigned v ;
    for (int d=index+1; d<hand->n_cards;d++){
      v = hand->cards[d]->value;
      if(v==ref){
	ref--;
      }
    }
    if (ref == 1){
      return -1;
    }
  }
  if (fs == NUM_SUITS){
    int straight_counter = 0;
    unsigned v1,v2;
    for (int q=index; q<hand->n_cards-1;q++){
      v1 = ((hand->cards)[q])-> value;
      v2 = ((hand->cards)[q+1])->value;
      if (v1-v2 > 1 ){
	return 0;
      }
      else if(v1-v2 == 1){
	straight_counter++;
	if (straight_counter==4){
	  return 1;
	}
      }
      else{
	continue;
      }
    }
    if (straight_counter>=4){
      return 1;
    }
    return 0;
  }
  // checking for straight_flush
  else{
    if (hand->cards[index]->suit != fs){
      return 0;
    }
    // straight flush counter
    int s_f_c = 0;
    unsigned ref_val,val;
    suit_t s;
    ref_val = ((hand->cards)[index])->value;
    for (int z = index ; z < hand->n_cards; z++){
      val = ((hand->cards)[z])->value;
      // s1 = ((hand->cards)[z])->suit;
      // V2 = ((hand->cards)[z+1])->value;
      s = ((hand->cards)[z])->suit;
      if (s_f_c ==0 && s == fs){
	ref_val = val;
	s_f_c++;
      }
      else if(s == fs && ref_val-val==1){
	ref_val = val;
	s_f_c ++;
      }
      else{
	continue;
      }
    }
    if (s_f_c >= 5){
      return 1;
    }
    return 0;
  }
}

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {
  hand_eval_t ans;
  int card_counter = 0;
  ans.ranking = what;
  for (int i=0;i<n; i++){
    ans.cards[i]= hand->cards[idx+i];
    card_counter++;
  }
  for (int j=0;j<idx;j++){
    if (card_counter==5){
      break;
    }
    ans.cards[card_counter]=hand->cards[j];
    card_counter++;
  }
  for (int k=idx+n;k<hand->n_cards;k++){
    if (card_counter==5){
      break;
    }
    ans.cards[card_counter]= hand->cards[k];
    card_counter++;
  }
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  qsort(hand1->cards,hand1->n_cards,sizeof(hand1->cards),card_ptr_comp);
  qsort(hand2->cards,hand2->n_cards,sizeof(hand2->cards),card_ptr_comp);
  const hand_eval_t h1 = evaluate_hand(hand1);
  const hand_eval_t h2 = evaluate_hand(hand2);
  if (h1.ranking != h2.ranking){
    return h2.ranking-h1.ranking;
  }
  else{
    for (int i=0; i <5;i++){
      unsigned v1 = h1.cards[i]->value;
      unsigned v2 = h2.cards[i]->value;
      if (v1 == v2){
	continue;
      }
      else{
	int dum = v1 - v2;
	return dum;
      }
    }
    return 0;
  }
}


//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand){
  unsigned * match_count = malloc(hand->n_cards * sizeof(*match_count));
  for (int k = 0 ; k < hand->n_cards ; k++){
    match_count[k]=1;
    //    printf("index = %d  value =%u\n",k,match_count[k]);
  }

  unsigned count = 1;
  for (int i =1; i < hand->n_cards; i++){
    if (hand->cards[i]->value == hand->cards[i-1]->value){
      count++;
      if (i == (hand->n_cards-1)){
	for (int j = (i-count+1); j<=i; j++){
	  match_count[j]=count;
	}
	//	return match_count;
      }
    }
    
    else{
      for (int j = (i-count); j<=(i-1); j++){
	match_count[j]=count;
      }
      if (i == (hand->n_cards-1)){
	match_count[i]=1;
	//	return match_count;
      }
      count = 1;
    }
    
  }
    
  return match_count;
}

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    //    printf("%zu  %zu\n",ind,from->n_cards);
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    //    printf("%zd\n",other_pair_idx+1);
    assert(other_pair_idx<=hand->n_cards-2);
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
