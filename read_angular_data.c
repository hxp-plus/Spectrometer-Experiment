//
// Created by hxp on 2020-11-07.
//

#include "read_angular_data.h"

const double **read_angular_data(char *filename, int data_start_line, int data_end_line) {

    FILE *data = fopen(filename, "r");
    printf("Reading datafile:\"%s\"\n", filename);
    const double *angle_degree = (read_lines(data, data_start_line, data_end_line, 2));
    printf("Read angle_degree Complete:\n");
    for (
            int i = data_start_line;
            i <=
            data_end_line;
            i++) {
        printf("%f\t", angle_degree[i - data_start_line]);
    }
    printf("\n");
    fclose(data);

    data = fopen(filename, "r");
    const double *angle_minute = (read_lines(data, data_start_line, data_end_line, 3));
    printf("Read angle_minute Complete:\n");
    for (
            int i = data_start_line;
            i <=
            data_end_line;
            i++) {
        printf("%f\t", angle_minute[i - data_start_line]);
    }
    printf("\n");

    const double **degree_minute = malloc(sizeof(double) * 2 * (data_end_line - data_start_line + 1));
    degree_minute[0] = angle_degree;
    degree_minute[1] = angle_minute;
    fclose(data);
    return degree_minute;
}