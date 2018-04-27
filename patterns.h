unsigned int power[8] = {
    19727,
    19305,
    21010,
    33938,
    0,
    49152,
    21329,
    37594,
};

unsigned int play[8] = {
    19855,
    25385,
    51785,
    37528,
    0,
    32768,
    25443,
    22858,
};

unsigned int stop[8] = {
    19855,
    8809,
    38931,
    38546,
    0,
    49152,
    25443,
    51482,
};

unsigned int rew[8] = {
    19855,
    17001,
    51785,
    37568,
    0,
    49152,
    25443,
    22810,
};

unsigned int ffwd[8] = {
    19855,
    27241,
    21266,
    37458,
    0,
    32768,
    25443,
    39706,
};

unsigned int *patterns[5] = {
    power,
    play,
    stop,
    rew,
    ffwd,
};

const char *pattern_names[5] = {
    "Power",
    "Play",
    "Stop",
    "Rewind",
    "Fast Forward",
};

struct Match_Tuple {
    int pattern;
    int degrees;
};
