//
// Created by hxp on 2020-11-07.
//

#ifndef SPECTROMETER_READCSV_H
#define SPECTROMETER_READCSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *get_field(char *line, int num);

double *read_lines(FILE *file_stream, int line_start, int line_end, int column);

#endif //SPECTROMETER_READCSV_H
