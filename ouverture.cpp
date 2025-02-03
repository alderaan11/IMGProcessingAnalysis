#include <stdio.h>
#include "image_ppm.h"


OCTET *erosion(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW){

    for (int i = 0; i < nH; i++)
    {
        for (int j = 0; j < nW; j++)
        {   
            ImgOut[i*nW+j] = ImgIn[i*nW+j];
            if(ImgIn[i*nW+j] == 255 || ImgIn[(i-1)*nW+j] == 255 || ImgIn[(i+1)*nW+j] == 255 || ImgIn[i*nW+j+1] == 255 || ImgIn[i*nW+j-1] == 255) ImgOut[i*nW+j] = 255;
        
        }
    }

    return ImgOut;
}

OCTET *dilatation(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW){

    for (int i = 0; i < nH; i++)
    {
        for (int j = 0; j < nW; j++)
        {   
            ImgOut[i*nW+j] = ImgIn[i*nW+j];
            if(ImgIn[i*nW+j] == 0 || ImgIn[(i-1)*nW+j] == 0 || ImgIn[(i+1)*nW+j] == 0 || ImgIn[i*nW+j+1] == 0 || ImgIn[i*nW+j-1] == 0) ImgOut[i*nW+j] = 0;
        
        }
    }

    return ImgOut;
}

int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgEcr[250];
    OCTET *ImgIn, *ImgOut, *ImgOut2;
    int nH, nW, nTaille;

    
    if (argc != 3)
    {
        printf("Usage ImgIn.pgm ImgOut.pgm\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcr);

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    allocation_tableau(ImgIn, OCTET, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);
    allocation_tableau(ImgOut2, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);
    erosion(ImgIn, ImgOut, nH, nW);
    dilatation(ImgOut, ImgOut2,nH,nW);
    ecrire_image_pgm(cNomImgEcr, ImgOut2, nH, nW);
    free(ImgIn);free(ImgOut);free(ImgOut2);

    return 1;
}