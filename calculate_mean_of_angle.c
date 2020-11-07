//
// Created by hxp on 2020-11-07.
//

#include "calculate_mean_of_angle.h"

double calculate_mean_of_angle(const double *angle_degree, const double *angle_minute,
                               int start_offset, int size_of_data) {
    double result_degree = gsl_stats_mean(angle_degree + start_offset, 4, size_of_data);
    double result_minute = gsl_stats_mean(angle_minute + start_offset, 4, size_of_data);
    return result_degree + result_minute / 60.0;
}