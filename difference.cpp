#include <cstdio>
#include <stdio.h>
#include "image_ppm.h"


int main(int argc, char *argv[])
{
    char cNomImgSeu[250],  cNomImgDil[250], cNomImgEcr[250];
    OCTET *ImgIn, *ImgIn2, *ImgOut;
    int nH, nW, nTaille;
    
    if (argc != 4)
    {
        printf("Usage ImgSeu.pbm ImgDil.pbm ImgOut.pbm\n");
        exit(1);
    }


    sscanf(argv[1], "%s", cNomImgSeu);
    sscanf(argv[2], "%s", cNomImgDil);
    sscanf(argv[3], "%s", cNomImgEcr);

    lire_nb_lignes_colonnes_image_pgm(cNomImgSeu, &nH, &nW);
    nTaille = nH  * nW;
    

    allocation_tableau(ImgIn, OCTET, nTaille);
    allocation_tableau(ImgIn2, OCTET, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    lire_image_pgm(cNomImgSeu, ImgIn, nTaille);
    lire_image_pgm(cNomImgDil, ImgIn2, nTaille);

    for (int i = 0; i < nH; i++)
    {
        for (int j = 0; j < nW; j++)
        {
            if (ImgIn[i*nW+j] == ImgIn2[i*nW+j]) ImgOut[i*nW+j] = 255;
            else ImgOut[i*nW+j] = 0;
        }
    }

    ecrire_image_pgm(cNomImgEcr, ImgOut, nH, nW);
    free(ImgIn); free(ImgIn2); free(ImgOut);
    
    return 1;
}