// test_couleur.cpp : Seuille une image couleur 

#include <fstream>
#include <stdio.h>
#include "image_ppm.h"


void table_verite(OCTET *ImgIn, OCTET *ImgSeu, int *tab, int nH, int nW){
    int compteur = 0;
    for (int i = 0; i < nH; i++){
        for (int j = 0; j < nW; j++){
            if(ImgIn[i*nW+j] == 0 && ImgSeu[i*nW+j]== 0) tab[3]++;
            if(ImgIn[i*nW+j] == 255 && ImgSeu[i*nW+j]== 0) tab[2]++;
            if(ImgIn[i*nW+j] == 0 && ImgSeu[i*nW+j]== 255) tab[1]++;
            if(ImgIn[i*nW+j] == 255 && ImgSeu[i*nW+j]== 255) tab[0]++;
    
        }
    }
    
}



int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgSeuil[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgSeuil);


   OCTET *ImgIn, *ImgSeu;
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgSeu, OCTET, nTaille);
   lire_image_pgm(cNomImgSeuil, ImgSeu, nH * nW);


   int t_verite[4] = {0, 0, 0, 0};

   table_verite(ImgIn, ImgSeu, t_verite, nH, nW);
    int n;
    sscanf(cNomImgSeuil, "out/tp4/ex6/table/skifg_%d.pgm", &n);

//    printf("True Positive : %d\n", t_verite[0]);
//    printf("False Positive : %d\n", t_verite[1]);
//    printf("False Negative : %d\n", t_verite[2]);
//    printf("True Negative : %d \n", t_verite[3]);
   double sens = (double)t_verite[0]/(t_verite[0]+t_verite[2]);
   double spec = (double)t_verite[3]/(t_verite[3]+t_verite[1]);
   double prec = (double)t_verite[0]/(t_verite[0]+t_verite[1]);
   double tpr = (t_verite[0] + t_verite[2]) > 0 ? (double)t_verite[0] / (t_verite[0] + t_verite[2]) : 0.0;
    double fpr = (t_verite[1] + t_verite[3]) > 0 ? (double)t_verite[1] / (t_verite[1] + t_verite[3]) : 0.0;

   double f1 = 2 * (prec * sens) / (prec + sens);
//    printf("Sensibilité : %lf\n", sens);
//    printf("Spécificité : %lf\n", spec);
//    printf("Précision : %lf\n", prec);
//    printf("fpr : %lf\n", fpr);
   
printf("%d %f %f\n",n,fpr,sens);
    //printf("%d %f\n",n,f1);
   free(ImgIn); free(ImgSeu);
   return 1;
}
