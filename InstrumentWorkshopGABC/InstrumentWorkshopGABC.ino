int BUTTON_PINS[4] = {22, 23, 32, 33};
#define BUZZER_PIN 25 // ESP32 GPIO21 pin connected to Buzzer's pin
int frequencies[4] = {392, 440, 494, 523};   //second half G-A-B-C
int buttonState[4] = {0, 0, 0, 0};
int POT_PIN = 34;   //potentiometer pin
int potValue = 0;
int pot_frequency = 0;
#define pot_button 1
int pot_button_state = 0;

void setup() {
  Serial.begin(9600);                // initialize serial
  pinMode(BUZZER_PIN, OUTPUT);       // set ESP32 pin to output mode
  pinMode(pot_button, INPUT_PULLUP);
  for (int i = 0; i < 4; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
}

void loop() {
  pot_button_state = digitalRead(pot_button);

  for (int i = 0; i < 4; i++) {
    buttonState[i] = digitalRead(BUTTON_PINS[i]);
  }

  while (pot_button_state == LOW){
    potValue = analogRead(POT_PIN); // Read value (0-4095)
    Serial.println(potValue);

    potValue = analogRead(POT_PIN); // Read 0-4095 [5]
    
    // Map pot value to a frequency range (e.g., 100Hz to 2000Hz)
    pot_frequency = map(potValue, 0, 4095, 100, 2000); 
    tone(BUZZER_PIN, pot_frequency); // Generate tone [3]
    pot_button_state = digitalRead(pot_button);
    delay(10); // Small delay for stability
  }

  while (buttonState[0] == LOW) {
    Serial.print("1");
      tone(BUZZER_PIN, frequencies[0]); // turn on
      buttonState[0] = digitalRead(BUTTON_PINS[0]);
  }

  while (buttonState[1] == LOW) {
    Serial.print("2");
      tone(BUZZER_PIN, frequencies[1]); // turn on
      buttonState[1] = digitalRead(BUTTON_PINS[1]);
  }

  while (buttonState[2] == LOW) {
    Serial.print("3");
      tone(BUZZER_PIN, frequencies[2]); // turn on
      buttonState[2] = digitalRead(BUTTON_PINS[2]);
  }

  while (buttonState[3] == LOW) {
    Serial.print("4");
      tone(BUZZER_PIN, frequencies[3]); // turn on
      buttonState[3] = digitalRead(BUTTON_PINS[3]);
  }

  noTone(BUZZER_PIN);  // turn off
}

