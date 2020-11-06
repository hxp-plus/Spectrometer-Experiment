#include <stdio.h>
#include "readcsv.h"

int main() {
    const int data_start_line=2;
    const int data_end_line=17;

    FILE* stream = fopen("../vertex-angle-triangular-prism-self-alignment.csv", "r");
    printf("Reading Data...\n");
    double* angle_degree=(read_lines(stream,data_start_line,data_end_line,2));
    printf("Read angle_degree Complete\n");
    for(int i=data_start_line; i<=data_end_line; i++) {
        printf("%f\t", angle_degree[i-data_start_line]);
    }
    printf("\n");
    fclose(stream);

    stream = fopen("../vertex-angle-triangular-prism-self-alignment.csv", "r");
    double* angle_minute=(read_lines(stream,data_start_line,data_end_line,3));
    printf("Read angle_minute Complete\n");
    for(int i=data_start_line; i<=data_end_line; i++) {
        printf("%f\t", angle_minute[i-data_start_line]);
    }
    printf("\n");
    fclose(stream);

    return 0;
}
