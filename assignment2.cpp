#include <bits/stdc++.h>
using namespace std;

int main() {
    char n;
    int r = 0;
    string biny = "";

    // 1. Read input
    for (int i = 0; i < 4; i++) {
        cin >> n;
        biny += n;
    }

    // 2. Find r
    for (int i = 0; i < 4; i++) {
        if (pow(2, i) >= 4 + i + 1) {
            r = i;
            break;
        }
    }

    // 3. Find parity positions (1-based: 1, 2, 4)
    vector<int> pos(r);
    for (int i = 0; i < r; i++) {
        pos[i] = pow(2, i);
    }

    // 4. Place '?' at parity slots
    vector<char> v(7);
    for (int i = 0; i < pos.size(); i++) {
        v[pos[i] - 1] = '?';
    }

    // 5. Fill remaining slots with data bits
    int k = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] != '?') {
            v[i] = biny[k];
            k++;
        }
    }

    // -------------------------------------------------------------
    // STEP 6: Calculate Even Parity for P1, P2, P4
    // -------------------------------------------------------------
    // Using 1-based indexing for convenience:
    // P1 (index 1) checks positions: 1, 3, 5, 7
    // P2 (index 2) checks positions: 2, 3, 6, 7
    // P4 (index 4) checks positions: 4, 5, 6, 7

    // P1 = v[2] ^ v[4] ^ v[6]
    int p1 = (v[2] - '0') ^ (v[4] - '0') ^ (v[6] - '0'); 
    v[0] = p1 + '0';

    // P2 = v[2] ^ v[5] ^ v[6]
    int p2 = (v[2] - '0') ^ (v[5] - '0') ^ (v[6] - '0'); 
    v[1] = p2 + '0';

    // P4 = v[4] ^ v[5] ^ v[6]
    int p4 = (v[4] - '0') ^ (v[5] - '0') ^ (v[6] - '0'); 
    v[3] = p4 + '0';

    cout << "\nEncoded Hamming Code (7-bit): ";
    for (auto it : v) cout << it;
    cout << endl;

    // -------------------------------------------------------------
    // STEP 7: Simulate Received Code (Introducing an Artificial Error)
    // -------------------------------------------------------------
    vector<char> rec = v;
    // cin<<error_bit;
    int error_bit = 5; // Let's artificially flip the bit at position 5 (1-based)
    rec[error_bit - 1] = (rec[error_bit - 1] == '0') ? '1' : '0';

    cout << "Received Hamming Code (with error at bit " << error_bit << "): ";
    for (auto it : rec) cout << it;
    cout << endl;

    // -------------------------------------------------------------
    // STEP 8: Error Detection Logic
    // -------------------------------------------------------------
    // Re-check parities on the received bits
    int c1 = (rec[0] - '0') ^ (rec[2] - '0') ^ (rec[4] - '0') ^ (rec[6] - '0');
    int c2 = (rec[1] - '0') ^ (rec[2] - '0') ^ (rec[5] - '0') ^ (rec[6] - '0');
    int c4 = (rec[3] - '0') ^ (rec[4] - '0') ^ (rec[5] - '0') ^ (rec[6] - '0');

    // Syndrome = c4 c2 c1 (in binary)
    int error_pos = (c4 * 4) + (c2 * 2) + (c1 * 1);

    if (error_pos == 0) {
        cout << "\nResult: No error detected in transmission." << endl;
    } else {
        cout << "\nResult: Error detected at position " << error_pos << "!" << endl;

        // Correct the error
        rec[error_pos - 1] = (rec[error_pos - 1] == '0') ? '1' : '0';

        cout << "Corrected Hamming Code: ";
        for (auto it : rec) cout << it;
        cout << endl;
    }

    return 0;
}
