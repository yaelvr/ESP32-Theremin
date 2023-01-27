int flag = 0;
//
int frequency;
int DISTANCIA = 0;
int DISTMEDIDA = 0;

int DISTVOL = 0;
int VOLUMEN = 0;
int volmed = 0;
//NOTA DERCHA
int pinEco = 27;
int pinGatillo = 14;
//VOLUMEN IZQUIERDA
int volTriger = 12;
int volEcho = 13;
//Declaramos el pin del zumbador
int pinZumbador = 26;
//Inicializamos las variables de la salida pwm
int canal = 0, frec = 2000, resolucion = 8;

void readUltrasonicDistance(void *pvParameters) {
  for (;;) {
    // este es tu segundo loop
    // aqui va el codigo de tu segunda tarea
    //Iniciamos el pin del emisor de reuido en salida
    pinMode(pinGatillo, OUTPUT);
    //Apagamos el emisor de sonido
    digitalWrite(pinGatillo, LOW);
    //Retrasamos la emision de sonido por 2 milesismas de segundo
    delayMicroseconds(2);
    // Comenzamos a emitir sonido
    digitalWrite(pinGatillo, HIGH);
    //Retrasamos la emision de sonido por 2 milesismas de segundo
    delayMicroseconds(10);
    //Apagamos el emisor de sonido
    digitalWrite(pinGatillo, LOW);
    //Comenzamos a escuchar el sonido
    pinMode(pinEco, INPUT);
    // Calculamos el tiempo que tardo en regresar el sonido
    DISTMEDIDA = pulseIn(pinEco, HIGH);
    DISTANCIA = 0.01723 * DISTMEDIDA;
    if (DISTANCIA > 45) {
      DISTANCIA = 0;
    }

    pinMode(volTriger, OUTPUT);
    //Apagamos el emisor de sonido
    digitalWrite(volTriger, LOW);
    //Retrasamos la emision de sonido por 2 milesismas de segundo
    delayMicroseconds(2);
    // Comenzamos a emitir sonido
    digitalWrite(volTriger, HIGH);
    //Retrasamos la emision de sonido por 2 milesismas de segundo
    delayMicroseconds(10);
    //Apagamos el emisor de sonido
    digitalWrite(volTriger, LOW);
    //Comenzamos a escuchar el sonido
    pinMode(volEcho, INPUT);
    // Calculamos el tiempo que tardo en regresar el sonido
    DISTVOL = 0.01723 * pulseIn(volEcho, HIGH);
    if (DISTVOL > 30) {
      DISTVOL = 0;
      VOLUMEN = 0;
    } else {
      VOLUMEN = int(255 - (DISTVOL * 8.5));
    }

  }
}

void setup() {
  Serial.begin(115200);
  //Inicializamos la salida del pwm
  ledcSetup(canal, frec, resolucion);
  //Declaramos pin donde se conecta el zumbador
  ledcAttachPin(pinZumbador, 0);
  xTaskCreate(readUltrasonicDistance, "mi_tarea", 10000, NULL, 1, NULL);
}

void loop() {
  //Declaramos la variable que va incrementando para que suene com mayor frecuencia
  // CONTADOR PARA QUE NO SE PASME EL LOOP
  flag++;
  if (flag == 10000) {
    flag = 0;
  }
  Serial.println("Volumen");
  Serial.println(VOLUMEN);
  
   if (DISTANCIA >= 0 && DISTANCIA <= 10) {
    // Do
    frequency = map(DISTANCIA, 0, 10, 261, 262);  // 261 - 262 Hz
    ledcWriteTone(canal, frequency);
    ledcWrite(canal, VOLUMEN);
  } else if (DISTANCIA >= 11 && DISTANCIA <= 20) {
    // Re
    frequency = map(DISTANCIA, 11, 20, 293, 294);  // 293 - 294 Hz
    ledcWriteTone(canal, frequency);
    ledcWrite(canal, VOLUMEN);
  } else if (DISTANCIA >= 21 && DISTANCIA <= 30) {
    // Mi
    frequency = map(DISTANCIA, 21, 30, 329, 330);  // 329 - 330 Hz
    ledcWriteTone(canal, frequency);
    ledcWrite(canal, VOLUMEN);
  }
  // Add more else if statements for the remaining notes
  else if (DISTANCIA >= 31 && DISTANCIA <= 40) {
    // Fa
    frequency = map(DISTANCIA, 31, 40, 349, 350);  // 349 - 350 Hz
    ledcWriteTone(canal, frequency);
    ledcWrite(canal, VOLUMEN);
  } else if (DISTANCIA >= 41 && DISTANCIA <= 50) {
    // Sol
    frequency = map(DISTANCIA, 41, 50, 392, 393);  // 392 - 393 Hz
    ledcWriteTone(canal, frequency);
    ledcWrite(canal, VOLUMEN);
  } else if (DISTANCIA >= 51 && DISTANCIA <= 60) {
    // La
    frequency = map(DISTANCIA, 51, 60, 440, 441);  // 440 - 441 Hz
    ledcWriteTone(canal, frequency);
    ledcWrite(canal, VOLUMEN);
  } else if (DISTANCIA >= 61 && DISTANCIA <= 70) {
    // Si
    frequency = map(DISTANCIA, 61, 70, 493, 494);  // 493 - 494 Hz
    ledcWriteTone(canal, frequency);
    ledcWrite(canal, VOLUMEN);
  }
  // Add a final else statement for any values outside of the range
  else {
    ledcWrite(canal, 0);  // turn off the speaker if the distance is not within the range
  }

  delay(10);
}