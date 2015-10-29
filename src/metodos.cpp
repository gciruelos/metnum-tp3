#include "metodos.h"

// h = 1


/*****************************************************************************
 *   UTILIDADES   
 *****************************************************************************/

template <typename T>
void printv(std::vector<T> v){
	for(int i = 0; i < v.size(); i++){
		if(i != 0) std::cout << ",";
		std::cout << v[i];
	}
	std::cout << std::endl;
}

std::vector<unsigned int> double_to_pixel(std::vector<double> ds){
	std::vector<unsigned int> is;
	for(unsigned int i = 0; i < ds.size(); i++){
		int x = ds[i];
		if(x > 255) x = 255;
		else if(x < 0) x = 0;
		is.push_back((unsigned int) x);
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

std::vector<unsigned int> splines(std::vector<unsigned int> valores_i, int cuadros){
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

       Todo el resto es muy parecido a interpolacion lineal
    */

    std::vector<double> as = valores;
    std::vector<double> bs;
    std::vector<double> cs;
    std::vector<double> ds;

	for(int i = 0; i < valores.size() - 1; i++){
		interpolados.push_back(valores[i]);
        // aca tengo que interpolar usando splines
        // (i, valores[i]) (i+1, valores[i+1])
        for(int j = 0; j < cuadros; j++){
            /*
                  z_0   z_1 .... z_{cuadros-1}
              i ---|-----|-------------|------i+1

              En realidad el z_j del programa es   z_j - i, o sea, 
              0 < z_j < 1
            */
            double z_j = ((double) (j+1)) / (cuadros+1); 
            interpolados.push_back(as[i] +
                                   bs[i] * z_j +
                                   cs[i] * z_j * z_j + 
                                   ds[i] * z_j * z_j * z_j);
        }
	}
	interpolados.push_back(valores[valores.size()-1]);
	
	return double_to_pixel(interpolados);
}	



std::vector<double> sistema_splines_cs(int tam, std::vector<double> ys){
	tam++;
	
	
	
	Matriz matriz_splines(tam, tam, 0);
	
	for(int i = 1; i<tam-1; i++){
		matriz_splines(i,i)   = 4;
		matriz_splines(i,i-1) = 1;
		matriz_splines(i,i+1) = 1;
	}
	matriz_splines(0,0) = 1;
	matriz_splines(tam-1, tam-1) = 1;
	
	std::vector<double> z(tam);
	z[0] = 0;
	z[tam-1] = 0;
	for(int i = 1; i<tam-2; i++){
		z[i] = 3*(ys[i+1]-2*ys[i]-ys[i-1]);		
	}
	
	matriz_splines.mostrar();
	
	// cs tiene c0..cn, a0..an esta en ys,
	// falta guardar en res eso mas d0..dn y b0..bn
	return matriz_splines.gaussian_elim(z);
}

	






