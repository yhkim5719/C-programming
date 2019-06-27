#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
	for (int i = 0; i < hand->n_cards; ++i) {
//		printf("%c%c ", value_letter(*((*hand).cards[i])), suit_letter(*((*hand).cards[i])));
		print_card(*(hand->cards[i]));
		printf(" ");
	}
}

int deck_contains(deck_t * d, card_t c) {
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

}
