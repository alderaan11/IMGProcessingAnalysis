#include <cstdio>
#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[])
{

    char cNomImgLue[250], cNomImgEcr[250];
    OCTET *ImgIn, *ImgOut;
    int nH, nW, nTaille;

    if (argc != 3)
    {
        printf("Usage ImgIn.pgm ImgOut.pgm\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcr);

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);

    nTaille = nH*nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    lire_image_pgm(cNomImgLue, ImgIn, nTaille);

    for(int i = 0; i< nH; i++)
    {
        for (int j = 0; j < nW; j++)
        {
            if (i == 0 || i==nH-1 ||j==0 || j==nW-1 ){ 
                ImgOut[i*nW+j] = ImgIn[i*nW+j];
                }else{
            ImgOut[i*nW+j] = ImgIn[i*nW+j];
            if (ImgIn[i*nW+j] == 0 || ImgIn[(i-1)*nW+j] == 0 || ImgIn[(i+1)*nW+j] == 0 || ImgIn[i*nW+j+1] == 0 || ImgIn[i*nW+j-1] == 0) ImgOut[i*nW+j] = 0;
        }}
    }

    ecrire_image_pgm(cNomImgEcr, ImgOut, nH, nW);
    free(ImgIn);free(ImgOut);

    return 1;
}