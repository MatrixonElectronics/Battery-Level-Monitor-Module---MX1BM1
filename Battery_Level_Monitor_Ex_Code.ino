/*
  ------------------------------------------------------------
  Battery Level Monitor Module - ADC Voltage Reading Example
  ------------------------------------------------------------
  Description:
    This example reads battery voltage from the CL pin of the
    Battery Level Monitor Module using on board voltage divider:
     R1 = 100kΩ (top)
     R2 = 10kΩ (bottom)
    The voltage divider output is enabled by driving the EN pin HIGH.
    After a short delay, the ADC reads the voltage at CL.
    The module is then disabled to conserve power.

  Hardware Requirements:
    - Battery Level Monitor Module - MX1MB1
    - Microcontroller with 3.3V ADC (e.g. ESP32, STM32, Pico)
    - CL output connected to analog pin
    - EN input connected to a GPIO

  Divider Scaling:
    Vbat = Vadc / (10k / (100k + 10k)) ≈ Vadc / 0.0909

  Battery Level Monitor Module © 2025 by Matrixon Electronics is 
  licensed under CC BY-SA 4.0.
  Author: Madhesh Ram Kishore Kumar
  Version: 1.0
  Date: July 2025
*/

#define EN_PIN 5
#define CL_PIN A0

void setup() {
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(EN_PIN, HIGH);     // Enable module
  delay(5);                        // Wait for stable output
  int raw = analogRead(CL_PIN);   // Read ADC value
  digitalWrite(EN_PIN, LOW);      // Disable module

  // Voltage divider: R1 = 100k, R2 = 10k
  // Divider ratio: CL = VBAT * (10 / 110) = VBAT * 0.0909
  // So, VBAT = CL / 0.0909

  float v_adc = raw * (3.3 / 4095.0);           // ADC voltage (assuming 12-bit ADC and 3.3V ref)
  float battery_voltage = v_adc / 0.0909;       // Reconstruct battery voltage

  Serial.print("Battery Voltage: ");
  Serial.print(battery_voltage, 2);             // 2 decimal places
  Serial.println(" V");

  delay(1000);
}
