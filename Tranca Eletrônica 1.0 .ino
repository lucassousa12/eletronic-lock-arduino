#include <LiquidCrystal.h>
#include <Keypad.h>
#define Led_vermelho A3
#define Led_amarelo A4
#define Led_verde A5


LiquidCrystal lcd(0,1,10,11,12,13);

const byte linhas= 4; 
const byte colunas= 4; 

char mapateclado[linhas][colunas]= {
{'1', '2', '3', }, 
{'4', '5', '6', }, 
{'7', '8', '9', },
{'*', '0', '#', }
};

byte pinoslinhas[linhas] = {9,8,7,6}; 
byte pinoscolunas[colunas]= {5,4,3,2};

Keypad teclado = Keypad(makeKeymap(mapateclado), pinoslinhas, pinoscolunas, linhas, colunas);

char conta1[ ] = {'1','2','3','4','5','6','\0'};
char conta2[ ] = {'6','5','4','3','2','1','\0'};
char conta3[ ] = {'1','4','7','3','6','9','\0'};
char entrada[ ] = {'0','0','0','0','0','0','\0'};

int contador =0; 
int erro =0;


//------------------------------------------------------------------------------------------------------------------

void setup(){


  lcd.begin(16,2);
  pinMode(Led_verde,OUTPUT);
  pinMode(Led_vermelho,OUTPUT);
  pinMode(Led_amarelo,OUTPUT);

  
  lcd.print("Inicializando..");
  delay(1500);
  lcd.clear();
}
  void gg(){
    
  lcd.setCursor(0,0);
  lcd.print("Digite a Senha:");
  digitalWrite(Led_amarelo, HIGH);

 

}

//------------------------------------------------------------------------------------------------------------------

void loop(){
 
  gg();
  
  char tecla = teclado.getKey();

  if (tecla) {

  
  lcd.setCursor(0,0);
  lcd.print("Digite a Senha: ");
  lcd.setCursor(contador, 1);
  lcd.print(tecla);
  delay(1);

  entrada[contador] = tecla;
  contador++;

  if (contador == 6 )
    {
  entrada[contador] = '\0';

  if((entrada[0] == conta1[0]) &&(entrada[1] == conta1[1]) && (entrada[2] == conta1[2]) && (entrada[3] == conta1[3])&& (entrada[4] == conta1[4])&& (entrada[5] == conta1[5]) && (entrada[6] == conta1[6])
           || (entrada[0] == conta2[0]) &&(entrada[1] == conta2[1]) && (entrada[2] == conta2[2]) && (entrada[3] == conta2[3])&& (entrada[4] == conta2[4])&& (entrada[5] == conta2[5]) && (entrada[6] == conta2[6])
           || (entrada[0] == conta3[0]) &&(entrada[1] == conta3[1]) && (entrada[2] == conta3[2]) && (entrada[3] == conta3[3])&& (entrada[4] == conta3[4])&& (entrada[5] == conta3[5]) && (entrada[6] == conta3[6]))  
        {
    PortaDesbloqueada();
  }

     else
     {
       PortaBloqueada();
 }}}}

//------------------------------------------------------------------------------------------------------------------

  void PortaDesbloqueada(){
      
     lcd.clear();
     lcd.print("Senha Correta!");
     digitalWrite(Led_amarelo, LOW); 
     digitalWrite(Led_verde,HIGH); 
     delay (500);
    
     lcd.clear();     
    
     lcd.print("Porta Aberta!");

     delay(8000);
     digitalWrite(Led_verde,LOW); 
     lcd.clear();
     lcd.print("Porta Fechada!");         
     digitalWrite(Led_vermelho, HIGH);
     delay(1500);
          
     digitalWrite(Led_vermelho, LOW);   
     contador = 0;
     lcd.clear();
     lcd.print ("Digite a Senha: ");
    digitalWrite(Led_amarelo, HIGH);
  }
    
//------------------------------------------------------------------------------------------------------------------
    
  void PortaBloqueada()
  {
     lcd.clear();
     lcd.print("Senha incorreta!");
     digitalWrite(Led_vermelho,HIGH);
     digitalWrite(Led_amarelo, LOW);
     delay(1500);
     
     digitalWrite(Led_vermelho,LOW); 
     contador = 0;
     erro++;    
     lcd.clear();
     lcd.print("Digite a Senha: ");
     digitalWrite(Led_amarelo, HIGH);
    
       if(erro>0){
       
          SistemaTravado();
       
        }
}
   
    
    
    

//----------------------------------------------------------------------------------------------------------

void SistemaTravado(){
  
    digitalWrite(Led_amarelo, LOW);
    digitalWrite(Led_verde, LOW);
    digitalWrite(Led_vermelho, HIGH);
  
    lcd.clear();
    lcd.print("Sistema Travado!");
    delay(1000);
    lcd.clear();
    digitalWrite(Led_vermelho, LOW);
    gg();
   
    
  
}
  
  

