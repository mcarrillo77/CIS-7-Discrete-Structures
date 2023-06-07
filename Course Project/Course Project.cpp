#include <iostream>
#include <string>

using namespace std;

const int numLetters = 26;
char vigenereTable[numLetters][numLetters];

// Function Declarations
void message(const string&);
void alphabetArray();
void userInput(string&);
string encrypt(const string& message, const string& key);
string decrypt(const string& message, const string& key);
int getChoice();  // Function to get the user's choice

int main()
{
    message("Welcome to DYLO's Vigenere Cipher!");
    alphabetArray();
    cout << endl;
    int choice = getChoice();

    return 0;
}

// Function Definitions

// Print messages
void message(const string& message)
{
    cout << message << endl;
}

// Get user input
void userInput(string& input)
{
    cin >> input;
    cout << endl << endl;
}

// Create table from alphabet
void alphabetArray()
{
    // i for row
    // j for columns

    for (int i = 0; i < numLetters; i++) {
        for (int j = 0; j < numLetters; j++) {
            vigenereTable[i][j] = 'A' + (j + i) % numLetters;
        }
    }
}


// Encryption/Decryption
string encrypt(const string& message, const string& key)
{
    string encryptedMessage;
    int keyLength = key.length();
    int messageLength = message.length();

    for (int i = 0; i < messageLength; i++) {
        
        char messageChar = toupper(message[i]);
        char keyChar = toupper(key[i % keyLength]);

        int rowIndex = messageChar - 'A';
        int columnIndex = keyChar - 'A';

        char encryptedChar = vigenereTable[rowIndex][columnIndex];
        encryptedMessage += encryptedChar;
    }

    cout << endl;

    return encryptedMessage;
}
string decrypt(const string& message, const string& key)
{
    string decryptedMessage;
    int messageLength = message.length();
    int keyLength = key.length();

    for (int i = 0; i < messageLength; i++) {
        char currentChar = toupper(message[i]);
        char keyChar = toupper(key[i % keyLength]);

        // Validate the character
        if (currentChar < 'A' || currentChar > 'Z') {
            // Handle the invalid character, such as skipping or displaying an error
            continue;
        }

        int keyOffset = keyChar - 'A';

        for (int currentOffset = 0; currentOffset < numLetters; currentOffset++) {
            if (vigenereTable[currentOffset][keyOffset] == currentChar) {
                char decryptedChar = 'A' + currentOffset;
                decryptedMessage += decryptedChar;
                break;
            }
        }
    }

    return decryptedMessage;
}


// Prompt user how to proceed
int getChoice()
{
    string choice;

    while (choice != "1" && choice != "2") {
        message("Enter either '1,' '2,' or 'q.' ");
        message("1. Encrypt");
        message("2. Decrypt");
        message("3. Quit");

        cout << endl;

        message("Encryption - Enter a message, then a key. You'll receive Encrypted message.");
        message("Decryption - Enter encrypted message, then key. You'll receive message.");

        cout << endl;

        // User enters mode
        getline(cin, choice);

        cout << endl;

        // Encryption
        if (choice == "1") {
            string userMessage;
            string key;

            message("Enter a message");
            userInput(userMessage);
            message("Enter a key");
            userInput(key);

            string encrypted = encrypt(userMessage, key);
            message("Ciphertext: " + encrypted);
        }
        // Decryption
        else if (choice == "2") {
            string userMessage;
            string key;

            message("Enter a ciphertext");
            userInput(userMessage);
            message("Enter the key used for decryption");
            userInput(key);

            string decrypted = decrypt(userMessage, key);
            message("Plaintext: " + decrypted);
        }
        // Quit
        else if (choice == "q") {
            break;
        }
        // Invalid
        else {
            message("Invalid choice. Please enter 1 or 2.");
            cout << endl;
        }
    }

    return 0;

}
