#include "utilfunc.h"

int main(int argc, char **argv)
{
	hashmap *tmp1;
	hashmap **hash_map;
	char *readInput;
	char *pch;
	char *pch1;
	int i;
	FILE *fIn;
	FILE *fOut;
	boolean inputFileExt;
	boolean outputFileExt;

	outputFileExt = F;
	inputFileExt = T;
	readInput = (char *)malloc(256 * sizeof(char));
	hash_map = init_hash_table();
	tmp1 = NULL;
	tmp1 = (hashmap *)malloc(sizeof(hashmap));
	fOut = NULL;
	fIn = NULL;

	if (readInput == NULL)
		exit(12);

	if (hash_map == NULL)
		exit(12);

	if(tmp1 == NULL)
		exit(12);

	if (argc == 1) {
		fgets(readInput, 255, stdin);
		fprintf(stdout, "%s\n", readInput);
	}

	if (argc > 1) {
		for (i = 1; i < argc; i++) {
			if (verf_file_ext(argv[i], i) == i + 1) {
				fIn = fopen(argv[i], "r");

				if (fIn == NULL)
					exit(12);

				inputFileExt = T;
			} else if (verf_file_ext(argv[i], i) == i + 2) {
				fOut = fopen(argv[i], "w+");

				if (fOut == NULL)
					exit(12);

				outputFileExt = T;
			} else if (verf_file_ext(argv[i], i) == i + 5)
				exit(12);
		}

		for (i = 1; i < argc; i++)
			if (verf_param(argv[i], i) == i) {
				pch1 = strtok(argv[i+1], "=");
				tmp1->name = NULL;
				tmp1->name =
					(char *)malloc((strlen(pch1) + 1) *
					sizeof(char));

				if (tmp1->name == NULL)
					exit(12);

				strcpy(tmp1->name, pch1);
				pch1 = strtok(NULL, "=");
				tmp1->value = NULL;
				tmp1->value =
					(char *)malloc((strlen(pch1) + 1) *
					sizeof(char));

				if (tmp1->value == NULL)
					exit(12);

				strcpy(tmp1->value, pch1);
				hash_table_insert(hash_map,
					tmp1->name,
					tmp1->value);
			}

			if (inputFileExt == T && outputFileExt == F) {
				while (fgets(readInput, 255, fIn) != NULL) {
					pch = strtok(readInput, "");
					while (pch != NULL) {;
					add_define_hash(pch, hash_map, &fIn);
					pch = strtok(NULL, "");
					}
				}
			} else if (inputFileExt == T && outputFileExt == T) {
				fgets(readInput, 255, fIn);
				fprintf(fOut, "%s", readInput);
			}
	}
	/*print_table(hash_map);*/
	hash_table_delete(hash_map, TABLE_SIZE);
	free(hash_map);
	free(readInput);
	free(tmp1);

	return 0;
}