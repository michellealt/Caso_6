
#include <stdio.h>
#include <string.h>
#include "archivo.h"

#define ARCHIVO_NOMBRE "produccion_turnos.csv"

int cargar_datos(RegistroProduccion registros[], int *total) {
    FILE *f = fopen(ARCHIVO_NOMBRE, "r");
    if (!f) return 0;

    char linea[256];
    if (!fgets(linea, sizeof(linea), f)) { 
        fclose(f);
        return 0;
    }

    *total = 0;
    while (fgets(linea, sizeof(linea), f) && *total < MAX_REGISTROS) {
        RegistroProduccion r;
        linea[strcspn(linea, "\n")] = 0;

        int leidos = sscanf(linea, "%[^;];%[^;];%[^;];%d;%f;%f;%d;%d", 
                            r.codigo_registro, r.fecha, r.centro_costo,
                            &r.turno, &r.materia_prima_kg, &r.desperdicio_kg,
                            &r.tiempo_min, &r.unidades_producidas);

        if (leidos == 8) {
            registros[*total] = r;
            (*total)++;
        }
    }
    fclose(f);
    return 1;
}

int guardar_datos(const RegistroProduccion registros[], int total) {
    FILE *f = fopen(ARCHIVO_NOMBRE, "w");
    if (!f) return 0;

    // CORRECCIÓN: Cabecera con comas según el enunciado del Caso 6
    fprintf(f, "codigo_registro,fecha,centro_costo,turno,materia_prima_kg,desperdicio_kg,tiempo_min,unidades_producidas\n");

    for (int i = 0; i < total; i++) {
        // Los registros sí se mantienen separados por punto y coma
        fprintf(f, "%s;%s;%s;%d;%.1f;%.1f;%d;%d\n",
                registros[i].codigo_registro, registros[i].fecha, registros[i].centro_costo,
                registros[i].turno, registros[i].materia_prima_kg, registros[i].desperdicio_kg,
                registros[i].tiempo_min, registros[i].unidades_producidas);
    }
    fclose(f);
    return 1;
}