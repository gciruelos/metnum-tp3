for i in ff6.avi motocross.avi penal.avi; do
    python2 tools/videoToTextfile.py data/$i data/$i".original.txt" 0
done
