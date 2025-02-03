#include <alloca.h>
#include <stdio.h>
#include "image_ppm.h"


int main(int argc, char *argv[])
{
    char cNomImgLue[250], datFile[250]; 
    int histo[255] = {0};
    int nH, nW, nTaille;
    OCTET *ImgIn;

    if (argc != 3)
    {
        printf("Usage ImgIn.pgm ImgIn.dat");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", datFile);

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

    FILE *f = fopen(datFile, "wb");
    if (f == NULL)
    {
        printf("Erreur pendant l'ouverture du fichier");
        exit(1);
    }

    for (int i = 0; i < 255; i++)
    {
        fprintf(f, "%d %d\n", i, histo[i]);
    }

    fclose(f);
    free(ImgIn);

    return 1;
}