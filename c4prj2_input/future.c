#include <stdio.h>
#include <stdlib.h>
#include "future.h"

void add_future_card (future_cards_t* fc, size_t index, card_t* ptr) {
	if (index >= fc->n_decks) {
		fc = realloc(fc, (fc->n_decks + 1) * sizeof(deck_t));
		while (index >= fc->n_decks) {
			fc->decks[fc->n_decks].cards = NULL;
			fc->decks[fc->n_decks].n_cards = 0;
			fc->n_decks++;
		}
	}

	fc->decks[index].cards=realloc(fc->decks[index].cards,(fc->decks[index].n_cards+1)*sizeof(*(fc->decks[index].cards)));
 	fc->decks[index].cards[fc->decks[index].n_cards]=ptr;
 	fc->decks[index].n_cards++;
}

void future_cards_from_deck (deck_t* deck, future_cards_t* fc) {
	for (size_t i = 0; i < fc->n_decks; i++) {
		if (deck->cards[i] == NULL) {
			perror("Need more cards in deck");
			return;
		}
		if (fc->decks[i].n_cards == 0) {continue;}
		for (int j = 0; j < fc->decks[i].n_cards; j++) {
			fc->decks[i].cards[j]->value = deck->cards[i]->value;
			fc->decks[i].cards[j]->suit = deck->cards[i]->suit;
		}
	}
}
