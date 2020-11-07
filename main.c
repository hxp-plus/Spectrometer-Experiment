#include <stdio.h>
#include "self_alignment_vertex.h"
#include "reflection_vertex.h"
#include "minimum-deflection-angle.h"

int main() {
    double vertex_a = self_alignment_vertex();
    printf("\n");
    double vertex_b = reflection_vertex();
    printf("\n");
    minimum_deflection_angle((vertex_a+vertex_b)/2.0);
    printf("\n");
    return 0;
}
