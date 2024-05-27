#include "Encryptions.h"
#include<iostream>
string Encryptions::generateEncryption(const string& plaintext)
{
    string encryptedText;
    string key = "4632785128!@#$%^&*()_+}{|:";
    for (int i = 0; i < plaintext.size(); ++i) {
        encryptedText += plaintext[i] ^ key[i % key.size()];
    }
    return encryptedText;
}
