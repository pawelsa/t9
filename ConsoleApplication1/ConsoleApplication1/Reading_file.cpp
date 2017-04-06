#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define PRNT(a) printf("\t%d\n",a)



int main() {

	FILE *f;
	f = fopen("dictionary.txt", "r");

	int size = 0;

	for (int i = 0; getc(f) != EOF; i++) {	//count words
		fseek(f, -1, SEEK_CUR);
		if (getc(f) == '\n')
			size++;
	}

	char** words;
	words = (char**)malloc((size) * sizeof(char*));

	fseek(f, 0, SEEK_SET);

	for (int i = 0; getc(f) != EOF; i++) {
		words[i]= (char*)malloc(16 * sizeof(char*));
		fscanf(f, "%s", words[i]);
	}
	
	/*for (int i = 0; i<size; i++)
		printf("%s\n", words[i]);
		*/
	fclose(f);

	return 0;
}