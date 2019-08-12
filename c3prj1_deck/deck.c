
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

int com (card_t c1,card_t c2){
  if ((c1.value == c2.value) &&(c1.suit == c2.suit)) return 1;
  return 0;

}

void print_hand(deck_t * hand){
  card_t ** card =hand -> cards ;
  card_t  card1;
  for (size_t i=0 ;i<(hand -> n_cards );i++){
    card1=**(card +i);
    print_card(card1);
  }
}

int deck_contains(deck_t * d, card_t c) {
  card_t ** card =d -> cards ;
  for (size_t i=0 ;i< d -> n_cards ;i++){
    if (com(**(card+i),c)) return 1;
  }

  return 0;
}

void shuffle(deck_t * d){
  card_t ** card =d -> cards ;
  card_t * temp;
  size_t n=d ->n_cards;
  int randarry;
  for (size_t i=0 ;i< n/2 ;i++){
    randarry= random()%(n-i)+i;
    temp=card[i];
    card[i]=card[randarry];
    card[randarry]=temp;
  }  
}

void assert_full_deck(deck_t * d) {
  card_t ** card =d -> cards ;
  card_t c;
  int count;
  
  for (size_t i=0 ;i< d -> n_cards ;i++){
    c=**(card+i);
    count=0;
    for (size_t j=0 ;j< d -> n_cards ;j++){
      if(com(**(card+j), c)) count ++;
    }
    assert(count ==1);
  }
}

void add_card_to(deck_t * deck, card_t c){
  
  card_t* c1=malloc(sizeof(*c1));
  
  c1->value = c.value;
  
  c1->suit = c.suit;
  
  deck ->cards= realloc(deck->cards,(deck ->n_cards + 1)*sizeof(*deck ->cards));
  
  deck ->cards[deck ->n_cards]=c1;
  
  deck ->n_cards ++;
  
}



card_t * add_empty_card(deck_t * deck){
  
  card_t* c1=malloc(sizeof(*c1));
  
  c1->value = 0;
  
  c1->suit = 0;
  
  deck ->cards= realloc(deck->cards,(deck ->n_cards + 1)*sizeof(*deck ->cards));
  
  deck ->cards[deck ->n_cards]=c1;
  
  deck ->n_cards ++;
  
  return c1;
  
}





deck_t * make_deck_exclude(deck_t * excluded_cards){
  
  deck_t* ans=malloc(sizeof(*ans));
  
  ans->cards=NULL;
  
  ans->n_cards=0;
  
  for(unsigned i=0;i<52;i++){
    
    card_t c= card_from_num(i);
    
    if(!deck_contains(excluded_cards,c)) add_card_to(ans,c);
    
  }
  
  return ans;
  
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  
  deck_t* deck=malloc(sizeof(*deck));
  
  deck->n_cards=0;
  
  deck->cards=NULL;
  
  for (size_t i=0 ; i<n_hands ;i++){
    
    for(int x=0 ; x<hands[i]->n_cards ;x++){
      
      deck->cards=realloc(deck->cards,(deck->n_cards+1)*sizeof(*deck->cards));
      
      deck->cards[deck->n_cards]=hands[i]->cards[x];
      
      deck->n_cards ++;
      
    }
    
  }
  
  deck_t* deck2=make_deck_exclude(deck);
  
  free(deck->cards);
  
  free(deck);
  
  return deck2 ;
  
}



void free_deck(deck_t * deck) {
  
  for(int i=0 ;i<deck->n_cards;i++){
    
    free(deck->cards[i]);
    
  }
  
  free(deck->cards);
  
  free(deck);
  
}


/*
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void print_hand(deck_t * hand){
	for (int i = 0; i < hand->n_cards; ++i) {
		print_card(*(hand->cards[i]));
//		if (i != hand->n_cards) {
//			printf(" ");
//		}
	}
}

int deck_contains(deck_t* d, card_t c) {
	if (d->n_cards != 0) {
		for (int i = 0; i < d->n_cards; ++i) {
			if (d->cards[i]->value == c.value && d->cards[i]->suit == c.suit) {
				return 1;
			}
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
	if(d->n_cards == 52) {return;}
	card_t tmp;
	for (int i = 0; i < 4; ++i) {
		tmp.suit = i;
		for (int j = 2; j < 15; ++j) {
		//	card_t tmp;
		//	tmp.suit = i;
			tmp.value = j;
			int chk = deck_contains(d, tmp);
			assert(chk == 1);
		}
	}			
	return;
}

void add_card_to(deck_t* deck, card_t c) {
	card_t* tmp = malloc(sizeof(card_t));
	tmp->value = c.value;
	tmp->suit = c.suit;
	deck->cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(*deck->cards));
	deck->cards[deck->n_cards] = tmp;
	deck->n_cards++;
}

card_t* add_empty_card(deck_t* deck) {
	card_t* e_card = malloc(sizeof(card_t));
	e_card->value = 0;
	e_card->suit = 0;
	add_card_to(deck, *e_card);

	return e_card;
}

deck_t* make_deck_exclude(deck_t* excluded_cards) {
	deck_t* tmp_deck = malloc(sizeof(*tmp_deck));
	tmp_deck->cards = NULL;
	tmp_deck->n_cards = 0;
	card_t tmp;
	for (unsigned i = 0; i < 52; i++) {
		tmp = card_from_num(i);
		if (deck_contains(excluded_cards, tmp) == 0) {
			add_card_to(tmp_deck, tmp);
		}
	}
	return tmp_deck;
}

deck_t* build_remaining_deck(deck_t** hands, size_t n_hands) {
	deck_t* tmp_deck = malloc(sizeof(*tmp_deck));
	tmp_deck->n_cards = 0;
	tmp_deck->cards = NULL;
	for (size_t i = 0; i < n_hands; i++) {
		for (int j = 0; j < hands[i]->n_cards; j++) {
			add_card_to(tmp_deck, *hands[i]->cards[j]);
		}
	}
	deck_t* remaining_deck = make_deck_exclude(tmp_deck);
	
	return remaining_deck;
}

void free_deck(deck_t* deck) {
	for (int i = 0; i < deck->n_cards; i++) {
		free(deck->cards[i]);
	}
	free(deck->cards);
	free(deck);
}
*/
