#include <stdio.h>
#include <pthread.h>
#include <math.h>

// Estructura para pasar información a los hilos
typedef struct {
    int base;
    int exponente;
    double resultado;
} ThreadArgs;

// Función que calculará la potencia
void* calcular_potencia(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    args->resultado = pow(args->base, args->exponente);
    printf("Hilo ligero - %d^%d = %.0f\n", args->base, args->exponente, args->resultado);
    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[3];
    ThreadArgs args[3];
    
    // Bases y exponentes para los cálculos
    int bases[] = {2, 3, 5};
    int exponentes[] = {8, 5, 3};

    // Crear hilos ligeros para calcular potencias
    for (int i = 0; i < 3; ++i) {
        args[i].base = bases[i];
        args[i].exponente = exponentes[i];
        pthread_create(&hilos[i], NULL, calcular_potencia, (void*)&args[i]);
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < 3; ++i) {
        pthread_join(hilos[i], NULL);
    }

    return 0;
}
