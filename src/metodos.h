#ifndef METODOS_H
#define METODOS_H

#include "matriz.h"
#include <vector>
#include <iostream>


std::vector<unsigned int> nn(std::vector<unsigned int> valores, int cuadros);

std::vector<unsigned int> lineal(std::vector<unsigned int> valores_i, int cuadros);

std::vector<unsigned int> splines(std::vector<unsigned int> valores_i, int cuadros,
                                  int radio);

#endif // METODOS_H
