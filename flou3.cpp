#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include "image_ppm.h"


int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgDil[250], cNomImgEcr[250];
    OCTET *ImgIn, *ImgDil, *ImgOut;
    int nH, nW, nTaille3, nTaille;

    if (argc != 4)
    {
        printf("Usage ImgIn.ppm ImgDil.pgm ImgOut.ppm");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgDil);
    sscanf(argv[3], "%s", cNomImgEcr);

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    nTaille3 = nTaille * 3;

    printf("%d %d %d %d\n", nH, nW, nTaille, nTaille3);

    allocation_tableau(ImgIn, OCTET, nTaille3);
    allocation_tableau(ImgOut, OCTET, nTaille3);
    allocation_tableau(ImgDil, OCTET, nTaille);

    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

    lire_image_pgm(cNomImgDil, ImgDil, nH * nW);

    printf("%d\n",nTaille3);

    for (int i = 0; i < nTaille3 ; i += 3) {
        int k = i /3;
        if(ImgDil[k] == 255){
             for (int j = 0; j < 3; j++) {
                int sum = 0;
                int count = 0;
                if (i - 3 >= 0) { 
                    sum += ImgIn[i + j - 3];
                    count++;
                }
                if (i + 3 < nTaille3) { 
                    sum += ImgIn[i + j + 3];
                    count++;
                }
                if (i - nW * 3 >= 0) {
                    sum += ImgIn[i + j -nW* 3];
                    count++;
                }
                if (i + nW * 3 < nTaille3) {
                    sum += ImgIn[i + j+nW * 3];
                    count++;
                }
                if (i - nW * 3 - 3 >= 0) {
                    sum += ImgIn[i + j -nW * 3 - 3];
                    count++;
                }
                if (i - nW * 3 + 3 >= 0) { 
                    sum += ImgIn[i + j - nW * 3+3];
                    count++;
                }
                if (i + nW * 3 - 3 < nTaille3) { 
                    sum += ImgIn[i + j +nW * 3 - 3];
                    count++;
                }
                if (i + nW * 3 + 3 < nTaille3) { 
                    sum += ImgIn[i + j + nW *3 + 3];
                    count++;
                }
                ImgOut[i + j] = sum/count;
            }
        }else{
            ImgOut[i] = ImgIn[i];
            ImgOut[i+1] = ImgIn[i+1];
            ImgOut[i+2] = ImgIn[i+2];
        }
}
    ecrire_image_ppm(cNomImgEcr, ImgOut, nH, nW);
    free(ImgIn); free(ImgOut);

    return 1;
}