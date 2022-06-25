#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define STOCK_INGREDIENTES “stockingredientes.bin”



//Paso 1
typedef struct
{
  char nombre_ingrediente[20];
  float cantidad;  //en kg o en litro segun el tipo de ingrediente
  char tipo[20]; /// "liquido" "solido"
  float costo; ///costo por kg o por litro según corresponda
}StockIngrediente;

int cantDatosArch(int,char[]);

//Paso 2
typedef struct
 {
   char nombre_preparacion[20];
   int cantidad; ///por unidad, no hay por peso
 }Preparacion;

 typedef struct
 {
    char nombre_ingrediente[20];
    float cantidad; ///puede ser en litro o en kg
 }IngredienteXReceta;

//Paso 3
 typedef struct
 {
   char nombre_preparacion[20];
   IngredienteXReceta ingredientes[20]; ///Puede tener hasta 20 ingredientes
   int cantIngredientes; ///los validos de ingredientes
 }Receta;

 typedef struct
 {
   char nombre_preparacion[20];
   int cantidad; ///por unidad, no hay por peso
 }PreparacionVenta;

 typedef struct
 {
   char nombre_preparacion[20];
   float precio_venta; ///precio por unidad
 }PrecioPreparacion;

 typedef struct
{
  char nombre_preparacion[20];
  int cantidad;
}PedidoPreparacion;

typedef struct
{
  int idVenta;
  PedidoPreparacion items_pedido[20]; ///puedo pedir hasta 20 items
  int cantItems; ///los validos del arreglo de items_pedido
  float valor_total; ///valor total a pagar
}Venta;

//Paso 4


int main()
{



    return 0;
}

//Paso 1
int cantDatosArch(int tamanioDato,char nombreArch[]){
    int cant = 0;
    FILE* arch = fopen(nombreArch,"rb");
    if (arch != NULL){
        fseek(arch,0,2);
        cant = ftell(arch)/(tamanioDato);
        if(fclose(arch) != 0){
            printf("- archivo cerrado fun cantDatos\n")   
        }
    }else{
        printf("- no se pudo abrir el archivo fun cantDatos\n");
    }
    return cant;
}

//Paso 2


//Paso 3


//Paso 4

















