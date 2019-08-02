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
	fc->decks[index] = malloc(sizeof(deck_t));
	ptr = add_empty_card(fc[index]);
}

void future_cards_from_deck (deck_t* deck, future_cards_t* fc) {
	for (size_t i = 0; i < fc->n_decks; i++) {
		if (deck->cards[i] == NULL) {
			perror("Need more cards in deck");
			return;
		}
		if (fc->decks[i].n_cards == 0) {continue;}
		for (int j = 0; j < fc->decks[i].n_cards; j++) {
			fc->decks[i]->cards[j]->value = deck->cards[i]->value;
			fc->decks[i]->cards[j]->suit = deck->cards[i]->suit;
		}
	}
}

/*
struct future_cards_tag {
  deck_t * decks;
  size_t n_decks;
};

 - void future_cards_from_deck(deck_t * deck, future_cards_t * fc);
   This function takes a deck (which has been shuffled),
   and a future_cards_t (which has been filled in with
   all the pointers to placeholders) and draws cards from
   the deck and assigns their values and suits to the
   placeholders pointed to in fc.
   For example if the deck is
     As Kh 8c ....
   and fc was created from the input
     3c 4c ?0 ?1 ?2
     5h 9d ?0 ?1 ?2
   then this function will draw As for ?0,
   and fill in the two placeholders for ?0 (which
   you can find with the pointers in fc, as described
   in the video).  Then it will draw Kh for ?1,
   and so on. Think about a case where this function would need to
   print an error message.

 - void add_future_card(future_cards_t * fc, size_t index, card_t * ptr);
   This adds ptr into the future cards for the given index (that is,
   which ?n it is). So if this is a future card for ?3, then index
   will be 3.  ptr will point at an existing placeholder card
   (it will point into a hand at a card which was added
   with add_empty_card).
   Note that it is entirely possible to have an input like
     Kh Qh As 4c 2c ?3 ?4
     Ac Qc As 4c 2c ?3 ?4
   (which might happen if e.g., someone edited a file that
   originally have ?0, ?1, and ?2 but replaced them when
   they became known). Or you might see ?3 before ?2.
   Your add_future_card should handle such
   cases by reallocing its array to be large enough to handle
   the specified index, and just having empty decks for
   the indicies that have not had add_future_card called
   on them yet.

/
