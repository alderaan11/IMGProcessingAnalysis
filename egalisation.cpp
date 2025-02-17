#include "image_ppm.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

    char cNomImgLue[250], c2[250], cNomImgEcrite[250];
    float histo[256] = {0};  // Correction : 256 au lieu de 255
    float f[256] = {0};  // Correction : 256 au lieu de 255
    OCTET *ImgIn, *ImgOut;
    int nTaille, nH, nW;

    // Vérification du nombre d'arguments
    if (argc < 4) {
        printf("Usage: %s <image_in.pgm> <fichier_cdf.txt> <image_out.pgm>\n", argv[0]);
        return 1;
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", c2);
    sscanf(argv[3], "%s", cNomImgEcrite);

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    lire_image_pgm(cNomImgLue, ImgIn, nTaille);

    // Calcul de l'histogramme
    for (int i = 0; i < nTaille; i++) {
        histo[ImgIn[i]]++; 
    }

    // Normalisation pour obtenir la DDP
    for (int i = 0; i < 256; i++) {
        histo[i] /= nTaille;
    }

    // Calcul de la fonction de répartition cumulée (CDF)
    f[0] = histo[0];
    for (int i = 1; i < 256; i++) {  // Correction : Commencer à 1
        f[i] = f[i - 1] + histo[i];
    }

    // Écriture de la CDF dans un fichier
    FILE *fichier = fopen(c2, "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", c2);
        return 1;
    }

    for (int i = 0; i < 256; i++) {
        fprintf(fichier, "%d %f\n", i, f[i]);
    }

    fclose(fichier);
    printf("Fichier '%s' généré avec succès.\n", c2);

    // Application de l'égalisation d'histogramme
    for (int i = 0; i < nTaille; i++) {
        ImgOut[i] = f[ImgIn[i]] * 255;  // Correction : Bien alloué avec 256 cases
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);

    free(ImgIn);
    free(ImgOut);

    return 0;
}
