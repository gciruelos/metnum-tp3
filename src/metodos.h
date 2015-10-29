#ifndef METODOS_H
#define METODOS_H

#include "matriz.h"
#include <vector>
#include <iostream>


std::vector<unsigned int> nn(std::vector<unsigned int> valores, int cuadros);

std::vector<unsigned int> lineal(std::vector<unsigned int> valores_i, int cuadros);

std::vector<unsigned int> splines(std::vector<unsigned int> valores_i, int cuadros);
std::vector<double>  sistema_splines_cs(int tamanio, std::vector<double> ys);

#endif // METODOS_H
