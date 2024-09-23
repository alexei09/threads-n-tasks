#include <stdio.h>
#include <pthread.h>

// Estructura para pasar datos a los hilos
typedef struct {
    int id;
    int inicio;
    int fin;
    long resultado;
} ThreadArgs;

// Función que sumará los números en el intervalo
void* sumar_intervalo(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    args->resultado = 0;
    for (int i = args->inicio; i <= args->fin; i++) {
        args->resultado += i;
    }
    printf("Hilo pesado %d - Suma de %d a %d es: %ld\n", args->id, args->inicio, args->fin, args->resultado);
    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[3];  // Definimos 3 hilos pesados
    ThreadArgs args[3];  // Estructura para pasar argumentos a los hilos

    // Definimos los intervalos de números
    int intervalos[][2] = {{1, 100}, {101, 200}, {201, 300}};

    // Crear hilos pesados
    for (int i = 0; i < 3; ++i) {
        args[i].id = i + 1;
        args[i].inicio = intervalos[i][0];
        args[i].fin = intervalos[i][1];
        pthread_create(&hilos[i], NULL, sumar_intervalo, (void*)&args[i]);
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < 3; ++i) {
        pthread_join(hilos[i], NULL);
    }

    return 0;
}
