#include "cards.h"
#include "deck.h"
#include "future.h"
#include "input.h"

int main(int argc, char** argv) {
	if (argc != 3) {return EXIT_FAILURE;}
	FILE* f = fopen(argv[1], "r");
	size_t* n;
	future_cards_t* fc;
	deck** input = read_input(f, n, fc);

}
