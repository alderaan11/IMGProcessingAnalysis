#include <cstdlib>
#include <stdio.h>
#include "image_ppm.h"
#include <stdlib.h>

int main (int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgOut[250], profil[250];

    OCTET *ImgIn, *ImgOut;
    int nTaille, nH, nW, lc, numero;

    if (argc != 6)
    {
        printf("Usage: ImgIn.pgm ImgOut.ppm ImgOut.dat lc numero\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgOut);
    sscanf(argv[3], "%s", profil);
    sscanf(argv[4], "%d", &lc);
    sscanf(argv[5], "%d", &numero);

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille * 3); // PPM = 3x plus grand (R,G,B)

    lire_image_pgm(cNomImgLue, ImgIn, nTaille);

    int p[nH] = {0};    

    if (lc == 0) // Extraction d'une ligne
    {
        for (int i = 0; i < nW; i++)
        {
            p[i] = ImgIn[numero * nW + i];

        }
        
    }
    else // Extraction d'une colonne
    {
        for (int i = 0; i < nH; i++)
        {
            p[i] = ImgIn[i * nW + numero];
        }
    }

    FILE *f = fopen(profil, "wb");
    if (f == NULL)
    {
        printf("Erreur pendant l'ouverture du fichier");
        exit(1);
    }

    for(int i = 0; i < nH; i++)
    {
        printf("%d %d\n", i, p[i]);
        fprintf(f, "%d %d\n", i, p[i]);
    }
    fclose(f);


    
    if (lc == 0){
        for (int y = 0; y < nH; y++)
        {
            for (int x = 0; x < nW; x++)
            {
                int index = (y * nW + x) * 3;
                if (y == numero - 1 || y == numero + 1) 
                {
                    ImgOut[index] = 255;   // Rouge
                    ImgOut[index + 1] = 0; // Vert
                    ImgOut[index + 2] = 0; // Bleu
                }
                else
                {
                    ImgOut[index] = ImgIn[y * nW + x];   // Gris
                    ImgOut[index + 1] = ImgIn[y * nW + x]; // Gris
                    ImgOut[index + 2] = ImgIn[y * nW + x]; // Gris
                }
            }
        }
    }else{
        for (int y = 0; y < nH; y++)
        {
            for (int x = 0; x < nW; x++)
            {
                int index = (y * nW + x) * 3;
                if (x == numero - 1 || x == numero + 1) 
                {
                    ImgOut[index] = 255;   // Rouge
                    ImgOut[index + 1] = 0; // Vert
                    ImgOut[index + 2] = 0; // Bleu
                }
                else
                {
                    ImgOut[index] = ImgIn[y * nW + x];   // Gris
                    ImgOut[index + 1] = ImgIn[y * nW + x]; // Gris
                    ImgOut[index + 2] = ImgIn[y * nW + x]; // Gris
                }
            }
        }
    }


    ecrire_image_ppm(cNomImgOut, ImgOut, nH, nW);
    
    free(ImgIn);
    free(ImgOut);

    printf("Image avec rectangle rouge enregistrée dans %s\n", cNomImgOut);
    return 0;
}
