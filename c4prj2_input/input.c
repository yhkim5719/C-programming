#include <string.h>
#include "input.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
	deck_t* tmp = malloc(sizeof(*tmp));
	tmp->cards = NULL;
	tmp->n_cards = 0;

	for(int i = 0; i < strlen(str); i++) {
    		if((str[i] == '\n')||(str[i] == ' ')){continue;}
    		else {
      			if(str[i] == '?') {
        			i++;
        			char* num = NULL; //[strlen(str)];
        			int j = 0;
        			while(!((str[i] == '\n')||(str[i] == ' '))) {
          				num[j]=str[i];
          				i++;
					j++;
				}
        			num[j]='\0';
        			add_future_card(fc,atoi(num),add_empty_card(tmp)) ;
      			} else {
        		card_t x = card_from_letters(str[i],str[i+1]);
        		add_card_to(tmp,x);
        		i++;
			}
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
	deck_t** input = NULL;
	size_t n_hand = 0;

	char* hand = NULL;
	size_t sz = 0;
	while (getline(&hand, &sz, f) >= 0) {
//		if(hand[0] == '\n') {continue;}
		input = realloc(input, (n_hand + 1) * sizeof(*input));
		deck_t* tmp = hand_from_string(hand, fc); // 
		if (tmp == NULL) {continue;}
		input[n_hand] = tmp; 
//		hand = NULL;
		n_hand++;
	}
	*n_hands = n_hand;
	free(hand);
	
	return input;
}

/*

- deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc);
  
   This function reads the input from f.  Recall that the input
   file has one hand per line (and that we represent a hand
   with a deck_t).  You should allocate a deck_t for each hand
   and place it into an array of pointers to deck_ts, which is your
   answer.
   This function needs to tell its caller how many hands it read.
   We could return a struct, but we are going to do this a
   different way: it will fill in *n_hands with the number
   of hands.  This is a bit different, but you have seen it
   before: this is how getline "returns" the string it
   read and the size of the space allocated to that string.

   As you read the input, if you encounter future cards
   (?0, ?1, ...), you should use add_empty_card to
   create a placeholder in the hand, and then add_future_card
   to make sure you will update it correctly when you draw
   later.  Also remember that you wrote add_card_to
   earlier in this course, as well as card_from_letters
   in Course 2.  These will both be handy here!

   I abstracted out the code to take one single line
   and parse it into a hand:
     deck_t * hand_from_string(const char * str, future_cards_t * fc)
   and recommend you do the same.

 Note that most of the rest of the code assumes that a poker hand
 has AT LEAST 5 cards in it.  Your read_input function should enforce
 this requirement. If there are fewer than 5 cards, print
 a useful error message and exit.
*/
