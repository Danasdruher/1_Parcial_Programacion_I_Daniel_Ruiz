/*
 * notebook.c
 *
 *  Created on: 21 oct. 2022
 *      Author: daniel
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <ctype.h>
#include <string.h>

#include "notebook.h"
#include "marca.h"
#include "tipo.h"
#include "datawerehouse.h"
#include "servicios.h"
#include "trabajo.h"
#include "output.h"
#include "cliente.h"



int menuPrincipal(void){

	int opcion;
	printf("    *** ABM Notebooks ***    \n\n");
	printf("=============================\n");
	printf("1.- ALTA NOTEBOOK\n");
	printf("2.- BAJA NOTEBOOK\n");
	printf("3.- MODIFICACIÓN NOTEBOOK\n");
	printf("4.- LISTAR NOTEBOOKS\n");
	printf("5.- LISTAR MARCAS\n");
	printf("6.- LISTAR TIPOS\n");
	printf("7.- LISTAR SERVICIOS\n");
	printf("8.- ALTA TRABAJO\n");
	printf("9.- LISTAR TRABAJOS\n");
	printf("10.-MOSTRAR INFORMES\n");
	printf("11.- SALIR\n");
	printf("=============================\n");
	printf("Ingrese Opción: ");
	scanf("%d", &opcion);
	printf("\n\n");
	return opcion;
}


int menuModificar(void){

	int opcion;
	printf("=============================\n");
	printf("1.- PRECIO\n");
	printf("2.- TIPO\n");
	printf("5.- SALIR\n");
	printf("=============================\n");
	printf("Ingrese la opción que quiere modificar: ");
	scanf("%d", &opcion);
	printf("\n\n");
	return opcion;
}

int inicializarNotebook(eNotebook notebooks[],int tam){
	int todoOk = 0;
	if (notebooks != NULL && tam > 0){
		for(int i=0; i<tam; i++){
			notebooks[i].isEmpty = 1;
		}
		todoOk = 1;
	}
	return todoOk;
}

int buscarLibre(eNotebook notebooks[],int tam){
	int indice = -1;
	if (notebooks != NULL && tam > 0){
		for(int i=0; i<tam; i++){
			if(notebooks[i].isEmpty){
				indice = i;
				break;
			}
		}
	}
	return indice;
}

int altaNotebooks(eNotebook notebooks[],int tam,eMarca marcas[], int tamMarca,eTipo tipos[],int tamTipo,eCliente clientes[],int tamClient,int* pId){
	int todoOk = 0;
	int indiceLibre;
	eNotebook auxNotebooks;
	if (notebooks != NULL && tam > 0 && pId != NULL){

		printf("    ***ALTA DE JUGADOR***\n\n");

		indiceLibre=buscarLibre(notebooks, tam);
		if(indiceLibre == -1){
			printf("No hay lugar disponible.\n");
		}
		else{

				auxNotebooks.id = *pId;
				(*pId)++;

				printf("Ingrese el modelo de notebook: ");
				__fpurge(stdin);
				scanf("%[^\n]s",auxNotebooks.modelo);

				mostrarMarcas(marcas, tamMarca);
				printf("Ingrese el id de la marca: ");
				scanf("%d",&auxNotebooks.idMarca);
				while(!validarIdMarcas(auxNotebooks.idMarca, marcas, tamMarca)){
					printf("Id no valido. Ingrese el id de la marca: ");
					scanf("%d",&auxNotebooks.idMarca);
				}

				mostrarTipos(tipos, tamTipo);
				printf("Ingrese el id del tipo de notebook: ");
				scanf("%d",&auxNotebooks.idTipo);
				while(!validarIdTipos(auxNotebooks.idTipo, tipos, tamTipo)){
					printf("Id no valido. Ingrese el id del tipo de notebook: ");
					scanf("%d",&auxNotebooks.idTipo);
				}
				mostrarClientes(clientes, tamClient);
				printf("Ingrese el id del cliente: ");
				scanf("%d",&auxNotebooks.idCliente);
				while(!validarIdClientes(auxNotebooks.idCliente, clientes, tamClient)){
					printf("Id no valido. Ingrese el id del tipo de notebook: ");
					scanf("%d",&auxNotebooks.idTipo);
				}

				printf("Ingrese el precio: ");
				scanf("%f",&auxNotebooks.precio);
				while(auxNotebooks.precio < 0){
					printf("Ingrese el precio: ");
					scanf("%f",&auxNotebooks.precio);
				};

				auxNotebooks.isEmpty = 0;
				notebooks[indiceLibre] = auxNotebooks;
				todoOk = 1;
			}
		printf("\n\n");
	}
	return todoOk;
}

void mostrarNotebook(eNotebook notebooks,int tam,eMarca marcas[], int tamMarca,eTipo tipos[],int tamTipo,eCliente clientes[], int tamClient){
	char nombreMarca[20];
	char nombreTipo[20];
	char nombreCliente[20];

	if(cargarNombreMarca(marcas, tamMarca,notebooks.idMarca, nombreMarca)==1 &&
	cargarNombreTipo(tipos, tamTipo, notebooks.idTipo, nombreTipo)==1 &&
	cargarNombreCliente(clientes, tamClient, notebooks.idCliente, nombreCliente)==1){
		printf("| %02d  |%-10s| %-10s |%-10s|%-10s| %9.2f |\n",
				notebooks.id,
				notebooks.modelo,
				nombreCliente,
				nombreMarca,
				nombreTipo,
				notebooks.precio);
	}
}

int mostrarNotebooks(eNotebook notebooks[],int tam,eMarca marcas[], int tamMarca,eTipo tipos[],int tamTipo,eCliente clientes[], int tamClient){
	int todoOk=0;
	int flag = 1;
	if(notebooks != NULL && tam > 0){
		printf("           *** Lista de Notebooks ***\n\n");
		printf("------------------------------------------------------------------\n");
		printf("| id  |  Modelo  |   Cliente   |   Marca  |   Tipo   |   Precio  |\n");
		printf("------------------------------------------------------------------\n");
		for (int i = 0; i < tam; i++){
			if(!notebooks[i].isEmpty){
				mostrarNotebook(notebooks[i],tam, marcas, tamMarca, tipos, tamTipo, clientes,tamClient);
				flag = 0;
			}
		}
		if (flag == 1){
			printf("Aun no se han cargado Notebooks!!!\n");
		}
		printf("------------------------------------------------------------------\n");
		todoOk=1;
	}
	printf("\n\n");

	return todoOk;
}

int buscarIdNotebooks(eNotebook notebooks[],int tam,int id){
	int indice = -1;
		if (notebooks != NULL && tam > 0){
			for(int i=0; i<tam; i++){
				if(notebooks[i].id == id && !notebooks[i].isEmpty){
					indice = i;
					break;
				}
			}
		}
		return indice;
}

int bajaNotebook(eNotebook notebooks[],int tam,eMarca marcas[], int tamMarca,eTipo tipos[],int tamTipo,eCliente clientes[], int tamClient){
	int todoOk = 0;
	int indice;
	int id;
	char confirmar;
	if (notebooks != NULL && tam > 0){
		printf("    ***BAJA DE NOTEBOOK***\n\n");
		mostrarNotebooks(notebooks,tam, marcas, tamMarca, tipos, tamTipo,clientes,tamClient);
		printf("Ingrese el id de la notebook que desea dar de baja: ");
		scanf("%d", &id);

		indice = buscarIdNotebooks(notebooks, tam, id);

		if(indice == -1){
			printf("El id: %d no se encuentra en el sistema\n",id);
		}
		else{
			printf("            *** Lista de Notebooks ***\n\n");
			printf("------------------------------------------------------------------\n");
			printf("| id  |  Modelo  |   Cliente   |   Marca  |   Tipo   |   Precio  |\n");
			printf("------------------------------------------------------------------\n");
			mostrarNotebook(notebooks[indice],tam, marcas, tamMarca, tipos, tamTipo,clientes,tamClient);
			printf("\nDesea dar de baja la notebook del id: %d?(s/n)\n", id);
			__fpurge(stdin);
			scanf("%c", &confirmar);
			if (confirmar=='s'){
				notebooks[indice].isEmpty = 1;
				todoOk = 1;
			}
			else{
				printf("Baja cancelada por el usuario!!!\n");
			}
		}
	}
	return todoOk;
}

int modificarNotebook(eNotebook notebooks[],int tam,eMarca marcas[], int tamMarca,eTipo tipos[],int tamTipo,eCliente clientes[], int tamClient){
	int todoOk = 0;
		int indice;
		int id;
		char confirmar;
		int auxIdTipo;
		float auxPrecio;
		if (notebooks != NULL && tam > 0){
			printf("    ***MODIFICAR NOTEBOOK***\n\n");
			mostrarNotebooks(notebooks, tam,marcas, tamMarca,tipos,tamTipo,clientes,tamClient);
			printf("Ingrese el id de la notebook que va a modificar: ");
			scanf("%d", &id);
			indice = buscarIdNotebooks(notebooks, tam, id);
			if(indice == -1){
				printf("El id: %d no se encuentra en el sistema\n",id);
			}
			else{
				printf("            *** Lista de Notebooks ***\n\n");
				printf("------------------------------------------------------------------\n");
				printf("| id  |  Modelo  |   Cliente   |   Marca  |   Tipo   |   Precio  |\n");
				printf("------------------------------------------------------------------\n");
				mostrarNotebook(notebooks[indice],tam,marcas, tamMarca,tipos,tamTipo,clientes,tamClient);
				printf("Confirme si quiere modificar la notebook con el id: %d?(s/n)\n", id);
				__fpurge(stdin);
				scanf("%c", &confirmar);
				if (confirmar=='s'){
					switch(menuModificar()){
						case 1:
							printf("Ingrese nuevo precio de notebook: ");
							scanf("%f",&auxPrecio);
							notebooks[indice].precio = auxPrecio;
							break;
						case 2:
							mostrarTipos(tipos, tamTipo);
							printf("Ingrese el id del tipo de notebook: ");
							scanf("%d",&auxIdTipo);
							while(!validarIdTipos(auxIdTipo, tipos, tamTipo)){
								printf("Id no valido. Ingrese el id del tipo de notebook: ");
								scanf("%d",&auxIdTipo);
							}
							notebooks[indice].idTipo = auxIdTipo;
							break;
						default:
							printf("Ingrese una opcion valida!!!\n");
							break;
					}
					todoOk = 1;
				}
				else{
					printf("Baja cancelada por el usuario!!!\n");
				}
			}
		}
		return todoOk;
}

int ordenarNotebooks(eNotebook notebooks[],int tam,eMarca marcas[], int tamMarca,eTipo tipos[],int tamTipo){
	int todoOk = 0;
	eNotebook auxId;
	if(notebooks != NULL && tam > 0){
		for(int i = 0; i < tam-1 ;i++){
			for(int j = i+1; j< tam ; j++){
				if(notebooks[i].id>notebooks[j].id){
					auxId = notebooks[i];
					notebooks[i] = notebooks[j];
					notebooks[j] = auxId;
				}
			}
		}
		todoOk = 1;
	}
	return todoOk;
}

int cargarNombreNotebook(eNotebook notebooks[],int tam, int id, char descripcion[]){
	int todoOk = 0;
		if(notebooks != NULL && tam > 0 && descripcion != NULL){
			for(int i=0; i < tam; i++){
				if(notebooks[i].id == id){
					strcpy(descripcion, notebooks[i].modelo);
					break;
				}
			}
			todoOk = 1;
		}
		return todoOk;
}
int validarIdNotebooks(int id,eNotebook notebooks[],int tam){
	int esValido = 0;
	if(notebooks != NULL && tam > 0){
		for(int i=0;i<tam;i++){
			if(notebooks[i].id == id){
				esValido = 1;
				break;
			}
		}

	}
	return esValido;
}
