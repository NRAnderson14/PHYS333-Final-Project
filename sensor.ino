/* sensor.ino
 * 
 * Detect and record IR patterns from remote controls
 *
 */

#define ARRAY_SIZE 8

unsigned int data_new[ARRAY_SIZE];

void setup() {

    // For initial testing
    Serial.begin(9600);
    Serial.println("Ready To Record");
}

void loop() {
    if (analogRead(A0) > 300) {
        rec_started(data_new);
        for (int i = 0; i < ARRAY_SIZE; i++)
            Serial.println(data_new[i]);

        Serial.println("End of pattern");
        delay(2000);
    }
}

void rec_started(unsigned int array[ARRAY_SIZE]) {
    //Handle the stuff here
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = record_into_int();
    }

}

int record_into_int() {
    int int_to_record = 0;
    int counter = 0;
    while (counter < 16) {
        if (analogRead(A0) > 300)
            int_to_record |= (1 << counter);

        counter++;
        delayMicroseconds(999);
    }
    return int_to_record;
}

/* Record the pattern into bits that represent every 1000 microseconds
 * Use an array of 8 ints
 */

