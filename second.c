#include <stdio.h>
#include <pthread.h>

// Estructura para pasar datos a los hilos
typedef struct {
    int id;
    int numero;
    long resultado;
} ThreadArgs;

// Función que calculará el factorial
void* calcular_factorial(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    args->resultado = 1;
    for (int i = 1; i <= args->numero; i++) {
        args->resultado *= i;
    }
    printf("Hilo ligero %d - Factorial de %d es: %ld\n", args->id, args->numero, args->resultado);
    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[3];  // Definimos 3 hilos
    ThreadArgs args[3];  // Estructura para pasar argumentos a los hilos

    int numeros[] = {5, 7, 10};  // Números para los cuales calcularemos el factorial

    // Crear hilos ligeros
    for (int i = 0; i < 3; ++i) {
        args[i].id = i + 1;
        args[i].numero = numeros[i];
        pthread_create(&hilos[i], NULL, calcular_factorial, (void*)&args[i]);
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < 3; ++i) {
        pthread_join(hilos[i], NULL);
    }

    return 0;
}
