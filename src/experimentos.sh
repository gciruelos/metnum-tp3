make clean && make
for i in ff6 penal motocross darthvader; do #Itero sobre cada archivo
	txttimes="data/$i/$i.times.txt"
	rm -f $txttimes
	for k in 1 2 4 8;do 					#Itero sobre cada cant de cuadros a interpolar
		txtf="data/$i.txt"
		echo "Convirtiendo $i a txt..."
		python2 tools/videoToTextfile.py "data/$i.avi" $txtf $k
		for j in 0 1 2 3 4; do 				#Itero sobre los métodos
			txtdiff="data/$i/$i.$j.diff.txt"
			txtout="data/$i/$i.$j.$k.out"
			txtoriginal="data/$i.original.txt"
			videoout="data/$i/$i.$j.$k.avi"
			echo "Interpolando $k cuadros con $j..."
			./tp $txtf $txtout $j $k $txttimes
			echo "Calculando error"
			python2 ecm.py $txtoriginal $txtout $txtdiff $k
			echo "Convirtiendo a video..."
			python2 tools/textfileToVideo.py $txtout $videoout	
		done
		rm -f $txtf
	done
done