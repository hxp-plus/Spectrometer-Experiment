//
// Created by hxp on 2020-11-07.
//

#include "self_alignment_vertex.h"
#include "calculate_mean_of_angle.h"

double get_vertex_angle_self_alignment(const double *angle_degree, const double *angle_minute,
                                       int offset_a, int offset_b, int data_size_per_set) {
    double angle_a = calculate_mean_of_angle(
            angle_degree, angle_minute, offset_a, data_size_per_set);
    double angle_b = calculate_mean_of_angle(
            angle_degree, angle_minute, offset_b, data_size_per_set);
    if (fabs(angle_b - angle_a) > 180)
        angle_b += 360;
    printf("\n------- start one set of self alignment method data: -------\n");
    printf("mean of angle a: %f degrees\n", angle_a);
    printf("mean of angle b: %f degrees\n", angle_b);
    double vertex_angle = 180 - fabs(angle_a - angle_b);
    printf("vertex angle: %f\n", vertex_angle);
    printf("--------- end one set of self alignment method data --------\n");
    return vertex_angle;
}

void self_alignment_vertex() {
    const int data_start_line = 2;
    const int data_end_line = 17;

    FILE *self_alignment_data = fopen("../vertex-angle-triangular-prism-self-alignment.csv", "r");
    printf("Reading self alignment Data...\n");
    const double *angle_degree = (read_lines(self_alignment_data, data_start_line, data_end_line, 2));
    printf("Read angle_degree Complete:\n");
    for (
            int i = data_start_line;
            i <=
            data_end_line;
            i++) {
        printf("%f\t", angle_degree[i - data_start_line]);
    }
    printf("\n");
    fclose(self_alignment_data);

    self_alignment_data = fopen("../vertex-angle-triangular-prism-self-alignment.csv", "r");
    const double *angle_minute = (read_lines(self_alignment_data, data_start_line, data_end_line, 3));
    printf("Read angle_minute Complete:\n");
    for (
            int i = data_start_line;
            i <=
            data_end_line;
            i++) {
        printf("%f\t", angle_minute[i - data_start_line]);
    }
    printf("\n");

    int data_size_per_set = (data_end_line - data_start_line) / 4;
    double vertex_data_set_1 =
            get_vertex_angle_self_alignment(angle_degree, angle_minute, 0, 2, data_size_per_set);
    double vertex_data_set_2 =
            get_vertex_angle_self_alignment(angle_degree, angle_minute, 1, 3, data_size_per_set);
    double mean_vertex_angle_alignment = (vertex_data_set_1 + vertex_data_set_2) / 2.0;
    printf("\nmean of vertex angle (self alignment method): %f\n", mean_vertex_angle_alignment);

    fclose(self_alignment_data);
}