//
// Created by hxp on 2020-11-07.
//

#include "self_alignment_vertex.h"

double get_vertex_angle_self_alignment(const double *angle_degree, const double *angle_minute,
                                       int offset_a, int offset_b, int data_size_per_set) {
    double angle_a = calculate_mean_of_angle(
            angle_degree, angle_minute, offset_a, data_size_per_set);
    double angle_b = calculate_mean_of_angle(
            angle_degree, angle_minute, offset_b, data_size_per_set);
    if (fabs(angle_b - angle_a) > 180)
    {
        if(angle_a > angle_b) {
            angle_b += 360;
        } else {
            angle_a += 360;
        }
    }
    printf("\n[Start one set of self alignment method data]\n");
    printf("mean of angle a: %f degrees\n", angle_a);
    printf("mean of angle b: %f degrees\n", angle_b);
    double vertex_angle = 180 - fabs(angle_a - angle_b);
    printf("vertex angle: %f\n", vertex_angle);
    printf("[End one set of self alignment method data]\n");
    return vertex_angle;
}

double self_alignment_vertex() {
    int data_start_line = 2;
    int data_end_line = 17;

    const double **degree_minute = read_angular_data("../vertex-angle-triangular-prism-self-alignment.csv",
                                                     data_start_line, data_end_line);
    int data_size_per_set = (data_end_line - data_start_line) / 4;
    double vertex_data_set_1 =
            get_vertex_angle_self_alignment(degree_minute[0], degree_minute[1], 0, 2, data_size_per_set);
    double vertex_data_set_2 =
            get_vertex_angle_self_alignment(degree_minute[0], degree_minute[1], 1, 3, data_size_per_set);
    double mean_vertex_angle_alignment = (vertex_data_set_1 + vertex_data_set_2) / 2.0;
    printf("\nmean of vertex angle (self alignment method): %f\n", mean_vertex_angle_alignment);
    return mean_vertex_angle_alignment;
}