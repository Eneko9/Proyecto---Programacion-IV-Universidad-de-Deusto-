/*
 * menu.c
 *
 *  Created on: 2 abr. 2021
 *      Author: eneko
 */

#include <stdio.h>
#include "menu.h"
#include <stdlib.h>
#include "utils.h"
#include <sys/stat.h>
#include "estructuras.h"

//	Constantes definidas en el programa
#define MAX_NomSec 30
#define MAX_NomProd 30
#define MAX_DescProd 100

//	funcion que pregunta si se quiere seguir operando o salir.
void preguntarSalida();

//funcion que comprueba si un fichero existe o no.
int existenciaFic(char *fichero);

//funcion que libera memoria de una seccion.
void freeSeccion(Seccion *sec);

//funcion que libera memoria de un producto.
void freeProducto(Producto *prod);

//funcion que libera memoria de una oferta.
void freeOferta(Oferta *ofr);

void menu() {
	//Se imprime el menu
	fflush(stdout);
	char *opciones[] = { "Añadir producto", "Añadir sección",
			"Eliminar sección", "Añadir oferta" };
	for (int i = 0; i < 4; i++) {
		printf("\n\t|%i.%s", i + 1, opciones[i]);
	}
	printf("\n\tPulsar 'q' para salir\n");
	printf("\tElija su opción: ");

	char c;
	fflush(stdin);
	scanf("%c", &c);
	printf("%c", c);

	//	varias opciones según lo que elija y que función quiere realizar
	//	opción 1: añadir un nuevo producto.
	if (c == '1') {
		fflush(stdin);
		printf("\n\n\tSección a la que quieres agregar el producto: ");
		Seccion sec;
		sec.nombre = malloc(sizeof(char) * (MAX_NomSec));
		fgets(sec.nombre, MAX_NomSec, stdin);
		sscanf(sec.nombre, "%s", sec.nombre);
		printf("%s", sec.nombre);

		printf("\n\tNombre del producto: ");
		Producto prod;
		prod.nombre = malloc(sizeof(char) * (MAX_NomProd));
		fgets(prod.nombre, MAX_NomProd, stdin);
		sscanf(prod.nombre, "%s", prod.nombre);
		printf("%s", prod.nombre);

		printf("\n\tStock en el almacén: ");
		scanf("%i", &prod.stock);
		printf("%i", prod.stock);

		printf("\n\tPrecio por unidad: ");
		scanf("%f", &prod.precio);
		printf("%f", prod.precio);

		char *nomficEx = concat(sec.nombre, ".txt");
		FILE *f;

		if (existenciaFic(nomficEx) == 0) {
			f = fopen(nomficEx, "a+");
			fprintf(f, "\n\n%s\nStock:%i\nPrecio:%f", prod.nombre, prod.stock,
					prod.precio);
		} else {
			printf("\n\n\tNo existe la sección '%s'", sec.nombre);
		}

		fclose(f);

		preguntarSalida();

		freeSeccion(&sec);
		freeProducto(&prod);

		//	opción 2: añadir una nueva sección.
	} else if (c == '2') {
		//Se pide el nombre de la seccion.
		Seccion sec2;
		fflush(stdin);
		printf("\n\n\tNombre: ");
		sec2.nombre = malloc(sizeof(char) * (MAX_NomSec));
		fgets(sec2.nombre, MAX_NomSec, stdin);
		sscanf(sec2.nombre, "%s", sec2.nombre);
		printf("%s", sec2.nombre);
		//Se crea el fichero con el nombre de la seccion que se ha introducido.
		FILE *f;
		char *nomfic = concat(sec2.nombre, ".txt");

		f = fopen(nomfic, "w");

		fclose(f);

		preguntarSalida();

		freeSeccion(&sec2);

		//	opción 3: eliminar una sección ya creada previamente (se eliminan con ella sus productos).
	} else if (c == '3') {
		//Se pide el nombre de la seccion que se desea eliminar
		fflush(stdin);
		printf("\n\n\tSelecciona la seccion que quieras elimimnar: ");
		Seccion sec3;
		sec3.nombre = malloc(sizeof(char) * (MAX_NomSec));
		fgets(sec3.nombre, MAX_NomSec, stdin);
		sscanf(sec3.nombre, "%s", sec3.nombre);
		printf("%s", sec3.nombre);
		char *nomficSec = concat(sec3.nombre, ".txt");

		if (existenciaFic(nomficSec) == 0) {
			remove(nomficSec);
			printf("\n");
		} else {
			printf("\n\n\tLa seccion '%s' no existe.\n", sec3.nombre);
		}
		//Se elimina el fichero

		preguntarSalida();

		freeSeccion(&sec3);

		//	opción 4: añadir ofertas a secciones.
	} else if (c == '4') {
		fflush(stdin);
		printf("\n\n\tNombre de la seccion a la que aplicar la oferta: ");
		Oferta o;
		o.sec.nombre = malloc(sizeof(char) * (MAX_NomSec));
		fgets(o.sec.nombre, MAX_NomSec, stdin);
		sscanf(o.sec.nombre, "%s", o.sec.nombre);
		printf("%s", o.sec.nombre);

		printf("\n\tPorcentaje de rebaja: ");
		scanf("%i", &(o.porcentaje));
		printf("%i", o.porcentaje);

		char* nombreFic = concat(o.sec.nombre, ".txt");

		FILE *f;

		if (existenciaFic(nombreFic) == 0) {
			f = fopen("ofertas.txt", "a+");
			fprintf(f, "Seccion: %s \t %i%% de descuento\n", o.sec.nombre,
					o.porcentaje);
		} else {

			printf("\n\n\tLa seccion '%s' no existe.\n", o.sec.nombre);

			fflush(stdin);
			fflush(stdout);
		}

		fclose(f);

		preguntarSalida();



		freeOferta(&o);

	} else if (c == 'q') {
		exit(-1);
	} else {
		printf("\n\n\tElige una tecla valida.");
		menu();
	}

}

void preguntarSalida() {
	printf("\n\tQuieres realizar otra operación?");
	printf("\n\t\t1- Si");
	printf("\n\t\t2- No");

	char x;
	fflush(stdin);
	scanf("%c", &x);

	if (x == '1') {
		menu();
	} else if (x == '2') {
		printf("\n\tSaliendo....");
		exit(-1);
	}
}

int existenciaFic(char *fichero) {
	struct stat buffer;
	int exist = stat(fichero, &buffer);
	return exist;
}

void freeSeccion(Seccion *sec) {
	free(sec->nombre);
}
void freeProducto(Producto *prod) {
	freeSeccion(&(prod->sec));
	free(prod->nombre);
}
void freeOferta(Oferta *ofr) {
	freeSeccion(&(ofr->sec));
}
