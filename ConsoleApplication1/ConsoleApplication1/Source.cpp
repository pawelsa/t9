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
char K[][5] = { " ",".?!","ABC","DEF","GHI","JKL","MNO","PQRS","TUV","WXYZ" };
const int number[9] = { 0, 3, 6, 9, 12, 16, 19, 24,28 };

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

	for (int i = 0; getc(f) != EOF; i++) {
		words[i] = (char*)malloc(16 * sizeof(char*));
		fscanf(f, "%s", words[i]);
	}
	fclose(f);
	return size;
}

	// trie node
	struct DICTIONARY
	{
		struct DICTIONARY *word[ALPHABET_SIZE];

		bool word_end; //IF TRUE - END OF WORD
	};

	// Returns new trie node (initialized to NULLs)
	struct DICTIONARY *create(void)
	{
		struct DICTIONARY *pNode = NULL;

		pNode = (struct DICTIONARY *)malloc(sizeof(struct DICTIONARY));

		if (pNode)
		{
			pNode->word_end = false;

			for (int i = 0; i < ALPHABET_SIZE; i++)
				pNode->word[i] = NULL;
		}

		return pNode;
	}

	// If not present, inserts key into trie
	// If the key is prefix of trie node, just marks leaf node
	void enter(struct DICTIONARY *root, char *words)
	{
		int level;
		int length = strlen(words);
		int index;
		
		struct DICTIONARY *pCrawl = root;

		for (level = 0; level < length; level++)
		{
			index = INDEX(words[level]);
			if (!pCrawl->word[index])
				pCrawl->word[index] = create();

			pCrawl = pCrawl->word[index];
		}

		// mark last node as leaf
		pCrawl->word_end = true;
	}

	int check(int length) {

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
		
		if (temp->word_end == 1) {
			for (int i = 0; letter[i] != -1; i++) {
				printf("%c", (letter[i] + 'a'));
			}
			printf(" ");
		}

		if(check(length)<28)
			for (int i = check(length); i < check(length + 1); i++) {
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

		for (int i = 0; i < 17; i++) {
			letter[i] = -1;
			scanned[i] = -1;
		}

		scanned[0] = 0;

		for (int i = 0; i < 3; i++)
			look_for(temp->word[number[scanned[length]]], 3);

		/*
		int length = 0;
		int letter[16];
		int scanned[16];
		char K[][5] = { " ",".?!","ABC","DEF","GHI","JKL","MNO","PQRS","TUV","WXYZ" };
		const int number[9] = { 0, 3, 6, 9, 12, 16, 19, 24,28 };
		*/

		return 0;
	}