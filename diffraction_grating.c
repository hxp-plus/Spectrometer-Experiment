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
    const double **degree_minute = read_angular_data("../data/diffraction_grating.csv", 4, 19);
    const double *wavelengths = read_wavelength_data("../data/diffraction_grating.csv", 4, 19);
    int dataset = 4;
    for (int i = 0; i < dataset; i++) {
        printf("\n[Start one set of diffraction grating data]\n");
        printf("Wavelength: %f\n", wavelengths[i * 4]);
        double delta_theta_1 = calculate_delta_theta(degree_minute[0], degree_minute[1],
                                                     i * 4, i * 4 + 2);
        printf("delta theta 1: %f\n", delta_theta_1);
        double grating_constant_1 = get_grating_constant(wavelengths[i * 4], delta_theta_1);
        printf("Grating constant 1: %f\n", grating_constant_1);

        printf("Wavelength: %f\n", wavelengths[i * 4 + 1]);
        double delta_theta_2 = calculate_delta_theta(degree_minute[0], degree_minute[1],
                                                     i * 4 + 1, i * 4 + 3);
        printf("delta theta 2: %f\n", delta_theta_2);
        double grating_constant_2 = get_grating_constant(wavelengths[i * 4 + 1], delta_theta_2);
        printf("Grating constant 2: %f\n", grating_constant_2);
        double mean_of_grating_constant = (grating_constant_1 + grating_constant_2) / 2.0;
        printf("Mean of grating constant: %f\n", mean_of_grating_constant);
        printf("[End one set of diffraction grating data]\n");
    }
}