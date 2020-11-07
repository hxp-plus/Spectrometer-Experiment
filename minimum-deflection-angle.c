//
// Created by hxp on 2020-11-07.
//

#include "minimum-deflection-angle.h"

double get_deflection_angle(const double * angle_degree, const double * angle_minute,
                            int angle_a_index, int angle_b_index) {
    double angle_a = angle_degree[angle_a_index] + angle_minute[angle_a_index]/60.0;
    double angle_b = angle_degree[angle_b_index] + angle_minute[angle_b_index]/60.0;
    if (fabs(angle_a - angle_b)>180) {
        if(angle_a < angle_b) {
            angle_a += 360;
        } else {
            angle_b += 360;
        }
    }
    return fabs(angle_a - angle_b);
}

double get_refractive_index(double vertex_angle,double deflection_angle) {
    return (sin((vertex_angle+deflection_angle)/180*M_PI/2.0)/sin(vertex_angle/180*M_PI/2.0));
}

void minimum_deflection_angle(double vertex_angle) {
    const double  ** degree_minute = read_angular_data("../minimum-deflection-angle.csv", 2, 17);
    const double * wavelengths = read_wavelength_data("../minimum-deflection-angle.csv", 2, 17);
    const int dataset=4;
    for(int i=0; i<dataset ;i++) {
        printf("\n[Start one set of minimum deflection data]\n");
        printf("Wavelength: %f\n", wavelengths[i*4]);
        double deflection_angle_1 = get_deflection_angle(degree_minute[0], degree_minute[1],
                                                       i*4,i*4+2);
        printf("Deflection angle 1: %f\n", deflection_angle_1);
        double reflective_index_1 = get_refractive_index(vertex_angle, deflection_angle_1);
        printf("Reflective index 1: %f\n", reflective_index_1);
        double deflection_angle_2 = get_deflection_angle(degree_minute[0], degree_minute[1],
                                                         i*4+1,i*4+3);
        printf("Deflection angle 2: %f\n", deflection_angle_2);
        double reflective_index_2 = get_refractive_index(vertex_angle, deflection_angle_2);
        printf("Reflective index 2: %f\n", reflective_index_2);
        double mean_of_deflection_angle = (deflection_angle_1 + deflection_angle_2)/2.0;
        printf("mean of deflection angle: %f\n", mean_of_deflection_angle);
        double mean_of_reflective_index = (reflective_index_1 + reflective_index_2)/2.0;
        printf("mean of reflective index: %f\n", mean_of_reflective_index);
        printf("[End one set of minimum deflection data]\n");
    }
}