
#include "cabecera.h"

void inicio(int cuantos, char **datos){

	clock_t inicioTiempo, finalTiempo;

	inicioTiempo = clock();

	registrarDatos(cuantos, datos);

	imprimirHasta_n(1);
	imprimirHasta_n(2);
	imprimirHasta_n(3);

	imprimirConvergencia(1);
	imprimirConvergencia(2);
	imprimirConvergencia(3);

	generadorDeSuma(1);
	generadorDeSuma(2);
	generadorDeSuma(3);

	generarImagen(1);
	generarImagen(2);
	generarImagen(3);

	finalTiempo = clock();

	especificarTiempo(inicioTiempo, finalTiempo);

}

void registrarDatos(int cuantos, char **datos){
	for (int i = 0; i < (cuantos - 1); i++){
		if(i < 3)
			series[0].valoresSerie[i] = atof(datos[i+1]);
		else
			if(i > 5)
				series[2].valoresSerie[i-6] = atof(datos[i+1]);
			else
				series[1].valoresSerie[i-3] = atof(datos[i+1]);
	}
}

void imprimirHasta_n(int serie){
	double k, h, n;
	double An = 0;

	switch(serie){

		case 1:// ⅀ k/i*h
		
			k = series[0].valoresSerie[0]; 
			h = series[0].valoresSerie[1]; 
			n = series[0].valoresSerie[2];

			if(h != 0){
				for (int i = 1; i <= n; i++)
					An += k/(i*h);
				printf("La serie 1 desde 1 hasta %d resulta: %f\n",(int) n, An);
				series[0].seIndetermina = 0;
			}
			else{
				printf("ERROR, Indeterminacion porque h = 0 en la serie 1.\n");
				series[0].seIndetermina = 1;
			}
		break;
		case 2:// ⅀ (k/h)^i

			k = series[1].valoresSerie[0]; 
			h = series[1].valoresSerie[1]; 
			n = series[1].valoresSerie[2];

			if(h != 0){
				for (int i = 0; i <= n; i++)
					An += pow((k/h), i);
				printf("La serie 2 desde 0 hasta %d resulta: %f\n",(int) n, An);
				series[1].seIndetermina = 0;
			}
			else{
				printf("ERROR, Indeterminacion porque h = 0, en la serie 2.\n");
				series[1].seIndetermina = 1;
			}
		break;
		case 3:// ⅀ (-1)^i * k^i *h^i
			
			k = series[2].valoresSerie[0]; 
			h = series[2].valoresSerie[1]; 
			n = series[2].valoresSerie[2];
			double a_x_b;

			for (int i = 0; i <= n; i++){
				a_x_b = pow(-1, i) * pow(k, i);
				An += a_x_b * pow(h, i);
			}
			printf("La serie 3 desde 0 hasta %d resulta: %f\n\n", (int) n, An);
			series[2].seIndetermina = 0;
		break;
		default:
			puts("No existe la serie :C");
		break;
	}

}

void imprimirConvergencia(int serie){

	switch(serie){
		case 1:
			puts("La serie 1 no Converge");
		break;
		case 2:
			if((series[1].valoresSerie[0] / series[1].valoresSerie[1]) < 1){
				puts("La serie 2 Converge");
				series[1].converge = 1;
			}
			else{
				puts("La serie 2 no Converge");
				series[1].converge = 0;
			}
		break;
		case 3:
			if((series[2].valoresSerie[0] * series[2].valoresSerie[1]) <= 1){
				puts("La serie 3 Converge.\n");
				series[2].converge = 1;
			}
			else{
				puts("La serie 3 no Converge.\n");
				series[2].converge = 0;
			}
		break;
		default:
			puts("No existe la serie :C");
		break;
	}
}

void generadorDeSuma(int serie){
	double k, h, n;
	double An = 0;
	int x = 0, y = 0;

	switch(serie){
		case 1:
			k = series[0].valoresSerie[0]; 
			h = series[0].valoresSerie[1]; 
			n = series[0].valoresSerie[2];

			if(!series[0].seIndetermina){
				for (int i = 1; i <= IMAGEN; i++){
					An += k/(i*h);
					if(An >= 1.12123515e-25){
						An = 1.12123515e-25;
					}
					series[0].arregloImagen[x][y] = An; 
					x++;
					if(x % 128 == 0){
						y++;
						x = 0;
					}
				}
			}

		break;
		case 2:
			k = series[1].valoresSerie[0]; 
			h = series[1].valoresSerie[1]; 
			n = series[1].valoresSerie[2];

			if(!series[1].seIndetermina){
				for (int i = 0; i <= IMAGEN; i++){
					An += pow((k/h), i);
					series[1].arregloImagen[x][y] = An; 
					x++;
					if(x % 128 == 0){
						y++;
						x = 0;
					}
				}
			}	
		break;
		case 3:
			k = series[2].valoresSerie[0]; 
			h = series[2].valoresSerie[1]; 
			n = series[2].valoresSerie[2];
			double a_x_b;

			for (int i = 0; i <= IMAGEN; i++){
				a_x_b = pow(-1, i) * pow(k, i);
				An += a_x_b * pow(h, i);
				if(An >= 1.12123515e-25){
					An = 1.12123515e-25;
				}
				series[2].arregloImagen[x][y] = An; 
				x++;
				if(x % 128 == 0){
					y++;
					x = 0;
				}
			}
		break;
		default:
			puts("No existe la serie :C");
		break;
	}

}

void especificarTiempo(clock_t inicioTiempo, clock_t finalTiempo){

	clock_t tiempoTotal;
	//tiempo total en milisegundos
	tiempoTotal = (double) (finalTiempo - inicioTiempo)/(CLOCKS_PER_SEC/1000);

	printf("\nTiempo total de evaluacion: %ld milisegundos.\n", tiempoTotal);

}

void escribirImagen(char *filename, char rgb[]) {

    int alto = TAM;
    int ancho = TAM;
    int tamanoImagen = IMAGEN * 9;
    char *datosImagen = (char *) malloc(tamanoImagen * sizeof(char));
    char tag[] = { 'B', 'M' };
    FILE *imagen = fopen(filename, "w+");

    for (int i = 0; i < tamanoImagen; i++)
    	datosImagen[i] = 0;

    // For each pixel in the RGB image...
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            // RGB
            for (int z = 0; z < 3; z++) {
                int index = 3 * TAM * i + 3 * j + z;
                //Guarda los datos
                datosImagen[index] = rgb[3*(i * ancho + j) + (2 - z)];
            }
        }
    }

    int header[] = {
        0, 0, 0x36, 0x28, ancho, alto, 0x180001, 
        0, 0, 0x002e23, 0x002e23, 0, 0
    };
    header[0] = sizeof(tag) + sizeof(header) + tamanoImagen;
    
    fwrite(&tag, sizeof(tag), 1, imagen);
    fwrite(&header, sizeof(header), 1, imagen);
    fwrite(datosImagen, tamanoImagen * sizeof(char), 1, imagen);
    fclose(imagen);
    free(datosImagen);
}

void generarImagen(int serie){

	switch(serie){
		case 1:
			puts("No se genero la imagen de la serie 1, la serie no converge.");
		break;
		case 2:
			if(series[1].converge && !series[1].seIndetermina){
				char *imagen = (char*) malloc(IMAGEN* sizeof(char) * 3);
				for (int i = 0; i < TAM; i++) {
	        		for (int j = 0; j < TAM; j++) {
	        			if(series[1].arregloImagen[i][j] < 9){
	        				int dato = series[1].arregloImagen[i][j]*250;
	        				imagen[3 * (i * TAM + j)] = i+j;
	            			imagen[3 * (i * TAM + j) + 1] = dato;
	            			imagen[3 * (i * TAM + j) + 2] = dato;
	        			}else{
		        			int dividido = series[1].arregloImagen[i][j]/3;
	        				imagen[3 * (i * TAM + j)] = i+j;
	            			imagen[3 * (i * TAM + j) + 1] = dividido;
	            			imagen[3 * (i * TAM + j)+ 2] = dividido;
	        			}
	        		}
	    		}
	    		escribirImagen("serie2.bmp", imagen);
			}
			else 
				puts("No se genero la imagen de la serie 2, la serie no converge.");
		break;
		case 3:
			if(series[2].converge && !series[2].seIndetermina){
				char *imagen = (char*) malloc(IMAGEN* sizeof(char) * 3);
	    		for (int i = 0; i < TAM; i++) {
	        		for (int j = 0; j < TAM; j++) {
	        			if(series[2].arregloImagen[i][j] < 9){
	        				int dato = series[2].arregloImagen[i][j]*250;
	        				imagen[3 * (i * TAM + j)] = i+j;
	            			imagen[3 * (i * TAM + j) + 1] = dato;
	            			imagen[3 * (i * TAM + j)+ 2] = dato;
	        			}else{
		        			int dividido = series[2].arregloImagen[i][j]/3;
	        				imagen[3 * (i * TAM + j)] = i+j;
	            			imagen[3 * (i * TAM + j) + 1] = dividido;
	            			imagen[3 * (i * TAM + j)+ 2] = dividido;
	        			}
	        		}
	    		}
	    		escribirImagen("serie3.bmp", imagen);
			}
			else
				puts("No se genero la imagen de la serie 3, la serie no converge.\n");
		break;
		default:
			puts("No existe la serie :C");
		break;
	}
}
