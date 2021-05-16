#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define T 10
#define PI acos(-1)

void init(int taille_desc,double* Map[T][T],int C[T][T])
{
    srand(time(NULL)) ; 
    int i,j,k ; 
    for (i=0; i<T;i++)
    {       
        for (j=0 ; j<T ; j++)
        {
             Map[i][j] = (double*) malloc(taille_desc * sizeof(double)) ; 
            if (Map[i][j] == NULL) 
            {
                printf("Erreur allocation") ; 
                exit(EXIT_FAILURE);
            }
    
            for (k=0; k<taille_desc;k++)
            {
                Map[i][j][k] = rand()/ (double) RAND_MAX ; 
                C[i][j] = 0 ; 
            }
        
        }
    }
}

double dist_n(int i,int j,int l,int c)
{
    return ((i-l)*(i-l)+(j-c)*(j-c)) ; 
}



double dist_eucl(double *descripteur, double *N, int n )
{
    double dist =0.0 ; 
    int i ; 
    for (i=0 ; i<n ; i++) dist += (descripteur[i]-N[i]) * (descripteur[i]-N[i]) ; 
    return (dist) ; 
}

double sigma(int t)                         // La fonction sigma qui décroit au cours de temps
{
    //double res = 1 / log(log(t+15)) -2;
     double res= 10*exp((double)-t * log(10) / 366);
    return res ;
}

double f_gamma(double sig,double dis)
{
    double res=(1/sqrt(2*PI))*exp(-dis/(sig*sig));
    return res;
}

int* BMU(double *descripteur, int taille_desc , double *Map[T][T]  )
{
    
    int* res= malloc(2*sizeof(int)) ; 
    if (res == NULL)
    {
        printf("Erreur allocation") ; 
        exit(EXIT_FAILURE);
    }
    // int l,c ; 
    int i,j,k ; 
    double min =0 ; 
    // FILE *tmp = fopen("comp.txt","w") ; 
    min = dist_eucl(descripteur,Map[0][0],taille_desc) ; 
    // printf("%lf\n" , min);
    for(i=0 ; i<T ; i++){
        for(j=0 ; j<T ;j++){ 
            double dis = dist_eucl(descripteur,Map[i][j],taille_desc) ;
            // fprintf(tmp , "%lf < %lf = %d\n", dis , min , dis < min) ; 
            if (dis < min)
            {
                res[0] = i ; 
                res[1] = j ; 
                min = dis ; 
            } 
        }
    }
     // printf("%d %d\n",res[0],res[1]) ; 
    // res[0] = l ; 
    // res[1] = c ; 
    return(res) ; 
}



void update_neurone(double *descripteur ,int taille_desc, double *Map[T][T] , int l,int c , int t)
{
    int i,j,k ; 
    for(i=0 ; i<T ; i++) {
        for(j=0 ; j<T;j++){
            for ( k = 0; k < taille_desc ;k++) 
            {
                double dis,sig ; 
                dis  = dist_n(l,c,i,j);
                sig = sigma(t) ; 
                Map[i][j][k] += f_gamma(sig,dis)*(descripteur[k]-Map[i][j][k]) ; 
            }
            
        }
    }
}

double test_precision( FILE *file , double *Map[T][T] , int category[T][T])
{
    int nb_desc , taille_desc ,type; 
    double res =0.0 ; 
    double *descripteur ; 
    
    int* vainq = malloc(2*sizeof(int));
    if (vainq == NULL)
    {
        printf("Erreur allocation") ; 
        exit(EXIT_FAILURE);
    }
    fscanf(file,"%d" , &nb_desc) ; 
    fscanf(file, "%d" , &taille_desc) ;

    descripteur = (double*) malloc(taille_desc*sizeof(double)); 
    if (descripteur == NULL)
    {
        printf("Erreur allocation") ; 
        exit(EXIT_FAILURE);
    } 
    int i,j ,l,c , nb = 0 ; 
    for (i=0 ; i<nb_desc ; i++)
    {
        fscanf(file , "%d" , &type) ; 
        for (j=0 ; j<taille_desc ; j++)   fscanf(file , "%lf" , &descripteur[j]) ; 
        vainq = BMU(descripteur , taille_desc , Map) ; 
        l = vainq[0] ;
        c = vainq[1] ;
        // printf("%d %d\n",l,c) ; 
         // printf("%d %d\n" , category[l][c], type) ; 
        if (category[l][c] == type) nb++ ; 
    }
    res = nb / (double) nb_desc ; 
    return (res*100.0) ; 

}
void apprentissage(char* nom_fichier,double* Map[T][T],int C[T][T])
{
    int nb_desc,taille_desc,k,t,type;
    FILE* file = fopen(nom_fichier,"r") ; 
    fscanf(file , "%d" , &nb_desc) ;  // Récupération du nombre de descripteurs
    fscanf(file , "%d" , &taille_desc) ;  // Récupération de la taille de descripteurs
    
     for (t=0 ; t<nb_desc ; t++)
    {
        printf("Apprentissage.. Itération %d\n" , t+1) ;

        // Récupération du descripteur 

        fscanf(file, "%d" , &type); 
        // printf("%d\n" , type);
        double* descripteur = (double*) malloc(taille_desc*sizeof(double)); 
        if (descripteur == NULL)
        {
     
            printf("Erreur allocation") ; 
            exit(EXIT_FAILURE);
        }
        for (k=0;k<taille_desc;k++) {fscanf(file, "%lf" , &descripteur[k]);}  

        // Recherche du neurone vainqueur 

            int l,c ; 
            int *vainq=malloc(2*sizeof(int));
            if (vainq == NULL)
            {
                printf("Erreur allocation") ; 
                exit(EXIT_FAILURE);
        
            }
            vainq = BMU(descripteur , taille_desc, Map );
            l =  vainq[0] ;  
            c = vainq[1] ;
            /// printf("%d %d\n ", l,c) ; 
            free(vainq); 
            C[l][c] = type ;  
            update_neurone(descripteur,taille_desc, Map ,l,c,t ); // Apprentissage du neurone vainqueur et de ses voisins
            free(descripteur) ; 
            // printf("%lf\n" , Map[3][6][4]) ; 
    
    }
}
            
             
