El formato de los archivos dentro de la carpeta *video* será el siguiente:

* 20 archivos .avi cuyo nombre es de la forma *video*.*met*.*cant_cuadros*.avi
* 20 archivos .out cuyo nombre es de la forma *video*.*met*.*cant_cuadros*.out
* 5 archivos .txt cuyo nombre es de la forma *video*.*met*.diff.txt que contiene los errores cometidos por cada método para las distintas *cant_cuadros*.
* 1 archivo  .txt cuyo nombre es de la forma *video*.times.txt que contiene los tiempos de ejecución de cada método para cada *cant_cuadros*

*met* es un número en 0 y 4 que representa el método utilizado para interpolar:

* 0 - Vecino más cercano (NN)
* 1 - Interpolación lineal (LINEAL)
* 2 - Splines con tamaño de bloque 4 (SPLINES4)
* 3 - Splines con tamaño de bloque 8 (SPLINES8) 
* 4 - Splines con tamaño de bloque 12 (SPLINES12) 

*cant_cuadros* es la cantidad de cuadros a reemplazar de *video*.original.avi por cuadros interpolados.

