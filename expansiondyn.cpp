#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"


int main(int argc, char *argv[]){

    char cNomImgLue[250], cNomImgOut[250];
    OCTET *ImgIn, *ImgOut;
    int histo[255] = {0};
    int nTaille, nH, nW;
    int xmin = 0;
    int xmax = 255;
    int x1, x2;

    if (argc != 3){
        printf("Usage: %s ImgIn.pgm ImgOut.pgm\n", argv[0]);
        exit(1);
    }


    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgOut);
    
    
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    for (int i=0; i < nH; i++)
    {
        for (int j=0; j < nW; j++)
        {
            histo[ImgIn[i*nW+j]]++;
        }
    }

    int k = 0;
    while(histo[k] == 0 && k < 256){
        k++;
    }
    x1 = k;
    printf("x1 : %d, %d\n", k, x1);

    while(histo[k]!=0 && k < 256){
        k++;
    }

    x2 = k-1;

    float alpha = 255 * x1 / (x2 - x1);
    float beta = (-255) * x2 / (x2 -x1);

    
    int histo2[255];
    for (int i = 0; i < 255; i++){
        
    }

    free(ImgIn);



    return 0;
}