#ifndef GESTION_H
#define GESTION_H

#include "produccion.h"

void registrar_turno(RegistroProduccion registros[], int *total);
void listar_registros(const RegistroProduccion registros[], int total);
void limpiar_entrada(char *cadena);

#endif
int buscar_por_codigo(const RegistroProduccion registros[], int total, const char *codigo);
int validar_duplicado_triada(const RegistroProduccion registros[], int total, const char *fecha, const char *centro, int turno);
void buscar_registro(const RegistroProduccion registros[], int total);

void actualizar_registro(RegistroProduccion registros[], int total);
void eliminar_registro(RegistroProduccion registros[], int *total);