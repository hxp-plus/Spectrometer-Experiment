cmake_minimum_required(VERSION 3.17)
project(spectrometer C)

set(CMAKE_C_STANDARD 99)


add_executable(spectrometer main.c readcsv.c readcsv.h self_alignment_vertex.c self_alignment_vertex.h reflection_vertex.c reflection_vertex.h calculate_mean_of_angle.c calculate_mean_of_angle.h minimum-deflection-angle.c minimum-deflection-angle.h read_angular_data.c read_angular_data.h read_wavelength_data.c read_wavelength_data.h diffraction_grating.c diffraction_grating.h)
target_link_libraries(spectrometer gsl gslcblas m)


