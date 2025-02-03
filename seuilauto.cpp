#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, nR, nG, nB;
    int sumR = 0, sumG = 0, sumB = 0, seuilR, seuilG, seuilB;

    if (argc != 3) 
    {
        printf("Usage: ImageIn.ppm ImageOut.ppm \n"); 
        exit(1);
    }
   
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;
   
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
  
    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    // Étape 1 : Calcul des moyennes des canaux R, G et B pour définir le seuil automatique
    for (int i = 0; i < nTaille3; i += 3)
    {
        sumR += ImgIn[i];     // Accumuler le canal Rouge
        sumG += ImgIn[i + 1]; // Accumuler le canal Vert
        sumB += ImgIn[i + 2]; // Accumuler le canal Bleu
    }

    seuilR = sumR / nTaille;
    seuilG = sumG / nTaille;
    seuilB = sumB / nTaille;

    printf("Seuil automatique calculé : R=%d, G=%d, B=%d\n", seuilR, seuilG, seuilB);

    // Étape 2 : Appliquer le seuillage basé sur les seuils calculés
    for (int i = 0; i < nTaille3; i += 3)
    {
        nR = ImgIn[i];
        nG = ImgIn[i + 1];
        nB = ImgIn[i + 2];

        ImgOut[i] = (nR > seuilR) ? 255 : 0;  // Seuillage pour le Rouge
        ImgOut[i + 1] = (nG > seuilG) ? 255 : 0; // Seuillage pour le Vert
        ImgOut[i + 2] = (nB > seuilB) ? 255 : 0; // Seuillage pour le Bleu
    }

    // Sauvegarder l'image seuillée
    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);
    
    return 0;
}
