# 🎄 Visualizzatore Musicale a Tema Natalizio 🎶

Un visualizzatore musicale interattivo basato su Pixel Art, progettato per fornire un feedback visivo in tempo reale dell'intensità sonora. Il sistema utilizza la matrice LED integrata di Arduino Uno R4 WiFi per animare un albero di Natale dinamico che funge da VU-meter grafico.

## 📖 Panoramica del Progetto

Il dispositivo elabora segnali audio acquisiti tramite un amplificatore operazionale (OpAmp) MAX4466. L'obiettivo è la rappresentazione dinamica dei decibel (dB) percepiti, con un'animazione che evolve attraverso 10 livelli di riempimento progressivo, ottimizzati per una griglia 8×12.

## 🛠 Hardware & Strumenti

### Componenti Necessari

- **Microcontrollore:** Arduino Uno R4 WiFi
- **Sensore:** Amplificatore operazionale MAX4466
- **Connettività:** Cavi jumper e cavo USB-C
- **Software:** Arduino IDE e libreria `Arduino_LED_Matrix.h`

### Schema di Cablaggio

| Pin MAX4466 | Pin Arduino Uno R4 | Funzione |
|-------------|-------------------|----------|
| VCC | 5V | Alimentazione OpAmp |
| GND | GND | Chiusura circuito |
| OUT | A0 | Segnale Analogico (Input) |

## ⚙️ Procedimento e Dettagli Tecnici

Il progetto è stato realizzato seguendo una metodologia di sviluppo parallela, dividendo il lavoro tra design delle animazioni e implementazione software.

1. **Analisi P2P (Peak-to-Peak):** All'interno di una finestra di campionamento di 50ms, il firmware calcola l'ampiezza picco-picco del segnale elettrico, isolando i picchi di volume dal rumore di fondo.

2. **Mappatura dei Livelli:** Il valore P2P viene normalizzato e convertito in un indice discreto (0-9) tramite la funzione `map()`, attivando il frame corrispondente alla fascia di intensità rilevata.

3. **Gestione Frame:** Le animazioni sono digitalizzate in matrici di byte e gestite tramite il file header `Animazione_Albero.h`. Il Frame 0 rappresenta lo stato di quiete (solo contorno), mentre i Frame 1-9 gestiscono il riempimento progressivo.

### Parametri di Calibrazione

```cpp
int sogliaSilenzio = 50;  // Filtro per rumore ambientale
int sensibilita = 200;    // Soglia per il picco massimo (Frame 9)
int reference = 100;      // Offset elettrico per il campionamento
```

## 👥 Team di Sviluppo

Progetto realizzato da: <br>
**Davide Sargiacomo, Roberto Andrea Marchetti, Michele Cabutto, Yassine Sakhoune**