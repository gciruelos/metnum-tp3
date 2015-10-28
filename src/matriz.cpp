#include "matriz.h"

Matriz::Matriz(int n, int m, double init) : n_(n), m_(m) {  
	for(int i = 0; i<n; i++){
    std::vector<double> row;
    for(int j = 0; j<m; j++){
      row.push_back(init);
    }
    mat.push_back(row);
  }
}

Matriz::Matriz(Matriz * vieja){
  n_ = vieja->n_;
  m_ = vieja->m_;
  mat = vieja->mat;
}

void Matriz::mostrar(){
  for(int i = 0; i<n_; i++){
    for(int j = 0; j<m_; j++){
      std::cout << mat[i][j] << " ";
    }
    std::cout << std::endl;
  }
    std::cout << std::endl;
}

int Matriz::columnas(){
  return m_;
}

int Matriz::filas(){
  return n_;
}

double &Matriz::operator()(const int &i, const int &j){
  return mat[i][j];
}

//Pre: A es triangular superior y no tiene ceros en la diagonal
std::vector<double> Matriz::backward_subst(std::vector<double> b){
  int n = b.size();
  std::vector<double> x(n, 0.0);
  
  for(int k = n-1; k>=0; k--){
    double numer = b[k];
    for(int i = k+1; i<n; i++){
      numer -= (*this)(k, i) * x[i];
    }
    x[k] = numer / (*this)(k,k);
  }
  return x;
}

//Pre: A es triangular inferior y no tiene ceros en la diagonal
std::vector<double> Matriz::forward_subst(std::vector<double> b){
  int n = b.size();
  std::vector<double> x(n, 0.0);

  for(int k = 0; k<n; k++){
    double numer = b[k];
    for(int i = 0; i<k; i++){
      numer -= (*this)(k, i) * x[i];
    }
    x[k] = numer / (*this)(k,k);
  }
  return x;
}


std::vector<double> Matriz::gaussian_elim(std::vector<double> b){
  int n = b.size();
  Matriz gauss(this);

  for(int i = 0; i<n; i++){
	  int fila = i+1;
      // modifico la fila
      // lo hago desde la posicion (i,i-1) hasta (i,i + 1), porque son los unicos elementos distintos de 0.
      // f_j - cte_fila * f_i 
      // cte_fila = prim/a_ii, donde prim es el primero de la fila
      double prim = gauss(fila,i);
     
      double coeff = prim/gauss(i,i);
      for(int j = i+1; j<n; j++){ 
        gauss(fila, j) -= gauss(i, j) * coeff;
      }
      gauss(fila, i) = 0.0;
      
      //modifico b
      b[fila] -= b[i] * coeff;     
  }

  // es triangular superior, aplicamos backward substitution
  return  gauss.backward_subst(b);
}
