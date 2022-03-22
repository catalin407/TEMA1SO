#include "utilfunc.h"

int verf_file_ext(char *str, int index) 
{
	char *ext;

	ext = strrchr(str, '.');

	if (ext != NULL) {
		if (strcmp("in", ext + 1) == 0)
			return index + 1;
		else if (strcmp("out", ext + 1) == 0)
			return index + 2;
		else if (strcmp("dir", ext + 1) == 0)
			return index + 3;
		else if (strcmp("subdir", ext + 1) == 0)
			return index + 4;
		else 
			return index + 5;
	} else
		return -1;
}

int verf_param(char *str, int index) 
{
	char *flag;

	flag = strrchr(str, '-');
	if (flag != NULL) {
		if (strcmp(FLAG1, flag) == 0)
			return index;
		if (strcmp(FLAG2, flag) == 0)
			return 0;
		if (strcmp(FLAG3, flag) == 0)
			return 0;
	}

	return -1;
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

char *read_from_file(FILE **f)
{
	char *read;

	read = (char *)malloc(255 * sizeof(char));

	return fgets(read, 255, *f);
}

void add_define_hash(char *str, hashmap **hash_table, FILE **f)
{
	char *token;
	char *str_tmp;
	char *del_str;
	hashmap tmp;
	int i;
	int j;
	int code;

	code = 1;

	if (strstr(str, "#define ") == NULL && strcmp(str, "\n") != 0 && strstr(str, "#undef ") == NULL) {
		for (i = 0; i < TABLE_SIZE; i++) {
			if (hash_table[i] != NULL)
				if (strstr(str, hash_table[i]->name) != NULL) {
					str_tmp = replaceWord(str, 
						hash_table[i]->name,
						hash_table[i]->value);
					code = 0;
					str = str_tmp;

					for (i = 0; i < TABLE_SIZE; i++) {
						if (hash_table[i] != NULL) {
							if (strstr(str, hash_table[i]->name) != NULL) {
								str_tmp = replaceWord(str, 
									hash_table[i]->name,
									hash_table[i]->value);
								code = 0;
								str = str_tmp;
							}
						}
					}
					if(test_if_cond(str, hash_table) == 0 && strstr(str, "#if") == NULL && strstr(str, "#endif") == NULL && strstr(str, "#else") == NULL && strstr(str, "#elif") == NULL)
						fprintf(stdout, "%s", str);
					else if (strstr(str, "printf") != NULL && test_if_cond(str, hash_table) == 0)
						fprintf(stdout, "%s", str);
					else if (test_if_def(str, hash_table) == 0 && strstr(str, "#ifndef") == NULL && strstr(str, "#endif") == NULL)
						fprintf(stdout, "%s", str);
				}
		}

		if (code == 1) {
			if(test_if_cond(str, hash_table) == 0 && strstr(str, "#if") == NULL && strstr(str, "#endif") == NULL && strstr(str, "#else") == NULL && strstr(str, "#elif") == NULL)
				fprintf(stdout, "%s", str);
			else if (strstr(str, "printf") != NULL && test_if_cond(str, hash_table) == 0)
				fprintf(stdout, "%s", str);
		}

	} else if (strcmp(str, "\n") != 0 && strstr(str, "define") != NULL) {
		token = strtok(str, " ");
		token = strtok(NULL, " ");
		tmp.name = (char *)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(tmp.name, token);
		token = strtok(NULL, "");
		if (strstr(token, "\\")) {
			str = read_from_file(f);
			token[strlen(token) - 2] = '\0';
			strcat(token, strtok(str, "") + 8);
			token[strlen(token) - 1] = '\0';
			token[strlen(token) - 1] = ' ';

			while (strstr(str, "\\") != NULL) {
				str = read_from_file(f);
				strcat(token, strtok(str, "\\") + 8);
			}

			str = read_from_file(f);
			strcat(token, strtok(str, "\\") + 7);
		}

		tmp.value = (char *)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(tmp.value, token);
		tmp.value[strlen(tmp.value) - 1] = '\0';
		hash_table_insert(hash_table, tmp.name, tmp.value);

	} else if (strcmp(str, "\n") != 0 && strstr(str, "undef") != NULL) {
		token = strtok(str, " ");
		token = strtok(NULL, " ");
		del_str = (char *)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(del_str, token);
		del_str[strlen(del_str) - 1] = '\0';
		hash_table_delete_define(hash_table, del_str);
	}
}

int test_if_cond(char *str)
{
	char *pch;
	static int cond;

	if(strstr(str, "#endif")  && strstr(str, "printf") == NULL) {
		cond =  0;
		return cond;
	}

	if(strstr(str, "#if") && strstr(str, "printf") == NULL) {
		pch = strtok(str, " ");
		pch = strtok(NULL, " ");
		if (atoi(pch) > 0)
			cond = 0;
		if(atoi(pch) == 0)
			cond = 1;
	}

	if(strstr(str,"#else") && cond == 0  && strstr(str, "printf") == NULL)
		cond = 1;
	else if(strstr(str,"#else") && cond == 1  && strstr(str, "printf") == NULL)
		cond = 0;

	if(strstr(str, "#elif")  && strstr(str, "printf") == NULL) {
		pch = strtok(str, " ");
		pch = strtok(NULL, " ");
		if (atoi(pch) > 0)
			cond = 0;
		if(atoi(pch) == 0)
			cond = 1;
	}

	return cond;
}

int test_if_def(char *str, hashmap **hash_table)
{
	char *pch;
	static int def;

	if(strstr(str, "#ifndef") && strstr(str, "printf") == NULL) {
		pch = strtok(str, " ");
		pch = strtok(NULL, " ");
		if (hash_table_lookup(hash_table, pch) != NULL)
			def = 0;
		if(hash_table_lookup(hash_table, pch) == NULL)
			def = 1;
	}

	return def;
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

hashmap **init_hash_table(void)
{
	hashmap **hash_table_new = 
		(hashmap **)malloc(TABLE_SIZE * sizeof(hashmap *));
	int i;

	if (hash_table_new) {
		for (i = 0; i < TABLE_SIZE; i++)
			hash_table_new[i] = NULL;
		return hash_table_new;
	}

	return NULL;
}

void print_table(hashmap **hash_table)
{
	int i;

	if (hash_table) {
		for (i = 0; i < TABLE_SIZE; i++) {
			if (hash_table[i] != NULL &&
				hash_table[i]->name != NULL)
				fprintf(stdout, "\n%s\t%s\n",
				hash_table[i]->name,
				hash_table[i]->value);
		}
	}
}


void hash_table_insert(hashmap **hash_table, char *name, char *value)
{
	hashmap *tmp;
	int try_hash;

	tmp = NULL;

	tmp = hash_table_lookup(hash_table, name);

	if (tmp != NULL) {
		free(tmp->value);
		tmp->value = 
			(char *)malloc(sizeof(char) * (strlen(value) + 1));
		strcpy(tmp->value, value);
		return;
	}

	try_hash = hash(name);

	while (hash_table[try_hash] != NULL &&
		hash_table[try_hash]->name != NULL) {
			if (hash_table[try_hash]->name != NULL) {
				try_hash++;
			}
			try_hash = try_hash % TABLE_SIZE;
	}

	hash_table[try_hash] = 
		(hashmap *)malloc(sizeof(hashmap));
	hash_table[try_hash]->name = 
		(char *)malloc(sizeof(char) * (strlen(name) + 1));
	hash_table[try_hash]->value = 
		(char *)malloc(sizeof(char) * (strlen(value) + 1));

	strcpy(hash_table[try_hash]->name, name);
	strcpy(hash_table[try_hash]->value, value);
}

hashmap *hash_table_lookup(hashmap **hash_table, char *name)
{
	int try_hash;

	try_hash = hash(name);

	if (hash_table) {
		while (hash_table[try_hash] != NULL) {
			if (strcmp(hash_table[try_hash]->name, name) == 0)
				return hash_table[try_hash];

			try_hash++;
			try_hash = try_hash % TABLE_SIZE;
		}
	}

	return NULL;
}

void hash_table_delete(hashmap **hash_table, int table_size)
{
	int i;

	if (hash_table) {
		for (i = 0; i < TABLE_SIZE; i++)
			if (hash_table[i] != NULL) {
				free(hash_table[i]->name);
				free(hash_table[i]->value);
				hash_table[i]->name = NULL;
				hash_table[i]->value = NULL;
				free(hash_table[i]);
				hash_table[i] = NULL;
			}
	}
}

void *hash_table_delete_define(hashmap **hash_table, char *name)
{
	int i;

	if (hash_table) {
		for (i = 0; i < TABLE_SIZE; i++)
			if (hash_table[i] != NULL && 
				hash_table[i]->name != NULL) 
				if (strcmp(hash_table[i]->name, name) == 0) {
					free(hash_table[i]->name);
					free(hash_table[i]->value);
					hash_table[i]->name = NULL;
					hash_table[i]->value = NULL;
					free(hash_table[i]);
					hash_table[i] = NULL;
				}
	}
}

void hash_table_delete_object(hashmap *object)
{
	if (object != NULL) {
		free(object->name);
		free(object->value);
		object->name = NULL;
		object->value = NULL;
		free(object);
	}
}
