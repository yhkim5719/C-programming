#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
	const card_t * const * cp1 = vp1;
	const card_t * const * cp2 = vp2;
	if ((*cp1)->value == (*cp2)->value) {
		return (*cp2)->suit - (*cp1)->suit;
		}
	else {
		return (*cp2)->value - (*cp1)->value;
	}
}

suit_t flush_suit(deck_t * hand) {
	suit_t suit_count[4] = {0};
	for (int i = 0; i < hand->n_cards; ++i) {
		suit_count[(hand->cards[i])->suit]++;
	}
	for (int i = 0; i < NUM_SUITS; ++i) {
		if (suit_count[i] >= 5) {
		return i;
		}
	}
	return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
	unsigned largest = arr[0];
	for (size_t i = 1; i < n; ++i) {
		if (largest < arr[i]) {
			largest = arr[i];
		}
	}
	return largest;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
	for (size_t i = 0; i < n; ++i) {
		if (match_counts[i] == n_of_akind) {
		return i;
		}
	}
	return -1;
}
ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
	for (size_t i = 0 /*match_idx + 1*/; i < hand->n_cards; ++i) {
		if (match_counts[i] > 1 &&
			hand->cards[i]->value != hand->cards[match_idx]->value) {
			return i;
		}
	}
	return -1;
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
	if (fs == NUM_SUITS) {
		int n_length = 0;
		int ref_value = hand->cards[index]->value;
		for (size_t i = index; i < hand->n_cards-1; ++i) {
			if (hand->cards[i+1]->value == ref_value-1) {
				n_length++;
			}
		}
		if (n_length >= 5) {return 1;}
		if (n_length == 4 && 
			hand->cards[index]->value == 5 && 		// TODO check the value
			hand->cards[0]->value == 14) {return -1;}
		return 0;
	} else {
		int n_length = 0;
		int ref_value = hand->cards[index]->value;
		for (size_t i = index; i < hand->n_cards-1; ++i) {
			if (hand->cards[i+1]->value == ref_value-1 && hand->cards[i+1]->suit == fs) {
				n_length++;
			}
		}
		if (n_length >= 5) {return 1;}
		if (n_length == 4 && 
			hand->cards[index]->value == 5 && 		// TODO check the value
			hand->cards[0]->value == 14 &&
			hand->cards[0]->suit == fs) {return -1;}
		return 0;
	}
}

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {
	hand_eval_t ans;
	ans.ranking = what;
	if (n != 0) {
		for (int i = 0; i < n; ++i) {
			ans.cards[i] = hand->cards[idx + i];
		}
		for (int i = n; i < 5; ++i) {
			for (int j = 0; j < hand->n_cards; ++j) {
				if ( j < idx || j > idx + n - 1) {
					ans.cards[i] = hand->cards[j];
				}
			}
		}
	} else {
		for (int i = 0; i < 5; ++i) {
			ans.cards[i] = hand->cards[i];
		}
	}
	return ans;
}


void sort_hand(deck_t * hand) {
	qsort(hand->cards, hand->n_cards, sizeof(card_t), card_ptr_comp);
	return;
}

int compare_hands(deck_t * hand1, deck_t * hand2) {
	sort_hand(hand1);
	sort_hand(hand2);
	hand_eval_t eval_hand1 = evaluate_hand(hand1);
	hand_eval_t eval_hand2 = evaluate_hand(hand2);
	int diff = eval_hand2.ranking - eval_hand1.ranking;
	if (diff != 0) {
		return eval_hand2.ranking - eval_hand1.ranking;
	} else {
		for (int i = 0; i < 5; ++i) {
			diff = (eval_hand2.cards[i])->value - (eval_hand1.cards[i])->value;
			if (diff == 0) {
				diff = (eval_hand1.cards[i])->suit - (eval_hand2.cards[i])->suit; 
				if (diff != 0) {
					return diff;
				}
			}
		}
	} 
	return diff;
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) ;

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