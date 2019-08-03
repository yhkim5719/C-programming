#include <stdio.h>
#include <stdlib.h>
#include "future.h"
#include "cards.h"
#include "deck.h"
#include "input.h"

int main (int argc, char** argv) {
	if (argc != 3) {
		perror("need more arg.");
		return EXIT_FAILURE;
	}
	future_cards_t* fc = malloc(sizeof(*fc));
	fc->n_decks = 0;
	fc->decks = NULL;
//	fc->decks[fc->n_decks].cards = NULL;
//	fc->decks[fc->n_decks].n_cards = 0;
	FILE* f = fopen(argv[1], "r");
	size_t sz = 0;
	deck_t** input = read_input(f, &sz, fc);
	for (int i = 0; i < sz; i++) {
		print_hand(input[i]);
		printf("\n\n");
	}
	
	deck_t* r_deck = build_remaining_deck(input, sz);
	future_cards_from_deck (r_deck, fc);

//	for (int i = 0; i < fc->n_decks; i++) {
		printf("r_deck \n");
		print_hand(r_deck);	
		printf("\n");
//	}

	for (int i = 0; i < fc->n_decks; i++) {
//		printf("fc[%zu] \n", fc->n_decks);
		for (int j = 0; j < fc->decks[i].n_cards; j++) {
		printf("fc->decks[%d].n_card[%zu] \n", i, fc->decks[i].n_cards);
		print_card(*fc->decks[i].cards[j]);	
		printf("\n");
		}
	}
	fclose(f);

	return 0;
}
