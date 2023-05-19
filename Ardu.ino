#include <Keypad.h>

#define PIN_LDR1 A11
#define PIN_LDR2 A12
#define PIN_LDR3 A13
#define PIN_LDR4 A14

#define PIN_MOTOR A8

char hexaKeys[2][2] = {
  {'1', '2'},
  {'3', '4'}
};

byte rowPins[2] = {5, 4}; 
byte colPins[2] = {3, 2}; 

bool motor_on = false;

// teclado
Keypad kp = Keypad(makeKeymap(hexaKeys), rowPins, colPins, 2, 2); 

void setup() {
	Serial.begin(9600);
 	// sensores
	pinMode(PIN_LDR1, INPUT);
 	pinMode(PIN_LDR2, INPUT);
 	pinMode(PIN_LDR3, INPUT);
 	pinMode(PIN_LDR4, INPUT);

	// motor
 	pinMode(PIN_MOTOR, OUTPUT);
}

void loop() {
	float ldr_va[4];
	ldr_va[0] = analogRead(PIN_LDR1); // todos entre 0 y 1023
	ldr_va[1] = analogRead(PIN_LDR2);
	ldr_va[2] = analogRead(PIN_LDR3);
	ldr_va[3] = analogRead(PIN_LDR4);
	
	float ldr_voltages[4];
	for (int i = 0; i < 4; ++i) 
		ldr_voltages[i] = (float) ldr_va[i] * 5.0f / 1023.0f; 
	
	// calculate lums and average lums
	float ldr_lums[4];
	float average_lums = 0.f;
	for (int i = 0; i < 4; ++i) {
		ldr_lums[i] = 0.447f * sqrt(ldr_voltages[i] * 100.0f;
		average_lums += ldr_lums[i];
	}
	average_lums /= 4.f;
	
	// turn the motor on or off
	if (average_lums >= 60 && !motor_on) {
		digitalWrite(PIN_MOTOR, HIGH);
	} else if (average_lums < 60) {
		digitalWrite(PIN_MOTOR, LOW);
	}
	
        // read the key and print the value
	char key = kp.getKey();
	if (key) {
		Serial.print("LDR elegido: ");
		Serial.println(key);
		Serial.print("Valor: ");
		Serial.print(ldr_lums[key - '1']);
	}	
}



void setup() {
	Serial.begin(9600);
 	pinMode(A0, INPUT);
}

// the loop function runs over and over again forever
void loop() {
	int read_value = analogRead(A0);
	int mapped_value = map(read_value, 0, (1 << 10) - 1, 0, (1 << 4) - 1);
     Serial.println(mapped_value);
     delay(100);
}
