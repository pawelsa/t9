#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE (26)
#define INDEX(c) ((int)c - (int)'a')

char** words;
int length = 0;
int letter[16];
int scanned[16];
const int number[9] = { 0, 3, 6, 9, 12, 16, 19, 24,28 };

struct DICTIONARY
	{
		struct DICTIONARY *word[ALPHABET_SIZE];

		bool word_end; //if true - end of the word
	};

	int read() {
	
	int size=0;
	FILE *f;
	f = fopen("dictionary.txt", "r");

	for (int i = 0; getc(f) != EOF; i++) {	//count words
		fseek(f, -1, SEEK_CUR);
		if (getc(f) == '\n')
			size++;
	}
	
	words = (char**)malloc((size) * sizeof(char*));

	fseek(f, 0, SEEK_SET);

	for (int i = 0; getc(f) != EOF; i++) {	//add to structure from file
		words[i] = (char*)malloc(16 * sizeof(char*));
		fscanf(f, "%s", words[i]);
	}
	fclose(f);
	return size;
}

	struct DICTIONARY *create(void)	//creates a new node to structure
	{
		struct DICTIONARY *nNode = NULL;

		nNode = (struct DICTIONARY *)malloc(sizeof(struct DICTIONARY));

		if (nNode)
		{
			nNode->word_end = false;

			for (int i = 0; i < ALPHABET_SIZE; i++)
				nNode->word[i] = NULL;
		}

		return nNode;
	}

	void enter(struct DICTIONARY *root, char *words)	//adds words to strusture
	{
		int level;
		int length = strlen(words);
		int index;
		
		struct DICTIONARY *temp = root;

		for (level = 0; level < length; level++)
		{
			index = INDEX(words[level]);

			if (!temp->word[index])
				temp->word[index] = create();

			temp = temp->word[index];
		}

		temp->word_end = true;	// Mark last node as leaf
	}

	int check(int length) {		//checks in what range of letters it should look for words depends on information if any key was pressed

		if (scanned[length] != -1)
			return number[scanned[length]];
		else
			return 29;

	}

	int look_for(DICTIONARY *temp, int a) {
		
		if (!temp)
			return NULL;

			letter[length] = a;
			length++;

		if (temp->word_end == 1) {		// Print complete word
			for (int i = 0; letter[i] != -1; i++) {
				printf("%c", (letter[i] + 'a'));
			}
			printf(" ");
		}

		if(check(length)<28)
			for (int i = check(length); i < number[scanned[length] + 1]; i++) {
				look_for(temp->word[i], i);

				letter[length] = -1;
			}
		else
			for (int i = 0; i < ALPHABET_SIZE; i++) {
				look_for(temp->word[i], i);

				letter[length] = -1;
			}
		
		length--;
	}
	
	

	// Driver
	int main()
	{

		int size = read();

		struct DICTIONARY *root = create();
		struct DICTIONARY *temp;

		// Construct trie
		for (int i = 0; i < size; i++)
			enter(root, words[i]);
		free(words);


		temp = root;

		for (int i = 0; i < 17; letter[i] = -1, scanned[i] = -1, i++);

		printf("Enter numbers (2-9) one by one (0 ends input) : ");
		
		for(int i=0;i<16;){
			scanf("%d", &scanned[i]);
			if ((scanned[i] > 1) && (scanned[i] < 10)) {	//check if input was correct
				scanned[i] -= 2;
				i++;
			}
			else if (scanned[i] == 0) {		//if input == 0 => end of inputs
				scanned[i] = -1;
				break;
			}
			else
				printf("Wrong input!");
		}

		int j = 0;
		for (int i = check(length); i < number[scanned[length] + 1]; i++, j++)
			look_for(temp->word[number[scanned[length]] + j], (number[scanned[length]] + j));

		return 0;
	}