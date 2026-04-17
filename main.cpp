#include <iostream>
#include <iomanip>
#include <vector>
#include "Nist Functions.cpp"
using namespace std;

int main()
{
    cout << "Welcome to my EAS Implementation program\n";
    cout << "What function would you like to test?:\n";
    cout << "1: AddRoundKey\n";
    cout << "2: SubBytes\n";
    cout << "3: InvSubBytes\n";
    cout << "4: RotWord\n";
    cout << "5: ShiftRows\n";
    cout << "6: InvShiftRows\n";
    cout << "7: MixColumns\n";
    cout << "8: InvMixColumns\n";
    cout << "9: KeyExpansion\n";
    cout << "10: InvKeyExpansion\n";
    cout << "11: KeyExpansionEIC\n";
    // Implement predetermined tests for each function, use switch to determine which to run based on user input.
    int test = 0;
    //Test values used for easy reading of different outputs for individual function outputs
    vector<long> testVals = {0xa1a2a3a4, 0xb1b2b3b4, 0xc1c2c3c4, 0xd1d2d3d4};
    unsigned testword = 0x11223344;
    vector<long> outputVals = {0x00};
    //Test values used to confirm correct function based on Appendix A.1 cipher example in the EAS Document.
    vector<long> testKey128 = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0xc3};
    int Nk128 = 4;
    cin >> test;
    cout << endl;
    unsigned bits2d[4][4];
    unsigned bitsResult2d[4][4];
    switch (test)
    {
    case 1:
        cout << "You chose to Test AddRoundKey\n";
        
        //outputVals = rotWord(testVals);
        cout << "After running RotWord\n";
        
        break;
    case 2:
        cout << "You chose to Test SubBytes\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            // Temporary Value to hold shifted bytes
            unsigned tempVal = 0;
            // Extracts each bit from the state and stores it in a temporary array
            bits2d[i][0] = (testVals[i] & 0xFF000000) >> 24;
            bits2d[i][1] = (testVals[i] & 0x00FF0000) >> 16;
            bits2d[i][2] = (testVals[i] & 0x0000FF00) >> 8;
            bits2d[i][3] = testVals[i] & 0x000000FF;
            cout << std::hex << bits2d[i][0] << " " << std::hex << bits2d[i][1] << " " << std::hex << bits2d[i][2] << " " << std::hex << bits2d[i][3] << "\n";
        }
        outputVals = SubBytes(testVals);
        cout << "After running RotWord\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            bits[0] = (outputVals[i] & 0xFF000000) >> 24;
            bits[1] = (outputVals[i] & 0x00FF0000) >> 16;
            bits[2] = (outputVals[i] & 0x0000FF00) >> 8;
            bits[3] = outputVals[i] & 0x000000FF;
            cout << std::hex << bits[0] << " " << std::hex << bits[1] << " " << std::hex << bits[2] << " " << std::hex << bits[3] << "\n";
        }
        break;
    case 3:
        cout << "You chose to Test InvSubBytes\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            // Temporary Value to hold shifted bytes
            unsigned tempVal = 0;
            // Extracts each bit from the state and stores it in a temporary array
            bits2d[i][0] = (testVals[i] & 0xFF000000) >> 24;
            bits2d[i][1] = (testVals[i] & 0x00FF0000) >> 16;
            bits2d[i][2] = (testVals[i] & 0x0000FF00) >> 8;
            bits2d[i][3] = testVals[i] & 0x000000FF;
            cout << std::hex << bits2d[i][0] << " " << std::hex << bits2d[i][1] << " " << std::hex << bits2d[i][2] << " " << std::hex << bits2d[i][3] << "\n";
        }
        outputVals = invSubBytes(testVals);
        cout << "After running InvSubBytes\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            bits[0] = (outputVals[i] & 0xFF000000) >> 24;
            bits[1] = (outputVals[i] & 0x00FF0000) >> 16;
            bits[2] = (outputVals[i] & 0x0000FF00) >> 8;
            bits[3] = outputVals[i] & 0x000000FF;
            cout << std::hex << bits[0] << " " << std::hex << bits[1] << " " << std::hex << bits[2] << " " << std::hex << bits[3] << "\n";
        }
        break;
    case 4:
        cout << "You chose to Test RotWord\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            // Temporary Value to hold shifted bytes
            unsigned tempVal = 0;
            // Extracts each bit from the state and stores it in a temporary array
            bits2d[i][0] = (testVals[i] & 0xFF000000) >> 24;
            bits2d[i][1] = (testVals[i] & 0x00FF0000) >> 16;
            bits2d[i][2] = (testVals[i] & 0x0000FF00) >> 8;
            bits2d[i][3] = testVals[i] & 0x000000FF;
            cout << std::hex << bits2d[i][0] << " " << std::hex << bits2d[i][1] << " " << std::hex << bits2d[i][2] << " " << std::hex << bits2d[i][3] << "\n";
        }
        //outputVals = rotWord(testVals);
        cout << "After running RotWord\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            bits[0] = (outputVals[i] & 0xFF000000) >> 24;
            bits[1] = (outputVals[i] & 0x00FF0000) >> 16;
            bits[2] = (outputVals[i] & 0x0000FF00) >> 8;
            bits[3] = outputVals[i] & 0x000000FF;
            cout << std::hex << bits[0] << " " << std::hex << bits[1] << " " << std::hex << bits[2] << " " << std::hex << bits[3] << "\n";
        }
        break;
    case 5:
        cout << "You chose to Test ShiftRows\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            // Temporary Value to hold shifted bytes
            unsigned tempVal = 0;
            // Extracts each bit from the state and stores it in a temporary array
            bits2d[i][0] = (testVals[i] & 0xFF000000) >> 24;
            bits2d[i][1] = (testVals[i] & 0x00FF0000) >> 16;
            bits2d[i][2] = (testVals[i] & 0x0000FF00) >> 8;
            bits2d[i][3] = testVals[i] & 0x000000FF;
            cout << std::hex << bits2d[i][0] << " " << std::hex << bits2d[i][1] << " " << std::hex << bits2d[i][2] << " " << std::hex << bits2d[i][3] << "\n";
        }
        outputVals = ShiftRows(testVals);
        cout << "After running ShiftRows\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            bits[0] = (outputVals[i] & 0xFF000000) >> 24;
            bits[1] = (outputVals[i] & 0x00FF0000) >> 16;
            bits[2] = (outputVals[i] & 0x0000FF00) >> 8;
            bits[3] = outputVals[i] & 0x000000FF;
            cout << std::hex << bits[0] << " " << std::hex << bits[1] << " " << std::hex << bits[2] << " " << std::hex << bits[3] << "\n";
        }
        break;
    case 6:
        cout << "You chose to Test InvShiftRows\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            // Temporary Value to hold shifted bytes
            unsigned tempVal = 0;
            // Extracts each bit from the state and stores it in a temporary array
            bits2d[i][0] = (testVals[i] & 0xFF000000) >> 24;
            bits2d[i][1] = (testVals[i] & 0x00FF0000) >> 16;
            bits2d[i][2] = (testVals[i] & 0x0000FF00) >> 8;
            bits2d[i][3] = testVals[i] & 0x000000FF;
            cout << std::hex << bits2d[i][0] << " " << std::hex << bits2d[i][1] << " " << std::hex << bits2d[i][2] << " " << std::hex << bits2d[i][3] << "\n";
        }
        outputVals = InvShiftRows(testVals);
        cout << "After running InvShiftRows\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            bits[0] = (outputVals[i] & 0xFF000000) >> 24;
            bits[1] = (outputVals[i] & 0x00FF0000) >> 16;
            bits[2] = (outputVals[i] & 0x0000FF00) >> 8;
            bits[3] = outputVals[i] & 0x000000FF;
            cout << std::hex << bits[0] << " " << std::hex << bits[1] << " " << std::hex << bits[2] << " " << std::hex << bits[3] << "\n";
        }
        break;
    case 7:
        cout << "You chose to Test MixColumns\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            // Temporary Value to hold shifted bytes
            unsigned tempVal = 0;
            // Extracts each bit from the state and stores it in a temporary array
            bits2d[i][0] = (testVals[i] & 0xFF000000) >> 24;
            bits2d[i][1] = (testVals[i] & 0x00FF0000) >> 16;
            bits2d[i][2] = (testVals[i] & 0x0000FF00) >> 8;
            bits2d[i][3] = testVals[i] & 0x000000FF;
            cout << std::hex << bits2d[i][0] << " " << std::hex << bits2d[i][1] << " " << std::hex << bits2d[i][2] << " " << std::hex << bits2d[i][3] << "\n";
        }
        outputVals = MixColumns(testVals);
        cout << "After running MixColumns\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            bits[0] = (outputVals[i] & 0xFF000000) >> 24;
            bits[1] = (outputVals[i] & 0x00FF0000) >> 16;
            bits[2] = (outputVals[i] & 0x0000FF00) >> 8;
            bits[3] = outputVals[i] & 0x000000FF;
            cout << std::hex << bits[0] << " " << std::hex << bits[1] << " " << std::hex << bits[2] << " " << std::hex << bits[3] << "\n";
        }
        break;
    case 8:
    cout << "You chose to Test InvMixColumns\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            // Temporary Value to hold shifted bytes
            unsigned tempVal = 0;
            // Extracts each bit from the state and stores it in a temporary array
            bits2d[i][0] = (testVals[i] & 0xFF000000) >> 24;
            bits2d[i][1] = (testVals[i] & 0x00FF0000) >> 16;
            bits2d[i][2] = (testVals[i] & 0x0000FF00) >> 8;
            bits2d[i][3] = testVals[i] & 0x000000FF;
            cout << std::hex << bits2d[i][0] << " " << std::hex << bits2d[i][1] << " " << std::hex << bits2d[i][2] << " " << std::hex << bits2d[i][3] << "\n";
        }
        outputVals = InvMixColumns(testVals);
        cout << "After running InvShiftRows\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            bits[0] = (outputVals[i] & 0xFF000000) >> 24;
            bits[1] = (outputVals[i] & 0x00FF0000) >> 16;
            bits[2] = (outputVals[i] & 0x0000FF00) >> 8;
            bits[3] = outputVals[i] & 0x000000FF;
            cout << std::hex << bits[0] << " " << std::hex << bits[1] << " " << std::hex << bits[2] << " " << std::hex << bits[3] << "\n";
        }
        break;
    //Need to make sure my KeyExpansion Functions work, will show different data to test.
    case 9:
    cout << "You chose to Test KeyExpansion\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            // Temporary Value to hold shifted bytes
            unsigned tempVal = 0;
            // Extracts each bit from the state and stores it in a temporary array
            bits2d[i][0] = (testVals[i] & 0xFF000000) >> 24;
            bits2d[i][1] = (testVals[i] & 0x00FF0000) >> 16;
            bits2d[i][2] = (testVals[i] & 0x0000FF00) >> 8;
            bits2d[i][3] = testVals[i] & 0x000000FF;
            cout << std::hex << bits2d[i][0] << " " << std::hex << bits2d[i][1] << " " << std::hex << bits2d[i][2] << " " << std::hex << bits2d[i][3] << "\n";
        }
        outputVals = InvMixColumns(testVals);
        cout << "After running KeyExpansion\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            bits[0] = (outputVals[i] & 0xFF000000) >> 24;
            bits[1] = (outputVals[i] & 0x00FF0000) >> 16;
            bits[2] = (outputVals[i] & 0x0000FF00) >> 8;
            bits[3] = outputVals[i] & 0x000000FF;
            cout << std::hex << bits[0] << " " << std::hex << bits[1] << " " << std::hex << bits[2] << " " << std::hex << bits[3] << "\n";
        }
        break;
    case 10:
    cout << "You chose to Test InvKeyExpansion\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            // Temporary Value to hold shifted bytes
            unsigned tempVal = 0;
            // Extracts each bit from the state and stores it in a temporary array
            bits2d[i][0] = (testVals[i] & 0xFF000000) >> 24;
            bits2d[i][1] = (testVals[i] & 0x00FF0000) >> 16;
            bits2d[i][2] = (testVals[i] & 0x0000FF00) >> 8;
            bits2d[i][3] = testVals[i] & 0x000000FF;
            cout << std::hex << bits2d[i][0] << " " << std::hex << bits2d[i][1] << " " << std::hex << bits2d[i][2] << " " << std::hex << bits2d[i][3] << "\n";
        }
        outputVals = InvMixColumns(testVals);
        cout << "After running InvKeyExpansion\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            bits[0] = (outputVals[i] & 0xFF000000) >> 24;
            bits[1] = (outputVals[i] & 0x00FF0000) >> 16;
            bits[2] = (outputVals[i] & 0x0000FF00) >> 8;
            bits[3] = outputVals[i] & 0x000000FF;
            cout << std::hex << bits[0] << " " << std::hex << bits[1] << " " << std::hex << bits[2] << " " << std::hex << bits[3] << "\n";
        }
        break;
    case 11:
    cout << "You chose to Test KeyExpansionEIC\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            // Temporary Value to hold shifted bytes
            unsigned tempVal = 0;
            // Extracts each bit from the state and stores it in a temporary array
            bits2d[i][0] = (testVals[i] & 0xFF000000) >> 24;
            bits2d[i][1] = (testVals[i] & 0x00FF0000) >> 16;
            bits2d[i][2] = (testVals[i] & 0x0000FF00) >> 8;
            bits2d[i][3] = testVals[i] & 0x000000FF;
            cout << std::hex << bits2d[i][0] << " " << std::hex << bits2d[i][1] << " " << std::hex << bits2d[i][2] << " " << std::hex << bits2d[i][3] << "\n";
        }
        outputVals = InvMixColumns(testVals);
        cout << "After running KeyExpansionEIC\n";
        for (int i = 0; i < 4; i++)
        {
            unsigned bits[4];
            bits[0] = (outputVals[i] & 0xFF000000) >> 24;
            bits[1] = (outputVals[i] & 0x00FF0000) >> 16;
            bits[2] = (outputVals[i] & 0x0000FF00) >> 8;
            bits[3] = outputVals[i] & 0x000000FF;
            cout << std::hex << bits[0] << " " << std::hex << bits[1] << " " << std::hex << bits[2] << " " << std::hex << bits[3] << "\n";
        }
        break;
    default:
        cout << "YOu didn't input anything/You didn't input a correct choice\n";
        break;
    }
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

    // Implement a command line interface

    unsigned bit1 = 0x00;
    unsigned bit2 = 0x01;
    unsigned bit3 = 0x10;
    unsigned bit4 = 0x11;
    unsigned bit5 = 0xff;
    unsigned word1 = 0x00DDEEFF;
    // Testing values for key expansions at sizes 128, 192, and 256 bits.
    vector<long> testKey128 = {(0x2b7e1516), (0x28aed2a6), (0xabf71588), (0x09cf4f3c)};
    vector<long> testKey192 = {(0x8e73b0f7), (0xda0e6452), (0xc810f32b), (0x809079e5), (0x62f8ead2), (0x522c6b7b)};
    vector<long> testKey256 = {(0x603deb10), (0x15ca71be), (0x2b73aef0), (0x857d7781), (0x1f352c07), (0x3b6108d7), (0x2d9810a3), (0x0914dff4)};

    // Test Values for the input and RoundKey from Appendix B for Cipher
    // Nb = 4, Nk = 4
    vector<long> testInputB = {(0x328831e0), (0x435a3137), (0xf6309807), (0xa88da234)};
    vector<long> testRoundKeyB = {(0x2b28ab09), (0x7eaef7cf), (0x15d2154f), (0x16a6883c)};

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

    // for (int i = 0; i < 4; i++)
    // {
    //     cout << std::hex <<testingVector[i] << endl;
    // }
    // testingVector = ShiftRows(testingVector);
    // cout << endl;
    // for (int i = 0; i < 4; i++)
    // {
    //     cout << std::hex <<testingVector[i] << endl;
    // }
    // testingVector = InvShiftRows(testingVector);
    // cout << endl;
    // for (int i = 0; i < 4; i++)
    // {
    //     cout << std::hex <<testingVector[i] << endl;
    // }
    // unsigned testSus = amogus[0][0] + amogus[0][1] + amogus[0][2] + amogus[0][3];
    // cout << std::hex << testSus << ": Testsus Confirmed\n";
    return 0;
}