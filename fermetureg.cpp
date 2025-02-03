#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"

void erosion(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
    for (int i = 1; i < nH - 1; i++) {
        for (int j = 1; j < nW - 1; j++) {
            int idx = i * nW + j;
            int min_val = ImgIn[idx];
            if (ImgIn[idx - nW] < min_val) min_val = ImgIn[idx - nW];
            if (ImgIn[idx + nW] < min_val) min_val = ImgIn[idx + nW];
            if (ImgIn[idx - 1] < min_val) min_val = ImgIn[idx - 1];
            if (ImgIn[idx + 1] < min_val) min_val = ImgIn[idx + 1];
            ImgOut[idx] = min_val;
        }
    }
}

void dilatation(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
    for (int i = 1; i < nH - 1; i++) {
        for (int j = 1; j < nW - 1; j++) {
            int idx = i * nW + j;
            int max_val = ImgIn[idx];
            if (ImgIn[idx - nW] > max_val) max_val = ImgIn[idx - nW];
            if (ImgIn[idx + nW] > max_val) max_val = ImgIn[idx + nW];
            if (ImgIn[idx - 1] > max_val) max_val = ImgIn[idx - 1];
            if (ImgIn[idx + 1] > max_val) max_val = ImgIn[idx + 1];
            ImgOut[idx] = max_val;
        }
    }
}

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgEcr[250];
    OCTET *ImgIn, *ImgTemp, *ImgOut;
    int nTaille, nH, nW;

    if (argc != 3) {
        printf("Usage: %s ImgIn.pgm ImgOut.pgm\n", argv[0]);
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcr);

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    allocation_tableau(ImgIn, OCTET, nTaille);
    allocation_tableau(ImgTemp, OCTET, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);
    dilatation(ImgIn, ImgTemp, nH, nW);
    erosion(ImgTemp, ImgOut, nH, nW);


    ecrire_image_pgm(cNomImgEcr, ImgOut, nH, nW);

    free(ImgIn);
    free(ImgTemp);
    free(ImgOut);
    return 0;
}
