#include <iostream>
#include <string>
#include <cctype>

using namespace std;

/*Function to remove spaces and non-alphabetical characters*/

string preprocessInput(const string& input) {
    string processedInput;
    for (char c : input)
    {
        if(isalpha(c))
        {
            processedInput.push_back(toupper(c));
        }
    }
    return processedInput;
}

/*Function to generate the Playfair cipher table*/

string generateKeyTable(const string& keyword) {
    string keyTable;
    string uniqueChars;

    /*Now we have to add characters to the keytable using the keyword*/

    for (char c : keyword)
    {
        c = toupper(c);
        if (uniqueChars.find(c) == string::npos)
        {
            uniqueChars.push_back(c);
            keyTable.push_back(c);
        }
    }
    
    /*Now we have to add the remaining alphabetic characters to the key table*/
    for (char c = 'A'; c <= 'Z'; c++)
    {
        if (c != 'J' && uniqueChars.find(c) == string::npos)
        {
            keyTable.push_back(c);
        }
    }
    
    return keyTable;
}

/*The function to perform the encryption*/

string encrypt(const string& plaintext, const string& keyTable) {

    string cipherText;
    const int tableSize = 5; /*Because Playfair cipher grid is 5x5*/

    for(int i=0; i< plaintext.length(); i +=2)
    {
        char first = plaintext[i];
        char second = (i + 1 < plaintext.length()) ? plaintext[i+1] : 'X';


        /*Finding the positions in the key table*/
        int firstRow, firstCol, secondRow, secondCol;
        for (int row = 0; row < tableSize; ++row)
        {
            for (int col = 0; col < tableSize; ++col)
            {
                if(keyTable[row* tableSize + col] == first)
                {
                    firstRow = row;
                    firstCol = col;
                }
                if(keyTable[row * tableSize + col] == second) {
                    secondRow = row;
                    secondCol = col;
                }
            }
        }
        
        /*Performing the Playfair cipher*/
        if(firstRow == secondRow) {
            firstCol = (firstCol + 1) % tableSize;
            secondCol = (secondCol + 1) % tableSize;
        } else if(firstCol == secondCol) {
            firstRow = (firstRow + 1) % tableSize;
            secondRow = (secondRow + 1) % tableSize;
        } else {
            int temp = firstCol;
            firstCol = secondCol;
            secondCol = temp;
        }

        cipherText.push_back(keyTable[firstRow * tableSize + firstCol]);
        cipherText.push_back(keyTable[secondRow * tableSize + secondCol]);        
    }
    return cipherText;
}

int main() {

    string keyword, plainText;

    cout << "Enter the keyword: ";
    cin >> keyword;
    cout << "Enter the plaintext: ";
    cin.ignore();
    getline(cin, plainText);

    /*Preprocess the input by removing spaces and non-alphabetical characters*/
    plainText = preprocessInput(plainText);

    /*Generate the Playfair cipher table*/
    string keytable = generateKeyTable(keyword);

    /*Perform encryption*/
    string ciphertext  = encrypt(plainText, keytable);

    cout << "Encrypted text: " << ciphertext << endl;
    return 0;
    system("pause");
}