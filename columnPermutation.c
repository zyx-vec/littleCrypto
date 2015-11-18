#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW 1024

char key[128];
int times[26];
int pos[26];
int permutation[128];
int col;
int row_num = 0;
int count = 0;
int col_length_count[128];
int order[128];

FILE* plaintext;
FILE* ciphertext;
FILE* result;

void get_permutation() {
	int len = strlen(key);
	col = len;
	int i;
	// count characters frequency in key.
	for (i = 0; i < len; i++) {
		times[ key[i]-'a' ] ++;
	}
	
	int cur = 0;
	for (i = 0; i < 26; i++) {
		if ( times[i] ) {
			cur += times[i];
			pos[i] = cur;
		}
	}

	for (i = 0; i < len; i++) {
		if (times[ key[i]-'a' ]) {
			permutation[i] = pos[ key[i]-'a' ] - (times[ key[i]-'a' ]-1);
			times[ key[i]-'a' ]--;
		}
	}
	printf("columns permutation is:\n");
	for (i = 0; i < len; i++) {
		printf("%d ", permutation[i]);
	}
	printf("\n");
}



void encrypt() {
	int i;
	// create strings to store each column's data.
	char* cols[col];
	for (i = 0; i < col; i++) {
		cols[i] = (char*)malloc(sizeof(char) * MAX_ROW);
	}
	// open file.
	plaintext = fopen("plain.txt", "r");
	ciphertext = fopen("cipher.txt", "w");
	if (plaintext == NULL || ciphertext == NULL) {
		printf("Can't open file!!!\n");
		return;
	}

	// read data from plain.txt, and store it in created strings.
	int col_num, index;
	char c;
	c = fgetc(plaintext);
	while ( !feof(plaintext) ) {
		col_num = count % col;
		index = col_length_count[col_num];
		//printf("col_num = %d index = %d data = %c\n", col_num, index, c);
		cols[col_num][index] = c;
		col_length_count[col_num]++;
		count++;
		c = fgetc(plaintext);
	}
	for (i = 0; i < col; i++) {
		index = col_length_count[i];
		cols[i][index] = '\0';
	}
	
	// fill 'q' at shorter column
	row_num = strlen(cols[0]);
	for (i = 1; i < col; i++) {
		if (strlen(cols[i]) < row_num) {
			cols[i][row_num-1] = 'X';
			cols[i][row_num] = '\0';
		}
	}

	// accorrding column order write data to file: cipher.txt
	for (i = 0; i < col; i++) {
		fputs(cols[permutation[i]-1], ciphertext);
	}
	fclose(plaintext);
	fclose(ciphertext);
}

void decrypt() {
	count = 0;
	int i;
	// create strings to store each column's data.
	char* cols[col];
	for (i = 0; i < col; i++) {
		cols[i] = (char*)malloc(sizeof(char) * MAX_ROW);
	}
	// open file.
	ciphertext = fopen("cipher.txt", "r");
	result = fopen("result.txt", "w");
	if (result == NULL || ciphertext == NULL) {
		printf("Can't open file!!!\n");
		return;
	}

	int size;
	i = 0;
	while (size = fread(cols[i], 1, row_num, ciphertext)) {
		cols[i][row_num] = '\0';
		//printf("%d: %s\n", i, cols[i]);
		i++;
	}

	for (i = 0; i < col; i++) {
		order[permutation[i]-1] = i;
	}

	// 
	int row_num = strlen(cols[0]);
	int j;
	for (i = 0; i < row_num; i++) {
		for (j = 0; j < col; j++) {
			if (cols[order[j]][i] != 'X')
				fputc(cols[order[j]][i], result);
		}
	}

	fclose(ciphertext);
	fclose(result);
}

int main () {
	printf("Input key (lower case):\n");
	gets(key);

	get_permutation();
	encrypt();
	decrypt();
	return 0;
}
