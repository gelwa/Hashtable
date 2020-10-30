#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define TABLE_SIZE 10
#define MAX_NAME 256


typedef struct person {
	char name[MAX_NAME];
	int age;
	//...add more info later
	struct person* next;
} person;


person* hash_table[TABLE_SIZE];		//Hashtable = Array of pointers (for dynamic storage)


//Hash function (keys = names)
unsigned int hash(char* name) {
	int length = strnlen(name, MAX_NAME);
	unsigned int value = 0;
	for (int i=0; i<length; i++) {
		value += name[i];						//adds ASCII value of each character
		value = (value * name[i]) % TABLE_SIZE;	//multiplies ASCII value of each character and divided by table length (to fit in table)
	}
	return value;
}

//function to set up table
bool init_hash_table() {
	for (int i=0; i<TABLE_SIZE; i++) {
		hash_table[i] = NULL;
	}
	//table is empty
}

//function that prints status of table
void print_table() {
	printf("\nStart\n");
	for (int i=0; i<TABLE_SIZE; i++) {
		if (hash_table[i] == NULL) {
			printf("\t%i\t---\n", i);
		}
		else {
			printf("\t%i\t", i);
			person* tmp = hash_table[i];
			while (tmp != NULL) {
				printf("%s - ", tmp->name);
				tmp = tmp->next;
			}
			printf("\n");
		}
	}
	printf("End\n\n");
}

//function to insert a person into table
bool hash_table_insert(person* p) {
	if (p==NULL) return false;
	int index = hash(p->name);				//hash function determines index
	p->next = hash_table[index];			//add person to front of list
	hash_table[index] = p;
	return true;
}

//find person by key (key = name)
person* lookup(char* name) {
	int index = hash(name);					//finds index
	person* tmp = hash_table[index];
	while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0) {
		tmp = tmp->next;					//continues to look in list until name found
	}
	return tmp;
}

person* delete(char* name) {
	int index = hash(name);					//finds index
	person* tmp = hash_table[index];
	person* prev = NULL;
	while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0) {
		prev = tmp;
		tmp = tmp->next;					//continues to look in list until name found
	}
	if (tmp == NULL) return NULL;			//not found
	if (prev == NULL) {
		hash_table[index] = tmp->next;
	} else {
		prev->next = tmp->next;
	}
	return tmp;

}

int main () {

	init_hash_table();
	print_table();

	person hp = {.name="Harry Potter", .age=18};
	person ned = {.name="Ned Stark", .age=50};
	person tony = {.name="Tony Stark", .age=40};
	person thomas = {.name="Thomas Shelby", .age=30};
	person khaleesi = {.name="Khaleesi", .age=20};
	person dumbledore = {.name="Dumbledore", .age=70};
	person ron = {.name="Ron Weasley", .age=18};
	person jon = {.name="Jon Snow", .age=20};
	person itachi = {.name="Itachi", .age=25};
	person naruto = {.name="Naruto", .age=20};
	person tsunade = {.name="Tsunade", .age=50};

	hash_table_insert(&hp);
	hash_table_insert(&ned);
	hash_table_insert(&tony);
	hash_table_insert(&thomas);
	hash_table_insert(&khaleesi);
	hash_table_insert(&dumbledore);
	hash_table_insert(&ron);
	hash_table_insert(&jon);
	hash_table_insert(&itachi);
	hash_table_insert(&naruto);
	hash_table_insert(&tsunade);
	print_table();


	person* tmp = lookup("Tony Stark");
	if (tmp == NULL) {
		printf("Not found!\n");
	} else {
		printf("Found %s\n", tmp->name);
	}


	tmp = lookup("Itachi");
		if (tmp == NULL) {
			printf("Not found!\n");
		} else {
			printf("Found %s\n", tmp->name);
		}


	delete("Tony Stark");
	tmp = lookup("Tony Stark");
	if (tmp == NULL) {
				printf("Not found!\n");
			} else {
				printf("Found %s\n", tmp->name);
			}
	print_table();


return 0;
}
