#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

char* string_gen() {
    static const char characters[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "!@#$%^&*(){}/\\.,><`~;:'\""
        "œ∑´®†¥¨ˆøπ“‘æ…¬˚∆˙©ƒ∂ßåΩ≈ç√∫˜µ≤≥˘¯ˇÆÚÅÍÏ˜ØÅˆ´Ï˜Ø´ÏØÅ◊∂";
    
    int length = rand() % 100;
    char *result = malloc(length);
    for (int i = 0; i < length; ++i) {
      result[i] = characters[rand() % (sizeof(characters) - 1)];
    }

    return result;
}

int glitch(FILE *fp) {
	char *random = string_gen();
	fwrite(random, sizeof(random[0]), sizeof(random)/sizeof(random[0]), fp);
	return 0;
}

int main(int argc, char **argv) {
	if (argc < 1) {
		printf("Error: No arguments given.\n");
		return -1;
	}

	// random number seed
	srand(time(NULL));
  
  // command-line arguments
	int iterations = atoi(argv[1]);
	char *filename = argv[2];

	FILE *fp;
	printf("Opening %s\n", filename);
	fp = fopen(filename, "r+");

	if (fp == NULL) {
		printf("Error: Could not open file.\n");
		return -2;
	}

	int i = 0;
	int j = 0;
	for (i = 0; i < iterations; i++) {
		int start = rand() % 2266880;
		int length = rand() % (2266880 / 6);

		printf("%d :: start = %d, length = %d\n", i, start, length);
		fseek(fp, start, SEEK_CUR);

		for (j = 0; j < length; j++) {
			glitch(fp);
		}

	}

	fclose(fp);
	return 0;
}