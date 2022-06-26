#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define STOCK_INGREDIENTES "stockingredientes.bin"
#define DEMANDA "demanda.bin"
#define RECETAS "recetas.bin"
#define STOCK_VENTA "stockventa.bin"

//Paso 1
typedef struct
{
  char nombre_ingrediente[20];
  float cantidad;  //en kg o en litro segun el tipo de ingrediente
  char tipo[20]; /// "liquido" "solido"
  float costo; ///costo por kg o por litro según corresponda
}StockIngrediente;

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

 
//prototipados-------------------------------------------------------------------------------------------------------------
//archivos
int cantDatosArch(int,char[]);
void despersistenciaStockIngre(StockIngrediente stock[50], int cantEle);
void persistenciaStockIngre(StockIngrediente stock[50], int validos);

void despersistenciaRecetas(Receta resetass[20], int cantEle);
void despersistenciaDemanda(Preparacion stock[50], int cantEle);
  
//paso 2
void mostrarStock(StockIngrediente[50],int);
void mostrarRecetas(Receta[20],int);
void cocinar(Preparacion,StockIngrediente[],Receta[20],int,int);
int comprobarStockParaPedido(Preparacion,StockIngrediente[],Receta[20],int);
int recetaDelPedido(Preparacion,Receta[20]);
void paseDemandaaArchivoStockVenta(int,Preparacion);
void persistenciaPreparadosParaVenta(PreparacionVenta[50],int);
void despersistenciaPreparadosParaVenta(PreparacionVenta[50],int);


//funciones---------------------------------------------------------------------
//archivos
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

void despersistenciaStockIngre(StockIngrediente stock[50], int cantEle){ // extraer info del archivo a arreglo
    FILE* fp;
    fp = fopen(STOCK_INGREDIENTES,"rb");
    if(fp != NULL){
        fread(stock,sizeof(StockIngrediente),cantEle,fp);
        if(fclose(fp) != 0){
            printf("- fallo al cerrar el archivo\n");
        }

    }else{
        printf("- fallo al abrir el archivo\n");
    }

}

void persistenciaStockIngre(StockIngrediente stock[50], int validos){ // guardar info en el archivo
    FILE* fp;
    fp = fopen(STOCK_INGREDIENTES,"wb");
    if(fp != NULL){
        fwrite(stock,sizeof(StockIngrediente),validos,fp);
        if(fclose(fp) != 0){
            printf("- fallo al cerrar el archivo\n");
        }else{
          printf("stock de ingredientes actualizado\n");
        }

    }else{
        printf("- fallo al abrir el archivo\n");
    }

}

void despersistenciaRecetas(Receta resetass[20], int cantEle) //"extraer Archivo pasar a arreglo"
{
    FILE* fp;
    fp = fopen(RECETAS,"rb");
    if(fp != NULL){
        fread(resetass,sizeof(Receta),cantEle,fp);
        if(fclose(fp) != 0){
            printf("- fallo al cerrar el archivo\n");
        }
    }else{
        printf("- fallo al abrir el archivo\n");
    }

}

void despersistenciaDemanda(Preparacion stock[50], int cantEle){
    FILE* fp;
    fp = fopen(DEMANDA,"rb");
    if(fp != NULL){
        fread(stock,sizeof(Preparacion),cantEle,fp);
        if(fclose(fp) != 0){
            printf("- fallo al cerrar el archivo\n");
        }

    }else{
        printf("- fallo al abrir el archivo\n");
    }

}

void despersistenciaPreparadosParaVenta(PreparacionVenta stock[50],int validos){
    FILE* fp;
    fp = fopen(STOCK_VENTA,"rb");
    if(fp != NULL){
        fread(stock,sizeof(PreparacionVenta),validos,fp);
        if(fclose(fp) != 0){
            printf("- fallo al cerrar el archivo\n");
        }

    }else{
        printf("- fallo al abrir el archivo\n");
    }

}

void persistenciaPreparadosParaVenta(PreparacionVenta stock[50],int validos){
    FILE* fp;
    fp = fopen(STOCK_VENTA,"wb");
    if(fp != NULL){
        fwrite(stock,sizeof(PreparacionVenta),validos,fp);
        if(fclose(fp) != 0){
            printf("- fallo al cerrar el archivo\n");
        }

    }else{
        printf("- fallo al abrir el archivo\n");
    }

}

 //paso 2
void mostrarStock(StockIngrediente ingredientes[50],int cant){
    for(int i = 0;i<cant;i++){
        printf("%s %.2f %s %.2f \n",ingredientes[i].nombre_ingrediente,ingredientes[i].cantidad,ingredientes[i].tipo,ingredientes[i].costo);
    }
}

void mostrarRecetas(Receta arr[20],int val){
    for(int i = 0;i<val;i++){
        printf("%s \n", arr[i].nombre_preparacion);
        for(int r = 0;r<arr[i].cantIngredientes;r++){
         printf("%s %.2f \n",arr[i].ingredientes[r].nombre_ingrediente , arr[i].ingredientes[r].cantidad);
        }
        printf("%i \n",arr[i].cantIngredientes);
        printf("------------------------------------------------------------------------------------\n");
    }

}
int recetaDelPedido(Preparacion orden,Receta arr[20]){

    int indice = 0;
    while(strcmp(orden.nombre_preparacion,arr[indice].nombre_preparacion) != 0){
        indice++;

    }
    printf(" el pedido es %s %i \n",orden.nombre_preparacion, orden.cantidad);
    printf("%s \n", arr[indice].nombre_preparacion);
    for(int r = 0;r<arr[indice].cantIngredientes;r++){
        printf("%s %.2f \n",arr[indice].ingredientes[r].nombre_ingrediente , arr[indice].ingredientes[r].cantidad);
    }
    //printf("%i \n",arr[indice].cantIngredientes);
    printf("receta encontrada\n") ;
    printf("------------------------------------------------------------------------------------\n");

    return indice;
}

int comprobarStockParaPedido(Preparacion demanda,StockIngrediente stock[],Receta recetario[20],int indiceRecetario){
    int productosACocinar = demanda.cantidad;
    //comprobar si hay suficientes ingredientes
    for(int i = 0;i<recetario[indiceRecetario].cantIngredientes;i++){
        int u = 0;
        while(strcmp(recetario[indiceRecetario].ingredientes[i].nombre_ingrediente,stock[u].nombre_ingrediente) != 0){
            u++;
        }
        //printf(" receta %s stock %s\n",recetario[indiceRecetario].ingredientes[i].nombre_ingrediente,stock[u].nombre_ingrediente);

        while((recetario[indiceRecetario].ingredientes[i].cantidad*productosACocinar) > stock[u].cantidad){
            productosACocinar--;
        }
    }
    if(productosACocinar < 1){
        productosACocinar = 0;
    }
    printf("se pueden hacer %i\n",productosACocinar);
    return productosACocinar;
}

void cocinar(Preparacion demanda,StockIngrediente stock[],Receta recetario[20],int indiceRecetario,int cantACocinar){
    for(int i = 0;i<recetario[indiceRecetario].cantIngredientes;i++){
        int u = 0;
        while(strcmp(recetario[indiceRecetario].ingredientes[i].nombre_ingrediente,stock[u].nombre_ingrediente) != 0){
            u++;
        }
        stock[u].cantidad = stock[u].cantidad - recetario[indiceRecetario].ingredientes[i].cantidad*cantACocinar;
        printf("se usaron %.2f %s \n",recetario[indiceRecetario].ingredientes[i].cantidad*cantACocinar ,recetario[indiceRecetario].ingredientes[i].nombre_ingrediente);

    }
    printf("----------------------------------------------------------------------------------------------------\n");

}

void paseDemandaaArchivoStockVenta(int cocinados,Preparacion pedido){
    PreparacionVenta aGuardar;
    strcpy(aGuardar.nombre_preparacion,pedido.nombre_preparacion);
    aGuardar.cantidad = cocinados;
    FILE* fp;
    fp = fopen(STOCK_VENTA,"ab");
    if(fp != NULL){
        fwrite(&aGuardar,sizeof(PreparacionVenta),1,fp);
        if(fclose(fp) != 0){
            printf("- fallo al cerrar el archivo\n");
        }
    }else{
        printf("- fallo al abrir el archivo\n");
    }
}





 


//Paso 3
/*void cargarPrecios(char nombre_preparacion[20], float precio_venta, int cantidad)
{
    char s;
    int pos=0;
    FILE* precios;
    precios=fopen(precios, "ab");
    if(precios != NULL){
        if(fclose(precios) != 0){
            printf("- fallo al cerrar el archivo\n");
        }

    }else{
        printf("- fallo al abrir el archivo\n");
    }
    
    do
    {
        printf("ingrese una preparacion a buscar\n");
        scanf("%i",&pos);
        fseek(precios,0,1);
        puts(nombre_preparacion[pos]);
        printf("ingrese un precio de venta\n");
        scanf("%f", &PrecioPreparacion.precio_venta);
        printf(" 's' para buscar otra preparacion\n")
    }while(s=='s');
}
*/
//Paso 4

















