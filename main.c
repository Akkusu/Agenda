//Programa que gerera un catalago de clientes
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define CIERTO 1
#define FALSO 0
#define LONGITUD_RegistroFederal 14
#define LONGITUD_NOMBRE 46
#define LONGITUD_RazonSocial 46

typedef struct {
		  char RegistroFederal[LONGITUD_RegistroFederal];
		  char Nombre[LONGITUD_NOMBRE];
		  char RazonSocial[LONGITUD_RazonSocial];
		} regCliente;

FILE *ptfCliente;
regCliente vtrCliente;

void vCICLO_MENU();
void vCrear();
char cAGREGAR_RegistroFederal(char RegistroFederalReceptor[], char RegistroFederalLocal[] );
char cAGREGAR_NOMBRE(char NombreReceptor[], char NombreLocal[]); 
char cAGREGAR_RazonSocial(char RazonSocialReceptor[], char RazonSocialLocal[]); 

regCliente rAgregar( regCliente vtrCliente );
regCliente rQuitar( regCliente vtrCliente );
regCliente rModificar( regCliente vtrCliente );

int iBUSCAR_RegistroFederal( char RegistroFederalBuscada[LONGITUD_RegistroFederal] );
int iBUSCAR_REGISTRO( char RegistroFederalBuscada[LONGITUD_RegistroFederal] );
void vBORRAR_REGISTRO( char RegistroFederalCancelada[LONGITUD_RegistroFederal] );
void vCAMBIAR_REGISTRO( regCliente vtrCliente, char Mat[LONGITUD_RegistroFederal] );

int iVALIDAR_RegistroFederal( char RegistroFederalSinValidar[LONGITUD_RegistroFederal] );
char cLETRAS_MAYUSCULAS( char Destino[], char Fuente[] );
void vIMPRIME( regCliente vtrCliente );

int iABRIR_PARA_LEER();
int iSELECCIONA_OPCION( int OpcionMenor , int OpcionMayor );

void gotoxy(short x, short y){
   COORD pos = {x, y};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

main(){
    vCICLO_MENU();
} 

void vCICLO_MENU(){
   int OpcionMenu;
   int OpcionMenor = 1, OpcionMayor = 6;
   do{
   	    system("color 0B");
        system("cls");
        printf("   +-----------------------------------------------------------------------------------------------+ ");
        printf( "\n   |                        *C A T A L A G O   D E   C L I E N T E S*                              |\n");
        printf("   |  1.- Crear nuevo catalago.           2.- Agregar nuevo cliente.   3.- Quitar cliente.         |\n");
		printf("   |  4.- Buscar y modificar clientes.    5.- Lista de clientes.       6.- Ordenar la lista.       |\n");
		printf("   |  7.- Salir del programa.                                                                      |\n");
		printf("   +-----------------------------------------------------------------------------------------------+ ");
        printf( "\n\n    Cual opcion desea realizar? :"    );
        OpcionMenu = iSELECCIONA_OPCION( OpcionMenor, OpcionMayor );
        switch( OpcionMenu ){
	       case 1:
		         vCrear();
		         break;
	       case 2:
		         rAgregar( vtrCliente );
		         break;
	       case 3:
		         rQuitar( vtrCliente );
		         break;
           case 4:
		         rModificar( vtrCliente );
		         break;
           case 5:
		         vIMPRIME( vtrCliente );
		         break;
		   case 7:
                 system("cls");
				 system("color 0E");
				 printf("   +-------------------------------------------------------------------+\n");
				 printf("   |  Usted ha elegido la opcion para salir del Programa... Gracias..  |\n");
				 printf("   +-------------------------------------------------------------------+\n");                      		  
                 system("pause");
                 break;
           default:
                  system("cls");
				  system("color 0C");           	
                  printf("La opcion NO ES PERMITIDA  ya que sale del rango \n");
                  printf("El programa concluira su funcion\n");             
                  system("pause");
                  break;
        } 
     }while(  OpcionMenu >= OpcionMenor && OpcionMenu < OpcionMayor );
 }

int iSELECCIONA_OPCION( int LimiteMenor , int LimiteMayor ){
   int OpcionSeleccionada;
   char Opcion[2];        
   do{
      scanf( "%s", Opcion );  
      OpcionSeleccionada = atoi( Opcion );
      if( OpcionSeleccionada == FALSO ){
          printf("La opcion seleccionada NO ES CORRECTA !!!\n");
          printf("El rango de opciones es de %d a %d, favor de intentar de nuevo \n", LimiteMenor, LimiteMayor );          
      }    
      else{
         if( OpcionSeleccionada < LimiteMenor || OpcionSeleccionada > LimiteMayor ){
         	system("color F0");
            printf("La opcion seleccionada NO ES CORRECTA !!!\n");
            printf("El rango de opciones es de %d a %d, favor de intentar de nuevo \n", LimiteMenor, LimiteMayor );
         }
      }  
   }while( OpcionSeleccionada < LimiteMenor || OpcionSeleccionada > LimiteMayor );
   return(OpcionSeleccionada);
} 

void vCrear(){
   int Opcion;
   int OpcionMenor = 1, OpcionMayor = 2;
   system("cls");
   system("color 0C");
   printf( "   |                        C R E A R                         |\n");
   printf( "   |        Esta opcion borrara el documento anterior  !!!!   |\n");
   printf( "   |              Deseas DESTRUIRLO? 1.-SI; 2.-NO :           |\n");
   printf("   +----------------------------------------------------------+\n");
   printf("   que elige: ");
   Opcion = iSELECCIONA_OPCION( OpcionMenor, OpcionMayor );
   if( Opcion == CIERTO ){
       ptfCliente = fopen( "c:Clientes.txt", "w" );  
       fclose( ptfCliente );    
   } 
}  

regCliente rAgregar( regCliente vtrCliente ){
   int i, Continuar, NoValido, Encontrado; 
   int Longitud, OpcionMenor = 1, OpcionMayor = 2;
   char RegistroFederalCapturada[LONGITUD_RegistroFederal], NombreCapturado[LONGITUD_NOMBRE];
   char RazonSocialCapturada[LONGITUD_RazonSocial];  
   ptfCliente = fopen( "c:Clientes.txt", "a+" );  
   do{
       do{
       	   system("color 0F");
       	   system("cls");
       	   printf("   +-------------------------------------------------------------+\n");
	       printf( "   |                       A  G  R  E  G  A  R                   |\n" );
	       cAGREGAR_RegistroFederal(RegistroFederalCapturada, RegistroFederalCapturada);
	       NoValido = iVALIDAR_RegistroFederal( RegistroFederalCapturada );
       }while( NoValido == CIERTO );
       Encontrado = iBUSCAR_RegistroFederal( RegistroFederalCapturada );  
       if( Encontrado ){
	      printf( "R F C    E X I S T E N T E \n" );
	      system( "pause" );
       }
       else{
          strcpy( vtrCliente.RegistroFederal, RegistroFederalCapturada );
          cAGREGAR_NOMBRE(NombreCapturado, NombreCapturado);
          cAGREGAR_RazonSocial(RazonSocialCapturada, RazonSocialCapturada);
	      cLETRAS_MAYUSCULAS( vtrCliente.Nombre, NombreCapturado );
   	      cLETRAS_MAYUSCULAS( vtrCliente.RazonSocial, RazonSocialCapturada );
   	      
	      fseek( ptfCliente, 1L, 2 );  
	      fwrite( &vtrCliente, sizeof( regCliente ), 1, ptfCliente ); 
       } 
       system("color 0E");
       system("cls");
       printf( "%cDesea seguir agregando mas clientes: 1.-si, 2.-no     : ",168 );
       Continuar = iSELECCIONA_OPCION( OpcionMenor, OpcionMayor );       
       strset( vtrCliente.RegistroFederal, ' ' );   
       strset( vtrCliente.Nombre, ' ' );   
       strset( vtrCliente.RazonSocial, ' ' );  
   }while( Continuar == CIERTO );
   fclose( ptfCliente );  
   return( vtrCliente );
} 

char cAGREGAR_RegistroFederal(char RegistroFederalReceptor[], char RegistroFederalLocal[]){
   printf( "   |  El R.F.C. del cliente solo debe tener , 13 caracteres :    |" );
   printf("\n   +-------------------------------------------------------------+");
   printf("\n    agregar: ");
   scanf( "%s", RegistroFederalLocal ); 
   return( RegistroFederalLocal[LONGITUD_RegistroFederal] );
} 

int iVALIDAR_RegistroFederal( char RegistroFederalSinValidar[LONGITUD_RegistroFederal] ){
   int Longitud, i, NoCumple;
   NoCumple = FALSO;
   Longitud = strlen( RegistroFederalSinValidar );
   for( i = 0; i < Longitud; i++ ){
      if( ! isdigit( RegistroFederalSinValidar[i] ) ){
	    NoCumple = FALSO;
      }  
   } 
   if( Longitud != 14 || NoCumple == CIERTO){
   	  //system("cls");
   	  system("color 0E");
      //printf( "   R.F.C incorrecto  !!! \n" );
      system( "pause" );
      system("cls");
      //printf( "   El R.F.C. es incorrecto debe tener %d caracteres \n", LONGITUD_RegistroFederal-1 );
      NoCumple = FALSO;
      //system( "pause" );
   } 
   return( NoCumple );
}  

char cAGREGAR_NOMBRE(char NombreReceptor[], char NombreLocal[]){
   int Longitud, i, NoCumple;
   do{
      NoCumple = FALSO;      
      printf( "Captura el nombre del cliente completo:\n\t  Nombre\n\t  Apellido paterno\n\t  Apellido materno \n\t Maximo %d caracteres : ", LONGITUD_NOMBRE-1 );
      scanf( " %[^\n]", NombreLocal );
      Longitud = strlen( NombreLocal );   
   
      for( i = 0; i < Longitud; i++ ){
         if( !isalpha(NombreLocal[i]) && !isspace(NombreLocal[i]) || Longitud > LONGITUD_NOMBRE-1 ){
	        NoCumple = CIERTO;
         }  
       } 
       
      if( NoCumple == CIERTO){
      	 system("cls");
         printf( "El nombre solo debe contener maximo %d LETRAS  !!! \n", LONGITUD_NOMBRE-1 );
         printf( "Favor de intentar de nuevo\n" );
         strset(NombreLocal, ' ');
         system( "pause" );
       }     
   }while(NoCumple == CIERTO);
return( NombreLocal[LONGITUD_NOMBRE] );
} 

char cAGREGAR_RazonSocial(char RazonSocialReceptor[], char RazonSocialLocal[]) {
   int Longitud, i, NoCumple;
   do{
      NoCumple = FALSO;
      system("cls");
      printf( "Ingresa la Razon Social del cliente, Maximo %d caracteres : ", LONGITUD_RazonSocial-1 );
      scanf( " %[^\n]", RazonSocialLocal );
      Longitud = strlen( RazonSocialLocal );   
   
      for( i = 0; i < Longitud; i++ ){
         if( !isalpha(RazonSocialLocal[i]) && !isspace(RazonSocialLocal[i]) || Longitud > LONGITUD_RazonSocial-1 ){
	        NoCumple = CIERTO;
         } 
       } 
       
      if( NoCumple == CIERTO){
         printf( "La Razon Social (nombre de empresa o negocio)solo debe contener maximo %d LETRAS  !!! \n",LONGITUD_RazonSocial-1 );
         printf( "Favor de intentar de nuevo\n" );
         strset(RazonSocialLocal, ' ');
         system( "pause" );
       }      
   }while(NoCumple == CIERTO);
return( RazonSocialLocal[5] );
} 

int iBUSCAR_RegistroFederal(char RegistroFederalBuscada[LONGITUD_RegistroFederal]){
    int Buscado;
    Buscado = 0;
    rewind( ptfCliente ); 
    do{
	     fread(&vtrCliente, sizeof( regCliente ), 1, ptfCliente ); 
	     if( ! strcmp( vtrCliente.RegistroFederal, RegistroFederalBuscada ) ){
	        Buscado = 1;     
	        break;
	     } 
    }while( ! feof( ptfCliente ) );  
    return( Buscado );
} 

 char cLETRAS_MAYUSCULAS( char Destino[], char Fuente[] ){
   int Longitud, i;   
   Longitud = strlen( Fuente );
   for( i=0; i < Longitud; i++ ){
       Destino[i] = toupper( Fuente[i] );
   }
   Destino[i]='\0';
   return(Destino[Longitud]);
}   

regCliente rQuitar( regCliente vtrCliente ){
   int Continuar, BorrarRegistro, ArchivoAbierto = 1, NoValido; 
   int Encontrado; 
   int OpcionMenor = 1, OpcionMayor = 2;
   char RegistroFederalCapturada[LONGITUD_RegistroFederal];  

   ArchivoAbierto = iABRIR_PARA_LEER();
   while( ArchivoAbierto ){
       do{ 
           system("cls");
           system("color 0E");
           printf("   +-------------------------------------------------------------+\n");
	       printf( "   |                    Q U I T A R                              |\n" );
	       cAGREGAR_RegistroFederal(RegistroFederalCapturada, RegistroFederalCapturada);
	       NoValido = iVALIDAR_RegistroFederal( RegistroFederalCapturada );
       }while( NoValido == CIERTO );
       Encontrado = iBUSCAR_REGISTRO( RegistroFederalCapturada );  
       if( ! Encontrado ){
       	  system("cls");
	      printf( "R.F.C.   I N E X I S T E N T E \n" );
	      system( "pause" );
       }
       else{  
	      printf( "\nEsta seguro de querer eliminar al cliente: 1.-SI, 2.-NO : \n" );
          BorrarRegistro = iSELECCIONA_OPCION( OpcionMenor, OpcionMayor );	      
	      if( BorrarRegistro == CIERTO ){
	         vBORRAR_REGISTRO( RegistroFederalCapturada );
	      } 
       } 
       printf( "\nDesea seguir eliminando clientes: 1.-SI, 2.-NO : \n" );
       Continuar = iSELECCIONA_OPCION( OpcionMenor, OpcionMayor );            
       if( Continuar != CIERTO ){
          fclose( ptfCliente );  
          return( vtrCliente );
       }  
   } 
}

int iABRIR_PARA_LEER(){
   int Abrir = 1; 
   ptfCliente = fopen( "c:Clientes.txt", "r" );  
   if( ptfCliente == NULL){
       printf( "\n\nADVERTENCIA ...!!! : NO puedo abrir el archivo porque No existe \n\n\n" );
       Abrir = 0;
   } 	      
   return( Abrir );
}   

int iBUSCAR_REGISTRO( char RegistroFederalBuscada[LONGITUD_RegistroFederal] ){
   int Buscado;
   Buscado = 0;
   rewind( ptfCliente ); 
   do{
       fread( &vtrCliente, sizeof( regCliente ), 1, ptfCliente ); 
       if( ! strcmp( vtrCliente.RegistroFederal, RegistroFederalBuscada)){
	      Buscado = 1;  
          printf( "nombre    : %s\n", vtrCliente.Nombre );
	      printf( "Razon Social   : %s\n", vtrCliente.RazonSocial );
	      break;
       } 
   }while( ! feof( ptfCliente ) );  
   return( Buscado );
}  

void vBORRAR_REGISTRO( char RegistroFederalCancelada[LONGITUD_RegistroFederal] ){
   FILE *ptfNuevo;
   rewind( ptfCliente );  
   ptfNuevo = fopen( "c:Clientes.new", "w" );  
   fread( &vtrCliente, sizeof(regCliente), 1, ptfCliente ); 
   do{
       if( strcmp( vtrCliente.RegistroFederal, RegistroFederalCancelada ) ){
	      fwrite( &vtrCliente, sizeof( regCliente ), 1, ptfNuevo );
       } 
       fread( &vtrCliente, sizeof( regCliente), 1, ptfCliente ); 
   }while( ! feof( ptfCliente ) );  
   fclose( ptfNuevo );
   fclose( ptfCliente );
   remove( "c:Clientes.txt" );
   rename( "c:Clientes.new", "c:Clientes.txt");
   ptfCliente = fopen( "c:Clientes.txt", "r" );  
}  

regCliente rModificar( regCliente vtrCliente ){
   int CambiarRegistro, ArchivoAbierto = 1, NoValido;
   int Continuar, Encontrado;
   int OpcionMenor = 1, OpcionMayor = 2;
   char RegistroFederalCapturada[LONGITUD_RegistroFederal];  
   
   ArchivoAbierto = iABRIR_PARA_LEER();   
   while( ArchivoAbierto ){
       do{  
           system("cls");
           printf("   +-------------------------------------------------------------+\n");
	       printf( "   |                   M O D I F I C A R                         | \n" );
	       cAGREGAR_RegistroFederal(RegistroFederalCapturada, RegistroFederalCapturada);
	       NoValido = iVALIDAR_RegistroFederal( RegistroFederalCapturada );
       }while( NoValido == CIERTO );
       Encontrado = iBUSCAR_REGISTRO( RegistroFederalCapturada );  
       if( ! Encontrado ){
       	  system("color 0C");
       	  system("cls");
       	  printf("   +----------------------------------------------+");
	      printf( "\n   |       R.F.C.   I N E X I S T E N T E         |\n" );
	      printf("   +----------------------------------------------+\n");
	      system( "pause" );
       }
       else{
	      printf( "\nDeseas guardar la modificacion: 1.-SI, 2.-NO : " );
          CambiarRegistro = iSELECCIONA_OPCION( OpcionMenor, OpcionMayor ); 
	      if( CambiarRegistro == CIERTO ){
	          vCAMBIAR_REGISTRO( vtrCliente, RegistroFederalCapturada );
	      } 
        } 
        printf( "\nDesea seguir modificando la lista: 1.-SI, 2.-NO : " );
        Continuar = iSELECCIONA_OPCION( OpcionMenor, OpcionMayor );
        if( Continuar != CIERTO ){
           fclose( ptfCliente );  
           return( vtrCliente );
        } 
   } 
}  

void vCAMBIAR_REGISTRO( regCliente vtrCliente, char RegistroFederalCambio[LONGITUD_RegistroFederal] ){
   char Nombre[LONGITUD_NOMBRE], RazonSocial[LONGITUD_RazonSocial];
   int Op, Longitud, i;
   char Opc;
   FILE *ptfNuevo;
   rewind( ptfCliente );  
   ptfNuevo = fopen( "c:Clientes.new", "w" );  
   fread( &vtrCliente, sizeof( regCliente), 1, ptfCliente ); 
   do{
       if( strcmp( vtrCliente.RegistroFederal, RegistroFederalCambio ) ){
	      fwrite( &vtrCliente, sizeof(regCliente), 1, ptfNuevo );
       }
       else{
	      printf( "\n Ingrese el nombre del cliente, Maximo %d caracteres : ", LONGITUD_NOMBRE-1 );
	      scanf( " %[^\n]", Nombre );
	      printf( "\n Ingrese la Razon Social del cliente, Maximo %d caracteres : ", LONGITUD_RazonSocial-1 );
	      scanf( "%s", RazonSocial );
          cLETRAS_MAYUSCULAS( vtrCliente.Nombre, Nombre );
          cLETRAS_MAYUSCULAS( vtrCliente.RazonSocial, RazonSocial );
	      fwrite( &vtrCliente, sizeof( regCliente), 1, ptfNuevo );
       }  
       fread( &vtrCliente, sizeof( regCliente), 1, ptfCliente ); 
   }while( ! feof ( ptfCliente ) );  
   fclose( ptfNuevo );
   fclose( ptfCliente );
   remove( "c:Clientes.txt" );
   rename( "c:Clientes.new", "c:Clientes.txt" ); 
   ptfCliente = fopen( "c:Clientes.txt", "r" );  
} 

void vIMPRIME( regCliente vtrCliente ){
   int Linea, ArchivoAbierto = 1;
   ArchivoAbierto = iABRIR_PARA_LEER();
   system("cls");
   if(ArchivoAbierto == 1){
   	  system("cls");
      system("color 0F");   
      fread( &vtrCliente, sizeof( regCliente ), 1, ptfCliente );
      Linea = 1;     
      gotoxy( 1, Linea ); printf("R.F.C");
      gotoxy( 15, Linea ); printf("Nombre");
      gotoxy( 50, Linea); printf("Razon Social");           
      Linea++;          
      do{          
           gotoxy( 1, Linea ); printf( "%s", vtrCliente.RegistroFederal );
           gotoxy( 15, Linea); printf( "%s", vtrCliente.Nombre );
           gotoxy( 50, Linea); printf( "%s", vtrCliente.RazonSocial );
           Linea = Linea + 1;
           fread( &vtrCliente, sizeof( regCliente), 1, ptfCliente );
        }while( ! feof( ptfCliente ) );
        printf( "\n" );
        system( "pause" );
        fclose( ptfCliente );
   } 
}
