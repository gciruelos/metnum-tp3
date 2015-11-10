import numpy as np
import cv2
import sys

#########################
# Parametros de entrada.#
#########################
videoFilename = sys.argv[1]
textFilename = sys.argv[2]
salto = int(sys.argv[3])+1

print "Archivo de video: " + videoFilename
print "Archivo de texto: " + textFilename
print "Salto: " + str(salto)

# Abrimos archivo de video.
video = cv2.VideoCapture(videoFilename)

# Obtenemos informacion basica.
nFrames = video.get(cv2.cv.CV_CAP_PROP_FRAME_COUNT)
frameRate = video.get(cv2.cv.CV_CAP_PROP_FPS)
height = video.get(cv2.cv.CV_CAP_PROP_FRAME_HEIGHT)
width = video.get(cv2.cv.CV_CAP_PROP_FRAME_WIDTH)

#print 'Abriendo archivo: ' + str(video.isOpened())
print 'Info del video:'
print '\t# frames:', str(nFrames), '\tHeight:', str(height), '\tWidht:', str(width), '\tFrame Rate:',str(frameRate)

# Guardamos informacion general en el archivo de salida.
f = open(textFilename,'w')
f.write(str(1 + int(nFrames) // salto) + '\n')
f.write(str(int(height)) + ',' + str(int(width)) + '\n')
f.write(str(int(frameRate)) + '\n')

# Bajamos al archivo los frames que nos interesan.
for k in xrange(0,int(nFrames),salto):
	ret, frame = video.read()
	grayFrame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	cv2.imshow('frame',grayFrame)
	k = k+salto
	video.set(cv2.cv.CV_CAP_PROP_POS_FRAMES,k)

	for i in range(0,int(video.get(4))):
		for j in range(0,int(video.get(3))-1):
			f.write(str(grayFrame[i][j]) + ',')
		f.write(str(grayFrame[i][int(video.get(3)-1)]))
		f.write('\n')

f.close()
video.release()
cv2.destroyAllWindows()
#print 'Fin'

