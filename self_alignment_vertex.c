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
    if (fabs(angle_b - angle_a) > 180) {
        if (angle_a > angle_b) {
            angle_b += 360;
        } else {
            angle_a += 360;
        }
    }
    printf("\n[Start one set of self alignment method data]\n");
    printf("mean of angle a: %f degrees\n", angle_a);
    char *cmd = malloc(sizeof(char) * 1024);
    sprintf(cmd,
            "sed -i '0,/{{ angle-a-avg }}/s/{{ angle-a-avg }}/$%f^\\\\circ$/' '/home/hxp/Desktop/分光计实验报告.tex'",
            angle_a);
    system(cmd);

    printf("mean of angle b: %f degrees\n", angle_b);
    sprintf(cmd,
            "sed -i '0,/{{ angle-b-avg }}/s/{{ angle-b-avg }}/$%f^\\\\circ$/' '/home/hxp/Desktop/分光计实验报告.tex'",
            angle_b);
    system(cmd);

    double vertex_angle = 180 - fabs(angle_a - angle_b);
    printf("vertex angle: %f\n", vertex_angle);
    printf("mean of angle b: %f degrees\n", angle_b);
    sprintf(cmd,
            "sed -i '0,/{{ vertex }}/s/{{ vertex }}/$%f^\\\\circ$/' '/home/hxp/Desktop/分光计实验报告.tex'",
            vertex_angle);
    system(cmd);
    printf("[End one set of self alignment method data]\n");
    return vertex_angle;
}

void write_data_to_latex(const double *degree, const double *minute, int offset, int data_size_per_set) {
    for (int i = 0; i < data_size_per_set; i++) {
        char *cmd = malloc(sizeof(char) * 1024);
        sprintf(cmd,
                "sed -i '0,/{{ angle }}/s/{{ angle }}/\\&$%d^\\\\circ %d^\\\\prime${{ angle }}/' '/home/hxp/Desktop/分光计实验报告.tex'",
                (int) degree[4 * i + offset],
                (int) minute[4 * i + offset]);
        system(cmd);
    }
    system("sed -i '0,/{{ angle }}/s/{{ angle }}//' '/home/hxp/Desktop/分光计实验报告.tex'");
}

double self_alignment_vertex() {
    int data_start_line = 2;
    int data_end_line = 21;

    const double **degree_minute = read_angular_data("../data/vertex-angle-triangular-prism-self-alignment.csv",
                                                     data_start_line, data_end_line);
    int data_size_per_set = (data_end_line - data_start_line + 1) / 4;
    write_data_to_latex(degree_minute[0], degree_minute[1], 0, data_size_per_set);
    write_data_to_latex(degree_minute[0], degree_minute[1], 2, data_size_per_set);
    write_data_to_latex(degree_minute[0], degree_minute[1], 1, data_size_per_set);
    write_data_to_latex(degree_minute[0], degree_minute[1], 3, data_size_per_set);
    double vertex_data_set_1 =
            get_vertex_angle_self_alignment(degree_minute[0], degree_minute[1], 0, 2, data_size_per_set);
    double vertex_data_set_2 =
            get_vertex_angle_self_alignment(degree_minute[0], degree_minute[1], 1, 3, data_size_per_set);
    double mean_vertex_angle_alignment = (vertex_data_set_1 + vertex_data_set_2) / 2.0;
    printf("\nmean of vertex angle (self alignment method): %f\n", mean_vertex_angle_alignment);
    char *cmd = malloc(sizeof(char) * 1024);
    sprintf(cmd,
            "sed -i '0,/{{ vertex-avg }}/s/{{ vertex-avg }}/$%f^\\\\circ$/' '/home/hxp/Desktop/分光计实验报告.tex'",
            mean_vertex_angle_alignment);
    system(cmd);
    return mean_vertex_angle_alignment;
}


