#include "image_ppm.h"
#include <stdio.h>

int main(int argc, char *argv[]){


     char cNomImgLue[250], c2[250],cNomImgEcrite[250];
    float histo[255]={0};
    float f[255];
    OCTET *ImgIn, *ImgOut;
    int nTaille, nH, nW;
    
    sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", c2);
    sscanf(argv[3], "%s", cNomImgEcrite);

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    lire_image_pgm(cNomImgLue, ImgIn, nTaille);

    for (int i=0; i < nH; i++)
    {
        for (int j=0; j < nW; j++)
        {
            histo[ImgIn[i*nW+j]]++;
        }
    }


    for (int i=0; i < 255; i++){
        histo[i] = histo[i]/nTaille;
    }

    f[0] = histo[0];
    for (int i = 0; i < 255; i++){
        f[i] = f[i-1]+histo[i];
    }

    FILE *fichier = fopen(c2, "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        return 1;
    }

    // Écriture des données (niveau de gris, probabilité cumulée)
    for (int i = 0; i < 256; i++) {
        fprintf(fichier, "%d %f\n", i, f[i]);
    }

    fclose(fichier);
    printf("Fichier 'cumulative_distribution.dat' généré avec succès.\n");

    for (int i = 0; i< nH; i++){
        for(int j = 0; j < nW; j++){
           ImgOut[i*nW+j] = f[ImgIn[i*nW+j]] * 255;
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);




    return 0;
}