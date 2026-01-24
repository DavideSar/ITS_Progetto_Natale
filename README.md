
# Visualizzatore Musicale - Albero di Natale

Un progetto Arduino che visualizza un'animazione di un albero di Natale su una matrice LED 8x12, reattivo al volume della musica.

## Descrizione

Questo progetto utilizza l'Arduino Uno R4 WiFi con un sensore microfono MAX4466 per creare un feedback visivo in tempo reale basato sull'intensità sonora. L'albero di Natale si riempie progressivamente su 10 livelli differenti a seconda del volume rilevato, creando un effetto simile a un VU-meter grafico.

## Hardware Necessario

- Arduino Uno R4 WiFi
- Amplificatore operazionale MAX4466
- Cavi jumper
- Cavo USB-C

## Collegamento

Collegare il MAX4466 all'Arduino come segue:

- **5V** → Pin 5V
- **GND** → Pin GND
- **OUT** → Pin A0 (analogico)

## Funzionamento

### Campionamento Audio
Il sistema campiona il segnale audio in finestre di 50ms, calcolando l'ampiezza picco-picco (P2P) per determinare l'intensità sonora.

### Mappatura Livelli
Il valore di volume viene mappato in 10 livelli (0-9), ciascuno corrispondente a un frame diverso dell'animazione.

### Visualizzazione
L'albero si riempie progressivamente sulla matrice LED: il livello 0 mostra solo il contorno, mentre il livello 9 lo mostra completamente illuminato.

## Parametri di Calibrazione

Modificabili nel codice:

```arduino
int sogliaSilenzio = 50;    // Valore minimo per ignorare il rumore
int sensibilita = 200;      // Soglia per raggiungere livello massimo
int reference = 100;        // Offset rumore
```

## Struttura del Progetto

- `Progetto_Natale.ino` - Sketch principale
- `Animazione_Albero.h` - File header con i 10 frame dell'albero

## Librerie Richieste

- `Arduino_LED_Matrix.h`

## Utilizzo

1. Collegare l'Arduino al PC
2. Caricare lo sketch tramite Arduino IDE
3. Aprire il Serial Monitor per il debug
4. Riprodurre musica natalizia - l'albero reagirà al volume!

## Autori

Progetto realizzato nel corso ITS EMBT03 da: <br>
Davide Sargiacomo, Roberto Andrea Marchetti, Michele Cabutto e Yassine Sakhoune
