#include <cstdio>
#include <stdio.h>
#include "image_ppm.h"


int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgEcr[250];
    OCTET *ImgIn, *ImgOut;
    int nH, nW, nTaille, nTaille3;


    if (argc != 3)
    {
        printf("Usage ImgIn.ppm ImgOut.pgm");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcr);

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    nTaille3 = nTaille * 3;

    allocation_tableau(ImgIn, OCTET, nTaille3);
    allocation_tableau(ImgOut, OCTET, nTaille);

    lire_image_ppm(cNomImgLue, ImgIn, nTaille);
    int j = 0;
    for (int i = 0; i < nTaille3; i+=3)
    {
        ImgOut[j] = ImgIn[i]*0.299 + 0.587*ImgIn[i+1]+ 0.114*ImgIn[i+2];
        j++;
    }

    ecrire_image_pgm(cNomImgEcr, ImgOut, nH, nW);
    free(ImgIn); free(ImgOut);

    return 1;
}

//https://twitter.com/Stations_Ski
//https://www.quebecvacances.com/images/photos/photos_320_240/bromont_montagne_dexperiences___station_de_ski_1_h.jpg