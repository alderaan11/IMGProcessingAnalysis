#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"

void erosion(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
    int channels = 3;
    for (int i = 1; i < nH - 1; i++) {
        for (int j = 1; j < nW - 1; j++) {
            for (int c = 0; c < channels; c++) {
                int idx = (i * nW + j) * channels + c;
                int min_val = ImgIn[idx];
                
                // Vérification des pixels voisins sans seuillage
                if (ImgIn[idx - nW * channels] < min_val) min_val = ImgIn[idx - nW * channels];
                if (ImgIn[idx + nW * channels] < min_val) min_val = ImgIn[idx + nW * channels];
                if (ImgIn[idx - channels] < min_val) min_val = ImgIn[idx - channels];
                if (ImgIn[idx + channels] < min_val) min_val = ImgIn[idx + channels];
                
                ImgOut[idx] = min_val;
            }
        }
    }
}

void dilatation(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
    int channels = 3;
    for (int i = 1; i < nH - 1; i++) {
        for (int j = 1; j < nW - 1; j++) {
            for (int c = 0; c < channels; c++) {
                int idx = (i * nW + j) * channels + c;
                int max_val = ImgIn[idx];
                
                // Vérification des pixels voisins sans seuillage
                if (ImgIn[idx - nW * channels] > max_val) max_val = ImgIn[idx - nW * channels];
                if (ImgIn[idx + nW * channels] > max_val) max_val = ImgIn[idx + nW * channels];
                if (ImgIn[idx - channels] > max_val) max_val = ImgIn[idx - channels];
                if (ImgIn[idx + channels] > max_val) max_val = ImgIn[idx + channels];
                
                ImgOut[idx] = max_val;
            }
        }
    }
}

void fermeture(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
    OCTET *ImgTemp;
    int nTaille = nH * nW * 3;
    allocation_tableau(ImgTemp, OCTET, nTaille);
    
    dilatation(ImgIn, ImgTemp, nH, nW);
    erosion(ImgTemp, ImgOut, nH, nW);
    
    free(ImgTemp);
}

int main(int argc, char *argv[]) {
    char cNomImgLue[250], cNomImgOut[250];
    OCTET *ImgIn, *ImgOut;
    int nTaille, nH, nW;

    if (argc != 3) {
        printf("Usage: %s ImgIn.ppm ImgOut.ppm\n", argv[0]);
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgOut);

   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);
	
    // Appliquer la fermeture (dilatation suivie d'érosion)
    fermeture(ImgIn, ImgOut, nH, nW);
    ecrire_image_ppm(cNomImgOut, ImgOut, nH, nW);

    free(ImgIn);
    free(ImgOut);
    return 0;
}
