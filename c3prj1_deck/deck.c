#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
	for (int i = 0; i < hand->n_cards; ++i) {
		print_card(*(hand->cards[i]));
		if (i != hand->n_cards) {
			printf(" ");
		}
	}
}

int deck_contains(deck_t * d, card_t c) {
	assert(d->n_cards == 0);
	for (int i = 0; i < d->n_cards; ++i) {
		if ((*(d->cards[i])).value == c.value && (*(d->cards[i])).suit == c.suit) {
			return 1;
		}
	}
  	return 0;
}

void shuffle(deck_t * d){
	for (int i = 0; i < d->n_cards; ++i) {
		int j = rand();
		card_t * tmp;
		tmp = d->cards[i];
		d->cards[i] = d->cards[j%(d->n_cards)];
		d->cards[j%(d->n_cards)] = tmp;	
	}
	return;

}

void assert_full_deck(deck_t * d) {
	assert(d->n_cards == 52);
	card_t tmp;
	for (int i = 0; i < 4; ++i) {
		tmp.suit = i;
		for (int j = 2; j < 15; ++j) {
		//	card_t tmp;
		//	tmp.suit = i;
			tmp.value = j;
			int chk = deck_contains(d, tmp);
			assert(chk == 1);
		}
	}			
	return;
}
