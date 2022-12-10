#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define TAM 75



typedef struct elemento{
    float precioPrd;
    int posicion;
}elemento;

typedef struct nodo{
    elemento e;
    struct nodo *abajo; //Este es el apuntador que nos ayudara a vincular todos los NODOS
}nodo;

//Estructura Pila
typedef struct pila{
    nodo *tope; //Este apuntador es clave ya que es el que nos determina en que elemento de la PILA estamos colocados.
}pila;


//Prototipos de funciones
int calcula_posicion(int clave_f);  //Calcula la posicion para localizarla en la HashTable
void creando_hashTable(int prdF[75][6], int hash_table[75][7]); //Utiliza la tabla original y la convierte en una tabla hash
void mostrar_tablaHash(int hash_table[75][7]);
int buscar_llave(int hash_table[75][7], int clave_buscada);
float CalculaPrecioPublico(int hash_table[75][7], int posicion);    //Esta funcion va haciendo pops en la pila y al mismo tiempo sumando 
                                                                    //el precioPublico de los productos

//Prototipos de funciones  para la pila
void Initialize(pila *s);   
//Si la inicializacion fue correcta pila1.tope == 000000 o NULL
void Push(pila *s, elemento e); 
//Se crea un nuevo nodo y se guarda el elemento e
elemento Pop(pila *s);  
//Se obtiene el elemento en tope y se elimina 
int Size(pila *s);
//Retorna el nuemro de elementos en la PILA
//boolean Empty(pila *s);
void Destroy(pila *s);
void Show(pila *s, int hash_table[75][7]);



int main(){
//Profe no pude ingresar todo los datos por un archivo txt.c
//Use el comando >archivo.txt en la terminal y funciono el ingreso de datos pero despues me causaba problemas 
//cuando intente usar scanf para controlar el programa obtenia datos basura y no pude solucionarlo.


//  COLUMNAS
//  | ID | UnidadesDispo | PrecioBase | FechaCad (dia/mes/year) |
    int productos[75][6] = {{100,42,244,5,5,2024},
{102,25,464,19,11,2024},
{104,6,310,2,4,2023},
{106,92,792,3,4,2022},
{108,92,386,3,10,2023},
{110,83,800,27,3,2024},
{112,48,299,12,7,2022},
{114,13,235,20,8,2022},
{116,4,782,3,10,2022},
{118,65,923,2,6,2023},
{120,48,610,23,10,2022},
{122,60,913,22,2,2023},
{124,17,832,21,7,2022},
{126,7,429,3,5,2023},
{128,47,776,21,10,2023},
{130,51,788,22,10,2024},
{132,30,808,25,11,2022},
{134,41,360,27,12,2023},
{136,45,599,27,8,2024},
{138,39,298,13,10,2024},
{140,34,877,20,7,2022},
{142,31,560,27,6,2022},
{144,22,910,15,5,2022},
{146,30,544,4,10,2022},
{148,87,674,12,1,2024},
{150,68,626,5,12,2023},
{152,51,549,22,5,2023},
{154,31,869,12,8,2022},
{156,58,472,4,4,2024},
{158,10,369,9,6,2022},
{160,23,315,27,11,2022},
{162,69,299,12,7,2024},
{164,11,952,25,6,2024},
{166,84,561,22,3,2024},
{168,92,598,15,5,2022},
{170,22,314,10,1,2023},
{172,82,929,24,8,2022},
{174,39,692,9,8,2024},
{176,29,675,19,8,2024},
{178,22,893,18,2,2023},
{180,10,607,6,4,2024},
{182,50,699,27,11,2022},
{184,25,795,25,6,2023},
{186,3,992,26,10,2022},
{188,24,986,5,12,2024},
{190,1,842,19,1,2024},
{192,99,262,30,3,2023},
{194,58,647,13,11,2023},
{196,39,349,11,6,2024},
{198,92,791,29,5,2022},
{200,3,431,3,4,2022},
{202,47,930,27,12,2024},
{204,70,317,25,1,2024},
{206,99,910,22,2,2024},
{208,58,641,23,6,2024},
{210,13,397,21,4,2023},
{212,62,470,22,10,2022},
{214,24,396,26,3,2023},
{216,89,387,28,10,2023},
{218,33,364,25,6,2024},
{220,77,290,29,1,2024},
{222,56,430,20,2,2024},
{224,46,638,29,10,2024},
{226,24,459,17,8,2023},
{228,50,816,7,2,2023},
{230,96,293,17,3,2023},
{232,89,462,6,7,2022},
{234,2,277,2,3,2024},
{236,14,525,16,2,2022},
{238,9,430,6,6,2022},
{240,22,534,7,11,2023},
{242,45,968,3,2,2023},
{244,36,625,14,3,2024},
{246,60,860,10,10,2024},
{248,55,874,6,10,2023}
};


                                    //COLUMNAS
    int hash_table[75][7] = {0};    //Status (1/0) | ID | UnidadesDispo | PrecioBase | FechaCad (dia/mes/year) |
                                    //1 indica hash oupado 0 hash libre

    printf("\n\tCreando hash table...\n");
    printf("\tCreando hash table...\n");
    creando_hashTable(productos, hash_table);
    printf("\tTABLA HASH CREADA CORRECTAMENTE\n");


    int clave_buscada;  //Sera el ID que se buscara en la Tabla Hash
    int opcion = 0;     //Variable para controlar el Menu Principal
    int opcion2 = 0;    //Variable para controlar el Menu de las Compras

    pila pila1;     //Pila para guardar los productos que el usuario comprara
    elemento e1;    //Es una estructura que gurdara el precio al publico y la posicion hash del producto
    
    int posicion;       //Sirve para guardar la posicion del producto en la tabla hash
    int precioPublico;  //Guardara el precio publico que es el precioBase mas el 60% del precioBase
    int compra;         //Variable para controlar el Menu de decision de Compra o NoCompra

    int n = 0;          //Guardara el tamanio de la pila 
    float suma_total;   //Guardara el total a pagar por los productos
    int i;      //Pus pal for pa que mas xd   
    int filas, columnas;    //Igual fueron usados para manipular fors de una matriz

    
    //Inicializamos Pila
    //printf("\n\tInicializando PILA:\n");
    Initialize(&pila1);
    //Comprobamos que la inicializacion se cumplio
    //printf("La direccion de es: %p\n", pila1.tope);
    //Show(&pila1, hash_table);

    while(opcion!=-1){
        printf("\n\n\t\tMENU PRINCIPAL");
        printf("\n\nEliga una opcion:");
        printf("\n\t1. Mostrar los datos orginales");
        printf("\n\t2. Mostar la TABLA HASH");
        printf("\n\t3. Buscar algun producto");
        printf("\n\t4. INGRESE A LA TIENDA");
        printf("\n\t-1. Salir del programa");
        printf("\n\t\tOpcion: ");
        scanf("%d",&opcion);
        
        switch(opcion){
            case 1:
                    printf("\n\t\tLos datos ORIGINALES son:\n");
                    printf("|\tID\t| UnidadesDispo | PrecioBase | FechaCad (dia/mes/year)\t\t\t|\n");
                    
                    for(filas=0; filas<TAM; filas++){
                        for(columnas=0; columnas<6; columnas++){
                            printf("%d\t", productos[filas][columnas]);
                        }
                        printf("\n");
                    }
            break;

            case 2:
                    mostrar_tablaHash(hash_table);
            break;

            case 3:
                    printf("\n\nIngrese un ID: ");
                    scanf("%d", &clave_buscada);
                    buscar_llave(hash_table, clave_buscada);
            break;

////////////CASE PARA LA TIENDA/////////////
//Dentro de este case exite otro menu switch para el menu de la tienda
            case 4:

                while(opcion2!=-1){
                    printf("\n\n\t\tBIENVENIDO AL KEV-MART");
                    printf("\n\nEliga una opcion:");
                    printf("\n\t1. Comprar un producto");
                    printf("\n\t2. Quitar articulo CIMA del carrito de compras");
                    printf("\n\t3. Mostrar carrito de compras");
                    printf("\n\t4. Mostrar TOTAL a PAGAR");
                    printf("\n\t-1. Regresar al Menu Principal");
                    printf("\n\t\tOpcion: ");
                    scanf("%d",&opcion2);
                    
                    switch(opcion2){
                        case 1:
                            printf(" \n\t\tBienvenido al Carrito de Compras\n");

                            printf("\nIngrese el ID del producto: ");
                            scanf("%d", &clave_buscada);
                            posicion = buscar_llave(hash_table, clave_buscada);

                            if(posicion==-2){
                                printf("Intentelo de nuevo o salga pulsando -1\n");
                            }else{
                                precioPublico = CalculaPrecioPublico(hash_table, posicion);
                                printf("\nDesea agregar este producto a su carrito?\t1=SI\t0=NO\n");
                                printf("Opcion: ");
                                scanf("%d", &compra);

                                switch(compra){
                                    case 1:
                                        e1.precioPrd = precioPublico;
                                        e1.posicion = posicion;
                                        Push(&pila1, e1);
                                        printf("\n\tEl producto ha sido AGREGADO a su carrito\n");

                                        Show(&pila1, hash_table);
                                    break;

                                    case 0:
                                        printf("\n\tEl producto NO se agrego\n");
                                    break;

                                    default:
                                        printf("\n\tValor invalido COMPRA CANCELADA, intentelo de nuevo\n");
                                    break;
                                }
                            }
                        break;

                        case 2:
                            n = Size(&pila1);
                            if(n==0){
                                printf("\n\tNO SE PUDO HACER EL POP\n");
                                Show(&pila1, hash_table);
                            }else if(n>0){
                                e1 = Pop(&pila1);
                                printf("\n\t\tEl producto ha sido ELIMINADO correctamente\n");
                                Show(&pila1, hash_table);
                            }
                        break;

                        case 3:
                            Show(&pila1, hash_table);
                        break;

                        case 4:
                            printf("\n\tHaciendo un Size\n");
                            n = Size(&pila1);
                            printf("El tamanio de la PILA es: %d\n", n);

                            if(n==0){
                                Show(&pila1, hash_table);
                            }else if(n>0){
                                Show(&pila1, hash_table);
                                suma_total = 0;

                                for(i=1; i<=n; i++){
                                    e1 = Pop(&pila1);
                                    suma_total = suma_total + e1.precioPrd;
                                }

                                printf("\n\n\t\tEl total a pagar es de: $%.2f", suma_total);
                            }
                        break;

                        case -1:
                        break;

                        default:
                            printf("\nValor INVALIDO eliga otra opcion");
                        break;

                    }//Fin del switch
                }//Fin del while 

                Show(&pila1, hash_table);
            break;

            case -1:
            break;

            default:
                printf("\nValor INVALIDO eliga otra opcion");
            break;

        }//Fin del switch
    }//Fin del while 

    Destroy(&pila1);

    return 0;
}//fin del main








//Definicion de las funciones

int calcula_posicion(int clave_f){
    int posicion_f;
    return posicion_f = clave_f % TAM;
}//Fin de calcula_posicion


float CalculaPrecioPublico(int hash_table[75][7], int posicion){
    //printf("posicion = %d", posicion);
    float precP;    //Precio al publico
    int precB;
    precB = (hash_table[posicion][3]);
    printf("\nPRECIO NORMAL: %d\n", precB);
    precP = ((precB*(.60)));
    printf("El 60 PORCIENTO de ganancia del producto es: %.2f\n", precP);
    precP = precP + precB;
    printf("PRECIO PUBLICO: %.2f\n", precP);

    return precP;
}//Fin de precioPublico


void creando_hashTable(int prdF[75][6], int hash_table[75][7]){
    int i;
    int posicion;

        for(int i=0; i<TAM; i++){
        posicion= calcula_posicion(prdF[i][0]);
        //printf("\n\tMOD = %d", posicion);
        while(hash_table[posicion][0] == 1){
            posicion++;
            if(posicion>(TAM-1)){
                posicion = 0;
            }
        }
        hash_table[posicion][0] = 1;            //Cambia el valor de estatus a 1

        hash_table[posicion][1] = prdF[i][0];  //Guarda el ID
        hash_table[posicion][2] = prdF[i][1];  //Guarda las unidades disponibles
        hash_table[posicion][3] = prdF[i][2];  //Guarda el precio base 
        hash_table[posicion][4] = prdF[i][3];  //Guarda el dia
        hash_table[posicion][5] = prdF[i][4];  //Guarda el mes
        hash_table[posicion][6] = prdF[i][5];  //Guarda el year
    }//fin del for
}//Fin de creando_hashTable


void mostrar_tablaHash(int hash_table[75][7]){
    int filas, columnas;

    printf("\nN#|Status|ID| UnidadesDispo | PrecioBase | FechaCad (dia/mes/year)\t\t\t|\n");
    for(filas=0; filas<TAM; filas++){
        printf("%d", filas+1);
        for(columnas=0; columnas<7; columnas++){
            printf("  %d\t", hash_table[filas][columnas]);
        }
        printf("\n");
    }
}//Fin de mostrar_tablaHash


int buscar_llave(int hash_table[75][7], int clave_buscada){
    int posicion;
    int break_cont = 0;
    int bandera = 1;

    printf("\nBuscando ID: %d...\n\n", clave_buscada);

        posicion = calcula_posicion(clave_buscada);
        while(hash_table[posicion][1] != clave_buscada){
        //while(table1[posicion].id != clave_buscada){
            posicion++;
            break_cont++;
            //printf("Buscando %d...\n", clave_buscada);
            if (posicion >(TAM-1)){
                posicion = 0;
            }
            if(break_cont==(TAM+1)){
                break;
            }
        }//Fin del while 

        if(break_cont==(TAM+1)){
            printf("\n\n\tLa clave %d NO FUE ENCONTRADA en la tabla hash:(");
            return -2;
        }else{
            printf("\n\n\tEl ID: %d tiene los datos:\n", clave_buscada);
            printf("\n\t\tProducto ID: %d\n", hash_table[posicion][1]);
            printf("\t\tUnidades disponibles: %d\n", hash_table[posicion][2]);
            printf("\t\tPrecioBase: %d\n", hash_table[posicion][3]);
            printf("\t\tFecha de Caducidad: %d/%d/%d\n", hash_table[posicion][4], hash_table[posicion][5], hash_table[posicion][6]);
            return posicion;
        }

}//buscar_llave




void Initialize(pila *s){
    s->tope = NULL;
    return;
}//FIn de Initialize


void Push(pila *s, elemento e){
    //Crear nuevo nodo
    nodo *aux;
    aux = (nodo *)malloc(sizeof(nodo)); 
    if(aux==NULL){
        printf("\nERROR: Desbordamiento de memoria no fue asignada memoria para este nuevo nodo\n");
        exit(1);
    }
    //Guardamos el elemento
    aux->e = e;
    //El nuevo nodo se guarda en la direccion de tope
    aux->abajo = s->tope;
    //tope se mueve "hacia arriba de la PILA"
    s->tope = aux;

    return;
}//Fin de Push


elemento Pop(pila *s){
    if(s->tope==NULL){
        printf("ERROR: la pila aun no tiene ningun elemento guardado\n");
        exit(1);
    }
    //Variables AUXILIARES 

    elemento dato;  //Nos sirve para retornar el elemento dado
    nodo *aux;      //Nos sirve para guardar temporalmente una direccion antes de borrarla

    //Guardamos el dato para deolverlo 
    dato = s->tope->e;
    //dato = *((*s).tope).e;    Esto es equivalente a lo de arriba


    aux = s->tope;  //Va aser la direccion que se va a borrar
    s->tope = s->tope->abajo;   //El tope ahora apunta al elemento de mas abajo por que el elemento 
                                //al que apuntaba como tope se va a eliminar

    free(aux);
    return dato;
}//fin de Pop


int Size(pila *s){
    nodo *aux;
    int n=0;    //Numero de elementos 

    aux = s->tope;
    while(aux != NULL){
        n++;
        aux = aux->abajo;
    }

    return n;
}//Fin de Size


void Destroy(pila *s){
    nodo *aux1;
    nodo *auxBORRA;
//Este if nos previene de que destruya una PILA que esta vacia
    if(s->tope!=NULL){
        aux1 = s->tope;

        while(aux1 != NULL){
            auxBORRA = aux1;
            aux1 = aux1->abajo;
            free(auxBORRA);
        }
        //Para dejar la pila inicializada como nueva para un nuevo uso
        s->tope = NULL;
    }

    return;
}//Fin de Destroy


void Show(pila *s, int hash_table[75][7]){
    int i;
    if(s->tope == NULL){
        printf("\n\tEL carrito esta vacio:c\n");
    }else{
        nodo *aux;
        aux = s->tope;

        printf("\n\tEl carrito de compras tiene los sig productos:\n\n");
        //printf("|Producto ID | PrecioBase | PrecioPublico|\n");
        printf("|Producto ID| UnidadesDispo | PrecioBase | FechaCad (dia/mes/year)|\n");
        printf("CIMA: \n");
        while(aux != NULL){
            printf("%d\t", hash_table[aux->e.posicion][1]);
            printf("%d\t", hash_table[aux->e.posicion][2]);
            printf("%d\t", hash_table[aux->e.posicion][3]);
            printf("%d/", hash_table[aux->e.posicion][4]);
            printf("%d/", hash_table[aux->e.posicion][5]);
            printf("%d\t", hash_table[aux->e.posicion][6]);
            printf("Precio A pagar: %.2f\n", aux->e.precioPrd);
            aux = aux->abajo;
        }
        //printf("\nNULL\n");
    }
}//Fin de Show