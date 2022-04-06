#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

#define command_length 15
#define name_length 200
#define header_size 5

int add_last(void **arr, int *len, data_structure *data)
{

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
	char *nume_s = (char *) calloc(name_length, 1);
	char *nume_d = (char *) calloc(name_length, 1);
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

	// for (int k = 0; k < i; k++) {
	// 	int c;
	// 	memcpy(&c, arr + k, 1);
	// 	printf("%u ", c);
	// }
	return data;
}

void insert(void **arr, int *len) {

	data_structure *data = get_data();
	add_last(arr, len, data);

	// add_last(arr, len, &data)
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
	void *arr = NULL;
	int len = 0;

	char *command = (char *) malloc(command_length * sizeof(char));
	do {
		scanf("%s", command);
	} while (switch_comm(command, arr, &len));





	free(command);

	return 0;
}
