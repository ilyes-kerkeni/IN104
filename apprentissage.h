#ifndef __APPRENTISSAGE_H__
#define __APPRENTISSAGE_H__
#define T 10

void init(int taille_desc,double* Map[T][T],int C[T][T]);

double dist_n(int i,int j,int l,int c) ; 

double dist_eucl(double *descripteur, double *N, int n ); 

double sigma(int t)      ;                    // La fonction sigma qui décroit au cours de temps

double f_gamma(double sig,double dis) ;

int* BMU(double *descripteur, int taille_desc , double *Map[T][T]  ) ; 

void update_neurone(double *descripteur ,int taille_desc, double *Map[T][T] , int l,int c ,int t) ; 

double test_precision( FILE *file , double *Map[T][T] , int category[T][T]) ; 

void apprentissage(char* nom_fichier,double* Map[T][T],int C[T][T]);
#endif
