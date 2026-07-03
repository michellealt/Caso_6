#include "produccion.h"

float calcular_rendimiento(float mp, float desp) {
    if (mp > 0) {
        return ((mp - desp) / mp) * 100.0f; // Fórmula oficial: ((MP - DESP) / MP) * 100
    }
    return 0.0f;
}