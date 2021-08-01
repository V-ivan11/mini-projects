/*
    Verduzco Lozano Iván Antonio
    N Reinas con generado de imagen
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Numero de reinas
#define N 6
//Pixeles de la Celda
#define CELDA 40

void apartarMemoria(int***, int, int);
void eliminarReina(int**, int, int);
void escribirImagen(char*, char*);
int esValida(int **, int, int);
void generarMatriz(int **, int **);
void generarImagen(int **, int *);
void imprimirTablero(int**, int*);
void ingresarSubcomp(int **, int, int, int, int, int, int);
int muerte(int *);
void nReinas(int**, int, int, int, int*, int*);
int reinaAnterior(int**, int);

int **matrizImagen = NULL;
char *imagen = NULL;

//PixelArt de la Reina
int pxQ[17][24]=
{
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,1,1,5,5,5,5,5,5,5,5,5,5,5,5,1,1,0,0,0,0},
    {0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0},
    {0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0},
    {0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0},
    {0,0,0,1,5,5,5,1,1,5,5,5,5,5,5,1,1,5,5,5,1,0,0,0},
    {0,0,1,5,5,1,1,0,1,5,5,5,5,5,5,1,0,1,1,5,5,1,0,0},
    {0,1,1,5,1,0,0,0,0,1,5,5,5,5,1,0,0,0,0,1,5,1,1,0},
    {1,5,5,1,0,0,0,0,0,1,5,5,5,5,1,0,0,0,0,0,1,5,5,1},
    {1,5,5,1,0,0,0,0,0,0,1,5,5,1,0,0,0,0,0,0,1,5,5,1},
    {0,1,1,0,0,0,0,0,0,0,1,5,5,1,0,0,0,0,0,0,0,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,5,5,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,5,5,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0}
};

int TAM = CELDA*N;

int main(int argc, char *argv[]){
    int **tablero = NULL;
    int *acciones = NULL;
    int i = 0, j = 0, configuraciones = 0;
    int *c = &configuraciones;

    //Apartado de Memoria
    apartarMemoria(&matrizImagen, TAM, TAM);
    apartarMemoria(&tablero, N, N);

    imagen = (char*) malloc(TAM*TAM*3 *sizeof(char));
    acciones = (int*)malloc(N*sizeof(int));
    for(i = 0; i < N; i++){
        tablero[i] = (int*)malloc(N*sizeof(int));
        acciones[i] = 0;
    }

    //Llamado del algoritmo
    nReinas(tablero, 0, 0, 0, acciones, c);

    //Desplegado de número de configuraciones
    printf("Total: %d\n",configuraciones);

    free(tablero);
    free(acciones);
    free(matrizImagen);
    free(imagen);
    return 0;
}

void apartarMemoria(int ***matriz, int tam1, int tam2){
    int **arr = NULL;
    int i = 0;

    arr = (int**) malloc(tam1 * sizeof(int*));

    for (i = 0; i < TAM; i++){
        *(arr + i) = (int*) malloc(tam2 * sizeof(int));
    }
    
    if (arr == NULL)
      return;
    
    *matriz = arr;
}

void eliminarReina(int **tablero, int fila, int columna){
    tablero[fila][columna] = 0;
}

void escribirImagen(char *filename, char *rgb) {
    int i = 0, j = 0, z = 0, index = 0;
    int alto = TAM;
    int ancho = TAM;
    //Tamaño del arreglo unidimiensional con la matriz imagen dentro
    int tamanoImagen = TAM*TAM * 3;
    char *datosImagen = (char *) malloc(tamanoImagen * sizeof(char));
    char tag[] = { 'B', 'M' };
    FILE *imagen = fopen(filename, "w+");

    for (i = 0; i < alto; i++) {
        for (j = 0; j < ancho; j++) {
            // RGB
            for (z = 0; z < 3; z++) {
                index = 3 * TAM * i + 3 * j + z;
                //Guarda los datos en el arreglo unidimensional
                datosImagen[index] = rgb[3*(i * ancho + j) + (2 - z)];
            }
        }
    }
    int header[] = {
        0, 0, 0x36, 0x28, ancho, alto, 0x180001, 
        0, 0, 0x002E23, 0x002E23, 0, 0
    };
    header[0] = sizeof(tag) + sizeof(header) + tamanoImagen;
    
    fwrite(&tag, sizeof(tag), 1, imagen);
    fwrite(&header, sizeof(header), 1, imagen);
    fwrite(datosImagen, tamanoImagen * sizeof(char), 1, imagen);
    fclose(imagen);
    free(datosImagen);
}

//Verifica si se puede poner la Reina en la celda
int esValida(int **tablero, int fila, int columna){
//Va buscando en columnas izquierdas
    int i = columna-1, d1 = fila-1, d2 = fila+1;

    while(i >= 0){
        if(tablero[fila][i])
            return 0;
        i--;
    }

    i = columna-1;
    while(i >= 0 && d1 >= 0){
        if(tablero[d1][i])
            return 0;
        i--; d1--;
    }

    i = columna-1;
    while(i >= 0 && d2 <= (N-1)){
        if(tablero[d2][i])
            return 0;
        i--;d2++;
    }

    return 1;
}

void generarMatriz(int **matriz, int **tablero){
//Genera la matriz principal para la imagen a partir del tablero

    int i = 0, j = 0, x = 0, y = 0, cc = 0;
    // CC para ir intercalando los colores del tablero
    for(i = 0; i < N; i++){
        cc--;
        for(j = 0; j < N; j++){
            //Cambiar los valores entre (1,0) y (3,2) para un cambio
            //de color del tablero, negro-blanco, personalizado
            if(cc % 2 == 0)
                ingresarSubcomp(matriz, 3, x, y, CELDA, CELDA, cc);
            else
                ingresarSubcomp(matriz, 2, x, y, CELDA, CELDA, cc);

            if(tablero[i][j] == 1)
                ingresarSubcomp(matriz, 5, x+11, y+8, 17, 24, cc);

            y += CELDA;
            cc++;
        }
        y = 0;
        x += CELDA;
    }
}

void generarImagen(int **tablero, int *c){
    //Le da color mediante RGB a la matriz de la imagen y genera la
    //imagen con el nombre del numero de configuración

    int i = 0, j = 0, r = 0, g = 0, b = 0;
    char num[5];
    char nombreArchivo[50];
    char *formato= ".bmp";
    sprintf(num, "%d", *(c));
    strcpy(nombreArchivo, num);
    strcat(nombreArchivo, formato);
    for(i = 0; i < TAM; i++){
        for(j = 0; j < TAM; j++){
            switch(matrizImagen[i][j]){
                case 0: //Negro
                    r = 0; g = 0; b = 0;
                break;
                case 1: //Blanco
                    r = 255; g = 255; b = 255;
                break;
                case 2: //Oscuro
                    r = 230; g = 250; b = 180;
                break;
                case 3: //Leve
                    r = 15; g = 80; b = 15;
                break;
                case 4: //Amarrillo
                    r = 255; g = 255; b = 0;
                break;
            }
            imagen[3 * (i * TAM + j)] = r;
            imagen[3 * (i * TAM + j) + 1] = g;
            imagen[3 * (i * TAM + j)+ 2] = b;
        }
    }

    escribirImagen(nombreArchivo, imagen);
}

void imprimirTablero(int**tablero, int *c){
    //imprime en la consola el tablero de la configuración actual
    int i = 0, j = 0;
    printf("Configuracion No. %d\n\n", *(c));
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            if(tablero[i][j])
                printf("[Q]");
            else
                printf("[ ]");
        }
        printf("\n");
    }
    printf("\n");
}

//Introduce los valores correspondientes de la celda a la matriz imagen
void ingresarSubcomp(int **matriz, int valor, int x, int y, int tamx, int tamy, int cc){
    int i = 0, j = 0, a = 0, b = 0;
    if(valor != 5){ //Solo celda
        for(a = x, i = 0; i < tamx; i++, a++){
            for(b = y, j = 0; j < tamy; j++, b++){
                matriz[a][b] = valor;
            }
        }
    }else{//Hay una reina
        for(a = x, i = 0; i < tamx; i++, a++){
            for(b = y, j = 0; j < tamy; j++, b++){
                if(pxQ[i][j] == 0){//Pone el fondo que debe de ir
                    if(cc % 2 == 0){
                        matriz[a][b] = 3;
                    }else{
                        matriz[a][b] = 2;
                    }
                }else{//Pone los colores del PixelArt de la Reina
                    matriz[a][b] = pxQ[i][j]-1;
                }
                
            }
        }
    }   
}

//Algunas acciones te llevan a la muerte
int muerte(int *acciones){
    //La implicada para parar el algoritmo de las N reinas
    //Si ya se paso por la última fila todas las columnas regresa muerte
    int i = 0, aux = 0;
    for(i = 1; i < N; i++){
        aux = acciones[i];
        if(aux != acciones[i-1] || aux != N-1)
            return 0;
    }
    return 1;
}

void nReinas(int **tablero, int columna, int fila, int q, int *acciones, int *c){
    for(fila = fila; fila < N; fila++){
        if(columna == 0 && fila == N-1){
            acciones[0] = N-1;
        }
        //Comienza la muerte
        if(acciones[0] == N-1 && (acciones[columna]<fila && acciones[columna-1])){
            acciones[columna] = fila;
        }
        if(esValida(tablero, fila, columna)){//Pone una reina
            tablero[fila][columna] = 1;
            if(q == N-1){//Si ya hay N en el tablero
                (*c)++;
                imprimirTablero(tablero, c);
                generarMatriz(matrizImagen, tablero);
                generarImagen(tablero, c);
                eliminarReina(tablero, fila, columna);
                //Elimina la última reina
                nReinas(tablero, columna, fila+1, q-1, acciones, c);
                return;
            }else{//Sigue a la siguiente columna
                nReinas(tablero, columna+1, 0, q+1, acciones, c);
            }
        }else{//No es valido, pone 0 en el tablero
            tablero[fila][columna] = 0;
        }
    }
    if(muerte(acciones)) return; //F
    else //Regresa a la anterior columna
        eliminarReina(tablero, reinaAnterior(tablero, columna-1), columna-1);
}

int reinaAnterior(int **tablero, int columna){
    //Busca en la columna en que fila esa la reina y lo retorna
    int i = 0;
    while(tablero[i][columna] == 0)
        i++;
    return i;
}