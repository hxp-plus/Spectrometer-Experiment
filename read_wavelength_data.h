//
// Created by hxp on 2020-11-07.
//

#ifndef SPECTROMETER_READ_WAVELENGTH_DATA_H
#define SPECTROMETER_READ_WAVELENGTH_DATA_H
#include "readcsv.h"
#include <stdio.h>
#include <stdlib.h>

const double *read_wavelength_data(char *filename, int data_start_line, int data_end_line);

#endif //SPECTROMETER_READ_WAVELENGTH_DATA_H
