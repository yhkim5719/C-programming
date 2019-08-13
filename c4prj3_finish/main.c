#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

int who_wins(deck_t** hands, size_t sz) {
	int winner = sz;
	int cur = 0;
	int tie = 0;
	for (int i = 0; i < sz - 1; i++) {
		if (compare_hands(hands[cur], hands[i + 1]) < 0) {
			cur = i + 1;
			tie = 0;
		} else if (compare_hands(hands[cur], hands[i + 1]) > 0) {
			continue;
		} else {
			tie = 1;
		}
	}	
	if (tie == 0) {
		winner = cur;
	}
	return winner;
}

int main(int argc, char ** argv) {
	if (argc != 3 && argc != 2) {
		perror("wrong # of argument");
		return EXIT_FAILURE;
	}
	FILE* f = fopen(argv[1], "r");
	size_t sz;
	future_cards_t* fc = malloc(sizeof(*fc));
	fc->n_decks = 0;
	fc->decks = NULL;
	
	deck_t** input = read_input(f, &sz, fc);

	deck_t* r_deck = build_remaining_deck(input, sz);

	unsigned int win[sz + 1];
	for (size_t i = 0; i < sz + 1; i++) {
		win[i] = 0;
	}

	unsigned int num_trials = 10000;
	if (argc == 3) {
		num_trials = atoi(argv[2]);
	}

	for (unsigned int i = 0; i < num_trials; i++) {
		shuffle(r_deck);
		future_cards_from_deck(r_deck, fc);
		win[who_wins(input, sz)]++;
	}
	for (size_t hand = 0; hand < sz; hand++) {
		float win_rate = (float)(100 * win[hand] / num_trials + 0.5);
		printf("Hand %zu won %u / %u times (%.2f%%)\n", hand, win[hand], num_trials, win_rate);
	}
	printf("And there were %u ties\n", win[sz]);

	if (fclose(f) != 0) {
		perror("cannot close file");
		return EXIT_FAILURE;
	}
	free_deck(fc->decks);
	free(fc);
  //YOUR CODE GOES HERE
  return EXIT_SUCCESS;
}
