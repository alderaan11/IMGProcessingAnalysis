// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
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


int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB, S;
  
  if (argc != 4) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm Seuil \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&S);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);
	
   erosion(ImgIn, ImgOut, nH, nW);

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
