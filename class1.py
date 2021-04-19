import numpy as np 
import matplotlib.image as im
import matplotlib.pyplot as plt 


def lire_image(nom_fichier):

    image=im.imread(nom_fichier)
    return image

def afficher_image(I):
    plt.imshow(I,'gray')
    plt.show()

def rgb2gray(I):
    c=I.shape[0]
    l=I.shape[1]
    g=np.zeros((c,l))
    for i in range(c):
        for j in range(l):
            g[i,j]=sum(I[i,j,:])/3
    return g







im=lire_image("python.jpeg")
grey=rgb2gray(im)
afficher_image(grey)
