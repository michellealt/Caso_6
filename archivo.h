#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include "produccion.h"

int cargar_datos(RegistroProduccion registros[], int *total);
int guardar_datos(const RegistroProduccion registros[], int total);

#endif