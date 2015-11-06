#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "metodos.h"

#include <ctime>
#include <stdio.h>

using namespace std;

enum metodo {
    NN = 0,
    LINEAL,
    SPLINES4,
    SPLINES8,
    SPLINES12,
};


int main(int argc, char * argv[]){
  /* argv[0] es el nombre del programa
   * argv[1] es el archivo de input
   * argv[2] es el archivo de output
   * argv[3] es el metodo a ejecutar
   * argv[4] es el cantidad de cuadros a agregar
   * argv[5] es el archivo de salida para los tiempos
   */


	char coma;
    char * aux;
    enum metodo m = (enum metodo) strtol(argv[3], &aux, 10);
    unsigned int cant_cuadros = strtol(argv[4], &aux, 10);
    unsigned int c, height, width, f;
    // Este va a ser un vector de height*width entradas, y cada entrada va 
    // a ser un vector de c(uadros) cantidad de entradas cada uno
    std::vector<std::vector<unsigned int> > frames;

    // abrimos el archivo de parametro y cargamos todo
    std::ifstream input_file(argv[1]);
    input_file >> c >> height >> coma >> width >> f;
    
    frames = std::vector<std::vector<unsigned int> >(height * width);

    for(unsigned int cuadro = 0; cuadro < c; cuadro++){
		for(unsigned int pixel = 0; pixel < height * width; pixel++){
            unsigned int gris;
            if(pixel % width != 0) input_file >> coma;
            input_file >> gris;
            
            
            frames[pixel].push_back(gris);
        }
    }
    input_file.close();
  

    /*
    // los achico para minimizar el uso de memoria (c++11)
    for(unsigned int pixel = 0; pixel < height * width; pixel++)
        frames[pixel].shrink_to_fit();
    */



    std::cout << "Interpolando usando el algoritmo ";
	if(m == NN)
        std::cout << "<<Nearest Neighbour>>";
	else if(m == LINEAL)
        std::cout << "<<Interpolacion Lineal>>";
	else if(m == SPLINES4)
        std::cout << "<<Splines4>>";
    else if(m == SPLINES8)
        std::cout << "<<Splines8>>";
    else if(m == SPLINES12)
        std::cout << "<<Splines12>>";

    std::cout << ". cant_cuadros = " << cant_cuadros
              << " ("<<  (c-1) * cant_cuadros << ")"<< std::endl;
    // abrimos el archivo de la red y lo cargamos 
    // ACA YA ESTA TODO LISTO PARA SER USADO
    std::ofstream out_file(argv[2], std::ofstream::out);
    
    
    std::vector<std::vector<unsigned int> > resultado; 
    
    /***********Tomo tiempos***********/
    clock_t begin = clock();

	for(unsigned int pixel = 0; pixel < height * width; pixel++){
		std::vector<unsigned int> valores = frames[pixel];
		std::vector<unsigned int> interpolado;
		
		
		if(m == NN)
			interpolado = nn(valores, cant_cuadros);
		else if(m == LINEAL)
			interpolado = lineal(valores, cant_cuadros);
		else if(m == SPLINES4)
			interpolado = splines(valores, cant_cuadros, 4);
        else if(m == SPLINES8)
            interpolado = splines(valores, cant_cuadros, 8);
        else if(m == SPLINES12)
            interpolado = splines(valores, cant_cuadros, 12);
		
		
		resultado.push_back(interpolado);
            unsigned int gris;
            input_file >> gris;
            frames[pixel].push_back(gris);
    }

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    FILE* times_file = fopen(argv[5], "a");
    fprintf(times_file, "Método %d, %d cuadros: %f\n", m, cant_cuadros, elapsed_secs);
    fclose(times_file);
    /***********************************/

    unsigned int nuevos_cuadros = (c-1) * cant_cuadros + c;
    std::cout << c << " " << cant_cuadros << " "<<  nuevos_cuadros << std::endl;
    out_file << nuevos_cuadros << std::endl;
    out_file << height << "," << width << std::endl;
    out_file << f << std::endl;    
  
  
    for(unsigned int cuadro = 0; cuadro < nuevos_cuadros; cuadro++){
	    for(unsigned int pixel = 0; pixel < height * width; pixel++){
		    if(pixel % width != 0) out_file << ",";
		    out_file << resultado[pixel][cuadro];
		    if((pixel+1) % width == 0) out_file << std::endl;
        }
    }
    
 
    /*
	std::vector<double> b(4);
	b[0] = 1;
	b[1] = 2;
	b[2] = 3;
	b[3] = 0;
	
	sistema_splines_cs(b); 
 */
 /*
    std::vector<unsigned int> ej(4);
    ej[0] = 0;
    ej[1] = 2;
    ej[2] = 1;
    ej[3] = 0;
    splines(ej, 1);
   */
    return 0;
}


