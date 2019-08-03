#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert((2 <= c.value) &&
	 (c.value <= VALUE_ACE) &&
	 (0 <= c.suit) &&
	 (c.suit < 4)
	 );
}

const char * ranking_to_string(hand_ranking_t r) {
  if (r == 0){
    return "STRAIGHT_FLUSH";
  } else if (r == 1) {
    return "FOUR_OF_A_KIND";
  } else if (r == 2) {
    return "FULL_HOUSE";
  } else if (r == 3) {
    return "FLUSH";
  } else if (r == 4) {
    return "STRAIGHT";
  } else if (r == 5) {
    return "THREE_OF_A_KIND";
  } else if (r == 6) {
    return "TWO_PAIR";
  } else if (r == 7) {
    return "PAIR";
  } else {
    return "NOTHING";
  }
} //not sure

char value_letter(card_t c) {
  if (c.value == 2) {
    return '2';
  } else if (c.value == 3) {
    return '3';
  } else if (c.value == 4) {
    return '4';
  } else if (c.value == 5) {
    return '5';
  } else if (c.value == 6) {
    return '6';
  } else if (c.value == 7) {
    return '7';
  } else if (c.value == 8) {
    return '8';
  } else if (c.value == 9) {
    return '9';
  } else if(c.value == 10) {
    return '0';
  } else if (c.value == 11) {
    return 'J';
  } else if (c.value == 12) {
    return 'Q';
  } else if (c.value == 13) {
    return 'K';
  } else if (c.value == 14) {
    return 'A';
  } //else {
   // return '?';
 // }
}

char suit_letter(card_t c) {
  if (c.suit == 0) {
   return 's';
  } else if (c.suit == 1) {
    return 'h';
  } else if (c.suit == 2) {
    return 'd';
  } else {// if (c.suit == 3) {
    return 'c';
 // }
   // return '!';  
}

void print_card(card_t c) {
  printf("%c%c", value_letter(c), suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
/*  if ((    (value_let != '2') &&
	   (value_let != '3') &&
	   (value_let != '4') &&
	   (value_let != '5') &&
	   (value_let != '6') &&
	   (value_let != '7') &&
	   (value_let != '8') &&
	   (value_let != '9') &&
	   (value_let != '0') &&
	   (value_let != 'J') &&
	   (value_let != 'Q') &&
	   (value_let != 'K') &&
	   (value_let != 'A')) ||
	  ((suit_let != 's') &&
	   (suit_let != 'h') &&
	   (suit_let != 'd') &&
	   (suit_let != 'c'))) {
    printf("You input wrong number.\n");
    exit(EXIT_FAILURE);*/
//  } else
 if (value_let == '2') {
      temp.value = 2;
  } else if (value_let == '3') {
      temp.value = 3;
  } else if (value_let == '4') {
      temp.value = 4;
  } else if (value_let == '5') {
      temp.value = 5;
  } else if (value_let == '6') {
      temp.value = 6;
  } else if (value_let == '7') {
      temp.value = 7;
  } else if (value_let == '8') {
      temp.value = 8;
  } else if (value_let == '9') {
      temp.value = 9;
  } else if (value_let == '0') {
      temp.value = 10;
  } else if (value_let == 'J') {
      temp.value = 11;
  } else if (value_let == 'Q') {
      temp.value = 12;
  } else if (value_let == 'K') {
      temp.value = 13;
  } else if (value_let == 'A') {
    temp.value = 14;
  }
  if (suit_let == 's') {
      temp.suit = 0;
  } else if (suit_let == 'h') {
      temp.suit = 1;
  } else if (suit_let == 'd') {
      temp.suit = 2;
  } else if (suit_let == 'c') {
      temp.suit = 3;
  } 
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  assert ((0 <= c) && (c < 52));
  temp.value = 2 + c % 13;
  if (c/13 == 3) {
    temp.suit = 3;
  } else if (c/13 == 2) {
    temp.suit = 2;
  } else if (c/13 == 1) {
    temp.suit = 1;
  } else if (c/13 == 0) {
    temp.suit = 0;
  }
  return temp;
}
