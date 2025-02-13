#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"


int main(int argc, char *argv[]){

    char cNomImgLue[250], c2[250];
    int nTaille, nTaille3, nH, nW;
    OCTET *ImgIn, *ImgOut;
    int nR, nG, nB;

    if (argc != 3)
    {
        printf("Usage ImgIn.ppm ImgIn.dat");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", c2);


    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);

    nTaille = nH*nW;
    nTaille3 = nTaille*3;

    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille3);


    int x1r = 10;
    int x2r = 55;
    int x1g = 5;
    int x2g = 40;
    int x1b = 5;
    int x2b = 35;

    for (int i = 0; i <nTaille3; i+=3){
        nR = ImgIn[i];
       nG = ImgIn[i+1];
       nB = ImgIn[i+2];
       if (nR < x1r) nR = x1r;
       if (nR > x2r) nR = x2r;
       if (nG < x1g) nG = x1g;
       if (nG > x2g) nG = x2g;
       if (nB <x1b) nB = x1b;
       if (nB > x2b) nB = x2b;
        ImgOut[i]= nR;
       ImgOut[i+1]=nG;
       ImgOut[i+2]=nB;
    }

    ecrire_image_ppm(c2, ImgOut, nH, nW);

   free(ImgIn);

    return 1;

}