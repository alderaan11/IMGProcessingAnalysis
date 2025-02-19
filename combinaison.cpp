#include <cstring>
#include <stdio.h>
#include "image_ppm.h"

void dilatation(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW){
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
}

void erosion(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW){
    for (int i = 0; i < nH; i++)
    {
        for (int j = 0; j < nW; j++)
        {   
            if (i == 0 || i==nH-1 ||j==0 || j==nW-1 ){ 
                ImgOut[i*nW+j] = ImgIn[i*nW+j];
                }
            else{
                ImgOut[i*nW+j] = ImgIn[i*nW+j];
                if(ImgIn[i*nW+j] == 255 || ImgIn[(i-1)*nW+j] == 255 || ImgIn[(i+1)*nW+j] == 255 || ImgIn[i*nW+j+1] == 255 || ImgIn[i*nW+j-1] == 255) ImgOut[i*nW+j] = 255;
            }
        }
    }
}
int main(int argc, char *argv[])
{

    char cNomImgLue[250], cNomImgEcr[250], combinaison[250];
    OCTET *ImgIn,*ImgOut;
    int nTaille, nH, nW;

    if (argc != 4)
    {
        printf("Usage ImgIn.pgm ImgOut.pgm Combinaison\n");
        exit(1);

    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcr);
    sscanf(argv[3], "%s", combinaison);

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    allocation_tableau(ImgIn,OCTET,nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);

    while(strlen(combinaison) > 0){
        int len = strlen(combinaison);
        char dernier = combinaison[len - 1];
        combinaison[len - 1 ]= '\0';

        if (dernier == 'e') {printf("erosion\n");erosion(ImgIn, ImgOut, nH, nW);}
        else {printf("dilatation\n");dilatation(ImgIn, ImgOut, nH, nW);}
memcpy(ImgIn, ImgOut, nTaille * sizeof(OCTET));
    }

    
    ecrire_image_pgm(cNomImgEcr, ImgOut, nH, nW);
    free(ImgIn); free(ImgOut);
    return 1;
}