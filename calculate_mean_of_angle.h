//
// Created by hxp on 2020-11-07.
//

#ifndef SPECTROMETER_CALCULATE_MEAN_OF_ANGLE_H
#define SPECTROMETER_CALCULATE_MEAN_OF_ANGLE_H

#include <gsl/gsl_statistics_double.h>

double calculate_mean_of_angle(const double *angle_degree, const double *angle_minute,
                               int start_offset, int size_of_data);

#endif //SPECTROMETER_CALCULATE_MEAN_OF_ANGLE_H
