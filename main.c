#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

#define command_length 15
#define name_length 200

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

// data_structure get_money(int type) {
// 	data_structure data = (data_structure) malloc(sizeof(data_structure));

// }

void insert(void **arr, int *len) {
	int tipul_dedicatiei;
	char *nume_s = (char *) calloc(name_length, 1);
	char *nume_d = (char *) calloc(name_length, 1);
	scanf("%d", &tipul_dedicatiei);
	scanf("%s", nume_s);
	// data_structure bancnota_1 = get_money(tipul_dedicatiei);
	// data_structure bancnota_2 = get_money(tipul_dedicatiei);
	scanf("%s", nume_d);
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
