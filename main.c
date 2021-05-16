#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "apprentissage.h"
#define T 10 // La taille du réseau de neurones
double *Map[T][T] ; // Le réseau de neurones
int C[T][T] ; // La carte des catégories 

char desc[10] = "color"; // on peut changer le nom du descripteur (color ou bien texture)
char cmd[30] = "python3 ";

char name[10];
bool lancer_desc = true; 
int test , type ; 

double *descripteur ; 
int nb_desc ;
int taille_desc ; 
int t ; 

int main()
{
    printf("Descripteur: couleur\n"); 
    
    //verifier si on veut lancer la creation des descripteurs
    if(lancer_desc){
        strcat(cmd, desc);
        strcat(cmd, ".py"); // on colle "py" le nom (color ou texture)
        system(cmd);  // on lance la commande (color.py ou bien texture.py)
    }

    strcpy(name, desc);
    strcat(name, ".txt"); // filename=color.txt ou bien texture.txt

    FILE* file = fopen(name,"r") ; 
    fscanf(file , "%d" , &nb_desc) ;  // Récupération du nombre de descripteurs
    fscanf(file , "%d" , &taille_desc) ;  // Récupération de la taille de descripteurs
    fclose(file);
   
    // initialiser neurones 
    init(taille_desc,Map,C);
    // Apprentissage  
    
    apprentissage(name,Map,C);
    
    

 
// Test de l'apprentissage et determination de la précision
int i,j ; 
 for(i=0;i<T;i++){
        for(j=0;j<T;j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }


char test_p[50] ; 
strcpy(test_p,desc) ; 
strcat(test_p,"_test.txt") ; 
FILE *test_file = fopen(test_p,"r") ; 
double precision ;
precision = test_precision(test_file, Map,C) ; 
printf("Précision = %lf\n" , precision) ; 
fclose(test_file) ; 
return(0); 


}
