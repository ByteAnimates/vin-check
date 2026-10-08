// The demo. Build and run:
//
//     c++ -std=c++17 -O2 -o main main.cpp
//     ./main
//
// `vin.cpp` is the snippet from the reel, generated from the episode. It is INCLUDED rather
// than linked because it is exactly what was on screen — two bare functions with no headers of
// their own — so the file you read is byte-for-byte the file you watched.
//
// 1M8GDM9AXKP042788 is the worked example VIN references use to explain the check digit,
// because its check digit is an X. A VIN identifies a vehicle, not a person.

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

using namespace std;

#include "vin.cpp"

/** A check that survives `-DNDEBUG`: `assert` is compiled out there, and this demo's output
    is a claim, so a failure has to stop it rather than print "verifies" anyway. */
static void require(bool ok, const char* what) {
    if (!ok) {
        cerr << "FAILED: " << what << "\n";
        exit(1);
    }
}

int main() {
    // The reel's `val` against the published transliteration table, letter by letter.
    const map<char, int> table = {
        {'A', 1}, {'B', 2}, {'C', 3}, {'D', 4}, {'E', 5}, {'F', 6}, {'G', 7}, {'H', 8},
        {'J', 1}, {'K', 2}, {'L', 3}, {'M', 4}, {'N', 5}, {'P', 7}, {'R', 9},
        {'S', 2}, {'T', 3}, {'U', 4}, {'V', 5}, {'W', 6}, {'X', 7}, {'Y', 8}, {'Z', 9},
    };
    for (auto [c, v] : table) require(val(c) == v, "val() matches the published table");
    cout << "val(): all 23 letters a VIN may use match the published table\n";

    const string vin = "1M8GDM9AXKP042788";
    string typo = vin;
    typo[9] = 'S'; // the reel's catch: the K typed as an S

    require(check(vin.c_str()) == 'X' && vin[8] == 'X', "the specimen checks out as X");
    require(check(typo.c_str()) == 'X', "the K typed as an S still checks out");
    cout << vin << " -> X, matches position 9\n" << typo << " -> X, still matches\n";

    // Every single-character error at the 16 positions that count, over the 33 characters a
    // VIN may use: it passes exactly when the new character is worth the same as the old.
    const string alphabet = "0123456789ABCDEFGHJKLMNPRSTUVWXYZ";
    int caught = 0, missed = 0;
    for (size_t i = 0; i < vin.size(); ++i) {
        if (i == 8) continue;
        for (char c : alphabet) {
            if (c == vin[i]) continue;
            string t = vin;
            t[i] = c;
            bool passes = check(t.c_str()) == vin[8];
            require(passes == (val(c) == val(vin[i])), "passes exactly when the values collide");
            (passes ? missed : caught) += 1;
        }
    }
    cout << "single-character errors: " << caught << " caught, " << missed
         << " missed, and every miss is two characters worth the same\n";

    // The lookalikes a person actually misreads are all caught.
    const char* pairs[][2] = {{"B", "8"}, {"S", "5"}, {"Z", "2"}, {"G", "6"}};
    for (auto& p : pairs) require(val(p[0][0]) != val(p[1][0]), "lookalikes have different values");
    cout << "B/8, S/5, Z/2, G/6: different values, so a misread is caught\n";
    return 0;
}
