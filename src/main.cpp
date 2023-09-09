
#include <AD9850SPI.h>
#include <SPI.h>


const int W_CLK_PIN = 13;
const int FQ_UD_PIN = 8;
const int RESET_PIN = 9;

double freq = 10000;
double inc = 10;
double trimFreq = 124999500;

int phase = 0;


void setFreq() {
  DDS.setfreq(freq, phase);
  Serial.println(freq);
}

void setup(){
  Serial.begin(9600);
  Serial.println("AD9850 Clockgen Test"); Serial.println("");
  DDS.begin(W_CLK_PIN, FQ_UD_PIN, RESET_PIN);
  DDS.calibrate(trimFreq);
  setFreq();
  DDS.up();
}

void loop(void) {
  freq += inc;
  setFreq();
  delay(100);
  if ( freq > 40000) freq = 10000;	
  int c = Serial.read();
  switch(c) {
    case '0': inc = 1.0 ; break;
    case '1': inc = 10.0; break;
    case '2': inc = 100.0; break;
    case '3': inc = 1000.0; break;
    case 'r': freq = 400000; break;
  } 
}
