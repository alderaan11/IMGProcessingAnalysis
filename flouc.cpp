#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgEcr[250];
    OCTET *ImgIn, *ImgOut;
    int nH, nW, nTaille, nTaille3;

    if (argc != 3)
    {
        printf("Usage ImgIn.ppm ImgOut.ppm");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcr);

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    nTaille3 = nTaille * 3;

    allocation_tableau(ImgIn, OCTET, nTaille3);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    lire_image_ppm(cNomImgLue, ImgIn, nTaille);

    for (int i = 0; i < nTaille3 ; i += 3) {
    for (int j = 0; j < 3; j++) {
        int sum = 0;
        int count = 0;
        if (i - nW * 3 >= 0) {
            sum += ImgIn[i + j - nW * 3];
            count++;
        }
        if (i + nW * 3 < nTaille3) {
            sum += ImgIn[i + j + nW * 3];
            count++;
        }
        ImgOut[i + j] = sum / count;
    }
}
    ecrire_image_ppm(cNomImgEcr, ImgOut, nH, nW);

    return 1;
}