#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define STOCK_INGREDIENTES "stockingredientes.bin"
#define DEMANDA "demanda.bin"
#define RECETAS "recetas.bin"
#define STOCK_VENTA "stockventa.bin"
#define PRECIOS "precios.bin"

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
void pasePreparacionAPreparacionVenta(Preparacion,PreparacionVenta,int);

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

 void pasePreparacionAPreparacionVenta(Preparacion aPasar,PreparacionVenta esto,int cocinados){
    strcpy(esto.nombre_preparacion,aPasar.nombre_preparacion);
    esto.cantidad = cocinados;
}








//Paso 3


//Paso 3

//void cargarPrecios(char nombre_preparacion[20], float precio_venta, int cantidad)
{
    /*"leerlo completo y dejarlo en memoria listo en una estructura de datos adecuada, ya que luego vamos
      a empezar la venta hacia el cliente final y debemos utilizar el precio."
      asi que habria que usar un arreglo paralelo a stock venta en vez del archivo para usar, y tener una funcion persistencia precios para guardar la info
    */
    char s;
    nombre_preparacion=despersistenciaPrecios(precios, validos);
     // estaria bueno aca una funcion que muestre una lista con las posiciones,nombre preparaciones para venta y cantidad hecha
    printf("'s' para modificar precios\n");
    fflush(stdin);
    scanf("%c", &s);
    if(s=='s'){
    modPrecios(precios, validos);
    }

   persistenciaPrecios(precios, validos);
}
void despersistenciaPrecios(PrecioPreparacion precios[50], int validos)
{
    FILE* fp;
    fp = fopen(PRECIOS,"rb");
    if(fp != NULL)
    {
        fread(precios,sizeof(PreciosPreparacion),validos ,fp);
        if(fclose(fp) != 0)
        {
            printf("- fallo al cerrar el archivo\n");
        }
    }
    else
    {
        printf("- fallo al abrir el archivo\n");
    }
}

void persistenciaPrecios(PrecioPreparacion precios[50], int validos)
{
    FILE* fp;
    fp = fopen("precios.bin","wb");
    if(fp != NULL)
    {
        fwrite(precios,sizeof(PreciosPreparacion),validos ,fp);
        if(fclose(fp) != 0)
        {
            printf("- fallo al cerrar el archivo\n");
        }
    }
    else
    {
        printf("- fallo al abrir el archivo\n");
    }
}

void modPrecios(PrecioPreparacion precios[50], int validos)
{
    char s;
    int pos=0;
    FILE* fp;
    fp = fopen(RECETAS,"wb");
    do
    {
        printf("ingrese una preparacion a buscar\n");
        scanf("%i",&pos);
        fseek(RECETAS,0,pos); //arreglar parametros
        puts(nombre_preparacion[pos]); //si nombre_preparacion fuera hola y pos = 1 imprimiria en pantalla o
        printf("ingrese un precio de venta\n");
        scanf("%f", &PrecioPreparacion.precio_venta);
        printf(" 's' para buscar otra preparacion\n")
        fflush(stdin);
        scanf("%c", &s);
    }
    while(s=='s');
     if(fclose(fp) != 0){
            printf("- fallo al cerrar el archivo\n");
        }

    }else{
        printf("- fallo al abrir el archivo\n");
    }
}
*/
//Paso 4
//Prototipados------------------------------------------------------------------------------
void cargarReceta(Receta);
void IngresarReceta(Receta[], int*);
void agregarIngrediente(Receta[], int);

//Funciones------------------------------------------------------------------------
 void cargarReceta(Receta a){
     char continuar;
int i=0;
printf("Ingrese el nombre de la receta: ");
fflush(stdin);
gets((a).nombre_preparacion);
fflush(stdin);
printf("Ingrese la cantidad de ingredientes: ");
fflush(stdin);
scanf("%i", (a).cantIngredientes);
printf("Ingrese los ingredientes: ");
do{
    fflush(stdin);
    gets((a.ingredientes[i]).nombre_ingrediente);
    printf("Ingrese la cantidad necesaria de este ingrediente: ");
    scanf("%f", (a.ingredientes[i]).cantidad);
    printf("Desea ingresar otro ingrediente? ");
    fflush(stdin);
    scanf("%c", continuar);
}while(i<20 && continuar == 's');

}

void IngresarRecetas(Receta recetass[], int* cant_ele){
    int i = 0;
    char continuar;
    do{
        cargarReceta(recetass[i]);
        printf("Desea ingresar otra receta? S/N ");
        fflush(stdin);
        scanf("%c", continuar);
        i++;
    }while(i<20 && continuar == 's');
    *cant_ele = i;

}

void agregarIngrediente(Receta recetass[], int cant_ele){
char nombre[20];
int i = 0;
printf("Ingrese el nombre de la receta a modificar. ");
fflush(stdin);
gets(nombre);
while(i<cant_ele && strcmpi(recetass[i].nombre_preparacion, nombre) != 0){
    i++;
}
recetass[i].cantIngredientes += 1;
int b = recetass[i].cantIngredientes;
printf("Ingrese el ingrediente que quiere agregar. ");
fflush(stdin);
gets(recetass[i].ingredientes[b].nombre_ingrediente);
printf("Ingrese la cantidad necesaria del ingrediente. ");
fflush(stdin);
gets(recetass[i].ingredientes[b].nombre_ingrediente);
}


int main(){
    Receta r;
    int cant_elem=0;
Receta resetass[20];
cargarReceta(r);

return 0;
}

