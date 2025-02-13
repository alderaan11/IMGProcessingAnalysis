#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"


int main(int argc, char *argv[]){

    char cNomImgLue[250], datFile[250];
    int nTaille, nTaille3, nH, nW;
    OCTET *ImgIn, *ImgOut;
    int nR, nG, nB;
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
    allocation_tableau(ImgOut, OCTET, nTaille3);

    for (int i=0; i < nTaille3; i += 3)
    {
        h_r[ImgIn[i]] ++;  h_g[ImgIn[i+1]] ++;  h_b[ImgIn[i+2]] ++;
    }

    int x1r, x1g, x1b = 0;
    int x2r, x2g, x2b = 0;

    int k = 0;
    while (h_r[k]==0) k++;
    x1r = k;

    for (int i = x1r; i < 255; i++){
        if(h_r[i] == 0) {
            x2r = i-1;
            break;
        }
    }
    printf("x1 : %d, x2 : %d\n", x1r, x2r);

    int u = 0;
    while (h_g[u]==0) u++;
    x1g = u;

    for (int i = x1g; i < 255; i++){
        if(h_g[i] == 0) {
            x2g = i-1;
            break;
        }
    }   
    printf("x1 : %d, x2 : %d\n", x1g, x2g);

    int w = 0;
    while (h_b[w]==0) w++;
    x1b = w;
    for (int i = x1b; i < 255; i++){
        if(h_b[i] == 0) {
            x2b = i-1;
            break;
        }
    }
    printf("x1 : %d, x2 : %d\n", x1b, x2b);

    int betar = 255 / (x2r - x1r);
    int alphar = (-255)*x1r / (x2r - x1r);
    int betag = 255 / (x2g - x1g);
    int alphag = (-255)*x1g / (x2g - x1g);
    int betab = 255 / (x2b - x1b);
    int alphab = (-255)*x1b / (x2b - x1b);

    printf("r: %d, %d\n", alphar, betar);
    printf("g: %d, %d\n", alphag, betag);
    printf("b: %d, %d\n", alphab, betab);

    for (int i=0; i < nTaille3; i+=3)   
     {
       nR = ImgIn[i];
       nG = ImgIn[i+1];
       nB = ImgIn[i+2];
       ImgOut[i]= alphar + (nR * betar);
       ImgOut[i+1]=alphag + (nG * betag);
       ImgOut[i+2]=alphab + (nB * betab);
     }
    
    ecrire_image_ppm(datFile, ImgOut, nH, nW);

   free(ImgIn);

    return 1;

}