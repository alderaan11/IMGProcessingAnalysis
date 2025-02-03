#include <cstdio>
#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[])
{
    char cNomImgLue[250], datFile[250];
    int nTaille, nTaille3, nH, nW;
    OCTET *ImgIn;
    int h_r[255]={0}, h_g[255]={0}, h_b[255]={0};

    if (argc != 3)
    {
        printf("Usage ImgIn.ppm ImgIn.dat");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", datFile);

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);

    nTaille = nH*nW;
    nTaille3 = nTaille*3;

    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nTaille);
//en multipliant par trois on met tout sur une même ligne

    for (int i=0; i < nTaille3; i += 3)
    {
        h_r[ImgIn[i]] ++;  h_g[ImgIn[i+1]] ++;  h_b[ImgIn[i+2]] ++;
    }

    FILE *f = fopen(datFile, "wb");
    if (f == NULL)
    {
        printf("Erreur pendant l'ouverture du fichier\n");
        exit(1);
    }

    for (int i = 0; i < 255; i++){
        fprintf(f, "%i %d %d %d\n", i, h_r[i], h_g[i], h_b[i]);
    }

    fclose(f); free(ImgIn);

    return 1;

}