#ifndef PRODUCCION_H
#define PRODUCCION_H

#define MAX_REGISTROS 100
#define MAX_CODIGO 16
#define MAX_FECHA 11
#define MAX_CENTRO 15

typedef struct {
    char codigo_registro[MAX_CODIGO];   
    char fecha[MAX_FECHA];               
    char centro_costo[MAX_CENTRO];       
    int turno;                           
    float materia_prima_kg;             
    float desperdicio_kg;                
    int tiempo_min;                      
    int unidades_producidas;             
} RegistroProduccion;

// Declaración de la función matemática de rendimiento
float calcular_rendimiento(float mp, float desp);

#endif