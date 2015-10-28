#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "matriz.h"
#include "metodos.h"


enum metodo {
    NNEIGHBOUR = 0,
    LINEAL,
    SPLINES
};


int main(int argc, char * argv[]){
  /* argv[0] es el nombre del programa
   * argv[1] es el archivo de input
   * argv[2] es el archivo de output
   * argv[3] es el metodo a ejecutar
   * argv[4] es el cantidad de cuadros a agregar
   */



    char * aux;
    enum metodo m = (enum metodo) strtol(argv[3], &aux, 10);
    unsigned int cant_cuadros = (argv[4], &aux, 10);
    unsigned int c, height, width, f;
    // Este va a ser un vector de height*width entradas, y cada entrada va 
    // a ser un vector de c(uadros) cantidad de entradas cada uno
    std::vector<std::vector<unsigned int> > frames;
    

    // abrimos el archivo de parametro y cargamos todo
    std::ifstream input_file(argv[1]);
    input_file >> c >> height >> width >> f;

    frames = std::vector<std::vector<unsigned int> >(height * width);

    for(unsigned int pixel = 0; pixel < height * width; pixel++){
        for(unsigned int cuadro = 0; cuadro < c; cuadro++){
            unsigned int gris;
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

    // abrimos el archivo de la red y lo cargamos 
    // ACA YA ESTA TODO LISTO PARA SER USADO
    std::ofstream solus_file(argv[2], std::ofstream::out);

    
	std::vector<double> b(3);
	b[0] = 1;
	b[1] = 2;
	b[2] = 3;
	
	Matriz a = sistema_splines(3, b); 
	a.mostrar();
 
    return 0;
}
