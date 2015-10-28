#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <iostream>
#include <utility> // std::pair

class Matriz {

public:
  // n = filas, m = columnas
  Matriz(int n, int m, double init);

  // constructor por copia
  Matriz(Matriz * vieja);

  void mostrar();

  int columnas();

  int filas();
  
  // esta funcion nos permite asignar y obtener los coeficientes
  // de la matriz
  double &operator()(const int &i, const int &j);  

  //Pre: A es triangular superior y no tiene ceros en la diagonal
  std::vector<double> backward_subst(std::vector<double> b);

  //Pre: A es triangular inferior y no tiene ceros en la diagonal
  std::vector<double> forward_subst(std::vector<double> b);

	//Factorizacion LU mejorada, haciendo la resta entre filas hasta que empiezan a haber ceros en f_i.
  std::vector<double> gaussian_elim(std::vector<double> b);

private:
    int n_;
    int m_;
    std::vector<std::vector<double> > mat;
};

#endif // MATRIZ_H
