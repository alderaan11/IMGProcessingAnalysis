#include <cstdio>
#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[])
{
    char cNomImgLue[250], gradient[250];
    int nH,nW,nTaille,v,h;
    OCTET *ImgIn, *ImgOut;

    if (argc != 3)
    {
        printf("Usage ImgIn.pgm ImgOut.pgm");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", gradient);

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    allocation_tableau(ImgIn, OCTET, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    lire_image_pgm(cNomImgLue, ImgIn, nTaille);

    for (int i = 0; i < nH; i++)
    {
        for (int j = 0; j < nW; j++){
            v = ImgIn[i*nW+j+1] - ImgIn[i*nW+j];
            h = ImgIn[(i+1)*nW+j] - ImgIn[i*nW+j];

            ImgOut[i*nW+j] = sqrt(pow(v,2) + pow(h,2));
        }
    }

    ecrire_image_pgm(gradient, ImgOut, nH, nW);
    free(ImgIn); free(ImgOut);
    return 1;
}