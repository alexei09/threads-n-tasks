#include <stdio.h>
#include <pthread.h>

// Estructura para pasar información a los hilos
typedef struct {
    int fila;
    int (*matriz1)[3];
    int (*matriz2)[3];
    int (*resultado)[3];
} ThreadArgs;

// Función que multiplicará una fila de la matriz
void* multiplicar_fila(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    
    // Procedimiento que muestra el cálculo de cada elemento en la fila
    for (int j = 0; j < 3; j++) {
        args->resultado[args->fila][j] = 0;
        printf("Hilo %d - Calculando fila %d, columna %d: ", args->fila + 1, args->fila + 1, j + 1);
        for (int k = 0; k < 3; k++) {
            printf("%d * %d", args->matriz1[args->fila][k], args->matriz2[k][j]);
            args->resultado[args->fila][j] += args->matriz1[args->fila][k] * args->matriz2[k][j];
            if (k < 2) {
                printf(" + ");
            }
        }
        printf(" = %d\n", args->resultado[args->fila][j]);  // Mostrar el resultado de la multiplicación para cada celda
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[3];
    ThreadArgs args[3];
    int matriz1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int matriz2[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    int resultado[3][3] = {0};  // Matriz para almacenar el resultado

    // Imprimir la matriz 1
    printf("Matriz 1:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matriz1[i][j]);
        }
        printf("\n");
    }

    // Imprimir la matriz 2
    printf("\nMatriz 2:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matriz2[i][j]);
        }
        printf("\n");
    }

    // Crear hilos para multiplicar cada fila de la matriz
    printf("\n--- Procedimiento de multiplicación ---\n");
    for (int i = 0; i < 3; ++i) {
        args[i].fila = i;
        args[i].matriz1 = matriz1;
        args[i].matriz2 = matriz2;
        args[i].resultado = resultado;
        pthread_create(&hilos[i], NULL, multiplicar_fila, (void*)&args[i]);
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < 3; ++i) {
        pthread_join(hilos[i], NULL);
    }

    // Imprimir la matriz resultante
    printf("\nResultado de la multiplicación de matrices:\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%d ", resultado[i][j]);
        }
        printf("\n");
    }

    return 0;
}
