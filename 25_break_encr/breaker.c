#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int lower_char (char c) {
	switch(c) {
		case 'A':
			return 'a';
		case 'a':
			return 'a';
		case 'B':
			return 'b';
		case 'b':
			return 'b';
		case 'C':
			return 'c';
		case 'c':
			return 'c';
		case 'D':
			return 'd';
		case 'd':
			return 'd';
		case 'E':
			return 'e';
		case 'e':
			return 'e';
		case 'F':
			return 'f';
		case 'f':
			return 'f';
		case 'G':
			return 'g';
		case 'g':
			return 'g';
		case 'H':
			return 'h';
		case 'h':
			return 'h';
		case 'I':
			return 'i';
		case 'i':
			return 'i';
		case 'J':
			return 'j';
		case 'j':
			return 'j';
		case 'K':
			return 'k';
		case 'k':
			return 'k';
		case 'L':
			return 'l';
		case 'l':
			return 'l';
		case 'M':
			return 'm';
		case 'm':
			return 'm';
		case 'N':
			return 'n';
		case 'n':
			return 'n';
		case 'O':
			return 'o';
		case 'o':
			return 'o';
		case 'P':
			return 'p';
		case 'p':
			return 'p';	//TODO
		case 'Q':
			return 'q';
		case 'q':
			return 'q';
		case 'R':
			return 'r';
		case 'r':
			return 'r';
		case 'S':
			return 's';
		case 's':
			return 's';
		case 'T':
			return 't';
		case 't':
			return 't';
		case 'U':
			return 'u';
		case 'u':
			return 'u';
		case 'V':
			return 'v';
		case 'v':
			return 'v';
		case 'W':
			return 'w';
		case 'w':
			return 'w';
		case 'X':
			return 'x';
		case 'x':
			return 'x';
		case 'Y':
			return 'y';
		case 'y':
			return 'y';
		case 'Z':
			return 'z';
		case 'z':
			return 'z';
	}
}

int count_freq(FILE * f) {
//	if (f == NULL) {return 0;}
	int count[26] = {0};
	int c;
	c = fgetc(f);
//	if (c == EOF) {EXIT_FAILURE;}
	while (c != EOF) {
//	while ((fgetc(f)) != EOF) {
		if (isalpha(c)) {
			c = lower_char(c);
			c -='a';
			count[c]++;
		}
		c = fgetc(f);
		continue;
	}
	int max = count[0];
	int idx = 0;
	for (int i = 1; i < 26; i++) {
//		printf("count[%d] = %d\n", i, count[i]);	//TODO
		if (max < count[i]) {
			max = count[i];
			idx = i;
			printf("max = %d\n", max);
			printf("idx = %d\n", idx);
		}
	}
	printf (/*"idx = */ "%d\n", idx - 'e' + 'a');
	if (idx == 0 && count[0] == 0) {return 0;}
	return idx + 'e' - 'a';
}
	
void decrypt(FILE * f, int key) {    
  int c;    
  while ((c = fgetc(f)) != EOF) {        
    if (isalpha(c)) {            
      c = lower_char(c);            
      c -= 'a';            
      c -= key;            
      c %= 26;            
      c += 'a';                
      printf("%c", c);
    }
    continue;
  }
}

int main(int argc, char ** argv) {  
  if (argc != 2) {    
    fprintf(stderr,"Usage: breaker inputFileName\n");    
    return EXIT_FAILURE;  
  }  
  FILE * f = fopen(argv[1], "r");  
  if (f == NULL) {    
    fprintf(stderr, "Could not open file");    
    return EXIT_FAILURE;  
  }
  int key = count_freq(f);  
  decrypt(f, key);  
  if (fclose(f) != 0) {    
    perror("Failed to close the input file!");    
    return EXIT_FAILURE;  
  }  
  return EXIT_SUCCESS;
}
