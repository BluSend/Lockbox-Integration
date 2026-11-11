#include <Adafruit_HX711.h>

// Define the data and clock pins
const uint8_t DATA_PIN = 2; 
const uint8_t CLOCK_PIN = 3;

// Parameters for converting raw value to gram
int32_t offset = 0; // varies among different load cells
float factor = 103.0f; // temp counts/g, varies among different load cells

Adafruit_HX711 hx711(DATA_PIN, CLOCK_PIN);

void setup() {
  Serial.begin(115200);
  
  // Wait for serial port to connect
  while (!Serial) {
    delay(10);
  }
  
  Serial.println("Adafruit HX711 Test!");
  
  // Initialize the HX711
  hx711.begin();
  
  // Tare channel A with gain 128 (standard for 4-wire load cells)
  Serial.println("Tareing...");
  hx711.tareA(0); 

  // ---- Offset estimation (load cell must be EMPTY) ----
  Serial.println("Measuring offset... keep load cell empty");
  delay(500); 
  for (int i = 0; i < 3; i++) {                 // discard first few readings
    hx711.readChannelBlocking(CHAN_A_GAIN_128);
  }
  int64_t sum = 0;
  const int N = 10;
  for (int i = 0; i < N; i++) {
    sum += hx711.readChannelBlocking(CHAN_A_GAIN_128);
  }
  offset = (int32_t)(sum / N);

  Serial.print("Offset: ");
  Serial.println(offset);
  // ------------------------------------------------------

  
}

void loop() {
  // Read blocking from Channel A with Gain 128
  int32_t raw = hx711.readChannelBlocking(CHAN_A_GAIN_128);
  float val = (float)(raw - offset) / factor; // grams
  
  Serial.print("Raw: ");
  Serial.print(raw);
  Serial.print("      ");
  Serial.print("g: ");
  Serial.println(val);
  
  delay(500);
}
