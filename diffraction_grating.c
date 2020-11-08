//
// Created by hxp on 2020-11-07.
//

#include "diffraction_grating.h"

double calculate_delta_theta(const double *angle_degree, const double *angle_minute,
                             int index_of_angle_a, int index_of_angle_b) {
    double angle_a = angle_degree[index_of_angle_a] + angle_minute[index_of_angle_a] / 60.0;
    double angle_b = angle_degree[index_of_angle_b] + angle_minute[index_of_angle_b] / 60.0;
    if (fabs(angle_a - angle_b) > 180) {
        if (angle_a < angle_b) {
            angle_a += 360;
        } else {
            angle_b += 360;
        }
    }
    return fabs(angle_a - angle_b) / 2.0;
}

double get_grating_constant(double wavelength, double theta) {
    return (wavelength) / sin(theta / 180 * M_PI);
}

void diffraction_grating() {
    const double **degree_minute = read_angular_data(
            "../data/diffraction_grating.csv", 2, 19);
    const double *wavelengths = read_wavelength_data(
            "../data/diffraction_grating.csv", 2, 19);
    int dataset = 4;
    for (int i = 2; i < dataset + 2; i++) {
        printf("\n[Start one set of diffraction grating data]\n");
        printf("Wavelength: %f\n", wavelengths[(i - 2) * 4 + 2]);
        char *cmd = malloc(sizeof(char) * 1024);
        sprintf(cmd,
                "sed -i '0,/{{ grating-%d }}/"
                "s/{{ grating-%d }}/%.1f{{ grating-%d }}/' "
                "'/home/hxp/Desktop/分光计实验报告.tex'",
                i - 1, i - 1, wavelengths[(i - 2) * 4 + 2], i - 1);
        system(cmd);
        sprintf(cmd,
                "sed -i '0,/{{ grating-%d }}/"
                "s/{{ grating-%d }}/\\&$%d^\\\\circ%d^\\\\prime$ {{ grating-%d }}/' "
                "'/home/hxp/Desktop/分光计实验报告.tex'",
                i - 1, i - 1, (int) degree_minute[0][(i - 2) * 4 + 2], (int) degree_minute[1][(i - 2) * 4 + 2], i - 1);
        system(cmd);
        sprintf(cmd,
                "sed -i '0,/{{ grating-%d }}/"
                "s/{{ grating-%d }}/\\&$%d^\\\\circ%d^\\\\prime$ {{ grating-%d }}/' "
                "'/home/hxp/Desktop/分光计实验报告.tex'",
                i - 1, i - 1, (int) degree_minute[0][(i - 2) * 4 + 2 + 1], (int) degree_minute[1][(i - 2) * 4 + 2 + 1],
                i - 1);
        system(cmd);
        sprintf(cmd,
                "sed -i '0,/{{ grating-%d }}/"
                "s/{{ grating-%d }}/\\&$%d^\\\\circ%d^\\\\prime$ {{ grating-%d }}/' "
                "'/home/hxp/Desktop/分光计实验报告.tex'",
                i - 1, i - 1, (int) degree_minute[0][0], (int) degree_minute[1][0], i - 1);
        system(cmd);
        sprintf(cmd,
                "sed -i '0,/{{ grating-%d }}/"
                "s/{{ grating-%d }}/\\&$%d^\\\\circ%d^\\\\prime$ {{ grating-%d }}/' "
                "'/home/hxp/Desktop/分光计实验报告.tex'",
                i - 1, i - 1, (int) degree_minute[0][1], (int) degree_minute[1][1], i - 1);
        system(cmd);
        sprintf(cmd,
                "sed -i '0,/{{ grating-%d }}/"
                "s/{{ grating-%d }}/\\&$%d^\\\\circ%d^\\\\prime$ {{ grating-%d }}/' "
                "'/home/hxp/Desktop/分光计实验报告.tex'",
                i - 1, i - 1,
                (int) degree_minute[0][(i - 2) * 4 + 2 + 2], (int) degree_minute[1][(i - 2) * 4 + 2 + 2],
                i - 1);
        system(cmd);
        sprintf(cmd,
                "sed -i '0,/{{ grating-%d }}/"
                "s/{{ grating-%d }}/\\&$%d^\\\\circ%d^\\\\prime$ {{ grating-%d }}/' "
                "'/home/hxp/Desktop/分光计实验报告.tex'",
                i - 1, i - 1,
                (int) degree_minute[0][(i - 2) * 4 + 2 + 3], (int) degree_minute[1][(i - 2) * 4 + 2 + 3],
                i - 1);
        system(cmd);
        double delta_theta_1 = calculate_delta_theta(degree_minute[0],
                                                     degree_minute[1],
                                                     (i - 2) * 4 + 2,
                                                     (i - 2) * 4 + 2 + 2);
        printf("delta theta 1: %f\n", delta_theta_1);

        double delta_theta_2 = calculate_delta_theta(degree_minute[0],
                                                     degree_minute[1],
                                                     (i - 2) * 4 + 2 + 1,
                                                     (i - 2) * 4 + 2 + 3);
        printf("delta theta 2: %f\n", delta_theta_2);

        double mean_of_delta_theta = (delta_theta_1 + delta_theta_2) / 2.0;
        printf("Mean of delta theta: %f\n", mean_of_delta_theta);
        sprintf(cmd,
                "sed -i '0,/{{ grating-%d }}/"
                "s/{{ grating-%d }}/\\&$%f^\\\\circ$ {{ grating-%d }}/' "
                "'/home/hxp/Desktop/分光计实验报告.tex'",
                i - 1, i - 1, mean_of_delta_theta, i - 1);
        system(cmd);

        double mean_of_grating_constant = get_grating_constant(
                wavelengths[(i - 2) * 4 + 2], mean_of_delta_theta);
        printf("Mean of grating constant: %f\n", mean_of_grating_constant);
        sprintf(cmd,
                "sed -i '0,/{{ grating-%d }}/"
                "s/{{ grating-%d }}/\\&$%f$/' "
                "'/home/hxp/Desktop/分光计实验报告.tex'",
                i - 1, i - 1, mean_of_grating_constant);
        system(cmd);
        printf("[End one set of diffraction grating data]\n");
    }
}