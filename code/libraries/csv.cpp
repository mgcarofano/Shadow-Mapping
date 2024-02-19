/*

	csv.cpp
	di Mario Gabriele Carofano

*/

/*	************************************************************************* */
//	LIBRERIE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*	************************************************************************* */
//	CODICI DI ERRORE

#define EMPTY_ARG_ERROR 1
#define INPUT_ARG_ERROR 2
#define FILE_OPENING_ERROR 3
#define OVERFLOW_ERROR 4

/*	************************************************************************* */
//	COSTANTI E VARIABILI GLOBALI

#define CSV_FIELDS_SEPARATOR 44
#define CSV_ROWS_SEPARATOR 10
#define CSV_FIELDS_PRECISION 10

/*	************************************************************************* */
//  FUNZIONI ACCESSORIE

double argToDouble(char *arg) {
	
	char *p;
	double out_double = 0.0;

	errno = 0;

	if (strlen(arg) == 0) {
		printf("Errore nella lettura dell'input! (EMPTY_ARG_ERROR)\n\n");
		printf("Esecuzione terminata.\n");
		exit(EMPTY_ARG_ERROR);
	}

	out_double = strtod(arg, &p);

	if (*p != '\0' || errno != 0) {
		printf("Errore nella lettura dell'input! (INPUT_ARG_ERROR)\n\n");
		printf("Esecuzione terminata.\n");
		exit(INPUT_ARG_ERROR);
	}
	
	return out_double;
}

void getDimensionsFromCSV(const char* path, int* rows_csv, int* cols_csv) {

	FILE* csv_file;
	char c = 0;
	int size = 0;

    *rows_csv = 0;
    *cols_csv = 0;

	if ((csv_file = fopen(path, "r")) == NULL) {
		printf("Errore durante l'esecuzione!\n");
		printf("Applicazione terminata.\n");
		exit(FILE_OPENING_ERROR);
	}

	fseek(csv_file, 0, SEEK_END);
    size = ftell(csv_file);
	if (size == 0) {
		*rows_csv = 0;
		*cols_csv = 0;
        return;
	}

	fseek(csv_file, 0, SEEK_SET);

	do {
		c = fgetc(csv_file);
		if (c == CSV_FIELDS_SEPARATOR) {
			*cols_csv += 1;
		}
        if (c == CSV_ROWS_SEPARATOR) {
            *cols_csv = 0;
			*rows_csv += 1;
        }
	} while (c != EOF);

	*cols_csv += 1;
	*rows_csv += 1;

}

/*	************************************************************************* */
//	CLASSI

class FileCSV {
    private:

        const char* path;
        int rows;
        int fields;
    
    public:

        FileCSV() {
            path = NULL;
            rows = 0;
            fields = 0;
        }

        FileCSV(const char* p) {
            path = p;
            getDimensionsFromCSV(path, &rows, &fields);
            printf("path: %s, rows: %d, fields: %d\n", path, rows, fields);
        }

        const char* getPath() {
            return path;
        }

        int getRows() {
            return rows;
        }

        int getFields() {
            return fields;
        }

        double** getMatrix() {
            FILE *file;
            char c, char_val[CSV_FIELDS_PRECISION] = {};
            int rows_csv = 0, cols_csv = 0;

            int i = -1;
            int row_count = 0, comma_count = 0;

            if ((file = fopen(path, "r")) == NULL) {
                printf("Errore durante l'esecuzione!\n");
                printf("Applicazione terminata.\n");
                exit(FILE_OPENING_ERROR);
            }

            double** ret = (double**) calloc(rows, sizeof(double*));
            for (i = 0; i < rows; i++) {
                ret[i] = (double*) calloc(fields, sizeof(double));
                for (int j = 0; j < fields; j++) {
                    ret[i][j] = 0.0;
                    // printf("ret[%d][%d]: %f\n", i, j, ret[i][j]);
                }
                // printf("\n");
            }

            i = -1;

            do {
                ++i;
                c = fgetc(file);

                // printf("%c", c);
                if (c != 44) {
                    if (i < CSV_FIELDS_PRECISION) {
                        char_val[i] = c;
                    }
                }
                
                if (c == 44 || c == 10 || c == EOF) {
                    char_val[i] = '\0';
                    ret[row_count][comma_count] = argToDouble(char_val);
                    comma_count += 1;

                    if (c == EOF) {
                        break;
                    }
                    
                    if (c == 10 || comma_count == fields) {
                        comma_count = 0;
                        row_count++;
                        if (row_count == rows) {
                            break;
                        }
                    }

                    for (i = 0; i < CSV_FIELDS_PRECISION; i++) {
                        char_val[i] = '0';
                    }
                    char_val[i] ='\0';

                    i = -1;
                }
            } while (1);

            // for (int i = 0; i < rows; i++) {
            //     for (int j = 0; j < fields; j++) {
            //         // printf("rows: %d, fields: %d\n", i, j);
            //         printf("point[%d][%d]: %f\n", i, j, ret[i][j]);
            //     }
            // }

            return ret;
        }
};

/*	************************************************************************* */
/*	RIFERIMENTI
	
*/
