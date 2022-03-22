#include "utilfunc.h"

int verf_file_ext(char *str) 
{
	char *ext;

	ext = strrchr(str, '.');
	if (ext != NULL) {
		if (strcmp("in", ext + 1) == 0 || 
			strcmp("out", ext + 1) == 0 ||
			strcmp("dir", ext + 1) == 0 ||
			strcmp("subdir", ext + 1) == 0)
			return 0;
		else
			return 1;
	}
}

int verf_param(char *str) 
{
	char *flag;

	flag = strrchr(str, '-');
	if (flag != NULL) {
		if (strcmp(FLAG1, flag) == 0 ||
			strcmp(FLAG2, flag) == 0 ||
			strcmp(FLAG3, flag) == 0)
			return 0;
		else {
			return 1;
		}
	}

}

char *replaceWord(const char *s, const char *oldW,
	const char *newW)
{
	char *result;
	int i, cnt = 0;
	int newWlen = strlen(newW);
	int oldWlen = strlen(oldW);

	/* Counting the number of times old word */
	/* occur in the string */
	for (i = 0; s[i] != '\0'; i++) {
		if (strstr(&s[i], oldW) == &s[i]) {
			cnt++;

			/* Jumping to index after the old word.*/
			i += oldWlen - 1;
		}
	}

	/* Making new string of enough length */
	result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1);

	i = 0;
	while (*s) {
		/* compare the substring with the result */
		if (strstr(s, oldW) == s) {
			strcpy(&result[i], newW);
			i += newWlen;
			s += oldWlen;
		} else
			result[i++] = *s++;
	}

	result[i] = '\0';
	return result;
}

int add_define_hash(char *str, person *tmp)
{
	char *token;
	char *str_tmp;
	int i;

	if (strstr(str, "define") == NULL && strcmp(str, "\n") != 0) {
		for (i = 0; i < TABLE_SIZE; i++) {
			if (hash_table[i] != NULL)
				if (strstr(str, hash_table[i]->name) != NULL) {
					str_tmp = replaceWord(str, 
							hash_table[i]->name,
							hash_table[i]->value);
					fprintf(stdout, "%s", str_tmp);
				} else 
					fprintf(stdout, "%s", str);
		}

		return 1;
	} else if (strcmp(str, "\n") != 0) {
		token = strtok(str, " ");
		token = strtok(NULL, " ");
		strcpy(tmp->name, token);
		token = strtok(NULL, " ");
		strcpy(tmp->value, token);
		tmp->value[strlen(tmp->value) - 1] = '\0';
		hash_table_insert(tmp);
	}
}

unsigned int hash(char *name)
{
	int i;
	int lenght = strnlen(name, MAX_NAME);
	unsigned int hash_value = 0;

	for (i = 0; i < lenght; i++) {
		hash_value += name[i];
		hash_value = (hash_value * name[i]) % TABLE_SIZE;
	}
	return hash_value;
}

void init_hash_table(void)
{
	int i;

	for (i = 0; i < TABLE_SIZE; i++)
		hash_table[i] = NULL;

}

void print_table(void)
{
	int i;

	printf("Start\n");
	for (i = 0; i < TABLE_SIZE; i++)
		if (hash_table[i] == NULL) 
			printf("\t%i\t---\n", i);
		else if (hash_table[i] == DELETED_NODE) 
			printf("\t%i\t---<deleted>\n", i);
			else 
				printf("\t%i\t%s\t%s\n", i, 
					hash_table[i]->name, 
					hash_table[i]->value);

		printf("End\n");
}

int hash_table_insert(person *p)
{
	int index;
	int i;
	int try_index;

	if (p == NULL) 
		return 1;

	index = hash(p->name);

	for (i = 0; i < TABLE_SIZE; i++) {
		try_index = (i + index) % TABLE_SIZE;
		if (hash_table[try_index] == NULL ||
			hash_table[try_index] == DELETED_NODE) {
			hash_table[try_index] = p;
			return 0;
		}
	}

	return 1;
}

person *hash_table_lookup(char *name)
{
	int index;
	int i;
	int try_index;

	index = hash(name);

	for (i = 0; i < TABLE_SIZE; i++) {
		try_index = (index + i) % TABLE_SIZE;
		if (hash_table[try_index] == NULL)
			return NULL;
		if (hash_table[try_index] == DELETED_NODE) 
			continue;
		if (strncmp(hash_table[try_index]->name, 
			name, TABLE_SIZE) == 0)
			return hash_table[try_index];
	}

	return NULL;
}

person *hash_table_delete(void)
{
	int i;
	person *tmp;

	for (i = 0; i < TABLE_SIZE; i++) {
		tmp = hash_table[i];
		hash_table[i] = NULL;
		return tmp;
	}

	return NULL;
}
