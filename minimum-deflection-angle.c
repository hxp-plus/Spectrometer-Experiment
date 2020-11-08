//
// Created by hxp on 2020-11-07.
//

#include "minimum-deflection-angle.h"

double get_deflection_angle(const double *angle_degree, const double *angle_minute,
                            int angle_a_index, int angle_b_index) {
    double angle_a = angle_degree[angle_a_index] + angle_minute[angle_a_index] / 60.0;
    double angle_b = angle_degree[angle_b_index] + angle_minute[angle_b_index] / 60.0;
    if (fabs(angle_a - angle_b) > 180) {
        if (angle_a < angle_b) {
            angle_a += 360;
        } else {
            angle_b += 360;
        }
    }
    return fabs(angle_a - angle_b);
}

double get_refractive_index(double vertex_angle, double deflection_angle) {
    return (sin((vertex_angle + deflection_angle) / 180 * M_PI / 2.0) / sin(vertex_angle / 180 * M_PI / 2.0));
}

void minimum_deflection_angle(double vertex_angle) {
    char *cmd = malloc(sizeof(char) * 1024);
    sprintf(cmd,
            "sed -i '0,/{{ vertex }}/"
            "s/{{ vertex }}/$%f^\\\\circ$/' "
            "'/home/hxp/Desktop/分光计实验报告.tex'",
            vertex_angle);
    system(cmd);
    const double **degree_minute = read_angular_data(
            "../data/minimum-deflection-angle.csv", 2, 17);
    const double *wavelengths = read_wavelength_data(
            "../data/minimum-deflection-angle.csv", 2, 17);
    const int dataset = 4;
    for (int i = 0; i < dataset; i++) {
        printf("\n[Start one set of minimum deflection data]\n");
        printf("Wavelength: %.1f\n", wavelengths[i * 4]);
        char *cmd = malloc(sizeof(char) * 1024);
        sprintf(cmd,
                "sed -i '0,/{{ deflection-angle-%d }}/"
                "s/{{ deflection-angle-%d }}/%.1f{{ deflection-angle-%d }}/' "
                "'/home/hxp/Desktop/分光计实验报告.tex'",
                i + 1, i + 1, wavelengths[i * 4], i + 1);
        system(cmd);
        sprintf(cmd,
                "sed -i '0,/{{ deflection-angle-%d }}/"
                "s/{{ deflection-angle-%d }}/\\&$%d^\\\\circ%d^\\\\prime$ {{ deflection-angle-%d }}/' "
                "'/home/hxp/Desktop/分光计实验报告.tex'",
                i + 1, i + 1, (int) degree_minute[0][i * 4], (int) degree_minute[1][i * 4], i + 1);
        system(cmd);
        sprintf(cmd,
                "sed -i '0,/{{ deflection-angle-%d }}/"
                "s/{{ deflection-angle-%d }}/\\&$%d^\\\\circ%d^\\\\prime$ {{ deflection-angle-%d }}/' "
                "'/home/hxp/Desktop/分光计实验报告.tex'",
                i + 1, i + 1, (int) degree_minute[0][i * 4 + 1], (int) degree_minute[1][i * 4 + 1], i + 1);
        system(cmd);
        sprintf(cmd,
                "sed -i '0,/{{ deflection-angle-%d }}/"
                "s/{{ deflection-angle-%d }}/\\&$%d^\\\\circ%d^\\\\prime$ {{ deflection-angle-%d }}/' "
                "'/home/hxp/Desktop/分光计实验报告.tex'",
                i + 1, i + 1, (int) degree_minute[0][i * 4 + 2], (int) degree_minute[1][i * 4 + 2], i + 1);
        system(cmd);
        sprintf(cmd,
                "sed -i '0,/{{ deflection-angle-%d }}/"
                "s/{{ deflection-angle-%d }}/\\&$%d^\\\\circ%d^\\\\prime$ {{ deflection-angle-%d }}/' "
                "'/home/hxp/Desktop/分光计实验报告.tex'",
                i + 1, i + 1, (int) degree_minute[0][i * 4 + 3], (int) degree_minute[1][i * 4 + 3], i + 1);
        system(cmd);
        double deflection_angle_1 = get_deflection_angle(degree_minute[0], degree_minute[1],
                                                         i * 4, i * 4 + 2);
        printf("Deflection angle 1: %f\n", deflection_angle_1);
        double deflection_angle_2 = get_deflection_angle(degree_minute[0], degree_minute[1],
                                                         i * 4 + 1, i * 4 + 3);
        printf("Deflection angle 2: %f\n", deflection_angle_2);
        double mean_of_deflection_angle = (deflection_angle_1 + deflection_angle_2) / 2.0;
        sprintf(cmd,
                "sed -i '0,/{{ deflection-angle-%d }}/"
                "s/{{ deflection-angle-%d }}/\\&$%f^\\\\circ$ {{ deflection-angle-%d }}/' "
                "'/home/hxp/Desktop/分光计实验报告.tex'",
                i + 1, i + 1, mean_of_deflection_angle, i + 1);
        system(cmd);
        printf("mean of deflection angle: %f\n", mean_of_deflection_angle);
        double mean_of_reflective_index = get_refractive_index(vertex_angle, mean_of_deflection_angle);
        printf("mean of reflective index: %f\n", mean_of_reflective_index);
        sprintf(cmd,
                "sed -i '0,/{{ deflection-angle-%d }}/"
                "s/{{ deflection-angle-%d }}/\\&$%f$/' "
                "'/home/hxp/Desktop/分光计实验报告.tex'",
                i + 1, i + 1, mean_of_reflective_index);
        system(cmd);
        printf("[End one set of minimum deflection data]\n");
    }
}