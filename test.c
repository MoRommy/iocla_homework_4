#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	
	void *arr = malloc(100);
	printf("sizeof arr: %d\n", sizeof(*arr));
	arr = realloc(arr, sizeof(arr) + 5);
	printf("sizeof arr: %d\n", sizeof(*arr));


	char *s = (char *)malloc(50);
	scanf("%s", s);
	//printf("%s size: %d length: %ld\n", s, sizeof(s), strlen(s));

	strcpy(arr, s);
	unsigned int ds = 257;
	memcpy(arr + strlen(s) + 1, &ds, 4);
	unsigned char dd;
	memcpy(&dd, arr + strlen(s) + 1, 4);
	printf("%s %u\n", arr, dd);

	for (int i = 0; i <= 15; i++) {
		int c;
		memcpy(&c, arr + i, 1);
		printf("%u ", c);
	}


	free(s);
	free(arr);
	return 0;
}


/*


8     ->   00001000
54    ->   00110110
250   ->   11111010
5     ->   00000101


100283912 -> 00000101 11111010 00110110 00001000



232   ->   11101000
253   ->   11111101

65000 ->   11111101 11101000





103   -> 01100111
214   -> 11010110 
18    -> 00010010
0     -> 00000000

1234535 ->   00000000 00010010 11010110 01100111


8 	  -> 00001000
54    -> 00011100

5     -> 00000101

insert 3 Andrei 100283912 12312312 Teo
insert Andrei2 100 100 Teo2
*/