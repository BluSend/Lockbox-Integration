#include <Adafruit_HX711.h>

// Define the data and clock pins
const uint8_t DATA_PINS[4] = {2, 4, 6, 8}; 
const uint8_t CLOCK_PINS[4] = {3, 5, 7, 9};

// Parameters for converting raw value to gram
int32_t offset[4] = {0, 0, 0, 0}; // varies among different load cells
float factor[4] = {97.0f, 103.0f, 100.0f, 100.0f}; // temp counts/g, varies among different load cells

Adafruit_HX711 hx711[4] = {
  Adafruit_HX711(DATA_PINS[0], CLOCK_PINS[0]),
  Adafruit_HX711(DATA_PINS[1], CLOCK_PINS[1]),
  Adafruit_HX711(DATA_PINS[2], CLOCK_PINS[2]),
  Adafruit_HX711(DATA_PINS[3], CLOCK_PINS[3]),
};

int32_t readRaw(uint8_t i) {
  return hx711[i].readChannelBlocking(CHAN_A_GAIN_128);
}

void tare_cell(uint8_t i){
  for (int k = 0; k < 3; k++) {                 // discard first few readings
    readRaw(i);
  }
  int64_t sum = 0;
  const int N = 10;
  for (int k = 0; k < N; k++) {
    sum += readRaw(i);
  }
  offset[i] = (int32_t)(sum / N);
}

float read_loadcell(uint8_t i){
  float val = (float)(readRaw(i) - offset[i]) / factor[i]; // grams

  /* if(val < 0){
    val = 0;
  } */ // uncomment this condition after testing has done
  return val;
}


void setup() {
  Serial.begin(115200);
  
  // Wait for serial port to connect
  while (!Serial) {
    delay(10);
  }
  
  Serial.println("Adafruit HX711 Test!");
  
  // Initialize the HX711
  hx711[0].begin();
  
  // Tare channel A with gain 128 (standard for 4-wire load cells)
  Serial.println("Tareing...");
  hx711[0].tareA(0); 

  // ---- Offset estimation (load cell must be EMPTY) ----
  Serial.println("Measuring offset... keep load cell empty");
  delay(500); 
  for (int i = 0; i < 3; i++) {                 // discard first few readings
    hx711[0].readChannelBlocking(CHAN_A_GAIN_128);
  }
  int64_t sum = 0;
  const int N = 10;
  for (int i = 0; i < N; i++) {
    sum += hx711[0].readChannelBlocking(CHAN_A_GAIN_128);
  }
  offset[0] = (int32_t)(sum / N);

  Serial.print("Offset: ");
  Serial.println(offset[0]);
  // ------------------------------------------------------

  
}


void loop() {
  // Read blocking from Channel A with Gain 128
  int32_t raw = hx711[0].readChannelBlocking(CHAN_A_GAIN_128);
  float val = (float)(raw - offset[0]) / factor[0]; // grams

  /* if(val < 0){
    val = 0;
  } */ // uncomment this condition after testing has done
  
  Serial.print("Raw: ");
  Serial.print(raw);
  Serial.print("      ");
  Serial.print("g: ");
  Serial.println(val);
  
  delay(500);
}
