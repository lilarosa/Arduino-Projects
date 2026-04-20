#include <math.h>  // Bietet mathematische Funktionen wie log() fuer die Temperaturberechnung.

const int analogPin = A0;  // Der NTC-Sensor ist am analogen Eingang A0 angeschlossen.
const int ledPin = 6;  // Die Status-LED ist an Pin 6 angeschlossen.
const int fanPin = 10;  // Der Luefter wird ueber Pin 10 geschaltet.

const float targetTempC = 20.0;  // Gewuenschte Solltemperatur in Grad Celsius.
const float hysteresisC = 0.5;  // Hysterese verhindert zu haeufiges Ein- und Ausschalten.

bool fanOn = false;  // Speichert, ob der Luefter aktuell eingeschaltet ist.
unsigned long lastLogTime = 0;  // Speichert den Zeitpunkt der letzten seriellen Ausgabe.
const unsigned long logIntervalMs = 2000;  // Ausgabeintervall fuer den seriellen Monitor in Millisekunden.

const int fixedResistor = 10000;  // Festwiderstand des Spannungsteilers in Ohm.
const int betaValue = 3950;  // Beta-Wert des NTC fuer die Umrechnung in Temperatur.
const int r0 = 10000;  // Nennwiderstand des NTC bei 25 Grad Celsius.

void setup() {  // Diese Funktion wird beim Start genau einmal ausgefuehrt.
  Serial.begin(9600);  // Startet die serielle Kommunikation mit 9600 Baud.
  pinMode(ledPin, OUTPUT);  // Setzt den LED-Pin als Ausgang.
  pinMode(fanPin, OUTPUT);  // Setzt den Luefter-Pin als Ausgang.
}  // Ende der Setup-Funktion.

void loop() {  // Diese Funktion laeuft danach fortlaufend in einer Schleife.
  int raw = analogRead(analogPin);  // Liest den aktuellen Analogwert des NTC ein.
  if (raw <= 0) {  // Prueft, ob ein ungueltiger oder kritischer Messwert vorliegt.
    delay(500);  // Wartet kurz, bevor erneut gemessen wird.
    return;  // Bricht den aktuellen Schleifendurchlauf ab.
  }  // Ende der Sicherheitsabfrage fuer den Messwert.

  float rNtc = fixedResistor * (1023.0 / raw - 1.0);  // Berechnet den aktuellen Widerstand des NTC.
  float tempK = 1.0 / (1.0 / 298.15 + (1.0 / betaValue) * log(rNtc / r0));  // Rechnet den Widerstand in Kelvin um.
  float tempC = tempK - 273.15;  // Wandelt Kelvin in Grad Celsius um.

  if (millis() - lastLogTime >= logIntervalMs) {  // Prueft, ob das Ausgabeintervall erreicht wurde.
    Serial.print("Temperature: ");  // Gibt einen Text als Einleitung im seriellen Monitor aus.
    Serial.print(tempC);  // Gibt den aktuellen Temperaturwert aus.
    Serial.println(" C");  // Ergaenzt die Einheit und erzeugt einen Zeilenumbruch.
    lastLogTime = millis();  // Speichert den Zeitpunkt der letzten Ausgabe.
  }  // Ende der seriellen Protokollierung.

  if (!fanOn && tempC > targetTempC + hysteresisC) {  // Schaltet ein, wenn der obere Grenzwert ueberschritten wird.
    digitalWrite(fanPin, HIGH);  // Aktiviert den Luefter.
    digitalWrite(ledPin, HIGH);  // Aktiviert die LED als Statusanzeige.
    fanOn = true;  // Merkt sich den neuen Zustand "Luefter an".
  } else if (fanOn && tempC < targetTempC - hysteresisC) {  // Schaltet aus, wenn der untere Grenzwert unterschritten wird.
    digitalWrite(fanPin, LOW);  // Deaktiviert den Luefter.
    digitalWrite(ledPin, LOW);  // Deaktiviert die LED.
    fanOn = false;  // Merkt sich den neuen Zustand "Luefter aus".
  }  // Ende der Zweipunktregelung mit Hysterese.

  delay(200);  // Kleine Pause zur Stabilisierung der Schleife.
}  // Ende der Hauptschleife.
