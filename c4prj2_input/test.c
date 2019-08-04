#include <stdio.h>
#include <stdlib.h>
#include "future.h"
#include "cards.h"
#include "deck.h"
#include "input.h"

int main (int argc, char** argv) {
	if (argc != 2) {
		perror("wrong # of arg.");
		return EXIT_FAILURE;
	}
	future_cards_t* fc = malloc(sizeof(*fc));
	fc->n_decks = 0;
	fc->decks = NULL;

	FILE* f = fopen(argv[1], "r");
	size_t sz = 0;
	deck_t** input = read_input(f, &sz, fc);
	
	deck_t* r_deck = build_remaining_deck(input, sz);
	future_cards_from_deck (r_deck, fc);

	printf("fc_from_deck\n\n");
	print_hand(r_deck);	
	printf("\n\n");

	for (int i = 0; i < fc->n_decks; i++) {
		for (int j = 0; j < fc->decks[i].n_cards; j++) {
		printf("fc->decks[%d].n_card[%zu] \n", i, fc->decks[i].n_cards);
		print_card(*fc->decks[i].cards[j]);	
		printf("\n");
		}
	}
	for (int i = 0; i < sz; i++) {
		print_hand(input[i]);
		printf("\n");
	}
	
	fclose(f);

	return 0;
}
