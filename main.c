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

//paso 2
void cargarTodosLosPrecios(PrecioPreparacion [], Receta[],int);
void persistenciaPrecios(PrecioPreparacion [], int);
void despersistenciaPrecios(PrecioPreparacion [], int* );
void mostrarUnPrecio(PrecioPreparacion);
void mostrarTodosLosPrecios(PrecioPreparacion [], int* );
void modificarUnPrecio(PrecioPreparacion [], int );
void registrarUnaVenta(PreparacionVenta [], Venta*, PrecioPreparacion [], int);
void registrarVariasVentas(PreparacionVenta [],Venta [],PrecioPreparacion [],int*,int*);
void persistenciaVentas(Venta [], int);
void despersistenciaVentas(Venta [], int*);


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

void cargarTodosLosPrecios(PrecioPreparacion precios_venta[], Receta nombre_preparacion[20], int cantidad)
{
    for(int i=0; i<validosRecetas; i++)
    {
        strcpy(precios[i].nombre_preparacion,nombre_preparacion[i].nombre_preparacion);
        printf("Ingrese el precio de %s:", precios[i].nombre_preparacion);
        scanf("%f", &precios[i].precio_venta);
    }

    persistenciaPrecios(precios_venta,validosRecetas);
}

void persistenciaPrecios(PrecioPreparacion precios[], int validos)
{
    FILE* fp ;
    fp=fopen(PRECIOS,"wb");
    if (fp != NULL)
    {
        fwrite(precios,sizeof(PrecioPreparacion),validos,fp);
        fclose(fp);
    }
}

void despersistenciaPrecios(PrecioPreparacion precios[], int* validos)
{
    FILE* fp;
    fp=fopen(PRECIOS,"rb");
    int i = 0;
    if (fp != NULL)
    {
        while (fread(&precios[i], sizeof(PrecioPreparacion),1,fp) > 0 )
        {
            i++;
        }
        fclose(fp);
        *validos = i;
    }

}

void mostrarUnPrecio(PrecioPreparacion p)
{
    printf("%s: %.3f\n", p.nombre_preparacion,p.precio_venta);
}

void mostrarTodosLosPrecios(PrecioPreparacion precios[], int* validosReceta)
{
    despersistenciaPrecios(precios,&validosReceta);

    for(int i=0; i<validosReceta; i++)
    {
        printf("%d. ",i);
        mostrarUnPrecio(precios[i]);
        printf("-----------\n");
    }
}

void modificarUnPrecio(PrecioPreparacion precios[], int validosReceta)
{
    int posicion;
    mostrarTodosLosPrecios(precios,validosReceta);
    printf("Posicion del precio que quiere cambiar: ");
    scanf("%d", &posicion);

    puts(precios[posicion].nombre_preparacion);
    printf("PRECIO ACTUAL: %.3f\n",precios[posicion].precio_venta);
    printf("PRECIO NUEVO: ");
    scanf("%f", &precios[posicion].precio_venta);

    persistenciaPrecios(precios,validosReceta);
}

void mostrarStockPreparados(PedidoPreparacion preparados[], int validosReceta)
{
    for(int i=0; i<validosReceta; i++)
    {
        printf("%s: %d\n", preparados[i].nombre_preparacion, preparados[i].cantidad);
        printf("---------------\n");
    }
}

void registrarUnaVenta(PreparacionVenta preparados[], Venta* p, PrecioPreparacion precios[], int validosReceta)
{
    int i=0; ///ITEMS CARGADOS
    int posicion;

    char seguir='s';

    printf("ID VENTA: ");
    scanf("%d", &((*p).idVenta));

    //mostrarStockPreparados(preparados, validosReceta);
    while(i<CANT_MAX && seguir=='s')
    {
        scanf("%d", &posicion);                                         ///PODEMOS PEDIR EL NOMBRE O LA POSICION, YO VEO MAS FACTIBLE PEDIR LA POSICION
        printf("Digite cuantas %s quiere pedir: ", precios[posicion].nombre_preparacion);
        scanf("%d", &(p->items_pedido->cantidad));

        preparados[posicion].cantidad = preparados[posicion].cantidad - (p->items_pedido->cantidad);///FALTA LA CONDICION DE QUE SI
        /// NO QUEDA MAS STOCK, DARLE LO MAXIMO QUE SE PUEDA
        (*p).valor_total+= (float)preparados[posicion].cantidad * precios[posicion].precio_venta;  ///SE VA A IR SUMANDO EL VALOR TOTAL DE LA VENTA
        i++;
        printf("Desea agregar algo mas?\n");
        fflush(stdin);
        scanf("%c", &seguir);
    }
   (*p).cantItems= i; ///VALIDOS DE LA VENTA
}

void registrarVariasVentas(PreparacionVenta preparados[], Venta ventas[], PrecioPreparacion precios[], int* validosReceta, int* validosVenta)
{
    int i= *validosVenta; ///ARRANCA A CARGAR DESDE LA ULTIMA POSICION DEL ARREGLO DE VENTAS
    char seguir='s';
    Venta p;

    while(i<CANT_MAX && seguir=='s')
    {
        registrarUnaVenta(preparados,&p,precios,validosReceta);
        ventas[i]= p;
        i++;
        printf("%d\n", ventas[i].idVenta);
        printf("Desea ingresar otra venta?\n");
        fflush(stdin);
        scanf("%c", &seguir);
    }

    *validosReceta=i;
    persistenciaVentas(ventas,validosVenta);
}

void persistenciaVentas(Venta ventas[], int validos)
{
    FILE* fp;
    fp=fopen(CANT_VENTAS, "wb");

    if(fp != NULL)
    {
        fwrite(ventas,sizeof(Venta),validos,fp);
        fclose(fp);
    }
}

void despersistenciaVentas(Venta ventas[], int* validos)
{
    FILE* fp;
    fp=fopen(CANT_VENTAS,"rb");

    int i = 0;
    if (fp != NULL)
    {
        while (fread(&ventas[i], sizeof(Venta),1,fp) > 0 )
        {
            i++;
        }
        fclose(fp);
        *validos = i;
    }
}

int cantidadDeVentas()
{
    FILE* fp;
    fp=fopen(CANT_VENTAS,"rb");
    int cant;
    if(fp != NULL)
    {
        fseek(fp,0,SEEK_END);
        cant= ftell(fp) / sizeof(Venta);
    }

    return cant;
}

void bajaDeUnaVenta(Venta ventas[],int validosVentas)
{
    FILE* fp;
    fp= fopen(PRECIOS,"r+b");
    int cantidadVentas= cantidadDeVentas();
    int i=0;
    Venta p;
    int id;

    printf("Ingrese el ID que quiere eliminar: ");
    scanf("%d", &id);


    if(fp != NULL)
    {
        fread(&p,sizeof(Venta),1,fp);
        while ( i < cantidadVentas && strcmpi(p.idVenta, id) != 0)
        {
            i++;
            fread(&p,sizeof(Venta),1,fp);
        }
        if (i < cantidadVentas)
        {
            p.baja = 1; ///doy de baja la persona
            fseek(fp,sizeof(Venta)*(-1),SEEK_CUR);
            fwrite(&p,sizeof(Venta),1,fp);
        }
        fclose(fp);

    }
}

void listaPreparadosYcantVentas (Preparacion prep,int validos)
{
    int i;
    for(i=0; i<validos; i++)
    {
        printf("Lista preparados: \n");
        printf("Nombre preparacion: %s \n",prep.nombre_preparacion);
        printf("Cantidad: %i \n",prep.cantidad);
    }

//Pendiente: prototipados, revisar


//Paso 4

















