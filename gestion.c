#include <stdio.h>
#include <string.h>
#include "gestion.h"

void registrar_turno(RegistroProduccion registros[], int *total) {
    if (*total >= MAX_REGISTROS) {
        printf("Error: Capacidad máxima de memoria alcanzada.\n");
        return;
    }

    RegistroProduccion nuevo;
    printf("\n--- REGISTRAR DATOS DE TURNO ---\n");
    
    printf("Código de registro (1-15 caracteres): ");
    fgets(nuevo.codigo_registro, MAX_CODIGO, stdin);
    limpiar_entrada(nuevo.codigo_registro);

    printf("Fecha (DD/MM/AAAA): ");
    fgets(nuevo.fecha, MAX_FECHA, stdin);
    limpiar_entrada(nuevo.fecha);

    printf("Centro de costo: ");
    fgets(nuevo.centro_costo, MAX_CENTRO, stdin);
    limpiar_entrada(nuevo.centro_costo);

    printf("Turno (1, 2 o 3): ");
    scanf("%d", &nuevo.turno);
    while(getchar() != '\n');

    if (nuevo.turno < 1 || nuevo.turno > 3) {
        printf("Error: Turno inválido.\n");
        return;
    }

    printf("Materia prima (kg): ");
    scanf("%f", &nuevo.materia_prima_kg);
    printf("Desperdicio (kg): ");
    scanf("%f", &nuevo.desperdicio_kg);
    
    // Validación de rangos obligatorios
    if (nuevo.materia_prima_kg < 0 || nuevo.desperdicio_kg < 0 || nuevo.desperdicio_kg > nuevo.materia_prima_kg) {
        printf("Error: Valores de materia prima o desperdicio fuera de rango.\n");
        while(getchar() != '\n');
        return;
    }

    printf("Tiempo (minutos): ");
    scanf("%d", &nuevo.tiempo_min);
    printf("Unidades producidas: ");
    scanf("%d", &nuevo.unidades_producidas);
    while(getchar() != '\n');

    if (nuevo.tiempo_min < 0 || nuevo.unidades_producidas < 0) {
        printf("Error: Tiempo o unidades no pueden ser negativos.\n");
        return;
    }

    registros[*total] = nuevo;
    (*total)++;
    printf("¡Registro agregado exitosamente en memoria!\n");
}

void listar_registros(const RegistroProduccion registros[], int total) {
    if (total == 0) {
        printf("\nNo hay registros que mostrar.\n");
        return;
    }

    printf("\n-\n");
    printf("%-7s | %-10s | %-10s | %-5s | %-10s | %-10s | %-8s\n", 
           "COD", "FECHA", "CENTRO", "TURNO", "MAT.PRIM", "DESPERD.", "REND(%)");
    printf("\n");
    
    for (int i = 0; i < total; i++) {
        float rend = calcular_rendimiento(registros[i].materia_prima_kg, registros[i].desperdicio_kg);
        printf("%-7s | %-10s | %-10s | %-5d | %-10.1f | %-10.1f | %-7.1f%%\n",
               registros[i].codigo_registro, registros[i].fecha, registros[i].centro_costo,
               registros[i].turno, registros[i].materia_prima_kg, registros[i].desperdicio_kg, rend);
    }
    printf("\n");
}

void limpiar_entrada(char *cadena) {
    cadena[strcspn(cadena, "\n")] = 0;
}
int buscar_por_codigo(const RegistroProduccion registros[], int total, const char *codigo) {
    for (int i = 0; i < total; i++) {
        if (strcmp(registros[i].codigo_registro, codigo) == 0) return i;
    }
    return -1;
}

int validar_duplicado_triada(const RegistroProduccion registros[], int total, const char *fecha, const char *centro, int turno) {
    for (int i = 0; i < total; i++) {
        if (strcmp(registros[i].fecha, fecha) == 0 &&
            strcmp(registros[i].centro_costo, centro) == 0 &&
            registros[i].turno == turno) {
            return i; 
        }
    }
    return -1;
}

void buscar_registro(const RegistroProduccion registros[], int total) {
    char codigo[MAX_CODIGO];
    printf("\nIngrese el código exacto a buscar: ");
    fgets(codigo, MAX_CODIGO, stdin);
    codigo[strcspn(codigo, "\n")] = 0;

    int idx = buscar_por_codigo(registros, total, codigo);
    if (idx == -1) {
        printf("Registro no encontrado.\n");
    } else {
        printf("\nRegistro encontrado:\n");
        listar_registros(&registros[idx], 1);
    }
}