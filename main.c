#include <stdio.h>
#include "produccion.h"
#include "gestion.h"
#include "archivo.h"

int main() {
    RegistroProduccion registros[MAX_REGISTROS];
    int total_registros = 0;
    int opcion;

    cargar_datos(registros, &total_registros); // Carga automática al arrancar

    do {
        printf("\n--- CONTROL DE PRODUCCIÓN POR CENTROS ---\n");
        printf("1. Registrar turno\n2. Listar registros\n3. Buscar registro\n");
        printf("4. Actualizar registro\n5. Eliminar registro\n6. Reporte eficiencia\n");
        printf("7. Guardar cambios\n8. Salir (Guardado automático)\n");
        printf("Seleccione una opción: ");
        
        if (scanf("%d", &opcion) != 1) {
            while(getchar() != '\n');
            continue;
        }
        while(getchar() != '\n');

        switch(opcion) {
            case 1: registrar_turno(registros, &total_registros); break;
            case 2: listar_registros(registros, total_registros); break;
            case 3: buscar_registro(registros, total_registros); break;
            case 4: actualizar_registro(registros, total_registros); break;
            case 5: eliminar_registro(registros, &total_registros); break;
            case 6: reporte_menor_desperdicio(registros, total_registros); break;
            case 7: guardar_datos(registros, total_registros); printf("¡Cambios guardados con exito!\n"); break;
            case 8: guardar_datos(registros, total_registros); printf("Guardado automático completo. ¡Adios!\n"); break;
        }
    } while (opcion != 8);

    return 0;
}