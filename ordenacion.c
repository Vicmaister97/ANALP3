/**
 *
 * Descripcion: Implementacion de funciones de ordenacion 
 *
 * Fichero: ordenacion.c
 * Autor: Alfonso Villar y Víctor García
 * Version: 3.2
 * Fecha: 4-11-2016
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "ordenacion.h"

/***************************************************/
/* Funcion: mergesort Fecha: 21/10/2016            */
/* Autores: Alfonso Villar y Victor Garcia         */
/*                                                 */
/* Entrada:   0 <= ip <= iu       tabla != NULL    */
/* int *tabla: Tabla con los numeros!=NULL         */
/* int ip: Posicion del primer elemento a ordenar  */
/* int iu: Posicion del ultimo elemento a ordenar  */
/*                                                 */
/* Salida: devuelve el numero de veces que se ha   */
/* ejecutado la OB si se ha ordenado la tabla o en */
/* caso de error devuelve ERR                      */
/***************************************************/

int mergesort(int* tabla, int ip, int iu){
	int m;
	int n;
	int ob = 0;

	if (ip > iu)
		return ERR;

	if (ip == iu)
		return OK;

	m = (int)(ip + iu) / 2;
	n = mergesort(tabla, ip, m);
	if (n == ERR)
		return ERR;

	ob += n;

	n = mergesort(tabla, m+1, iu);
	if (n == ERR)
		return ERR;

	ob += n;

	n = merge (tabla, ip, iu, m);

	ob += n;
	return ob;
}

/***************************************************/
/* Funcion: merge Fecha: 21/10/2016                */
/* Autores: Alfonso Villar y Victor Garcia         */
/*                                                 */
/* Entrada: 0 <= ip <= imedio <= iu   tabla != NULL*/
/* int *tabla: Tabla con los numeros!=NULL         */
/* int ip: Posicion del primer elemento a ordenar  */
/* int iu: Posicion del ultimo elemento a ordenar  */
/* int imedio: Posicion del elemento medio de la   */
/* tabla                                           */
/*                                                 */
/* Salida: devuelve el numero de veces que se ha   */
/* ejecutado la OB si se ha ordenado la tabla o en */
/* caso de error devuelve ERR                      */
/***************************************************/

int merge(int* tabla, int ip, int iu, int imedio){
	int i;
	int j;
	int k;
	int cont;
	int* tabla2;
	tabla2 = (int*)malloc((iu-ip+1)*sizeof(int));
	if (tabla2 == NULL)
		return ERR;

	i = ip;
	j = imedio + 1;
	k = 0;
	cont = 0;

	while (i <= imedio && j <= iu){
		cont ++;
		if (tabla[i] < tabla[j]){ /*OB del algoritmo*/
			tabla2[k] = tabla[i];
			i++;
		}
		else{
			tabla2[k] = tabla[j];
			j++;
		}
		k++;
	}

	if (i > imedio){ /*copia el resto de la tabla derecha*/
		while (j <= iu){
			tabla2[k] = tabla[j];
			j++;
			k++;
		}
	}
	
	else if (j > iu){ /*copia el resto de la tabla izquierda*/
		while (i <= imedio){
			tabla2[k] = tabla[i];
			i++;
			k++;
		}
	}

	for(i=ip, j = 0; i <= iu; i++, j++){
		tabla[i] = tabla2[j];
	}
	
	free(tabla2);

	return cont;
}

/***************************************************/
/* Funcion: quicksort Fecha: 4/11/2016             */
/* Autores: Alfonso Villar y Victor Garcia         */
/*                                                 */
/* Entrada:   0 <= ip <= iu       tabla != NULL    */
/* int *tabla: Tabla con los numeros!=NULL         */
/* int ip: Posicion del primer elemento a ordenar  */
/* int iu: Posicion del ultimo elemento a ordenar  */
/*                                                 */
/* Salida: devuelve el numero de veces que se ha   */
/* ejecutado la OB si se ha ordenado la tabla o en */
/* caso de error devuelve ERR                      */
/***************************************************/

int quicksort(int* tabla, int ip, int iu){
	int m;
	int *pos = NULL;
	int ob = 0;

	pos = (int *)malloc(sizeof(pos[0]));
	if (pos == NULL)
		return ERR;
	
	if (ip > iu){
		free (pos);
		return ERR;
	}

	if (ip == iu){
		free (pos);
		return ob;
	}

	else{
		ob = partir(tabla, ip, iu, pos);
		if (ob == ERR){
			free (pos);
			return ERR;
		}

		m = *pos;

		if (ip < m)
			ob += quicksort (tabla, ip, m-1);
		if (m+1 < iu)
			ob += quicksort (tabla, m+1, iu);
	}
	free (pos);
	return ob;
}

/***************************************************/
/* Funcion: quicksort_avg Fecha: 4/11/2016         */
/* Autores: Alfonso Villar y Victor Garcia         */
/*                                                 */
/* Entrada:   0 <= ip <= iu       tabla != NULL    */
/* int *tabla: Tabla con los numeros!=NULL         */
/* int ip: Posicion del primer elemento a ordenar  */
/* int iu: Posicion del ultimo elemento a ordenar  */
/*                                                 */
/* Salida: devuelve el numero de veces que se ha   */
/* ejecutado la OB si se ha ordenado la tabla o en */
/* caso de error devuelve ERR                      */
/***************************************************/

int quicksort_avg(int* tabla, int ip, int iu){
	int m;
	int *pos = NULL;
	int ob = 0;

	pos = (int *)malloc(sizeof(pos[0]));
	if (pos == NULL)
		return ERR;
	
	if (ip > iu){
		free (pos);
		return ERR;
	}

	if (ip == iu){
		free (pos);
		return ob;
	}

	else{
		ob = partir_avg(tabla, ip, iu, pos);
		if (ob == ERR){
			free (pos);
			return ERR;
		}

		m = *pos;

		if (ip < m)
			ob += quicksort (tabla, ip, m-1);
		if (m+1 < iu)
			ob += quicksort (tabla, m+1, iu);
	}
	free (pos);
	return ob;
}

/***************************************************/
/* Funcion: quicksort_stat Fecha: 4/11/2016        */
/* Autores: Alfonso Villar y Victor Garcia         */
/*                                                 */
/* Entrada:   0 <= ip <= iu       tabla != NULL    */
/* int *tabla: Tabla con los numeros!=NULL         */
/* int ip: Posicion del primer elemento a ordenar  */
/* int iu: Posicion del ultimo elemento a ordenar  */
/*                                                 */
/* Salida: devuelve el numero de veces que se ha   */
/* ejecutado la OB si se ha ordenado la tabla o en */
/* caso de error devuelve ERR                      */
/***************************************************/

int quicksort_stat(int* tabla, int ip, int iu){
	int m;
	int *pos = NULL;
	int ob = 0;

	pos = (int *)malloc(sizeof(pos[0]));
	if (pos == NULL)
		return ERR;
	
	if (ip > iu){
		free (pos);
		return ERR;
	}

	if (ip == iu){
		free (pos);
		return ob;
	}

	else{
		ob = partir_stat(tabla, ip, iu, pos);
		if (ob == ERR){
			free (pos);
			return ERR;
		}

		m = *pos;

		if (ip < m)
			ob += quicksort (tabla, ip, m-1);
		if (m+1 < iu)
			ob += quicksort (tabla, m+1, iu);
	}
	free (pos);
	return ob;
}

/***************************************************/
/* Funcion: partir Fecha: 4/11/2016                */
/* Autores: Alfonso Villar y Victor Garcia         */
/*                                                 */
/* Entrada:   0 <= ip <= iu       tabla != NULL    */
/* int *tabla: Tabla con los numeros!=NULL         */
/* int ip: Posicion del primer elemento a ordenar  */
/* int iu: Posicion del ultimo elemento a ordenar  */
/* int *pos:Puntero que recibe el pivote           */
/*                                                 */
/* Salida: devuelve el numero de veces que se ha   */
/* ejecutado la OB si se ha ordenado la tabla o en */
/* caso de error devuelve ERR                      */
/***************************************************/

int partir(int* tabla, int ip, int iu,int *pos){
	int m;
	int k;
	int aux;
	int i;
	int ob;

	ob = medio (tabla, ip, iu, pos);
	if (ob == ERR)
		return ERR;

	m = *pos;
	k = tabla[m];

	aux = tabla[ip];
	tabla[ip] = tabla[m];
	tabla[m] = aux;

	m = ip;

	for (i = ip +1; i <= iu; i++){
		if (tabla[i] < k){
			m++;
			aux = tabla[i];
	        tabla[i] = tabla[m];
	        tabla[m] = aux;
		}
		ob ++;
	}

	
	aux = tabla[ip];
	tabla[ip] = tabla[m];
	tabla[m] = aux;

	*pos = m;

	return ob;
}

/***************************************************/
/* Funcion: partir_avg Fecha: 4/11/2016            */
/* Autores: Alfonso Villar y Victor Garcia         */
/*                                                 */
/* Entrada:   0 <= ip <= iu       tabla != NULL    */
/* int *tabla: Tabla con los numeros!=NULL         */
/* int ip: Posicion del primer elemento a ordenar  */
/* int iu: Posicion del ultimo elemento a ordenar  */
/* int *pos:Puntero que recibe el pivote           */
/*                                                 */
/* Salida: devuelve el numero de veces que se ha   */
/* ejecutado la OB si se ha ordenado la tabla o en */
/* caso de error devuelve ERR                      */
/***************************************************/

int partir_avg(int* tabla, int ip, int iu,int *pos){
	int m;
	int k;
	int aux;
	int i;
	int ob;

	ob = medio_avg (tabla, ip, iu, pos);
	if (ob == ERR)
		return ERR;

	m = *pos;
	k = tabla[m];

	aux = tabla[ip];
	tabla[ip] = tabla[m];
	tabla[m] = aux;

	m = ip;

	for (i = ip +1; i <= iu; i++){
		if (tabla[i] < k){
			m++;
			aux = tabla[i];
	        tabla[i] = tabla[m];
	        tabla[m] = aux;
		}
		ob ++;
	}

	
	aux = tabla[ip];
	tabla[ip] = tabla[m];
	tabla[m] = aux;

	*pos = m;

	return ob;
}

/***************************************************/
/* Funcion: partir_stat Fecha: 4/11/2016           */
/* Autores: Alfonso Villar y Victor Garcia         */
/*                                                 */
/* Entrada:   0 <= ip <= iu       tabla != NULL    */
/* int *tabla: Tabla con los numeros!=NULL         */
/* int ip: Posicion del primer elemento a ordenar  */
/* int iu: Posicion del ultimo elemento a ordenar  */
/* int *pos:Puntero que recibe el pivote           */
/*                                                 */
/* Salida: devuelve el numero de veces que se ha   */
/* ejecutado la OB si se ha ordenado la tabla o en */
/* caso de error devuelve ERR                      */
/***************************************************/

int partir_stat(int* tabla, int ip, int iu,int *pos){
	int m;
	int k;
	int aux;
	int i;
	int ob;

	ob = medio_stat (tabla, ip, iu, pos);
	if (ob == ERR)
		return ERR;

	m = *pos;
	k = tabla[m];

	aux = tabla[ip];
	tabla[ip] = tabla[m];
	tabla[m] = aux;

	m = ip;

	for (i = ip +1; i <= iu; i++){
		if (tabla[i] < k){
			m++;
			aux = tabla[i];
	        tabla[i] = tabla[m];
	        tabla[m] = aux;
		}
		ob ++;
	}

	
	aux = tabla[ip];
	tabla[ip] = tabla[m];
	tabla[m] = aux;

	*pos = m;

	return ob;
}

/***************************************************/
/* Funcion: medio Fecha: 4/11/2016                 */
/* Autores: Alfonso Villar y Victor Garcia         */
/*                                                 */
/* Entrada:   0 <= ip <= iu       tabla != NULL    */
/* int *tabla: Tabla con los numeros!=NULL         */
/* int ip: Posicion del primer elemento a ordenar  */
/* int iu: Posicion del ultimo elemento a ordenar  */
/* int *pos:Puntero que recibe el pivote           */
/*                                                 */
/* Salida: Devuelve la posicion del pivote         */
/***************************************************/

int medio(int *tabla, int ip, int iu,int *pos){
	*pos = ip;
	return 0;
}


/***************************************************/
/* Funcion: medio_avg Fecha: 4/11/2016             */
/* Autores: Alfonso Villar y Victor Garcia         */
/*                                                 */
/* Entrada:   0 <= ip <= iu       tabla != NULL    */
/* int *tabla: Tabla con los numeros!=NULL         */
/* int ip: Posicion del primer elemento a ordenar  */
/* int iu: Posicion del ultimo elemento a ordenar  */
/* int *pos:Puntero que recibe el pivote           */
/*                                                 */
/* Salida: Devuelve la posicion del pivote         */
/***************************************************/

int medio_avg(int *tabla, int ip, int iu,int *pos){
	*pos = ip;
	return (int) (ip+iu)/2;
}


/***************************************************/
/* Funcion: medio_stat Fecha: 4/11/2016            */
/* Autores: Alfonso Villar y Victor Garcia         */
/*                                                 */
/* Entrada:   0 <= ip <= iu       tabla != NULL    */
/* int *tabla: Tabla con los numeros               */
/* int ip: Posicion del primer elemento a ordenar  */
/* int iu: Posicion del ultimo elemento a ordenar  */
/*                                                 */
/* Salida: Devuelve la posicion del pivote         */
/***************************************************/

int medio_stat(int *tabla, int ip, int iu,int *pos){
	int m = (int) (ip+iu)/2;
	if (ip < m) {
		if (m < iu){
			*pos = m;
			return m;
		}
		else { 
			if (ip < iu){
				*pos = iu;
				return iu;
			}
			*pos = ip;
			return ip;
		}}
	else {
		if (iu < m){
			*pos = m;
			return m;
		}
		else {
			if (ip < iu){
				*pos = ip;
				return ip;
			}
			*pos = iu;
			return iu;
		}}
	}