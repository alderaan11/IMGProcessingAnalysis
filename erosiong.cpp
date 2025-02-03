#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"


int main(int argc, char *argv[]){

    char cNomImgLue[250], cNomImgEcr[250];
    OCTET *ImgIn, *ImgOut;

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
    allocation_tableau(ImgOut, OCTET, nTaille);
    lire_image_pgm(cNomImgLue,ImgIn, nTaille);


    for (int i = 1; i < nH-1; i++){
        for(int j = 1; j < nH - 1; j++){
             int idx = i * nW + j;
            ImgOut[idx] = ImgIn[idx];
            
            int min_val = ImgIn[idx];
            if (ImgIn[idx - nW] < min_val) min_val = ImgIn[idx - nW];
            if (ImgIn[idx + nW] < min_val) min_val = ImgIn[idx + nW];
            if (ImgIn[idx - 1] < min_val) min_val = ImgIn[idx - 1];
            if (ImgIn[idx + 1] < min_val) min_val = ImgIn[idx + 1];
            
            ImgOut[idx] = min_val;
        }
        }
        ecrire_image_pgm(cNomImgEcr, ImgOut, nH, nW);

    free(ImgIn);
    free(ImgOut);
    return 0;
        return 0;

    }















