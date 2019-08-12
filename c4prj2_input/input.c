#include <string.h>
#include <ctype.h>
#include "input.h"
#include "future.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
	deck_t* tmp = malloc(sizeof(*tmp));
	tmp->cards = NULL;
	tmp->n_cards = 0;
	for(int i = 0; i < strlen(str); i++) {
		if(isspace(str[i])) {
			continue;
		}
		if(str[i] == '?' && isdigit(str[i+1])) {
        		char num[5];
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
		perror("short number of card");
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


/*		// hand_from_string part
		if( ('2' <= str[i] && str[i] <= '9') || (str[i] == '0' || str[i] == 'A' || str[i] == 'K' || str[i] == 'Q' || str[i] == 'J')) {
			i++;
			if(str[i] == 's' || str[i] == 'd' || str[i] == 'h' || str[i] == 'c') { 
	        		card_t c = card_from_letters(str[i-1], str[i]);
        			add_card_to(tmp, c);
        		} else {
				continue;
			}
		} else if(str[i] == '?' && isdigit(str[i+1])) {
        		char num[5];
        		int j = 0;
        		i++;
        		while(isdigit(str[i])) {
          			num[j++] = str[i++];
			}
        		num[j] = '\0';
        		add_future_card(fc, strtoul(num, NULL, 0), add_empty_card(tmp));
      		} else {
			continue;
    		}
*/
