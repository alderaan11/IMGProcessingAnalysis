#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"


int main(int argc, char *argv[]){

    char cNomImgLue[250], c2[250], datFile[250];
    int nTaille, nTaille3, nH, nW;
    OCTET *ImgIn, *Img2, *ImgOut;
    int nR, nG, nB;
    int h_r[255]={0}, h_g[255]={0}, h_b[255]={0};

    if (argc != 4)
    {
        printf("Usage ImgIn.ppm ImgIn.dat");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", c2);
    sscanf(argv[3], "%s", datFile);

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);

    nTaille = nH*nW;
    nTaille3 = nTaille*3;

    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille3);
    allocation_tableau(Img2, OCTET, nTaille3);

    for (int i=0; i < nTaille3; i += 3)
    {
        h_r[ImgIn[i]] ++;  h_g[ImgIn[i+1]] ++;  h_b[ImgIn[i+2]] ++;
    }

    int x1r = 90;
    int x2r = 220;
    int x1g = 55;
    int x2g = 170;
    int x1b = 50;
    int x2b = 150;

    for (int i = 0; i <nTaille3; i++){
        nR = ImgIn[i];
       nG = ImgIn[i+1];
       nB = ImgIn[i+2];
       if (nR <= x1r) nR = x1r;
       if (nR >= x2r) nR = x2r;
       if (nG <= x1g) nG = x1g;
       if (nG >= x2g) nG = x2g;
       if (nB <= x1b) nB = x1b;
       if (nB >= x2b) nB = x2b;
        Img2[i]= nR;
       Img2[i+1]=nG;
       Img2[i+2]=nB;
    }

    ecrire_image_ppm(c2, Img2, nH, nW);

    
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
        
       nR = Img2[i];
       nG = Img2[i+1];
       nB = Img2[i+2];
       if (nR <= x1r) nR = x1r;
       if (nR >= x2r) nR = x2r;
       if (nG <= x1g) nG = x1g;
       if (nG >= x2g) nG = x2g;
       if (nB <= x1b) nB = x1b;
       if (nB >= x2b) nB = x2b;
       ImgOut[i]= alphar + (nR * betar);
       ImgOut[i+1]=alphag + (nG * betag);
       ImgOut[i+2]=alphab + (nB * betab);
     }
    
    ecrire_image_ppm(datFile, ImgOut, nH, nW);

   free(ImgIn);

    return 1;

}