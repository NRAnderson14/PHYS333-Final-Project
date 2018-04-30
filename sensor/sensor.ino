/* sensor.ino
 * 
 * Decode IR signals from a remote control,
 *  and give a guess as to which button was pressed
 *
 * Nathan Anderson
 * Physics 333
 * Spring 2018
 */

// Our patterns to compare against
#include "patterns.h"

// Size for the arrays we record the signals into
#define ARRAY_SIZE 8

unsigned int recording_array[ARRAY_SIZE];

void setup() {
    Serial.begin(9600);
    Serial.println("Ready To Record");
}

void loop() {
    if (analogRead(A0) > 300) {
        record_into(recording_array);
        print_results(recording_array);
        delay(1000);
    }
}


// Records the data from the IR sensor into an array
void record_into(unsigned int array[ARRAY_SIZE]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = record_into_int();
    }

}

/* Records 16 milliseconds of IR data into one 16-bit integer
 * Each bit in the integer represents one millisecond, measured
 *  at its rising edge, where 1 represents a high value and 0 
 *  a low value
 */
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

/* Determine the amount a given pattern is similar to one of the
 *  pattern we have previously recorded
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

/* Print out the results of a Match_Tuple, taken from a 
 *  comparison with one of our patterns on file
 */
void print_results(unsigned int array[ARRAY_SIZE]) {
    Match_Tuple res = amount_similar(array);
    if (res.degrees > 2) {
        Serial.print("Most similar to: ");
        Serial.println(pattern_names[res.pattern]);
        Serial.print("Degrees of similarity: ");
        Serial.print(res.degrees);
        Serial.println("/8\n");
    } else {
        Serial.println("Unable to find good match!\n");
    }
}
