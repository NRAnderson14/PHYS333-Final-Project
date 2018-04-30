/* sensor.ino
 * 
 * Detect and record IR patterns from remote controls
 *
 */
#include "patterns.h"

#define ARRAY_SIZE 8

unsigned int data_new[ARRAY_SIZE];

void setup() {

    // For initial testing
    Serial.begin(9600);
    Serial.println("Ready To Record");
}

void loop() {
    if (analogRead(A0) > 300) {
        record_into(data_new);
        for (int i = 0; i < ARRAY_SIZE; i++)
            Serial.println(data_new[i]);

        print_results(data_new);
        delay(1000);
    }
}



void record_into(unsigned int array[ARRAY_SIZE]) {
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
        delayMicroseconds(1000);
    }
    return int_to_record;
}

/* Record the pattern into bits that represent every 1000 microseconds
 * Use an array of 8 ints
 */
Match_Tuple amount_similar(unsigned int array[ARRAY_SIZE]) {
    int best_match;
    int degrees_similar = 0;
    int inner_matches = 0;
    int prev_matches = 0;
    Match_Tuple res;

    for (int outer = 0; outer < 5; outer++) {
        for (int inner = 0; inner < 8; inner++) {
            if (array[inner] == patterns[outer][inner]) {
                inner_matches++;
            }
        }

        if (inner_matches > prev_matches) {
            best_match = outer;
            prev_matches = inner_matches;
            degrees_similar = inner_matches;
        }

        inner_matches = 0;
    }

    res.pattern = best_match;
    res.degrees = degrees_similar;

    return res;
}

void print_results(unsigned int array[ARRAY_SIZE]) {
    Match_Tuple res = amount_similar(array);
    Serial.print("Most similar to: ");
    Serial.println(pattern_names[res.pattern]);
    Serial.print("Degrees of similarity: ");
    Serial.print(res.degrees);
    Serial.println("/8\n");
}
