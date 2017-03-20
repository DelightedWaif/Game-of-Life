import numpy as np
import random
import time
#run Conway's Game of Life
def IPA(x):                 #IPA if your colony of drinkers
    eco = np.zeros((x,x),dtype=int)
    return eco
#    print (eco)

def stout(i,j,check,matrix):
    #pub is your 3X3 matrix
    pub = np.matrix([[matrix[i-1][j-1], matrix[i][j-1], matrix[i+1][j-1]], [matrix[i-1][j], matrix[i][j], matrix[i+1][j]], [matrix[i-1][j+1], matrix[i][j+1], matrix[i+1][j+1]]])
    print (pub)
def Lager(matrix, x):

    for i in range(x):
        for j in range(x):
            matrix[i][j] = random.randrange(0,2)
            stout(i,j,matrix[i][j],matrix)
    #print(matrix)
n = 10
x = IPA(n)
Lager(x, n)
