#include <iostream>
#include <string>

using namespace std;

// Function to determine the class based on the first octet
char getIpClass(int firstOctet) {
    if (firstOctet >= 0 && firstOctet <= 127) return 'A';
    else if (firstOctet >= 128 && firstOctet <= 191) return 'B';
    else if (firstOctet >= 192 && firstOctet <= 223) return 'C';
    else if (firstOctet >= 224 && firstOctet <= 239) return 'D';
    else if (firstOctet >= 240 && firstOctet <= 255) return 'E';
    else return 'X'; 
}

// Function to determine the default subnet mask (String format)
string getDefaultSubnetMask(char ipClass) {
    switch (ipClass) {
        case 'A': return "255.0.0.0";
        case 'B': return "255.255.0.0";
        case 'C': return "255.255.255.0";
        default : return "N/A";
    }
}

// Function to get the number of networks in 2^n format
string getNumberOfNetworks(char ipClass) {
    switch (ipClass) {
        case 'A': return "2^7 (128 possible networks, 126 usable)"; 
        case 'B': return "2^14 (16,384 possible networks)"; 
        case 'C': return "2^21 (2,097,152 possible networks)";  
        default : return "N/A"; 
    }
}

// Function to calculate usable hosts using the 2^n - 2 formula
long long int getUsableHosts(char ipClass) {
    switch (ipClass) {
        case 'A': return (1LL << 24) - 2; 
        case 'B': return (1LL << 16) - 2; 
        case 'C': return (1LL << 8) - 2;  
        default : return 0; 
    }
}

int main() {
    int octet1, octet2, octet3, octet4;
    char dot1, dot2, dot3;

    cout << "Enter an IP address (format: x.x.x.x): ";
    
    if (cin >> octet1 >> dot1 >> octet2 >> dot2 >> octet3 >> dot3 >> octet4) {
        
        if (dot1 == '.' && dot2 == '.' && dot3 == '.' &&
            (octet1 >= 0 && octet1 <= 255) && (octet2 >= 0 && octet2 <= 255) &&
            (octet3 >= 0 && octet3 <= 255) && (octet4 >= 0 && octet4 <= 255)) {
            
            cout << "\n--- Results ---" << endl;
            cout << "IP Address       : " << octet1 << "." << octet2 << "." << octet3 << "." << octet4 << endl;
            
            // Special check for Loopback Address
            if (octet1 == 127) {
                cout << "Class            : A (Reserved)" << endl;
                cout << "Notes            : Loopback address (used for local host testing, e.g., localhost)." << endl;
                cout << "Starting IP      : 127.0.0.0" << endl;
                cout << "Last IP          : 127.255.255.255" << endl;
            } else {
                char ipClass = getIpClass(octet1);
                cout << "Class            : " << ipClass << endl;
                
                if (ipClass == 'A' || ipClass == 'B' || ipClass == 'C') {
                    cout << "Subnet Mask      : " << getDefaultSubnetMask(ipClass) << endl;
                    cout << "No. of Networks  : " << getNumberOfNetworks(ipClass) << endl;
                    
                    cout << "Usable Hosts     : " << getUsableHosts(ipClass) 
                         << " (calculated via 2^n - 2 (Minus 2 because the first address is reserved for the Network ID and the last address is reserved for the Broadcast address.))" << endl;
                    
                    cout << "Starting IP      : ";
                    if (ipClass == 'A') cout << octet1 << ".0.0.0" << endl;
                    else if (ipClass == 'B') cout << octet1 << "." << octet2 << ".0.0" << endl;
                    else if (ipClass == 'C') cout << octet1 << "." << octet2 << "." << octet3 << ".0" << endl;

                    cout << "Last IP          : ";
                    if (ipClass == 'A') cout << octet1 << ".255.255.255" << endl;
                    else if (ipClass == 'B') cout << octet1 << "." << octet2 << ".255.255" << endl;
                    else if (ipClass == 'C') cout << octet1 << "." << octet2 << "." << octet3 << ".255" << endl;

                } else if (ipClass == 'D') {
                    cout << "Notes            : Multicast address (No standard subnet mask, networks, or hosts)" << endl;
                } else if (ipClass == 'E') {
                    cout << "Notes            : Experimental address (No standard subnet mask, networks, or hosts)" << endl;
                }
            }
            
        } else {
            cout << "Invalid IP address format or octets out of bounds (0-255)." << endl;
        }
    } else {
        cout << "Invalid input." << endl;
    }

    return 0;
}
