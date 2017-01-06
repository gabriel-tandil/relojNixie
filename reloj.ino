#include <DS3231.h>

byte brillo;// brillo maximo 0, minimo 255
byte digito0;
byte digito1;
unsigned long milis;
byte vizualizador;
byte datoMostrado;
// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);
const byte cantDatos=4;
const byte v0=10;
const byte v1=11;

void setup() {
  rtc.begin();
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(vo, OUTPUT);//pwm pero al revez visualizador 0
  pinMode(v1, OUTPUT); //pwm pero al revez visualizador 1
  pinMode(12, OUTPUT); //buzer
  
}

void loop() {
  unsigned long milisAct= millis();
  if (milisAct-milis>=1000){
    milis=milisAct;
    
    if (datoMostrado%cantDatos==0){
       mostrar(rtc.getTime().hour); 
    }
    if (datoMostrado%cantDatos==1){
       mostrar(rtc.getTime().min);       
    }
    if (datoMostrado%cantDatos==2){
       mostrar(rtc.getTime().sec);       
    }
    if (datoMostrado%cantDatos==3){
       mostrar((byte)rtc.getTemp()+0.5);    // sumo .5 para redondear en vez de truncar   
    }
    datoMostrado++;
  }
  
  refrescarVisualizadores();

}

void refrescarVisualizadores() {

  if (vizualizador%2==0) {
    digitalWrite(v1, HIGH);// apago display 1
    digitalWrite(digito1, LOW); //apago digito1

    analogWrite(v0, brillo);  // enciendo display 0
    digitalWrite(digito0, HIGH); // enciendo digito 0
  }
  else
  {

    digitalWrite(10, HIGH);// apago display 0
    digitalWrite(digito0, LOW); //apago digito0

    analogWrite(v0, brillo);// enciendo display 1
    digitalWrite(digito1, HIGH); // enciendo digito 1
  }
  vizualizador++;
}

void mostrar (byte v){
  digitalWrite(digito0, LOW);// borro el valor anteriot
  digitalWrite(digito1, LOW);// borro el valor anteriot
  digito0=v/10;
  digito1=v%10;
}


