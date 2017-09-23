int vibr_Pin =3; //Pin analogico para sensor de vibracion
int valvePin = 4; //pin para valvula
int tiempoVibracion = 0;
int tiempoTolerancia = 10; //10 segundos de tolerancia
bool valvulaAbierta = true;

void setup(){

  pinMode(vibr_Pin, INPUT); //poner vibr_Pin como entrada para las mediciones
  pinMode(valvePin, OUTPUT); //setea pin de valvula como salida
  Serial.begin(9600); //salida serial 9600
 // Serial.println("----------------------Vibration demo------------------------");
}
void loop(){
  long measurement =TP_init();

 // Serial.print("measurment = ");
  Serial.println(measurement);
  if (measurement > 1000){ //si la vibracion es mayor a mil
      delay(490);//espera medio segundo, se debe sumar  el delay de TP_init()
      if(++tiempoVibracion>tiempoTolerancia){//si el tiempo de que ha durado la vibracion supera la tolerancia
          //se cambia estado de valvula
          valvulaAbierta = !valvulaAbierta;
      }
  }
  else{
    tiempoVibracion=0;
  }

  if(valvulaAbierta){
      digitalWrite(valvePin, HIGH);
  }else{
      digitalWrite(valvePin, LOW);
  }
}

long TP_init(){
  delay(10);
  long measurement=pulseIn (vibr_Pin, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}
