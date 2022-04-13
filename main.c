#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "structs.h"

#define COMMAND_LENGTH 15
#define NAME_LENGTH 200
#define HEADER_SIZE 5

void printArr(void *arr, int len) {
	printf("Arr addr: %p\n", arr);
	for (int k = 0; k < len; k++) {
			char c;
			memcpy(&c, arr + k, 1);
			printf("%d ", c);
		}
	printf("\n");
}

unsigned int get_starting_position(void *arr) {
	unsigned int i = 0, len;
	char c;
	//printArr(arr, 40);
	//printf("starting memcpy from %p\n", arr);
	memcpy(&c, arr + i, 1);
	//printf("end memcpy with c: %u\n", c);
	while (c != 0) {
		//printf("i am in while c: %u\n", c);
		memcpy(&len, arr + i + 1, 4);
		i += len;
		memcpy(&c, arr + i, 1);
	}
	//printf("end get_starting_position\n");
	return i;
}

int add_last(void **arr, int *len, data_structure *data)
{	
	//printf("add_last called\n");
	//printArr(*arr, 40);
	unsigned int i = get_starting_position(*arr);
	//printf("starting pos: %u\n", i);

	unsigned int element_len = data->header->len;
	//printf("element_len: %u\n", element_len);
	*arr = realloc(*arr, i + element_len + 1);
	void *p = *arr;
	unsigned char zero = 0;
	memcpy(p + i + element_len, &zero, 1);
	//p[i + element_len] = 0;

	unsigned char c = data->header->type;
	memcpy(p + i, &c, sizeof(char));
	i += sizeof(char);
	memcpy(p + i, &element_len, sizeof(int));
	i += sizeof(int);
	memcpy(p + i, data->data, element_len - HEADER_SIZE);
	*len = *len + 1;
	//printArr(p, 60);
	//printf("done add_last\n");
	return 0;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{

	return 0;
}

void find(void *data_block, int len, int index) 
{

}

int delete_at(void **arr, int *len, int index)
{

	return 0;
}

int get_dim1(int type) {
	if (type == 1)
		return 1;
	if (type == 2)
		return 2;
	return 4;
}

int get_dim2(int type) {
	if (type == 1)
		return 1;
	return 4;
}

data_structure *get_data() {
	int type, b1, b2;
	char *nume_s = (char *) malloc(NAME_LENGTH);
	char *nume_d = (char *) malloc(NAME_LENGTH);
	scanf("%d", &type);
	scanf("%s", nume_s);
	scanf("%d", &b1);
	scanf("%d", &b2);
	scanf("%s", nume_d);
	int data_size = strlen(nume_s) + get_dim1(type) +
				   strlen(nume_d) + get_dim2(type) + 2; //2 * \0
	data_structure *data = (data_structure *) malloc(sizeof(data_structure));
	head *h = (head *) malloc(sizeof(head));
	h->type = type;
	h->len = HEADER_SIZE + data_size;

	void *arr = (void *)malloc(data_size);
	int i = strlen(nume_s) + 1;
	memcpy(arr, nume_s, i);
	memcpy(arr + i, &b1, get_dim1(type));
	i += get_dim1(type);
	memcpy(arr + i, &b2, get_dim2(type));
	i += get_dim2(type);
	memcpy(arr + i, nume_d, strlen(nume_d) + 1);
	i += strlen(nume_d) + 1;
	
	data->header = h;
	data->data = arr;

	free(nume_s);
	free(nume_d);
	//printf("done get_data!\n");
	return data;
}

void insert(void **arr, int *len) {
	data_structure *data = get_data();
	add_last(arr, len, data);
	free(data->header);
	free(data->data);
	free(data);
	//printf("arr len:%d\n", *len);
	//printArr(*arr, 60);
}

void insert_at() {
	
}

void print_by_type(int b1, int b2, int type) {
	if (type == 1)
		printf("%"PRId8"\n%"PRId8"\n\n", (int8_t)b1, (int8_t)b2);
	else if (type == 2)
		printf("%"PRId16"\n%"PRId32"\n\n", (int16_t)b1, b2);
	else
		printf("%"PRId32"\n%"PRId32"\n\n", b1, b2);
}

void print(void *arr) {
	unsigned int i = 0;
	char c, c2;
	memcpy(&c, arr + i, 1);
	while (c != 0) { //cat timp am elemente in vector, le printez
		char type;
		memcpy(&type, arr + i, 1);
		printf("Tipul %u\n", type);
		unsigned int current_elem_dimension;
		memcpy(&current_elem_dimension, arr + i + 1, 4);
		int len = 5;
		printf("%s", (char *)arr + i + len);
		do {
			memcpy(&c2, arr + i + len, 1);
			//printf("%c", c2);
			len++;
		} while (c2 != 0);
		printf(" pentru ");
		unsigned int b1, b2;
		memcpy(&b1, arr + i + len, get_dim1(type));
		len += get_dim1(type);
		memcpy(&b2, arr + i + len, get_dim2(type));
		len += get_dim2(type);
		printf("%s\n", (char *)arr + i + len);
		do {
			memcpy(&c2, arr + i + len, 1);
			//printf("%c", c2);
			len++;
		} while (c2 != 0);
		print_by_type(b1, b2, type);

		i += current_elem_dimension;
		memcpy(&c, arr + i, 1);
	}
}

void find_caller() {
	
}

void delete() {
	
}

int switch_comm(char *command, void **arr, int *len) {
	if (!strcmp(command, "exit"))
		return 0;
	if (!strcmp(command, "insert"))
		insert(arr, len);
	if (!strcmp(command, "insert_at"))
		insert_at();
	if (!strcmp(command, "print"))
		print(*arr);
	if (!strcmp(command, "find"))
		find_caller();
	if (!strcmp(command, "delete_at"))
		delete();
	return 1;
}

int main() {
	// the vector of bytes u have to work with
	// good luck :)
	// start
	void *arr = calloc(1, 0);
	//printf("init arr addr: %p\n", arr);
	//printf("address arr: %p\n", &arr);
	int len = 0;

	char *command = (char *) malloc(COMMAND_LENGTH * sizeof(char));
	do {
		scanf("%s", command);
	} while (switch_comm(command, &arr, &len));





	free(command);
	free(arr);
	return 0;
}
