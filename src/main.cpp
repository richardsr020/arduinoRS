#include <Arduino.h>

const int amplitude = 512;  // Moitié de 1023 pour centrer l'onde
const int offset = 512;     // Décalage pour éviter les valeurs négatives
const float frequency = 1.0; // Fréquence en Hz
const float samplingRate = 100.0; // Nombre d'échantillons par seconde

void setup() {
    Serial.begin(500000);
    while (!Serial);  // Attend que la connexion série soit prête
    Serial.println("PONG");  // Répond au test de connexion
}

void loop() {
    static float t = 0.0; // Temps simulé

    // Génération d'une sinusoïde : y = A * sin(2πft) + offset
    int valeur = amplitude * sin(2.0 * PI * frequency * t) + offset;
    
    // Convertir en 2 octets (Little Endian)
    byte low = valeur & 0xFF;
    byte high = (valeur >> 8) & 0xFF;
    Serial.write(low);
    Serial.write(high);

    // Incrémenter le temps en fonction de la fréquence d'échantillonnage
    t += 1.0 / samplingRate;
    delayMicroseconds(10000);  // Ajuste selon le taux d'échantillonnage (100 Hz)
}