# Como funciona: 
# $1 : es el video que se quiere procesar
# $2 : es el metodo que se quiere usar
# $3 : es la cantidad de cuadros que se quiere interpolar
txtf=$1".txt"
txtoriginal=$1".original.txt"
txtout=aca.out
rm -f data/out.avi
python2 metnum.py build
python2 tools/videoToTextfile.py $1 $txtf $3
python2 tools/videoToTextfile.py $1 $txtoriginal 0
echo "Interpolando..."
./tp $txtf $txtout $2 $3
echo "Convirtiendo a video..."
python2 ecm.py $txtoriginal $txtout $3
python2 tools/textfileToVideo.py $txtout data/out.avi 
echo "Abriendo video..."
vlc data/out.avi 
