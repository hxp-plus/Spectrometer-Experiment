#include <stdio.h>
#include <time.h>
#include "self_alignment_vertex.h"
#include "reflection_vertex.h"
#include "minimum-deflection-angle.h"
#include "diffraction_grating.h"

int main() {
    clock_t begin = clock();

    system("cp ../template.tex ~/Desktop/分光计实验报告.tex");

    double vertex_a = self_alignment_vertex();
    printf("\n");
    double vertex_b = reflection_vertex();
    printf("\n");
    minimum_deflection_angle((vertex_a + vertex_b) / 2.0);
    printf("\n");
    diffraction_grating();
    clock_t end = clock();
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("\nAll Done! Time used: %f s\n", time_spent);

    system("bash -c 'cd ~/Desktop && xelatex 分光计实验报告.tex'");
    return 0;
}
