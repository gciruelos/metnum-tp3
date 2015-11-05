import numpy as np
import cv2
import sys

#########################
# Parametros de entrada.#
#########################
textFilename = sys.argv[1]
videoFilename = sys.argv[2]

file = open(textFilename,"r")

# Guardamos informacion basica.
nFrames = int(file.readline())
hw = file.readline().split(',')
height = int(hw[0])
width = int(hw[1])
frameRate = int(file.readline())

# Imprimimos los parametros, para validar.
print 'Parametros generales del video:'
print '\t# frames:', str(nFrames), '\tHeight:', str(height), '\tWidht:', str(width), '\tFrame Rate:',str(frameRate)

fourcc = cv2.cv.CV_FOURCC('M','P','4','2')
video = cv2.VideoWriter(videoFilename, fourcc, frameRate, (width,height),0)

for k in range(0,int(nFrames)):
    frame = np.zeros((height,width,1), np.uint8)

    for i in range(0,int(height)):
        line = file.readline().split(',')
        for j in range(0,int(width)):
            frame[i][j][0] = line[j]

    video.write(frame)

video.release()
