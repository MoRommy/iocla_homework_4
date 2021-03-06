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
	//for test development
}

unsigned int get_position_by_index(void *arr, int index) {
	if (index == 0)
		return 0;
	unsigned int i = 0, len, el_index = 0;
	char c;
	memcpy(&c, arr + i, 1);
	while (c != 0) {
		memcpy(&len, arr + i + 1, 4);
		i += len;
		memcpy(&c, arr + i, 1);
		el_index++;
		if (el_index == index)
			return i;
	}
	return i;
}

int add_last(void **arr, int *len, data_structure *data)
{	
	unsigned int i = get_position_by_index(*arr, -1);
	unsigned int data_length = data->header->len;
	*arr = realloc(*arr, i + data_length + 1);
	unsigned char zero = 0;
	memcpy(*arr + i + data_length, &zero, 1);
	unsigned char c = data->header->type;
	memcpy(*arr + i, &c, sizeof(char));
	i += sizeof(char);
	memcpy(*arr + i, &data_length, sizeof(int));
	i += sizeof(int);
	memcpy(*arr + i, data->data, data_length - HEADER_SIZE);
	*len = *len + 1;
	return 0;
}


int add_at(void **arr, int *len, data_structure *data, int index)
{
	unsigned int i = get_position_by_index(*arr, index);
	unsigned int final_pos = get_position_by_index(*arr, -1);
	unsigned int data_length = data->header->len;
	*arr = realloc(*arr, final_pos + data_length + 1);
	memmove(*arr + i + data_length, *arr + i, final_pos - i);
	int c = 0;
	memcpy(*arr + i, &c, 1);
	unsigned char c2 = data->header->type;
	memcpy(*arr + i, &c2, sizeof(char));
	i += sizeof(char);
	memcpy(*arr + i, &data_length, sizeof(int));
	i += sizeof(int);
	memcpy(*arr + i, data->data, data_length - HEADER_SIZE);
	*len = *len + 1;
	return 0;
}

int delete_at(void **arr, int *len, int index)
{
	unsigned int i = get_position_by_index(*arr, index);
	unsigned int final_pos = get_position_by_index(*arr, -1);
	unsigned int data_length;
	memcpy(&data_length, *arr + i + 1, 4);
	memmove(*arr + i, *arr + i + data_length, final_pos - (i + data_length) + 1);
	*arr = realloc(*arr, final_pos - data_length + 1);
	*len = *len - 1;
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
	return data;
}

void insert(void **arr, int *len) {
	data_structure *data = get_data();
	add_last(arr, len, data);
	free(data->header);
	free(data->data);
	free(data);
}

void insert_at(void **arr, int *len) {
	int insert_pos;
	scanf("%d", &insert_pos);
	data_structure *data = get_data();
	add_at(arr, len, data, insert_pos);
	free(data->header);
	free(data->data);
	free(data);
}

void print_by_type(int b1, int b2, int type) {
	if (type == 1)
		printf("%"PRId8"\n%"PRId8"\n\n", (int8_t)b1, (int8_t)b2);
	else if (type == 2)
		printf("%"PRId16"\n%"PRId32"\n\n", (int16_t)b1, b2);
	else
		printf("%"PRId32"\n%"PRId32"\n\n", b1, b2);
}

void print_el (void *arr) {
	char type;
	memcpy(&type, arr, 1);
	printf("Tipul %u\n", type);
	unsigned int current_elem_dimension;
	memcpy(&current_elem_dimension, arr + 1, 4);
	int len = 5;
	printf("%s", (char *)arr + len);
	char c2;
	do {
		memcpy(&c2, arr + len, 1);
		len++;
	} while (c2 != 0);
	printf(" pentru ");
	unsigned int b1, b2;
	memcpy(&b1, arr  + len, get_dim1(type));
	len += get_dim1(type);
	memcpy(&b2, arr + len, get_dim2(type));
	len += get_dim2(type);
	printf("%s\n", (char *)arr + len);
	do {
		memcpy(&c2, arr + len, 1);
		len++;
	} while (c2 != 0);
	print_by_type(b1, b2, type);
}

void print(void *arr) {
	unsigned int i = 0;
	char c;
	memcpy(&c, arr + i, 1);
	while (c != 0) { //cat timp am elemente in vector, le printez
		unsigned int current_elem_dimension;
		memcpy(&current_elem_dimension, arr + i + 1, 4);
		print_el(arr + i);
		i += current_elem_dimension;
		memcpy(&c, arr + i, 1);
	}
}

void find(void *data_block, int len, int pos) 
{
	int index = 0;
	unsigned int i = 0;
	char c;
	memcpy(&c, data_block + i, 1);
	while (c != 0 && index < pos) { //cat timp am elemente in vector, le printez
		unsigned int current_elem_dimension;
		memcpy(&current_elem_dimension, data_block + i + 1, 4);
		i += current_elem_dimension;
		memcpy(&c, data_block + i, 1);
		index++;
	}
	if (index == pos)
		print_el(data_block + i);
}

void find_caller(void *arr) {
	int pos = 0;
	scanf("%d", &pos);
	find(arr, 0, pos);
}

void delete(void **arr, int *len) {
	int index;
	scanf("%d", &index);
	delete_at(arr, len, index);
}

int switch_comm(char *command, void **arr, int *len) {
	if (!strcmp(command, "exit"))
		return 0;
	if (!strcmp(command, "insert"))
		insert(arr, len);
	if (!strcmp(command, "insert_at"))
		insert_at(arr, len);
	if (!strcmp(command, "print"))
		print(*arr);
	if (!strcmp(command, "find"))
		find_caller(*arr);
	if (!strcmp(command, "delete_at"))
		delete(arr, len);
	return 1;
}

int main() {
	void *arr = calloc(1, 1);
	int len = 0;
	char *command = (char *) malloc(COMMAND_LENGTH * sizeof(char));
	do {
		scanf("%s", command);
	} while (switch_comm(command, &arr, &len));
	free(command);
	free(arr);
	return 0;
}
