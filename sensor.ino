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
        delayMicroseconds(1000);
    }
    return int_to_record;
}

/* Record the pattern into bits that represent every 1000 microseconds
 * Use an array of 8 ints
 */
Match_Tuple amount_similar(unsigned int array[ARRAY_SIZE]) {
    int pattern_matched;
    int degrees_similar = 0;
    int inner_comp = 0;
    Match_Tuple res;

    for (int each_pattern = 0; each_pattern < 5; each_pattern++) {
        for (int this_patt = 0; this_patt < 8; this_patt++)
            if (patterns[each_pattern] == array[this_patt])
                inner_comp++;

        if (inner_comp > degrees_similar) {
            degrees_similar = inner_comp;
            pattern_matched = each_pattern;
        }
    }

    res.pattern = pattern_matched;
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
