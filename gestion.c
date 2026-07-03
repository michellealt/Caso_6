#include <stdio.h>
#include <string.h>
#include "gestion.h"

void registrar_turno(RegistroProduccion registros[], int *total) {
    if (*total >= MAX_REGISTROS) {
        printf("Error: Capacidad maxima de memoria alcanzada.\n");
        return;
    }

    RegistroProduccion nuevo;
    printf("\n--- REGISTRAR DATOS DE TURNO ---\n");
    
    printf("Codigo de registro (1-15 caracteres): ");
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
        printf("Error: Turno invalido.\n");
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

void actualizar_registro(RegistroProduccion registros[], int total) {
    char codigo[MAX_CODIGO];
    printf("\nIngrese el código del registro a actualizar: ");
    fgets(codigo, MAX_CODIGO, stdin);
    codigo[strcspn(codigo, "\n")] = 0;

    int idx = buscar_por_codigo(registros, total, codigo);
    if (idx == -1) {
        printf("Registro no encontrado.\n");
        return;
    }

    printf("Modificando registro %s (El código no puede cambiarse).\n", codigo);
    printf("Nueva Materia Prima (kg): ");
    scanf("%f", &registros[idx].materia_prima_kg);
    printf("Nuevo Desperdicio (kg): ");
    scanf("%f", &registros[idx].desperdicio_kg);
    while(getchar() != '\n');
    
    printf("¡Registro actualizado en memoria!\n");
}

void eliminar_registro(RegistroProduccion registros[], int *total) {
    char codigo[MAX_CODIGO];
    printf("\nIngrese el código del registro a eliminar: ");
    fgets(codigo, MAX_CODIGO, stdin);
    codigo[strcspn(codigo, "\n")] = 0;

    int idx = buscar_por_codigo(registros, *total, codigo);
    if (idx == -1) {
        printf("Registro no encontrado.\n");
        return;
    }

    char conf;
    printf("¿Esta seguro de eliminar el registro %s? (s/n): ", codigo);
    scanf(" %c", &conf);
    while(getchar() != '\n');

    if (conf == 's' || conf == 'S') {
        for (int i = idx; i < (*total) - 1; i++) {
            registros[i] = registros[i + 1];
        }
        (*total)--;
        printf("Registro eliminado.\n");
    }
}
void reporte_menor_desperdicio(const RegistroProduccion registros[], int total) {
    char centro[MAX_CENTRO];
    printf("\nCentro de costo a evaluar: ");
    fgets(centro, MAX_CENTRO, stdin);
    centro[strcspn(centro, "\n")] = 0;

    float desp[4] = {0.0f, 0.0f, 0.0f, 0.0f}; 
    int conteo[4] = {0, 0, 0, 0};

    for (int i = 0; i < total; i++) {
        if (strcmp(registros[i].centro_costo, centro) == 0) {
            desp[registros[i].turno] += registros[i].desperdicio_kg;
            conteo[registros[i].turno]++;
        }
    }

    int turno_menor = -1;
    float min_desp = 1e9;

    for(int t = 1; t <= 3; t++) {
        if (conteo[t] > 0 && desp[t] < min_desp) {
            min_desp = desp[t];
            turno_menor = t;
        }
    }

    if (turno_menor != -1) {
        printf("\n>>> El turno con MENOR desperdicio en %s es el Turno %d (%.1f kg) <<<\n", centro, turno_menor, min_desp);
    } else {
        printf("No hay datos suficientes de este centro.\n");
    }
}