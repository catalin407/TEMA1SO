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
#define TABLE_SIZE 31
#define DELETED_NODE (person *)(0xFFFFFFFFFFFFFFFFUL)

typedef enum { F, T } boolean;

typedef struct {
	char *name;
	char *value;
} hashmap;

int verf_file_ext(char *str, int index);
int verf_param(char *str, int index);
char *replaceWord(const char *s, const char *oldW, const char *newW);
void add_define_hash(char *str, hashmap **hash_table, FILE **f);
char *read_from_file(FILE **f, char *read);
int test_if_cond(char *str);
int test_if_def(char *str, hashmap **hash_table);

unsigned int hash(char *name);
hashmap **init_hash_table(void);
void print_table(hashmap **hash_table);
void hash_table_insert(hashmap **hash_table, char *name, char *value);
hashmap *hash_table_lookup(hashmap **hash_table, char *name);
void hash_table_delete(hashmap **hash_table, int table_size);
void *hash_table_delete_define(hashmap **hash_table, char *name);
void hash_table_delete_object(hashmap *object);

#endif
