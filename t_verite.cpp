// test_couleur.cpp : Seuille une image couleur 

#include <fstream>
#include <stdio.h>
#include "image_ppm.h"


void table_verite(OCTET *ImgIn, OCTET *ImgSeu, int *tab, int nH, int nW){
    for (int i = 0; i < nH; i++){
        for (int j = 0; j < nW; j++){
            if(ImgIn[i*nW+j] == 0 && ImgSeu[i*nW+j]== 0) tab[3]++;
            if(ImgIn[i*nW+j] == 255 && ImgSeu[i*nW+j]== 0) tab[2]++;
            if(ImgIn[i*nW+j] == 0 && ImgSeu[i*nW+j]== 255) tab[1]++;
            if(ImgIn[i*nW+j] == 255 && ImgSeu[i*nW+j]== 255) tab[0]++;
    
        }
    }
        printf("Tableau : ");

    for(int i =0; i < 4; i++){
        printf("%d", tab[i]);
    }
    printf("\n");
}



int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgRef[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgRef);


   OCTET *ImgIn, *ImgSeu, *ImgRef;
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgRef, OCTET, nTaille);
    lire_image_pgm(cNomImgRef, ImgRef, nTaille);

 std::ofstream fichierROC("out/tp4/ex6/roc2.dat");
  std::ofstream fichierF1("out/tp4/ex6/f1.dat");

    if (!fichierROC.is_open()) {
        printf("Erreur lors de la création du fichier roc_curve.dat\n");
        exit(1);
    }
    
    for(int k=0; k < 256; k++){
        printf("\n\n%d",k);
        allocation_tableau(ImgSeu, OCTET, nTaille);


        int t_verite[4] = {0, 0, 0, 0};

        for (int i=0; i < nH; i++){
            for (int j=0; j < nW; j++)
                {
                if ( ImgIn[i*nW+j] < k) ImgSeu[i*nW+j]=0; 
                else ImgSeu[i*nW+j]=255;
                }
        }   
        char nomFichier[100];
        sprintf(nomFichier, "out/tp4/ex6/table/%d.pgm", k);
        ecrire_image_pgm(nomFichier, ImgSeu, nH, nW);
        table_verite(ImgRef, ImgSeu, t_verite, nH, nW);

        printf("True Positive : %d\t", t_verite[0]);
        printf("False Positive : %d\t", t_verite[1]);
        printf("False Negative : %d\t", t_verite[2]);
        printf("True Negative : %d \t", t_verite[3]);
        
        double sens = (double)t_verite[0]/(t_verite[0]+t_verite[2]);
        double spec = (double)t_verite[3]/(t_verite[3]+t_verite[1]);
        double prec = (double)t_verite[0]/(t_verite[0]+t_verite[1]);
                double fpr = 1.0 - spec;

        double f1 = 2 * (prec * sens) / (prec + sens);
        printf("Sensibilité : %lf\t", sens);
        printf("Spécificité : %lf\t", spec);
        printf("Précision : %lf\t", prec);
        printf("F1-Score : %lf\n", f1);
//        printf("fpr : %lf\n", fpr);

        fichierROC << fpr << " " << sens << "\n";
        fichierF1 << k << " " << f1 << "\n";

        ecrire_image_pgm(nomFichier, ImgSeu, nH, nW);

        
    }
    fichierF1.close();
    fichierROC.close();
    printf("Fichier roc_curve.dat généré avec succès !\n");
   free(ImgIn); free(ImgSeu);
   return 1;
}
