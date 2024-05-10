/**
 * @file poems.cpp
 * @author Ryan Sordillo
 * @brief 
 * @date 2/14/2024
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
/**
* Turns the poem array into a string to be printed
* @param poem array
* @param lines number of lines from user input
* @return poem string
*/
string write_poem(string * poem, int lines) {
    string poem_str = "";
        for (int i = 0; i < lines; i++) {
            poem_str += poem[i] + "\n";
        }
        return poem_str;
}
/**
* Generates a string array by keeping track of syllables in each line
* Adds each word which is randomly picked
* Also keeps track of the longest line for use in a later function
* @param lines the input number of lines
* @param syllables array of how many syllables of each line has
* @param max_length keeps track of longest line
* @return poem generated poem in a array 
*/
string * generate_poem(int lines, int * syllables, int& max_length) {
    max_length = 0;
    string * poem = new string[lines];

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
            line += word;
            remaining_syllables -= syllables_in_word;
            if (remaining_syllables > 0) {
                line += " ";
            }
        }
        poem[i] = line;
        if (line.size() > max_length) {
            max_length = line.size();
        }
    }
    return poem;
}
/**
* If user input says so, goes through each line and capitalizes the first letter in each line
* @param poem_str poem string that is going to be capitalized
* @return string of poem with capitalized letters 
*/
string capitalize(string poem_str) {
    for (int i = 0; i < poem_str.length(); i++) {
        if (i == 0 || poem_str[i - 1] == '\n') {
            poem_str[i] = toupper(poem_str[i]);
        }
    }
    return poem_str;
}
/**
* Goes through the poem array from the bottom to the top, gets the letters in each column and displays
*them in correct format. Adds spaces where necesarry to account for no letters
* @param lines the input number of lines
* @param poems string array of poem generated from previous function
* @param max_length the longest line of the poem
* @return string of poem turned vertical
*/
string verticalize(string* poem, int lines, int& max_length) {
    string vertical_poem = "";
    int character = 0;
    while (character < max_length) {
        for (int row = lines - 1; row >= 0; row--) {
            if (character < poem[row].size()) {
                if (poem[row][character] == ' ') {
                    vertical_poem += ' ';
                    continue;
                }
                vertical_poem += poem[row][character];
            }
            else {
                vertical_poem += ' ';
            }
        }
        vertical_poem += '\n';
        character++;
    }
    return vertical_poem;
}

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
    int max_length;
    rand_int(seed);
    string * poem = generate_poem(lines, syllables, max_length);
    string output;

    if (settings[0] == 1) {
        output = write_poem(poem, lines);
        output = capitalize(output);
    }
    else if (settings[1] == 1) {
        output = verticalize(poem, lines, max_length);
    }
    else {
        output = write_poem(poem, lines);
    }
    cout << output;

    delete [] syllables;
    delete [] poem;
    return 0;
}
