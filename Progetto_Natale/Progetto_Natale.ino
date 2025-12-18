#include "Arduino_LED_Matrix.h"
#include "Animazione_Albero.h" // file con i disegni

ArduinoLEDMatrix matrix;

//#define LOGARITMIC
const int micPin = A0;
const int ledPin = LED_BUILTIN;
const int sampleWindow = 50; 

// Parametri di calibrazione
int sogliaSilenzio = 50;        // Valore minimo per ignorare il rumore di fondo
int sensibilita = 200;          // Oltre questo valore si raggiunge il livello massimo
int reference = 100;            // Offset rumore

float logVal;

// Struttura per gestire il frame corrente da inviare alla matrice
uint8_t frame[8][12]; 


// array di puntatori per accedere ai disegni (0-9) definiti nel file .h
const byte (*livelliAnimazione[10])[12] = {
  disegno0, // Livello 0 (Silenzio)
  disegno1, // Livello 1
  disegno2, 
  disegno3,
  disegno4,
  disegno5,
  disegno6,
  disegno7,
  disegno8,
  disegno9  // (Massimo volume)
};

void setup() {
  Serial.begin(115200);
  matrix.begin();
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long startMillis = millis();
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // 1. Campionamento
  while (millis() - startMillis < sampleWindow) {
    int sample = analogRead(micPin);
    if (sample < 1024) {
      if (sample > signalMax) signalMax = sample;
      else if (sample < signalMin) signalMin = sample;
    }
  }

  // Calcolo ampiezza P2P
  int diff = (int)signalMax - (int)signalMin - reference;
  if (diff < 0) diff = 0;
  unsigned int peakToPeak = (unsigned int)diff;

  if(peakToPeak > 5000) peakToPeak = 0;

  // intensità luminosa
  int intensitaLed = map(peakToPeak, sogliaSilenzio, sensibilita, 0, 255);
  intensitaLed = constrain(intensitaLed, 0, 255); 
  analogWrite(ledPin, intensitaLed);

  // 2. Mappatura del valore su 10 LIVELLI (da 0 a 9)
  // Invece di mappare su 96 LED, mappiamo sull'indice dell'array di disegni
  int indiceLivello = 0;

#ifdef LOGARITMIC
  if (peakToPeak > 2) { 
    logVal = log10((float)peakToPeak);

  
    indiceLivello = map((logVal - 2.2) * 3000, 0, 600, 0, 9); 
  }
#else
  if (peakToPeak > sogliaSilenzio) {
      indiceLivello = map(peakToPeak, sogliaSilenzio, sensibilita, 1, 9);
  } else {
      indiceLivello = 0;
  }
#endif

  indiceLivello = constrain(indiceLivello, 0, 9);

  aggiornaMatrice(indiceLivello);
  
  // 4. Invio del frame alla matrice
  matrix.renderBitmap(frame, 8, 12);

  // Debug
  Serial.print("Vol:");
  Serial.print(peakToPeak);
  Serial.print(" | Livello:");
  Serial.println(indiceLivello);
}

void aggiornaMatrice(int livelloSelezionato) {
// Scansione per righe e colonne
  for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 12; c++) {
      // pixel dal disegno salvato in Animazione_Albero.h al frame corrente
      frame[r][c] = livelliAnimazione[livelloSelezionato][r][c]; 
    }
  }
}