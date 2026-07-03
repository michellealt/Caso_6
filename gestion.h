#ifndef GESTION_H
#define GESTION_H

#include "produccion.h"

void registrar_turno(RegistroProduccion registros[], int *total);
void listar_registros(const RegistroProduccion registros[], int total);
void limpiar_entrada(char *cadena);

#endif