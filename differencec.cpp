#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"


void difference(OCTET *ImgOrig, OCTET *ImgDilat, OCTET *ImgDiff, int nH, int nW) {
    int nTaille = nH * nW * 3;
    for (int i = 0; i < nTaille; i++) {
        ImgDiff[i] = abs(ImgDilat[i] - ImgOrig[i]);
        printf("%d\n", ImgDiff[i]);
    }
}

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgDilat[250], cNomImgDiff[250];
    OCTET *ImgIn, *ImgDilat, *ImgDiff;
    int nTaille, nH, nW;

    if (argc != 4) {
        printf("Usage: %s ImgIn.ppm ImgDilat.ppm ImgDiff.ppm\n", argv[0]);
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgDilat);
    sscanf(argv[3], "%s", cNomImgDiff);

  
 lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgDilat, OCTET, nTaille3);
      lire_image_ppm(cNomImgDilat, ImgIn, nH * nW);

	allocation_tableau(ImgDiff, OCTET, nTaille3)
    // Calculer la différence entre l'image originale et l'image dilatée
    difference(ImgIn, ImgDilat, ImgDiff, nH, nW);
    ecrire_image_ppm(cNomImgDiff, ImgDiff, nH, nW);

    free(ImgIn);
    free(ImgDilat);
    free(ImgDiff);
    return 0;
}
