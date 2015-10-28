#ifndef METODOS_H
#define METODOS_H

#include "matriz.h"
#include <vector>
#include <iostream>

std::vector<double>  sistema_splines_cs(int tamanio, std::vector<double> ys);

std::vector<unsigned int> nn(std::vector<unsigned int> valores, int cuadros);


#endif // METODOS_H
