const int trigPin = 3; //envia o sinl para o sensor medir
const int echoPin = 2; //pino resposta, envia o sinal de volta ao arduino
const int dataPin = 11;
const int latchPin = 8;
const int clockPin = 12;

// cada byte desses acende um segmentos
const byte numeros[10] = {
B00111111, // 0
B00000110, // 1
B01011011, // 2
B01001111, // 3
B01100110, // 4
B01101101, // 5
B00000111, // 7
 B01111111, // 8
 B01101111  // 9
 };
// definindo todos os pinos como saida
void setup() {
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(dataPin, OUTPUT);
pinMode(latchPin, OUTPUT);
pinMode(clockPin, OUTPUT);
Serial.begin(9600);
  }

void loop() {
// medição sendo realizada
digitalWrite(trigPin, LOW); // sensor inicialmente desligado
  delay(2);
 digitalWrite(trigPin, HIGH); // sensor é ativado para realizar a medição
 delay(10);
digitalWrite(trigPin, LOW);
 long duracao = pulseIn(echoPin, HIGH); // calcula quanto tempo demora para o som ir e voltar
int distancia = duracao / 58; // convertendo para cm

if (distancia > 9999) distancia = 9999; 

// digitos de unidade , dezena, centena , e milhar sendo repartidos para cada display
int milhar = (distancia / 1000) % 10;
int centena = (distancia / 100) % 10;
int dezena = (distancia / 10) % 10;
int unidade = distancia % 10;
 Serial.print("Distância: "); // imprime a mensagem com a distancia no terminal
 Serial.println(distancia);

// cascateamento dos registradores sendo realiazado(interconectando eles e passando as informações para cada um individualmente)
digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, numeros[milhar]);   
shiftOut(dataPin, clockPin, MSBFIRST, numeros[centena]); 
shiftOut(dataPin, clockPin, MSBFIRST, numeros[dezena]);   
shiftOut(dataPin, clockPin, MSBFIRST, numeros[unidade]); 
digitalWrite(latchPin, HIGH);
delay(300);
 }