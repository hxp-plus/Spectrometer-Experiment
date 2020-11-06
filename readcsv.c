//
// Created by hxp on 2020-11-07.
// Read a csv file and extract data from given lines and a given column.

#include "readcsv.h"

const char *get_field(char *line, int num) {
    const char* tok;
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")) {
        if (!--num)
            return tok;
    }
    return NULL;
}

double *read_lines(FILE* file_stream, int line_start, int line_end, int column) {
    char line[1024];
    double *result = malloc(sizeof(double)*(line_end-line_start+1));
    int current_line = 0;
    while (fgets(line, 1024, file_stream)) {
        if(current_line < line_start -1) {
            current_line++;
            continue;
        }
        if(current_line > line_end -1) {
            break;
        }
        char* tmp = strdup(line);
        result[current_line+1-line_start] = strtod(get_field(tmp,column),NULL);
        current_line++;
    }
    return result;
}