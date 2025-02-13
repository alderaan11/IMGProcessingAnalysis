#include "image_ppm.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    char cR[250], cB[250], cNomImgEcrite[250];
    float hR[256] = {0}, hB[256] = {0};  // Histogrammes
    float fR[256] = {0}, fB[256] = {0};  // Fonctions de répartition
    int T[256];  // Table de correspondance entre les niveaux de gris
    OCTET *ImgR, *ImgB, *ImgOut;
    int nTaille, nH, nW;

    if (argc < 4) {
        printf("Usage: %s <image_ref.pgm> <image_a_transformer.pgm> <image_resultat.pgm>\n", argv[0]);
        exit(1);
    }

    sscanf(argv[1], "%s", cR);
    sscanf(argv[2], "%s", cB);
    sscanf(argv[3], "%s", cNomImgEcrite);

    lire_nb_lignes_colonnes_image_pgm(cR, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgR, OCTET, nTaille);
    allocation_tableau(ImgB, OCTET, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    lire_image_pgm(cR, ImgR, nTaille);
    lire_image_pgm(cB, ImgB, nTaille);

    // Calcul des histogrammes
    for (int i = 0; i < nTaille; i++) {
        hR[ImgR[i]]++;
        hB[ImgB[i]]++;
    }

    // Normalisation pour obtenir les DDP
    for (int i = 0; i < 256; i++) {
        hR[i] /= nTaille;
        hB[i] /= nTaille;
    }

    // Calcul des fonctions de répartition cumulées (CDF)
    fR[0] = hR[0];
    fB[0] = hB[0];

    for (int i = 1; i < 256; i++) {
        fR[i] = fR[i - 1] + hR[i];
        fB[i] = fB[i - 1] + hB[i];
    }

   for (int a = 0; a < 256; a++) {
    int index_B = 0;
    
    // Trouver le niveau de gris correspondant dans fB
    while (index_B < 255 && fB[index_B] < fR[a]) {
        index_B++;
    }

    // Assurer que la transformation est bien répartie
    if (index_B == 0) {
        T[a] = 0;
    } else if (index_B == 255) {
        T[a] = 255;
    } else {
        // Interpolation linéaire entre les niveaux de gris adjacents
        float alpha = (fR[a] - fB[index_B - 1]) / (fB[index_B] - fB[index_B - 1] + 1e-6);
        T[a] = (1 - alpha) * (index_B - 1) + alpha * index_B;
    }
}



    // Transformation de l'image B en appliquant T(a)
    for (int i = 0; i < nTaille; i++) {
        ImgOut[i] = T[ImgB[i]];
    }

    // Sauvegarde de l'image spécifiée
    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);

    free(ImgR);
    free(ImgB);
    free(ImgOut);

    return 0;
}
