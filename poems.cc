/**
 * @file poems.cpp
 * @author 
 * @brief 
 * @date 
 */


/* ------- Do not change anything in this section (below) ------- */

#include <iostream>
#include <climits>
#include <string>

using namespace std;

const int ROWS = 9;
const int COLS = 5;

const string HIRAGANA[ROWS][COLS] = 
                        {{ "a",   "i",   "u",  "e",  "o"},
                         {"ka",  "ki",  "ku", "ke", "ko"},
                         {"sa", "shi",  "su", "se", "so"},
                         {"ta", "chi", "tsu", "te", "to"},
                         {"na",  "ni",  "nu", "ne", "no"},
                         {"ha",  "hi",  "hu", "he", "ho"},
                         {"ma",  "mi",  "mu", "me", "mo"},
                         {"ra",  "ri",  "ru", "re", "ro"},
                         {"ya",  "wa",  "yu",  "n", "yo"}
                        };

const int A = 125;
const int C = 11;
const int MOD = 1024;

const int SYL_IN_WORD_MAX = 5;
const int NUM_LINES_MAX = 15;
const int NUM_SYLS_MAX = 40;

/**
 * @brief A pseudo-random number generator
 * Note: seed is an *optional parameter*. If an argument is passed to this
 * function, the state will be reset to this seed. Otherwise, if you call the
 * function with no arguments, seed will be set to the default of INT_MIN.
 * When this happens, the state will be updated to the next pseudo-random
 * number. Either way, the state is returned.
 * 
 * @param seed (optional) - When passed, resets the seed
 * @return int - The pseudo-random integer.
 */
int rand_int(int seed = INT_MIN) {
    static int state = 0;

    if (seed != INT_MIN) {
        // If a seed is passed, then set/reset the state
        state = seed;
    }
    else {
        // Otherwise, update the state to the next pseudo-random number
        state = (A * state + C) % MOD;
    }

    return state;
}

/* ------- Do not change anything in the section above ------- */
string generate_poem(int lines, int * syllables) {
    string poem[NUM_LINES_MAX];
    for (int i = 0; i < lines; i++) {
        int remaining_syllables = syllables[i];
        string line = "";
        while (remaining_syllables > 0) {
            int syllables_in_word = rand_int() % SYL_IN_WORD_MAX + 1;
            if (syllables_in_word > remaining_syllables) {
                syllables_in_word = remaining_syllables;
            }
            string word = "";
            for (int s = 0; s < syllables_in_word; s++) {
                int row = rand_int() % ROWS;
                int col = rand_int() % COLS;
                word += HIRAGANA[row][col];
            }
            line += word + " ";
            remaining_syllables -= syllables_in_word;
        }
        poem[i] = line;
    }
    string poem_str = "";
    for (int i = 0; i < lines; i++) {
        poem_str += poem[i] + "\n";
    }
    return poem_str;
}
string capitalize(string poem_str, int settings[]) {
    if (settings[0] == 1) {
        for (int i = 0; i < poem_str.length(); i++) {
            if (i == 0 || poem_str[i - 1] == '\n') {
                poem_str[i] = toupper(poem_str[i]);
            }
        }
    }
    return poem_str;
}
// string verticalize(string poem_str, int settings[]) {
//     string vertical_poem = "";
//     if (settings[1] == 1) {

//     }
// }

// Controls operation of program
int main() {
    int seed;
    cin >> seed;

    int lines;
    cin >> lines;

    int * syllables = new int[lines];
    for (int i = 0; i < lines; i++) 
        cin >> syllables[i];

    int settings[2];
    for (int i = 0; i < 2; i++)
        cin >> settings[i];

    rand_int(seed);
    string poem = generate_poem(lines, syllables);
    //poem = generate_poem(lines, syllables);
    poem = capitalize(poem, settings);
    //poem = verticalize(poem, settings);
    cout << poem;

    delete [] syllables;

    return 0;
}
