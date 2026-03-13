#include <iostream>
#include <iomanip>
#include <vector>
#include "Nist Functions.cpp"
using namespace std;

int main() {
    cout << "Welcome to my EAS Implementation program\n";
    // string test = "";
    // cin >> test;
    // cout << "You input: "<< test << endl;
    unsigned amogus[4][4] = {{0x000000AA, 0x0000AA00, 0x00AA0000, 0xAA000000}, {0x000000BB, 0x0000BB00, 0x00BB0000, 0xBB000000}, {0x000000CC, 0x0000CC00, 0x00CC0000, 0xCC000000}, {0x000000DD, 0x0000DD00, 0x00DD0000, 0xDD000000}};
    std::vector<long> testingVector = {0xA1A2A3A4, 0xB1B2B3B4, 0xC1C2C3C4, 0xD1D2D3D4};
    // for (int i =0; i < 4; i++)
    // {
    //     cout << std::hex << testingVector[i] << " ";
    // }
    // cout << endl;
    // testingVector = ShiftRows(testingVector);
    // for (int i =0; i < 4; i++)
    // {
    //     cout << std::hex << testingVector[i] << " ";
    // }

    unsigned bit1 = 0x00;
    unsigned bit2 = 0x01;
    unsigned bit3 = 0x10;
    unsigned bit4 = 0x11;
    unsigned bit5 = 0xff;
    unsigned word1 = 0x00DDEEFF;
    //Testing values for key expansions at sizes 128, 192, and 256 bits.
    vector<long> testKey128= {(0x2b7e1516), (0x28aed2a6), (0xabf71588), (0x09cf4f3c)};
    vector<long> testKey192= {(0x8e73b0f7), (0xda0e6452), (0xc810f32b), (0x809079e5), (0x62f8ead2), (0x522c6b7b)};
    vector<long> testKey256= {(0x603deb10), (0x15ca71be), (0x2b73aef0), (0x857d7781), (0x1f352c07), (0x3b6108d7), (0x2d9810a3), (0x0914dff4)};

    //Test Values for the input and RoundKey from Appendix B for Cipher
    //Nb = 4, Nk = 4
    vector<long> testInputB = {(0x328831e0),(0x435a3137),(0xf6309807),(0xa88da234)};
    vector<long> testRoundKeyB = {(0x2b28ab09),(0x7eaef7cf),(0x15d2154f),(0x16a6883c)};

    // cout << std::hex << Sbox(bit1) << endl;
    // cout << std::hex << Sbox(0xDD) << endl;
    // cout << std::hex << sArray[0xD][0xD] << endl;
    // cout << std::hex << subWord(word1) << endl;
    // cout << std::hex << invSubBytes(subWord(word1)) << endl;

    // for (int i =0; i < 4; i++)
    // {
    //     for (int a =0; a <4; a++)
    //     {
    //     cout << std::hex << amogus[i][a] << " ";
    //     }
    //     cout << endl;
    // }

    // cout << (-1%4) << "\n";

    // for (int i = 0; i <4; i++)
    // {   
    // for (int a = 0; a < 4; a++)
    //     {
    //     //Shift is equal to column + row modulos 4
    //     int shift = (a-i) % 4;
    //     cout << "shift: " << shift << "\n";
    //     cout << std::hex << amogus[i][shift] << " ";
    //     }
    // cout << endl;
    // }   

    for (int i = 0; i < 4; i++)
    {
        cout << std::hex <<testingVector[i] << endl;
    }
    // testingVector = ShiftRows(testingVector);
    // cout << endl;
    // for (int i = 0; i < 4; i++)
    // {
    //     cout << std::hex <<testingVector[i] << endl;
    // }
    testingVector = InvShiftRows(testingVector);
    cout << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << std::hex <<testingVector[i] << endl;
    }
    // unsigned testSus = amogus[0][0] + amogus[0][1] + amogus[0][2] + amogus[0][3];
    // cout << std::hex << testSus << ": Testsus Confirmed\n";
    return 0;
}