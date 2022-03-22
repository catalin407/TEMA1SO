#include "utilfunc.h"

int main(int argc, char **argv)
{	
	person tmp;
	char *ext;
	char *flag;
	char *readInput;
	char *pch;
	int i;
	int outIndex;
	int inIndex;
	FILE *fIn;
	FILE *fOut;
	boolean goodExt; 
	boolean goodParam;
	boolean inputFileExt;
	boolean outputFileExt;
	boolean noCode;

	outIndex = -1;
	inIndex = -1;
	goodExt = T;
	goodParam = T;
	outputFileExt = F;
	noCode = T;
	inputFileExt = T;
	readInput = (char *)malloc(255 * sizeof(char));
	hash_table = (person **)malloc(sizeof(person *) * TABLE_SIZE);
	init_hash_table();

	if (readInput == NULL)
		return 1;

	if (argc == 1) {
		fgets(readInput, 255, stdin);
		fprintf(stdout, "%s\n", readInput);
	}

	if (argc > 1) {
		for (i = 1; i < argc; i++)
			if (verf_file_ext(argv[i]) == 1)
				return 1;

		for (i = 1; i < argc; i++)
			if (verf_param(argv[i]) == 1)
				return 1;

		if (goodExt == T && goodParam == T) {

			for (i = 0; i < argc; i++) {
				ext = strrchr(argv[i], '.');

				if (strcmp("in", ext + 1) == 0) {
					inputFileExt = T;
					inIndex = i;
				} else 
					if (strcmp("out", ext + 1) == 0) {
						outputFileExt = T;
						outIndex = i;
					}
			}

			if (inputFileExt == T && outputFileExt == F) {
				fIn = fopen(argv[inIndex], "r");
				while (fgets(readInput, 255, fIn) != NULL) {
					if (strstr(readInput, "#") == NULL &&
						noCode == T) {
						fprintf(stdout, "%s", readInput);
					} else { 
						noCode = F;
						pch = strtok(readInput, "");
					while (pch != NULL) {
						add_define_hash(pch, &tmp);
						pch = strtok(NULL, "");
					}

					}
				}

				fclose(fIn);
			} else 
				if (inputFileExt == T && outputFileExt == T) {
					fIn = fopen(argv[inIndex], "r");
					fOut = fopen(argv[outIndex], "w");
					fgets(readInput, 255, fIn);
					fprintf(fOut, "%s", readInput);
					fclose(fIn);
					fclose(fOut);
				}
		}
	}
	hash_table_delete();
	free(readInput);
	free(*hash_table);

	return 0;
}
