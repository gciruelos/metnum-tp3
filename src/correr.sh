python metnum.py build
./tp data/funnybaby.txt aca.out $1 $2
python tools/textfileToVideo.py
vlc data/out.avi
