#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

#define command_length 15
#define name_length 200
#define header_size 5

int add_last(void **arr, int *len, data_structure *data)
{	
	printf("addl_last called\n");
	unsigned int i = sizeof(*arr);
	printf("sizeof arr: %u\n", i);
	unsigned int element_len = data->header->len;
	printf("element_len: %u\n", element_len);
	*arr = realloc(*arr, i + element_len);
	unsigned char c = data->header->type;
	memcpy(*arr + i, &c, sizeof(char));
	i += sizeof(char);
	memcpy(*arr + i, &element_len, sizeof(int));
	i += sizeof(int);
	memcpy(*arr + i, data->data, element_len - header_size);
	*len = *len + 1;
	printf("done add_last\n");
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

void printArr(void *arr, int len) {
	printf("Arr addr: %p\n", arr);
	for (int k = 0; k < len; k++) {
			char c;
			memcpy(&c, arr + k, 1);
			printf("%d ", c);
		}
	printf("\n");
}

data_structure *get_data() {
	int type, b1, b2;
	char *nume_s = (char *) malloc(name_length);
	char *nume_d = (char *) malloc(name_length);
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
	h->len = header_size + data_size;

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
	printf("arr len:%d\n", *len);
	printArr(*arr, 60);
}

void insert_at() {
	
}

void print() {
	
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
		print();
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
	void *arr = malloc(0);
	printf("main %lu\n", sizeof(*arr));
	printf("init arr addr: %p\n", arr);
	int len = 0;

	char *command = (char *) malloc(command_length * sizeof(char));
	do {
		scanf("%s", command);
	} while (switch_comm(command, arr, &len));





	free(command);

	return 0;
}
