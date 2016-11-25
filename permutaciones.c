/**
 *
 * Descripcion: Implementacion de funciones de generacion de permutaciones
 *
 * Fichero: permutaciones.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2016
 *
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "permutaciones.h"

/***************************************************/
/* Funcion: aleat_num Fecha: 30/09/2016            */
/* Autores: Alfonso Villar y Victor Garcia         */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:  0 <= inf <= sup                       */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/*                                                 */
/* Salida:                                         */
/* int: numero aleatorio                           */
/***************************************************/
int aleat_num(int inf, int sup)
{
	assert(inf <= sup);
	return inf + rand() % (sup - inf + 1);
}

/***************************************************/
/* Funcion: genera_perm Fecha: 30/09/2016          */
/* Autores: Alfonso Villar y Victor Garcia         */
/*                                                 */
/* Rutina que genera una permutacion               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:      0 < n                            */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/*                                                 */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */
/***************************************************/
int* genera_perm(int n)
{
	int i;	
	int* perm = (int *) malloc(n * sizeof(perm[0]));

	if (perm == NULL) 
		return NULL;

	for (i = 0; i < n; i++) 
		perm[i] = i + 1;

	for (i = 0; i < n; i++){
		int aux = perm[i];
		int ran = aleat_num(i, n - 1);
		perm[i] = perm[ran]; /*Hacemos un swap iterativo entre cada elemento de la tabla y otro en una posición aleatoria*/
		perm[ran] = aux;
	}

	return perm;	
}

/***************************************************/
/* Funcion: genera_permutaciones Fecha: 30/09/2016 */
/* Autores: Alfonso Villar y Victor Garcia         */
/*                                                 */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias de tamanio elementos                 */
/*                                                 */
/* Entrada:   0 < n_perms && 0 < tamanio           */
/* int n_perms: Numero de permutaciones            */
/* int tamanio: Numero de elementos de cada        */
/* permutacion                                     */
/*                                                 */
/* Salida:                                         */
/* int**: Array de punteros a enteros              */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */
/***************************************************/
int** genera_permutaciones(int n_perms, int tamanio)
{
	int i;
	int** resul = (int **) malloc(n_perms * sizeof (resul[0]));

	if (resul == NULL)
		return NULL;

	for (i = 0; i < n_perms; i++)
		if ((resul[i] = genera_perm(tamanio)) == NULL){
			free (resul);
			return NULL;
			}
	return resul;
}