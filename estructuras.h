/*
 * estructuras.h
 *
 *  Created on: 12 abr. 2021
 *      Author: eneko
 */

#ifndef ESTRUCTURAS_H_
#define ESTRUCTURAS_H_

typedef struct {
	char *nombre;
} Seccion;

typedef struct {
	char *nombre;
	Seccion sec;
	int stock;
	float precio;
} Producto;

typedef struct {
	Seccion sec;
	int porcentaje;
} Oferta;


#endif /* ESTRUCTURAS_H_ */
