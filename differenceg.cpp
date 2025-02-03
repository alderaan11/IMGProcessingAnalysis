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

void difference(OCTET *ImgOrig, OCTET *ImgDilat, OCTET *ImgDiff, int nH, int nW) {
    for (int i = 0; i < nH * nW; i++) {
        ImgDiff[i] = abs(ImgDilat[i] - ImgOrig[i]);
    }
}

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgDilat[250], cNomImgDiff[250];
    OCTET *ImgIn, *ImgDilat, *ImgDiff;
    int nTaille, nH, nW;

    if (argc != 4) {
        printf("Usage: %s ImgIn.pgm ImgDilat.pgm ImgDiff.pgm\n", argv[0]);
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgDilat);
    sscanf(argv[3], "%s", cNomImgDiff);

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    allocation_tableau(ImgIn, OCTET, nTaille);
    allocation_tableau(ImgDilat, OCTET, nTaille);
    allocation_tableau(ImgDiff, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);

    // Appliquer la dilatation
    dilatation(ImgIn, ImgDilat, nH, nW);
    ecrire_image_pgm(cNomImgDilat, ImgDilat, nH, nW);

    // Calculer la différence entre l'image originale et l'image dilatée
    difference(ImgIn, ImgDilat, ImgDiff, nH, nW);
    ecrire_image_pgm(cNomImgDiff, ImgDiff, nH, nW);

    free(ImgIn);
    free(ImgDilat);
    free(ImgDiff);
    return 0;
}
