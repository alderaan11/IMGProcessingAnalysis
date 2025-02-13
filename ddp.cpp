#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[])
{

    char cNomImgLue[250], ddp[250];
    float histo[256]={0};
    OCTET *ImgIn;
    int nTaille, nH, nW;
    
    sscanf(argv[1], "%s", cNomImgLue);
  
    sscanf(argv[2], "%s", ddp);

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);

    lire_image_pgm(cNomImgLue, ImgIn, nTaille);

    for (int i=0; i < nH; i++)
    {
        for (int j=0; j < nW; j++)
        {
            histo[ImgIn[i*nW+j]]++;
        }
    }



    FILE *f = fopen(ddp, "wb");
    if (f == NULL)
    {
        printf("Erreur pendant l'ouverture du fichier");
        exit(1);
    }

    int sum = 0;
    for (int i = 0; i < 256; i++)
    {   
        //histo[i] = histo[i]/nTaille;
        histo[i] = histo[i]/nTaille;
        printf("%d, %f\n",i, histo[i]);
        fprintf(f, "%d %f\n", i, histo[i]);
    }

    fclose(f);
    free(ImgIn);
    

    return 1;
}