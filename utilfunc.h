#ifndef UTILFUNC_H
#define UTILFUNC_H   1
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#define FLAG1 "-D"
#define FLAG2 "-I"
#define FLAG3 "-o"
#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person *)(0xFFFFFFFFFFFFFFFFUL)

typedef enum { F, T } boolean;

typedef struct {
	char name[MAX_NAME];
	char value[MAX_NAME];
} person;

person **hash_table;

int verf_file_ext(char *str);
int verf_param(char *str);
char *replaceWord(const char *s, const char *oldW, const char *newW);
int add_define_hash(char *str, person *tmp);
unsigned int hash(char *name);
void init_hash_table(void);
void print_table(void);
int hash_table_insert(person *p);
person *hash_table_lookup(char *name);
person *hash_table_delete(void);

#endif
