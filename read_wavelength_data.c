//
// Created by hxp on 2020-11-07.
//

#include "read_wavelength_data.h"

const double *read_wavelength_data(char *filename, int data_start_line, int data_end_line) {

    FILE *data = fopen(filename, "r");
    printf("\nReading datafile:\"%s\"\n", filename);
    const double *wavelength = (read_lines(data, data_start_line, data_end_line, 4));
    printf("Read wavelength Complete:\n");
    for (
            int i = data_start_line;
            i <=
            data_end_line;
            i++) {
        printf("%f\t", wavelength[i - data_start_line]);
    }
    printf("\n");
    fclose(data);

    return wavelength;
}
