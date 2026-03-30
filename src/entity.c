#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/entity.h"

/* =========================================================
 * entity.c
 * Implementarea ciclului de viață al entității și a funcțiilor
 * de conversie.
 * ========================================================= */

/* ----------------------------------------------------------
 * Funcții de conversie
 * ---------------------------------------------------------- */

const char *entity_type_to_str(EntityType type)
{
    /* TODO: returnează șirul corespunzător fiecărei valori enum */
    (void)type;
    return "UNKNOWN";
}

EntityType str_to_entity_type(const char *str)
{
    /* TODO: compară str cu numele cunoscute și returnează enum-ul */
    (void)str;
    return (EntityType)-1;
}

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

Entity *entity_create(const char *name, EntityType type, int id)
{
    /* TODO: alocă Entity, duplică name, atribuie câmpurile */
    (void)name;
    (void)type;
    (void)id;
    return NULL;
}

void entity_free(Entity *e)
{
    /* TODO: eliberează name, apoi structura */
    (void)e;
}

/* ----------------------------------------------------------
 * Afișare
 * ---------------------------------------------------------- */

void entity_print(const Entity *e)
{
    /* TODO: afișează "<id> <name> <TYPE>" */
    (void)e;
}
