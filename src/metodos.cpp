#include "metodos.h"
#define MIN(a,b) ((a)<(b)?(a):(b))

const double h = 1;


/*****************************************************************************
 *   UTILIDADES   
 *****************************************************************************/

template <typename T>
void printv(std::vector<T> v){
	std::cout << "{" ;
	for(int i = 0; i < v.size(); i++){
		if(i != 0) std::cout << ", ";
		std::cout << v[i];
	}
	
	std::cout << "}"<< std::endl;
}

std::vector<unsigned int> double_to_pixel(std::vector<double> ds){
	std::vector<unsigned int> is;
	for(unsigned int i = 0; i < ds.size(); i++){
		int x = ds[i];
		if(x > 255) x = 255;
		else if(x < 0) x = 0;
		is.push_back((unsigned int) (x + 0.5));
	}
	return is;
}
     

std::vector<double> pixel_to_double(std::vector<unsigned int> is){
	std::vector<double> ds;
	for(unsigned int i = 0; i < is.size(); i++)
		ds.push_back((double) is[i]);
	return ds;
}                      


/*****************************************************************************
 *   NEAREST NEIGHBOUR         
 *****************************************************************************/
std::vector<unsigned int> nn(std::vector<unsigned int> valores, int cuadros){
	std::vector<unsigned int> interpolados;
	
	//printv(valores);
	
	for(int i = 0; i < valores.size() - 1; i++){
		interpolados.push_back(valores[i]);
		
		for(int j = 0; j < cuadros/2; j++)
			interpolados.push_back(valores[i]);
			
		for(int j = cuadros/2; j < cuadros; j++)
			interpolados.push_back(valores[i+1]);
		//std::cout << "asd" << std::endl;
	}
	interpolados.push_back(valores[valores.size()-1]);
	
	return interpolados;
}	



/*****************************************************************************
 *   INTERPOLACION LINEAL FRAGMENTARIA       
 *****************************************************************************/


std::vector<unsigned int> lineal(std::vector<unsigned int> valores_i, int cuadros){
    std::vector<double> valores = pixel_to_double(valores_i);
	std::vector<double> interpolados;
	
	/* 
       La tablita de valores es:
       0 | valores[0]
       1 | valores[1]
        ...
       i | valores[i]
        ...
       n | valores[n]
    */

	for(int i = 0; i < valores.size() - 1; i++){
		interpolados.push_back(valores[i]);
        // aca tengo que interpolar linealmente
        // (i, valores[i]) (i+1, valores[i+1])

        // (f(b)-f(a))/(b-a) (x-a) + f(a)
        // = (valores[i+1]-valores[i]) (x - i) + valores[i]
        // los cortes en el medio tienen que ser:
        // 1/(cuadros+1) , 2/(cuadros+1), ..., cuadros/(cuadros+1)
        // a esos les llamo z_j
        for(int j = 0; j < cuadros; j++){
            double z_j = ((double) (j+1)) / (cuadros+1); 
            interpolados.push_back(
                    (valores[i+1] - valores[i]) * z_j + valores[i]);
        }
        
	}
	interpolados.push_back(valores[valores.size()-1]);
	
	return double_to_pixel(interpolados);
}	


/*****************************************************************************
 *   SPLINES CUBICOS
 *****************************************************************************/

void splines_bloque(std::vector<double> ys, int cuadros,
                    std::vector<double>* resultado){
    //std::vector<double> local;
			
	int sz = ys.size();
	int n = sz-1;
    std::vector<double> as = ys;
    std::vector<double> bs(sz);
    std::vector<double> cs(sz);
    std::vector<double> ds(sz);
    
    
    // STEP 1 : nada
    // STEP 2
    std::vector<double> alpha(sz);
    for(int i = 1; i < n; i++){ 
		alpha[i] = 3*(as[i+1]-as[i])/h - 3*(as[i]-as[i-1])/h;
	}
	
	// STEP 3
	std::vector<double> l(sz);	
	std::vector<double> mu(sz);	
	std::vector<double> z(sz);
	l[0] = 1;
	mu[0] = 0;
	z[0] = 0;
	
	// STEP 4
	for(int i = 1; i < n; i++){ 
		l[i] = 2*(2*h) - h * mu[i-1];
		mu[i] = h/l[i];
		z[i] = (alpha[i] - h*z[i-1])/l[i];
	}
	
	// STEP 5
	l[n] = 1;
	z[n] = 0;
	cs[n] = 0;
	
	// STEP 6
	for(int j = n-1; j >= 0; j--){
		cs[j] = z[j] - mu[j]*cs[j+1];
		bs[j] = (as[j+1] - as[j])/h - h*(cs[j+1] + 2*cs[j])/3;
		ds[j] = (cs[j+1] - cs[j])/(3*h);
	}
			
	for(int i = 0; i < n; i++){
		resultado->push_back(ys[i]);
        //local.push_back(ys[i]);
        // aca tengo que interpolar usando splines
        // (i, valores[i]) (i+1, valores[i+1])
        for(int j = 0; j < cuadros; j++){
            /*
                  z_0   z_1 .... z_{cuadros-1}
              i ---|-----|-------------|------i+h

              En realidad el z_j del programa es   z_j - i, o sea, 
              0 < z_j < 1
            */
            double z_j = h*((double) (j+1)) / (cuadros+1); 
            resultado->push_back(as[i] +
                                 bs[i] * z_j +
                                 cs[i] * z_j * z_j + 
                                 ds[i] * z_j * z_j * z_j);
            // local.push_back(as[i] +
            //                      bs[i] * z_j +
            //                      cs[i] * z_j * z_j + 
            //                      ds[i] * z_j * z_j * z_j);
        }
	} 
}

std::vector<unsigned int> splines(std::vector<unsigned int> valores_i, int cuadros,
                                  int radio){
    std::vector<double> valores = pixel_to_double(valores_i);
	std::vector<double> interpolados;
	
    int inicio = 0;
    while (inicio < valores.size()){
		std::vector<double> bloque;
		int n = MIN(radio, valores.size()-inicio);
        //std::cout << inicio << " " << n << std::endl << "\t";
		for(int i = 0; i < n; i++){
            //std::cout << inicio+i << ", ";
			bloque.push_back(valores[inicio+i]);
		}
        //std::cout << std::endl;
		splines_bloque(bloque, cuadros, &interpolados);
		inicio += radio-1;
	}
    //std::cout << std::endl;
	interpolados.push_back(valores[valores.size()-1]);
	//printv(interpolados);
	
	return double_to_pixel(interpolados);
}	

	






