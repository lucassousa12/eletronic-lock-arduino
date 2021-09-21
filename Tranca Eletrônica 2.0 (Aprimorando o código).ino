#include <LiquidCrystal.h>
#include <Keypad.h>
#define Led_vermelho A3
#define Led_amarelo A4
#define Led_verde A5

LiquidCrystal lcd(0,1,10,11,12,13);

const byte linhas= 4; 
const byte colunas= 4; 

char mapateclado[linhas][colunas]= {
{'1', '2', '3','A' }, 
{'4', '5', '6','B' }, 
{'7', '8', '9','C' },
{'*', '0', '#','D' }
};

byte pinoslinhas[linhas] = {9,8,7,6}; 
byte pinoscolunas[colunas]= {5,4,3,2};

Keypad teclado = Keypad(makeKeymap(mapateclado), pinoslinhas, pinoscolunas, linhas, colunas);

char conta1[ ]  = {'1','2','3','4','5','6','\0'};
char conta2[ ]  = {'1','6','9','6','6','6','\0'};
char conta3[ ]  = {'1','4','7','3','6','9','\0'};
char entrada[6];
char confirmar[ ] = {'0','0','0','0','0','0','\0'};
int contador =0; 
int erro, conta = 0;
int botao;
int opc = 0;
bool verificador = false;
//------------------------------------------------------------------------------------------------------------------

void setup(){

  lcd.begin(16,2);
  pinMode(Led_verde,OUTPUT);
  pinMode(Led_vermelho,OUTPUT);
  pinMode(Led_amarelo,OUTPUT);
  pinMode(A0,INPUT);
  
  lcd.print("Inicializando...");
  delay(000);
  lcd.clear();
 }

//------------------------------------------------------------------------------------------------------------------

void loop(){
 	Menu();
}  

//-----------------------------------------------------------------------------------------------------------------
//Destrava a Tranca pelo lado de dentro da porta.
void btns(char t){
  if (botao == HIGH){ 
    	lcd.clear();
      contador = 0;
    	PortaDesbloqueada();
  	} 
//Botão para Retornar ao Menu da Tela inicial.
   if(t == 'D'){
    opc = 0;
    contador = 0;
    lcd.clear();
    do{
       Menu(); 
    } while(opc == 0);
    }
  }

 void ledVerde(){
    digitalWrite(Led_verde, HIGH);
    digitalWrite(Led_amarelo, LOW);
    digitalWrite(Led_vermelho, LOW);
 }
  void ledAmarelo(){
    digitalWrite(Led_verde, LOW);
    digitalWrite(Led_amarelo, HIGH);
    digitalWrite(Led_vermelho, LOW);
 }
  void ledVermelho(){
    digitalWrite(Led_verde, LOW);
    digitalWrite(Led_amarelo, LOW);
    digitalWrite(Led_vermelho, HIGH);
 }

void Menu(){
  
  botao = digitalRead(A0);
  char tecla = teclado.getKey();
  opc = 0;
  verificador = false;
  btns(tecla);

  ledVermelho();
  lcd.setCursor(0,0);
  lcd.print("Destrancar: A");
  lcd.setCursor(0,1);
  lcd.print("Alterar Senha: B");
  if(tecla == 'A'){
    opc = 1;
    lcd.clear();
    contador = 0;
    do{
      DigitarSenha();
    } while(opc == 1);
  } else if(tecla == 'B'){
    opc = 2;
    lcd.clear();
    do{
      Redefinir();
    } while(opc == 2);
  }
   
}
//------------------------------------------------------------------------------------------------------------------
 //Parte onde há a inserção dos algarismos.
void insere(char t){
 
  if ((t) && (contador<6)){ 
    lcd.setCursor(contador, 1);
    lcd.print("*");
    entrada[contador] = t;
    contador++;
}
 btns(t);
}

//Confirmação e comparação das senhas.
void compara(char t, int perfil){

  int contadorSenha = 0;

  if (t == '#'){
     entrada[contador] = '\0';
  switch(perfil){
    case 1:
      for (int i = 0; i < 6; i++){
        if (entrada[i] == conta1[i]){
          contadorSenha++;
        }
      }
    case 2:
      for (int i = 0; i < 6; i++){
        if (entrada[i] == conta2[i]){
          contadorSenha++;
        }
      }
    case 3:
      for (int i = 0; i < 6; i++){
        if (entrada[i] == conta3[i]){
          contadorSenha++;
        }
      }
    case 4:
      for (int i = 0; i < 6; i++){
        if (entrada[i] == conta1[i] || entrada[i] == conta2[i] || entrada[i] == conta3[i]){
         contadorSenha++;
        }
      }
  }
  if (contadorSenha == 6){
    verificador = true;
    contadorSenha = 0;
  } else {
    PortaBloqueada();
    contadorSenha = 0;
    verificador = false;
  }
    }
    btns(t);
  }
//Parte onde a senha é digitada e comparada para o bloqueio ou desbloqueio da Tranca Eletrônica.
void DigitarSenha(){
  
  botao = digitalRead(A0);
  char tecla = teclado.getKey();
  btns(tecla);
 
  //Prepara o lcd e os leds para a inserção da senha.
  
  ledAmarelo();
  lcd.setCursor(0,0);
  lcd.print("Digite a Senha: ");
  insere(tecla);
  compara(tecla, 4);
  if(verificador){
    SenhaCorreta();
  }
}

//------------------------------------------------------------------------------------------------------------------

void Redefinir(){
  
  botao = digitalRead(A0);
  char tecla = teclado.getKey(); 
  
  ledAmarelo();
  lcd.setCursor(0,0);
  lcd.print("Senha: 1, 2");
  lcd.setCursor(0,1);
  lcd.print("   ou  3?");
  switch(tecla){
    case '1':
      conta = 1;
    case '2':
      conta = 2;
    case '3':
      conta = 3;
  }
  if(tecla == '1' || tecla == '2' || tecla == '3'){
    lcd.clear();
    opc = 4;
    do{
    SenhaAtual();
    } while(opc = 4);
  }
/*
  if((tecla == '1') || (tecla == '2') || (tecla == '3')){
   
    lcd.clear();
  }
 	 while(tecla == '1'){
  		 SenhaAtual1();
  }
 	 while(tecla == '2'){
   		 SenhaAtual2();
  }
     while(tecla == '3'){
   		 SenhaAtual3();
  }*/
  btns(tecla);
 }

//------------------------------------------------------------------------------------------------------------------

void SenhaAtual(){
  
  botao = digitalRead(A0);
  char tecla = teclado.getKey();
  btns(tecla);

  ledAmarelo();
  lcd.setCursor(0,0);
  lcd.print("Senha Atual: ");
  insere(tecla);
  compara(tecla, conta);
  if(verificador){
    RedefinirConta1();
  }  
}

//------------------------------------------------------------------------------------------------------------------

void SenhaAtual2(){
  
  botao = digitalRead(A0);
  char tecla = teclado.getKey();
  
  ledAmarelo();
  lcd.setCursor(0,0);
  lcd.print("Senha Atual: ");
  
  if(tecla == 'D'){
    lcd.clear();
    contador = 0;
    }
  while(tecla == 'D'){
    Menu();     
  }
  
  if ((tecla) && (contador<6)){
  lcd.setCursor(0,0);
  lcd.print("Senha Atual: ");
  lcd.setCursor(contador, 1);
  lcd.print("*");
  entrada[contador] = tecla;
  contador++;
  }
  	  if (tecla == '#'){
    	 entrada[contador] = '\0';
       if((entrada[0] == conta2[0]) &&(entrada[1] == conta2[1]) && (entrada[2] == conta2[2]) && (entrada[3] == conta2[3])&& (entrada[4] == conta2[4])&& (entrada[5] == conta2[5]) && (entrada[6] == conta2[6])){
           contador = 0;
           lcd.clear();
            
         while(true){
           RedefinirConta2();
          }}
          else{
           SenhaIncorreta2();
          }}
 if (botao == HIGH){ //Destrava a Tranca pelo lado de dentro da porta.
    lcd.clear();
    PortaDesbloqueada();
  }}

//------------------------------------------------------------------------------------------------------------------

void SenhaAtual3(){
  
  botao = digitalRead(A0);
  char tecla = teclado.getKey();
  
  ledAmarelo();
  lcd.setCursor(0,0);
  lcd.print("Senha Atual: ");
  
  if(tecla == 'D'){
    lcd.clear();
    contador = 0;
    }
  while(tecla == 'D'){
    Menu();     
  }
  
  if ((tecla) && (contador<6)){
  lcd.setCursor(0,0);
  lcd.print("Senha Atual: ");
  lcd.setCursor(contador, 1);
  lcd.print("*");
  entrada[contador] = tecla;
  contador++;
  }
    if (tecla == '#'){
     	entrada[contador] = '\0';
       if((entrada[0] == conta3[0]) &&(entrada[1] == conta3[1]) && (entrada[2] == conta3[2]) && (entrada[3] == conta3[3])&& (entrada[4] == conta3[4])&& (entrada[5] == conta3[5]) && (entrada[6] == conta3[6])){
           contador = 0;
           lcd.clear();
            
         while(true){
           RedefinirConta3();
          }}
          else{
           SenhaIncorreta3();
          }}
 if (botao == HIGH){ //Destrava a Tranca pelo lado de dentro da porta.
    lcd.clear();
    PortaDesbloqueada();
  }}

//------------------------------------------------------------------------------------------------------------------

void RedefinirConta1(){
  
  botao = digitalRead(A0);
  char tecla = teclado.getKey();

  ledAmarelo();
  lcd.setCursor(0,0);
  lcd.print("Nova Senha: ");
  
 if ((tecla) && (contador<6)){ 
  lcd.setCursor(0,0);
  lcd.print("Nova Senha: ");
  lcd.setCursor(contador, 1);
  lcd.print("*");
  entrada[contador] = tecla;
  contador++;
 }
 	  if (tecla == '#'){
        
    	 entrada[contador] = '\0';
         lcd.clear();
   		 contador = 0;
   		  confirmar[0] = entrada[0];
   		  confirmar[1] = entrada[1];
   		  confirmar[2] = entrada[2];
   		  confirmar[3] = entrada[3];
  		  confirmar[4] = entrada[4];
  	      confirmar[5] = entrada[5];
   		  confirmar[6] = entrada[6];
        
         while(true){     
   		  ConfirmarSenha1();
         }}
  btns(tecla);
 }

//------------------------------------------------------------------------------------------------------------------

void RedefinirConta2(){
  
  botao = digitalRead(A0);
  char tecla = teclado.getKey();
  
  ledAmarelo();
  lcd.setCursor(0,0);
  lcd.print("Nova Senha: ");
  
  if(tecla == 'D'){
    lcd.clear();
    contador = 0;
    }
  while(tecla == 'D'){
    Menu();     
  }
  
  if ((tecla) && (contador<6)){
     lcd.setCursor(0,0);
     lcd.print("Nova Senha: ");
     lcd.setCursor(contador, 1);
     lcd.print("*");
     entrada[contador] = tecla;
     contador++;
  }
   if (tecla == '#'){
     
    	 entrada[contador] = '\0';
         lcd.clear();
   		 contador = 0;
   		  confirmar[0] = entrada[0];
   		  confirmar[1] = entrada[1];
   		  confirmar[2] = entrada[2];
   		  confirmar[3] = entrada[3];
  		  confirmar[4] = entrada[4];
  	      confirmar[5] = entrada[5];
   		  confirmar[6] = entrada[6];
        
         while(true){     
   		  ConfirmarSenha2();
        }}
 if (botao == HIGH){ //Destrava a Tranca pelo lado de dentro da porta.
    lcd.clear();
    PortaDesbloqueada();
  }}

//------------------------------------------------------------------------------------------------------------------

void RedefinirConta3(){
  
  botao = digitalRead(A0);
  char tecla = teclado.getKey();
  
  ledAmarelo();
  lcd.setCursor(0,0);
  lcd.print("Nova Senha: ");
  
  if(tecla == 'D'){
    lcd.clear();
    contador = 0;
    }
  while(tecla == 'D'){
    Menu();     
  }
  
   if ((tecla) && (contador<6)){ 
    lcd.setCursor(0,0);
    lcd.print("Nova Senha: ");
    lcd.setCursor(contador, 1);
    lcd.print("*");
    entrada[contador] = tecla;
    contador++;
     }
      if (tecla == '#'){
        
    	 entrada[contador] = '\0';
         lcd.clear();
   		 contador = 0;
   		  confirmar[0] = entrada[0];
   		  confirmar[1] = entrada[1];
   		  confirmar[2] = entrada[2];
   		  confirmar[3] = entrada[3];
  		  confirmar[4] = entrada[4];
  	      confirmar[5] = entrada[5];
   		  confirmar[6] = entrada[6];
        
         while(true){     
   		  ConfirmarSenha3();
        }}
 if (botao == HIGH){ //Destrava a Tranca pelo lado de dentro da porta.
    lcd.clear();
    PortaDesbloqueada();
  }}

//------------------------------------------------------------------------------------------------------------------

void ConfirmarSenha1(){
  
  botao = digitalRead(A0);
  char tecla = teclado.getKey();
  
  ledAmarelo();
  lcd.setCursor(0,0);
  lcd.print("Confirme Senha: ");

   if ((tecla) && (contador<6)){
      lcd.setCursor(0,0);
      lcd.print("Confirme Senha: ");
      lcd.setCursor(contador, 1);
      lcd.print("*");
      entrada[contador] = tecla;
      contador++;
       }
     if (tecla == '#'){
    	 entrada[contador] = '\0';

     	   if((entrada[0] ==  confirmar[0]) &&(entrada[1] ==  confirmar[1]) && (entrada[2] == confirmar[2]) && (entrada[3] ==  confirmar[3])&& (entrada[4] ==  confirmar[4])&& (entrada[5] ==  confirmar[5]) && (entrada[6] ==  confirmar[6])){
               
               contador = 0;
               conta1[0] = entrada[0];
               conta1[1] = entrada[1];
               conta1[2] = entrada[2];
               conta1[3] = entrada[3];
               conta1[4] = entrada[4];
               conta1[5] = entrada[5];
               conta1[6] = entrada[6];
             
       while(true){     
   		  SenhaRedefinida();
       }}
             else{
               lcd.clear(); 
               contador = 0;
                while(true){        		  
                 RedefinirConta1();
                }}}
  btns(tecla);
 }

//------------------------------------------------------------------------------------------------------------------
              
void ConfirmarSenha2(){
  
  botao = digitalRead(A0);
  char tecla = teclado.getKey();
  
  ledAmarelo();
  lcd.setCursor(0,0);
  lcd.print("Confirme Senha: ");
  
  if(tecla == 'D'){
    lcd.clear();
    contador = 0;
    }
  while(tecla == 'D'){
    Menu();     
  }
  
   if ((tecla) && (contador<6)){ 
      lcd.setCursor(0,0);
      lcd.print("Confirme Senha: ");
      lcd.setCursor(contador, 1);
      lcd.print("*");
      entrada[contador] = tecla;
      contador++;
       }
      if (tecla == '#'){
    	 entrada[contador] = '\0';
    
     	   if((entrada[0] ==  confirmar[0]) &&(entrada[1] ==  confirmar[1]) && (entrada[2] == confirmar[2]) && (entrada[3] ==  confirmar[3])&& (entrada[4] ==  confirmar[4])&& (entrada[5] ==  confirmar[5]) && (entrada[6] ==  confirmar[6])){
               
               contador = 0;
               conta2[0] = entrada[0];
               conta2[1] = entrada[1];
               conta2[2] = entrada[2];
               conta2[3] = entrada[3];
               conta2[4] = entrada[4];
               conta2[5] = entrada[5];
               conta2[6] = entrada[6];
             
       while(true){     
   		  SenhaRedefinida();
       }}
             else{
               lcd.clear(); 
               contador = 0;
                while(true){        		  
                 RedefinirConta2();
                }}}
 if (botao == HIGH){ //Destrava a Tranca pelo lado de dentro da porta.
    lcd.clear();
    PortaDesbloqueada();
  }}

//------------------------------------------------------------------------------------------------------------------
      
void ConfirmarSenha3(){
  
  botao = digitalRead(A0);
  char tecla = teclado.getKey();
  
  ledAmarelo();
  lcd.setCursor(0,0);
  lcd.print("Confirme Senha: ");
  
  if(tecla == 'D'){
    lcd.clear();
    contador = 0;
    }
  while(tecla == 'D'){
    Menu();     
  }
  
   if ((tecla) && (contador<6)){
      lcd.setCursor(0,0);
      lcd.print("Confirme Senha: ");
      lcd.setCursor(contador, 1);
      lcd.print("*");
      entrada[contador] = tecla;
      contador++;
       }
   if (tecla == '#'){
    	 entrada[contador] = '\0';
   
     	   if((entrada[0] ==  confirmar[0]) &&(entrada[1] ==  confirmar[1]) && (entrada[2] == confirmar[2]) && (entrada[3] ==  confirmar[3])&& (entrada[4] ==  confirmar[4])&& (entrada[5] ==  confirmar[5]) && (entrada[6] ==  confirmar[6])){
               
               contador = 0;
               conta3[0] = entrada[0];
               conta3[1] = entrada[1];
               conta3[2] = entrada[2];
               conta3[3] = entrada[3];
               conta3[4] = entrada[4];
               conta3[5] = entrada[5];
               conta3[6] = entrada[6];
             
       while(true){     
   		  SenhaRedefinida();
       }}
             else{
               lcd.clear(); 
               contador = 0;
                while(true){        		  
                 RedefinirConta3();
                }}}
 if (botao == HIGH){ //Destrava a Tranca pelo lado de dentro da porta.
    lcd.clear();
    PortaDesbloqueada();
  }}

//------------------------------------------------------------------------------------------------------------------     
      
void SenhaRedefinida(){
     
         ledVerde();
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Senha redefinida");
         lcd.setCursor(0,1);
         lcd.print("com sucesso.");
         delay(3000);
         lcd.clear();
         erro = 0;
  
       while(true){     
   		 Menu();
       }}  

//------------------------------------------------------------------------------------------------------------------
void SenhaCorreta(){
     lcd.clear();
     lcd.print("Senha Correta!");
     ledVerde();
     delay(2000);
     lcd.clear();     
     PortaDesbloqueada();
}   

void PortaDesbloqueada(){
        
     lcd.print("Porta Aberta!");
     delay(1000);
     digitalWrite(Led_verde,LOW); 
     lcd.clear();
     lcd.print("Porta Fechada!");         
     digitalWrite(Led_vermelho, HIGH);
     delay(1000);
          
     digitalWrite(Led_vermelho, LOW);   
     contador = 0;
     lcd.clear();
     digitalWrite(Led_amarelo, HIGH);
     erro = 0;
  
  while(true){
 		 Menu();
  }}
    
//------------------------------------------------------------------------------------------------------------------
    
void PortaBloqueada(){
    
   
    ledVermelho();
    lcd.clear();
    lcd.print("Senha Incorreta!");
    delay(2000);
    lcd.clear();
    lcd.print("Tente Novamente!");
    delay(1000);
    
     
     digitalWrite(Led_vermelho,LOW); 
     contador = 0;
     erro++;    
     lcd.clear();
     DigitarSenha();
     digitalWrite(Led_amarelo, HIGH);
    
       if(erro>2){       
          SistemaTravado();       
        }}
      
//----------------------------------------------------------------------------------------------------------

void SistemaTravado(){
  
    ledVermelho();
    lcd.clear();
    lcd.print("Sistema Travado!");
    delay(30000);
    lcd.clear();
    digitalWrite(Led_vermelho, LOW);
    erro = 0;
      while(true){
 		 Menu();
  }
   }    

//----------------------------------------------------------------------------------------------------------

void SenhaIncorreta1(){
  
  digitalWrite(Led_vermelho, HIGH);
  contador = 0;
  lcd.clear();
  lcd.print("Senha Incorreta!");
  delay(2000);
  lcd.clear();
  lcd.print("Tente Novamente!");
  delay(1000);
  lcd.clear();
  SenhaAtual();
}

//----------------------------------------------------------------------------------------------------------

void SenhaIncorreta2(){
  
  digitalWrite(Led_vermelho, HIGH);
  contador = 0;
  lcd.clear();
  lcd.print("Senha Incorreta!");
  delay(2000);
  lcd.clear();
  lcd.print("Tente Novamente!");
  delay(1000);
  lcd.clear();
  SenhaAtual2();
}

//----------------------------------------------------------------------------------------------------------

void SenhaIncorreta3(){
  
  ledVermelho();
  contador = 0;
  lcd.clear();
  lcd.print("Senha Incorreta!");
  delay(2000);
  lcd.clear();
  lcd.print("Tente Novamente!");
  delay(1000);
  lcd.clear();
  SenhaAtual3();
}