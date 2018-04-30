/* patterns.h
 *
 * IR Patterns and definitions for use by sensor.ino
 */

// Contains all of the patterns we need to look at
unsigned int patterns[10][8] = {
    {19855, // Power
    19305,
    21266,
    33938,
    0,
    49152,
    21329,
    37594},

    {19855, // Play
    25385,
    51785,
    37528,
    0,
    32768,
    25443,
    22858},

    {19855, // Stop
    8809,
    38931,
    38546,
    0,
    49152,
    25443,
    51482},

    {19855, // Rewind
    17001,
    51785,
    37568,
    0,
    49152,
    25443,
    22810},

    {19855, // Fast-Forward
    27241,
    21266,
    37458,
    0,
    32768,
    25443,
    39706},
};

// Contains all of the names for the patterns,
// respective to the order in the patterns array
const char *pattern_names[5] = {
    "Power",
    "Play",
    "Stop",
    "Rewind",
    "Fast Forward",
};

// Type used to return info about how close a reading was
// to our pre-defined patterns
struct Match_Tuple {
    int pattern;
    int degrees;
};
