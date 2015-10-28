#include "metodos.h"


Matriz sistema_splines(int tamanio, std::vector<double> ys){
	int h = 1;
	Matriz matriz_splines = Matriz(tamanio, tamanio, 0);
	
	for(int i = 1; i<tamanio; i++){
		matriz_splines(i,i) = 2*h;
		matriz_splines(i,i-1) = h;
		matriz_splines(i,i+1) = h;
	} 	
	std::vector<double> b;
	b[0] = 0;
	b[tamanio-1] = 0;
	for(int i = 1; i<tamanio-2; i++){
		b[i] = 3*(ys[i+1]-2*ys[i]-ys[i-1]);		
	}
	
	std::vector<double> cs = matriz_splines.gaussian_elim(b);
	
	// cs tiene c0..cn, a0..an esta en ys, falta guardar en res eso mas d0..dn y b0..bn
	
	Matriz res = Matriz(tamanio,4,0);
	
	
	
	return res;
}
