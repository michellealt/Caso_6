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
    
    // 1. CÓDIGO
    printf("Código de registro (1-15 caracteres): ");
    scanf("%15s", nuevo.codigo_registro);
    while(getchar() != '\n'); // Limpieza profunda del buffer

    // Validar si el código ya existe
    if (buscar_por_codigo(registros, *total, nuevo.codigo_registro) != -1) {
        printf("Error: registro duplicado. El codigo_registro %s ya existe.\n", nuevo.codigo_registro);
        return;
    }

    // 2. FECHA
    printf("Fecha (DD/MM/AAAA): ");
    scanf("%10s", nuevo.fecha);
    while(getchar() != '\n'); 

    // 3. CENTRO DE COSTO
    printf("Centro de costo (ej. M-101): ");
    scanf("%14s", nuevo.centro_costo);
    while(getchar() != '\n'); 

    // 4. TURNO
    printf("Turno (1, 2 o 3): ");
    if (scanf("%d", &nuevo.turno) != 1) {
        printf("Error: Entrada inválida.\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n'); 

    if (nuevo.turno < 1 || nuevo.turno > 3) {
        printf("Error: turno inválido.\n"); // Mensaje exacto caso de prueba 5
        return;
    }

    //  Validar duplicidad de (fecha, centro_costo, turno)
    if (validar_duplicado_triada(registros, *total, nuevo.fecha, nuevo.centro_costo, nuevo.turno) != -1) {
        printf("Error: registro duplicado. Ya existe un registro con esa fecha, centro de costo y turno.\n");
        return;
    }

    // 5. MATERIA PRIMA Y DESPERDICIO
    printf("Materia prima (kg): ");
    if (scanf("%f", &nuevo.materia_prima_kg) != 1) { while(getchar() != '\n'); return; }
    printf("Desperdicio (kg): ");
    if (scanf("%f", &nuevo.desperdicio_kg) != 1) { while(getchar() != '\n'); return; }
    while(getchar() != '\n'); 
    
    // El desperdicio NO puede ser mayor a la materia prima
    if (nuevo.desperdicio_kg > nuevo.materia_prima_kg) {
        printf("Error: valores fuera de rango.\n");
        return;
    }
    if (nuevo.materia_prima_kg < 0 || nuevo.desperdicio_kg < 0) {
        printf("Error: valores fuera de rango.\n");
        return;
    }

    // 6. TIEMPO Y UNIDADES
    printf("Tiempo (minutos): ");
    if (scanf("%d", &nuevo.tiempo_min) != 1) { while(getchar() != '\n'); return; }
    printf("Unidades producidas: ");
    if (scanf("%d", &nuevo.unidades_producidas) != 1) { while(getchar() != '\n'); return; }
    while(getchar() != '\n'); 

    if (nuevo.tiempo_min < 0 || nuevo.unidades_producidas < 0) {
        printf("Error: Tiempo o unidades no pueden ser negativos.\n");
        return;
    }

    // Guardar en memoria si pasó todos los filtros
    registros[*total] = nuevo;
    (*total)++;
    printf("Registro almacenado en memoria; mensaje de éxito.\n"); 
}

void listar_registros(const RegistroProduccion registros[], int total) {
    if (total == 0) {
        printf("\nNo hay registros que mostrar.\n");
        return;
    }

    printf("\n=========================================================================================\n");
    printf("%-7s | %-10s | %-10s | %-5s | %-10s | %-10s | %-8s\n", 
           "COD", "FECHA", "CENTRO", "TURNO", "MAT.PRIM", "DESPERD.", "REND(%)");
    printf("=========================================================================================\n");
    
    for (int i = 0; i < total; i++) {
        float rend = calcular_rendimiento(registros[i].materia_prima_kg, registros[i].desperdicio_kg);
        printf("%-7s | %-10s | %-10s | %-5d | %-10.1f | %-10.1f | %-6.1f%%\n",
               registros[i].codigo_registro, registros[i].fecha, registros[i].centro_costo,
               registros[i].turno, registros[i].materia_prima_kg, registros[i].desperdicio_kg, rend);
    }
    printf("=========================================================================================\n");
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
    scanf("%15s", codigo);
    while(getchar() != '\n');

    int idx = buscar_por_codigo(registros, total, codigo);
    if (idx == -1) {
        printf("Error: registro no encontrado.\n"); 
    } else {
        printf("\nRegistro encontrado:\n");
        listar_registros(&registros[idx], 1); 
    }
}

void actualizar_registro(RegistroProduccion registros[], int total) {
    char codigo[MAX_CODIGO];
    printf("\nIngrese el código del registro a actualizar: ");
    scanf("%15s", codigo);
    while(getchar() != '\n');

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
    
    printf("El registro se actualiza en memoria conservando el codigo_registro.\n"); 
}

void eliminar_registro(RegistroProduccion registros[], int *total) {
    char codigo[MAX_CODIGO];
    printf("\nIngrese el código del registro a eliminar: ");
    scanf("%15s", codigo);
    while(getchar() != '\n');

    int idx = buscar_por_codigo(registros, *total, codigo);
    if (idx == -1) {
        printf("Registro no encontrado.\n");
        return;
    }

    char conf;
    printf("¿Está seguro de eliminar el registro %s? (s/n): ", codigo);
    scanf(" %c", &conf);
    while(getchar() != '\n');

    if (conf == 's' || conf == 'S') {
        for (int i = idx; i < (*total) - 1; i++) {
            registros[i] = registros[i + 1];
        }
        (*total)--;
        printf("El registro se elimina y el listado se reordena.\n"); 
    }
}

void reporte_menor_desperdicio(const RegistroProduccion registros[], int total) {
    char centro[MAX_CENTRO];
    printf("\nCentro de costo a evaluar: ");
    scanf("%14s", centro);
    while(getchar() != '\n');

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
        printf("\n>>> Se indica el turno con menor desperdicio acumulado para ese centro: Turno %d (%.1f kg) <<<\n", turno_menor, min_desp); 
    } else {
        printf("No hay datos suficientes de este centro.\n");
    }
}

void limpiar_entrada(char *cadena) {
    cadena[strcspn(cadena, "\n")] = 0;
}