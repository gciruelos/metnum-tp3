python2 metnum.py build
echo "Convirtiendo video a txt"
python2 tools/videoToTextfile.py
echo "Interpolando..."
./tp data/funnybaby.txt aca.out $1 $2
echo "Convirtiendo a video..."
python2 tools/textfileToVideo.py
echo "Abriendo video..."
vlc data/out.avi
