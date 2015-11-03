# Como funciona: 
# $1 : es el video que se quiere procesar
# $2 : es la cantidad de cuadros que se quiere interpolar
# $3 : es el metodo que se quiere usar
txtf=$1".txt"
txtout=aca.out
rm -f data/out.avi
python2 metnum.py build
python2 tools/videoToTextfile.py $1 $txtf $2
echo "Interpolando..."
./tp $txtf $txtout $3 $2
echo "Convirtiendo a video..."
python2 ecm.py $txtf $txtout $2  
python2 tools/textfileToVideo.py $txtout data/out.avi 
echo "Abriendo video..."
vlc data/out.avi 
