/* sensor.ino
 * 
 * Detect and record IR patterns from remote controls
 *
 */

#define IR_SENSOR_IN 2
#define IR_LED_OUT 3

void setup() {
    // Interrupts will be used to detect input
    pinMode(IR_SENSOR_IN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(IR_SENSOR_IN),
                    receiving_started, RISING);

    pinMode(IR_LED_OUT, OUTPUT);

    // For initial testing
    Serial.begin(9600);
    Serial.println("Still working");
}

void loop() {
    // If we get a signal to send a transmission back out
}

struct pattern {
    int **delays;
}

/*
 * receiving_started()
 * 
 * Handle the recording of an incoming IR transmission
 *   from a remote control
 */
void receiving_started() {
    // Look at IR_SENSOR_IN, and record it
    // Also need to disable this ISR until recording done
    noInterrupts();
    Serial.print("Rising pin at time: ");
    Serial.println(micros());
    interrupts();
    // Maybe get the time of the first flash, time of second, etc
    // Put this in an array for later use
}
