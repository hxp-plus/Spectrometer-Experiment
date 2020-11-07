//
// Created by hxp on 2020-11-07.
//

#include "reflection_vertex.h"


double get_vertex_angle_vertex(const double *angle_degree, const double *angle_minute,
                               int offset_a, int offset_b, int data_size_per_set) {
    double angle_a = calculate_mean_of_angle(
            angle_degree, angle_minute, offset_a, data_size_per_set);
    double angle_b = calculate_mean_of_angle(
            angle_degree, angle_minute, offset_b, data_size_per_set);
    if (fabs(angle_b - angle_a) > 180)
        angle_b += 360;
    printf("\n------- start one set of vertex method data: -------\n");
    printf("mean of angle a: %f degrees\n", angle_a);
    printf("mean of angle b: %f degrees\n", angle_b);
    double vertex_angle = 0.5 * fabs(angle_a - angle_b);
    printf("vertex angle: %f\n", vertex_angle);
    printf("--------- end one set of vertex method data --------\n");
    return vertex_angle;
}

void reflection_vertex() {
    int data_start_line = 2;
    int data_end_line = 21;
    const double **degree_minute = read_data("../vertex-angle-triangular-prism-reflection.csv",
                                             data_start_line, data_end_line);
    int data_size_per_set = (data_end_line - data_start_line) / 4;
    double vertex_data_set_1 =
            get_vertex_angle_vertex(degree_minute[0], degree_minute[1], 0, 2, data_size_per_set);
    double vertex_data_set_2 =
            get_vertex_angle_vertex(degree_minute[0], degree_minute[1], 1, 3, data_size_per_set);
    double mean_vertex_angle_alignment = (vertex_data_set_1 + vertex_data_set_2) / 2.0;
    printf("\nmean of vertex angle (reflection method): %f\n", mean_vertex_angle_alignment);


}