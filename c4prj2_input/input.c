#include <string.h>
#include <ctype.h>
#include "input.h"
#include "future.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
	deck_t* tmp = malloc(sizeof(deck_t));
	tmp->cards = NULL;
	tmp->n_cards = 0;
	for(size_t i = 0; i < strlen(str); i++) {
		if(isspace(str[i])) {
			continue;
		}
		if(str[i] == '?' && isdigit(str[i + 1])) {
        		char num[3];
        		int j = 0;
			i++;
        		while(isdigit(str[i])) {
          			num[j] = str[i];
				j++;
				i++;
			}
        		num[j] = '\0';
			size_t idx = strtoul(num, NULL, 0);
        		add_future_card(fc, idx, add_empty_card(tmp));
		} else {
			card_t c = card_from_letters(str[i], str[i + 1]);
			add_card_to(tmp, c);
			i++;
		}
  	}
	if (tmp->n_cards < 5) {
		perror("short cards input");
		return NULL;
	}
	return tmp;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
	if (f == NULL) {
		perror("Invalid file");
		return NULL;
	}
	deck_t** input = NULL; // malloc(sizeof(*input));
	size_t n_hand = 0;

	char* line = NULL;
	size_t sz = 0;
	while (getline(&line, &sz, f) >= 0) {
		input = realloc(input, (n_hand + 1) * sizeof(*input));
		deck_t* tmp = hand_from_string(line, fc); 
		if (tmp == NULL) {continue;}
		input[n_hand] = tmp;
		n_hand++;
	}
	free(line);

	*n_hands = n_hand;
	
	return input;
}
