import numpy as np
import sys
from math import *

#########################
# Parametros de entrada.#
#########################
original = sys.argv[1]
interpolado = sys.argv[2]
cant_cuadros = int(sys.argv[3])


file_original = open(original,"r")
file_interpolado = open(interpolado,"r")

# Guardamos informacion basica.
nFrames_original = int(file_original.readline())
nFrames_interpol = int(file_interpolado.readline())
nFrames = min([nFrames_original, nFrames_interpol])

hw = file_original.readline().split(',')
file_interpolado.readline()

height = int(hw[0])
width = int(hw[1])
file_original.readline()
file_interpolado.readline()

ecms = []
psnrs = []
print 'nFrames', nFrames_original, nFrames_interpol

for k in range(0,int(nFrames)-1):
    frame_original = np.zeros((height,width,1), np.uint8)
    frame_interpolado = np.zeros((height,width,1), np.uint8)

    ecm = 0.0

    for i in range(0,int(height)):
        line_original = file_original.readline().split(',')
        line_interpolado = file_interpolado.readline().split(',')
        for j in range(0,int(width)):
            frame_original[i][j][0] = line_original[j]
            frame_interpolado[i][j][0] = line_interpolado[j]

    if k % (cant_cuadros + 1) != 0: # si es un cuadro de los que interpolamos
        for i in range(0,int(height)):
            for j in range(0,int(width)):
                dif = int(frame_original[i][j][0]) - int(frame_interpolado[i][j][0])
                ecm += float(dif)**2.0

        ecm /= float(height*width)
        if ecm > 0.0001:
            ecms.append(ecm)
            psnrs.append(10 * log10(255.0**2 / ecm))

print 'Error Cuadratico Medio', ecms
print 'Peak to Signal Noise Ratio', psnrs
print len(ecms)
