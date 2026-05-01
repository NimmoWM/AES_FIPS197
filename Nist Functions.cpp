//Link to specifications.
//https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197-upd1.pdf
//TODO: FIX type differences between functions and their calls, and get RoundKey implemented properly, and add a proper Main function
//Changes Between last upload: Implemented Key Expansion Function, started code for Key Expansion EIC (Not completed Yet)

#include <vector>
#include <iostream>
#include <iomanip>

unsigned c = 0b01100011;
//Array used for Sbox() function called by subWord and Key Expansion Functions
unsigned sArray[16][16] = 
{
    {0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76},
    {0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0},
    {0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15},
    {0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75},
    {0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0x39,0x29,0xe3,0x2f,0x84},
    {0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x7f,0x4a,0x4c,0x58,0xcf},
    {0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x21,0x50,0x3c,0x9f,0xa8},
    {0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x7f,0x10,0xff,0xf3,0xd2},
    {0xcd,0x0c,0x13,0xec,0x5f,0x97,0x24,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x91,0x28,0x73},
    {0x60,0x81,0x4f,0xdc,0x22,0x06,0x90,0x5c,0x46,0xee,0xb8,0x14,0xde,0x86,0x8b,0xdb},
    {0xe0,0x32,0x3a,0x0a,0x49,0xd5,0x24,0xa9,0xc2,0xd3,0xac,0x62,0x91,0x7a,0xe4,0x79},
    {0xe7,0xc8,0x37,0x6d,0x8d,0xa6,0x4e,0xc6,0x6c,0x56,0xf4,0xea,0x65,0xbd,0xae,0x08},
    {0xba,0x78,0x25,0x2e,0x1c,0x03,0xb4,0x0e,0xe8,0xdd,0xf4,0xb9,0x4b,0xbd,0x8b,0x8a},
    {0x70,0x3e,0xb5,0x66,0x48,0xd9,0xf6,0x94,0x61,0x35,0x74,0xe9,0x86,0xc1,0x1d,0x9e},
    {0xe1,0xf8,0x98,0x11,0x69,0xe6,0x8e,0x68,0x9b,0x1e,0x57,0xe9,0x86,0xc1,0x28,0xdf},
    {0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x87,0x0f,0xce,0x54,0xbb,0x16},
};

//Array used for inverse sArray
unsigned sInvArray[16][16] = 
{
    {0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,},
    {0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,},
    {0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e,},
    {0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,},
    {0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,},
    {0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,},
    {0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06,},
    {0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b,},
    {0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,},
    {0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,},
    {0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b,},
    {0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,},
    {0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,},
    {0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,},
    {0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,},
    {0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d,},
};

// *Depricated implementation*
// //Word array for round Constant, stored in a 2d Array
// unsigned Rcon[10][4] = 
// {
//     {0x01,0x00,0x00,0x00},
//     {0x02,0x00,0x00,0x00},
//     {0x04,0x00,0x00,0x00},
//     {0x08,0x00,0x00,0x00},
//     {0x10,0x00,0x00,0x00},
//     {0x20,0x00,0x00,0x00},
//     {0x40,0x00,0x00,0x00},
//     {0x80,0x00,0x00,0x00},
//     {0x1b,0x00,0x00,0x00},
//     {0x36,0x00,0x00,0x00},
// };
//Word array for round Constant, stored as a whole word in a single dimensional array for conviencence.
unsigned Rcon[10] = 
{
    {0x01000000},
    {0x02000000},
    {0x04000000},
    {0x08000000},
    {0x10000000},
    {0x20000000},
    {0x40000000},
    {0x80000000},
    {0x1b000000},
    {0x36000000},
};


//Array used by mixColumns()
unsigned mixArray[4] = {0x02, 0x01, 0x01, 0x03};

void outputToConsole(std::vector<long> input)
{
    std::cout << "Outputting to console\n";
    for (int i = 0; i < 4; i++)
        {
            unsigned bits2d[4][4];
            // Temporary Value to hold shifted bytes
            unsigned tempVal = 0;
            // Extracts each bit from the state and stores it in a temporary array
            bits2d[i][0] = (input[i] & 0xFF000000) >> 24;
            bits2d[i][1] = (input[i] & 0x00FF0000) >> 16;
            bits2d[i][2] = (input[i] & 0x0000FF00) >> 8;
            bits2d[i][3] = input[i] & 0x000000FF;
            std::cout << std::hex << bits2d[i][0] << " " << std::hex << bits2d[i][1] << " " << std::hex << bits2d[i][2] << " " << std::hex << bits2d[i][3] << "\n";
        }
}

//Todo: Test Roundkey Function
//std::vector<long> AddRoundKey(std::vector<long> state, long word[])
std::vector<long> AddRoundKey(std::vector<long> state, std::vector<long> word)
{
    std::cout << "\n+++++++Entering AddRound Key Function+++++++\n";
    //addRoundkey
    //Add proper implementation
    unsigned bits[4][4];
    for (int i = 0; i < 4; i++)
    {
    bits[0][i] = ((state[i] & 0xFF000000) >> 24);
    bits[1][i] = ((state[i] & 0x00FF0000) >> 16);
    bits[2][i] = ((state[i] & 0x0000FF00) >> 8);
    bits[3][i] = (state[i]  & 0x000000FF);
    }

    for(int i = 0; i < 4; i++)
    {
    bits[i][0] = bits[i][0] ^ word[i];
    bits[i][1] = bits[i][1] ^ word[i];
    bits[i][2] = bits[i][2] ^ word[i];
    bits[i][3] = bits[i][3] ^ word[i];
    }

    for (int a = 0; a < 4; a++)
    {
    state[a] = (bits[a][0] << 24) + (bits[a][1] << 16) + (bits[a][2] << 8)+ (bits[a][3]);
    }
    std::cout << "+++++++Exiting AddRound Key Function+++++++\n" << std::endl;
    return state;
}

unsigned Sbox(unsigned input)
{
    unsigned output = 0;

    //All std::cout sections of code are for debugging.
    // std::cout << std::hex << input << std::endl;
    // std::cout << std::hex << (input & 0xF0) << std::endl;
    //Extracts individual characters from byte
    unsigned x = (input & (0xF0)) >> 4;
    unsigned y = input & (0x0F);
    // std::cout << std::hex << x << std::endl;
    // std::cout << std::hex << y << std::endl;
    output = sArray[x][y];

    return output;
}

unsigned Sinvbox(unsigned input)
{
    unsigned output = 0;

    //All std::cout sections of code are for debugging.
    // std::cout << std::hex << input << std::endl;
    // std::cout << std::hex << (input & 0xF0) << std::endl;
    //Extracts individual characters from byte
    unsigned x = (input & (0xF0)) >> 4;
    unsigned y = input & (0x0F);
    // std::cout << std::hex << x << std::endl;
    // std::cout << std::hex << y << std::endl;
    output = sInvArray[x][y];
    
    return output;
}

unsigned subWord(unsigned input)
{
    unsigned bits[4];
    //Extracts each bit and runs them through the Sbox function
    bits[0] = Sbox((input & 0xFF000000) >> 24);
    bits[1] = Sbox((input & 0x00FF0000) >> 16);
    bits[2] = Sbox((input & 0x0000FF00) >> 8);
    bits[3] = Sbox(input  & 0x000000FF);
    // std::cout << "Bits 0:" << std::hex << bits[0] << std::endl;
    // std::cout << "Bits 1:" << std::hex << bits[1] << std::endl;
    // std::cout << "Bits 2:" << std::hex << bits[2] << std::endl;
    // std::cout << "Bits 3:" << std::hex << bits[3] << std::endl;
    unsigned output = 0;
    int a = 0;
    while (a < 4)
    {
        output += ((bits[a]) << (24-(8 * a)));
        a++;
    }
    return output;
}


//Convert argument and output into vector of longs
std::vector<long> invSubBytes(std::vector<long>& input)
{
    unsigned bits[4][4];
    for (int row = 0; row < 4; row++)
    {
        //Extracts each bit and runs them through the Sbox function
        bits[0][row] = Sinvbox((input[row] & 0xFF000000) >> 24);
        bits[1][row] = Sinvbox((input[row] & 0x00FF0000) >> 16);
        bits[2][row] = Sinvbox((input[row] & 0x0000FF00) >> 8);
        bits[3][row] = Sinvbox(input[row] & 0x000000FF);
        // std::cout << "Bits 0:" << std::hex << bits[0][row] << std::endl;
        // std::cout << "Bits 1:" << std::hex << bits[1][row] << std::endl;
        // std::cout << "Bits 2:" << std::hex << bits[2][row] << std::endl;
        // std::cout << "Bits 3:" << std::hex << bits[3][row] << std::endl;
        unsigned output = 0;
        int a = 0;
        while (a < 4)
        {
            output += ((bits[a][row]) << (24-(8 * a)));
            a++;
        }
        input[row] = output;
    }
    return input;
}

unsigned rotWord(unsigned input)
{
    unsigned bits[4];
    bits[0] = (input & 0xFF000000) >> 24;
    bits[1] = (input & 0x00FF0000) >> 16;
    bits[2] = (input & 0x0000FF00) >> 8;
    bits[3] = input & 0x000000FF;
    unsigned output = 0;
    for (int a = 0; a < 4; a++)
    {
        // std::cout << "Current iterator is: A" << a << std::endl;
        //Shift is equal to column + row modulos 4
        int shift = (1 + a) % 4;
        // std::cout << std::hex << bits[shift] << " ";
        //Bits are bitshifted back to position in increments of 8
        output += ((bits[shift]) << (24-(8 * a)));
    }
    return output;
}

std::vector<long> SubBytes(std::vector<long>& state)
{
    //std::byte amogus = 0xaa;
    int row = 0;
    
    while (row < 4)
    {
        //Extracts individual bytes from a selected row of state
        unsigned bits[4];
        //The individual bytes after being ran through the S-Box
        unsigned bitsSquigly[4];
        //b * b^-1 = {01}
        //Temporary Value to hold shifted bytes
        unsigned tempVal = 0;  
        //Extracts each bit from the state and stores it in a temporary array
        bits[0] = Sbox((state[row] & 0xFF000000) >> 24);
        bits[1] = Sbox((state[row] & 0x00FF0000) >> 16);
        bits[2] = Sbox((state[row] & 0x0000FF00) >> 8);
        bits[3] = Sbox(state[row] & 0x000000FF);
        //Actual transformation for each bit in the state
        //Resets i increment counter when i reaches 4
        for (int a = 0; a < 4; a++)
        {
            tempVal += ((bits[a]) << (24-(8 * a)));
        }
        //std::cout << "tempVal is: " << std::hex << tempVal << "\n";
        state[row] = tempVal;
        row++;
    }
    return state;
}

//Using a vector passed by reference for the storage of bytes
std::vector<long> ShiftRows(std::vector<long>& state)
{
    int row = 0;
    
    while (row < 4)
    {
        //Extracts individual bytes from a selected row of state
        unsigned bits[4];
        //Temporary Value to hold shifted bytes
        unsigned tempVal = 0;  
        //Extracts each bit from the state and stores it in a temporary array
        bits[0] = (state[row] & 0xFF000000) >> 24;
        bits[1] = (state[row] & 0x00FF0000) >> 16;
        bits[2] = (state[row] & 0x0000FF00) >> 8;
        bits[3] = state[row] & 0x000000FF;
        //Actual transformation for each bit in the state
        //Resets i increment counter when i reaches 4
        for (int a = 0; a < 4; a++)
        {
            // std::cout << "Current iterator is: A" << a << std::endl;
            //Shift is equal to column + row modulos 4
            int shift = (row + a) % 4;
            // std::cout << std::hex << bits[shift] << " ";
            //Bits are bitshifted back to position in increments of 8
            tempVal += ((bits[shift]) << (24-(8 * a)));
        }
        // std::cout << std::endl << "tempVal is:";
        // std::cout << std::hex << tempVal << std::endl;
        state[row] = tempVal;
        row++;
    }
    return state;
}

//Using a vector passed by reference for the storage of bytes
std::vector<long> InvShiftRows(std::vector<long>& state)
{
    int row = 0;
    
    while (row < 4)
    {
    //Extracts individual bytes from a selected row of state
    unsigned bits[4];
    //Temporary Value to hold shifted bytes
    unsigned tempVal = 0;  
    //Extracts each bit from the state and stores it in a temporary array
    bits[0] = (state[row] & 0xFF000000) >> 24;
    bits[1] = (state[row] & 0x00FF0000) >> 16;
    bits[2] = (state[row] & 0x0000FF00) >> 8;
    bits[3] = state[row] & 0x000000FF;
    //Actual transformation for each bit in the state
    //Resets i increment counter when i reaches 4
    for (int a = 0; a < 4; a++)
        {
        // std::cout << "Current iterator is: A" << a << std::endl;
        //SUsed (4 - row) + a modulos 4 for the shift formula, using the normal formula but subtracting caused overflow issues.
        int shift = ((4 - row)+ a)% 4;
        //std::cout << "Shift: " << shift<< " ";
        //Bits are bitshifted back to position in increments of 8
        tempVal += ((bits[shift]) << (24-(8 * a)));
        }
    // std::cout << std::endl << "tempVal is:";
    // std::cout << std::hex << tempVal << std::endl;
    state[row] = tempVal;
    row++;
    }
    return state;
}

std::vector<long> MixColumns(std::vector<long>& state)
{
    int row = 0;
    unsigned tempVal = 0;
    //Extracts individual bytes and stores them in a 2d array
    unsigned bits[4][4];
    unsigned results[4][4];
    while (row < 4)
    {
    //unsigned mogus = 0x0F;
    //Extracts each bit from the state and stores it in a temporary array
    bits[0][row] = (state[row] & 0xFF000000) >> 24;
    bits[1][row] = (state[row] & 0x00FF0000) >> 16;
    bits[2][row] = (state[row] & 0x0000FF00) >> 8;
    bits[3][row] = state[row] & 0x000000FF;
    row++;
    }
    int a = 0;
    while (a < 4)
    {
    results[0][a] = ((0x02)*bits[0][a]) ^ ((0x03)*bits[1][a]) ^ ((0x01)*bits[2][a]) ^ ((0x01)*bits[3][a]);
    results[1][a] = ((0x01)*bits[0][a]) ^ ((0x02)*bits[1][a]) ^ ((0x03)*bits[2][a]) ^ ((0x01)*bits[3][a]);
    results[2][a] = ((0x01)*bits[0][a]) ^ ((0x01)*bits[1][a]) ^ ((0x02)*bits[2][a]) ^ ((0x03)*bits[3][a]);
    results[3][a] = ((0x03)*bits[0][a]) ^ ((0x01)*bits[1][a]) ^ ((0x01)*bits[2][a]) ^ ((0x02)*bits[3][a]);
    // std::cout << "Results: " << std::hex << results[0][a] << "\n";
    // std::cout << "Results: " << std::hex << results[1][a] << "\n";
    // std::cout << "Results: " << std::hex << results[2][a] << "\n";
    // std::cout << "Results: " << std::hex << results[3][a] << "\n";
    a++;
    }
    //Iffy on if this section is working right or not?
    for (int b = 0; b < 4; b++)
    {
    state[b] = (results[b][0] << 24) + (results[b][1] << 16) + (results[b][2] << 8) + (results[b][3]);
    std::cout << "Results for row " << b << ": " << std::hex << state[b] << "\n";
    }
    //Return state
    return state;
}

std::vector<long> InvMixColumns(std::vector<long>& state)
{
    int row = 0;
    unsigned tempVal = 0;
    //Extracts individual bytes and stores them in a 2d array
    unsigned bits[4][4];
    unsigned results[4][4];
    while (row < 4)
    {
    //unsigned mogus = 0x0F;
    //Extracts each bit from the state and stores it in a temporary array
    bits[0][row] = (state[row] & 0xFF000000) >> 24;
    bits[1][row] = (state[row] & 0x00FF0000) >> 16;
    bits[2][row] = (state[row] & 0x0000FF00) >> 8;
    bits[3][row] = state[row] & 0x000000FF;
    row++;
    }
    int a = 0;
    while (a < 4)
    {
        results[0][a] = ((0x0e)*bits[0][a]) ^ ((0x0b)*bits[1][a]) ^ ((0x0d)*bits[2][a]) ^ ((0x09)*bits[3][a]);
        results[1][a] = ((0x09)*bits[0][a]) ^ ((0x0e)*bits[1][a]) ^ ((0x0b)*bits[2][a]) ^ ((0x0d)*bits[3][a]);
        results[2][a] = ((0x0d)*bits[0][a]) ^ ((0x09)*bits[1][a]) ^ ((0x0e)*bits[2][a]) ^ ((0x0b)*bits[3][a]);
        results[3][a] = ((0x0b)*bits[0][a]) ^ ((0x0d)*bits[1][a]) ^ ((0x09)*bits[2][a]) ^ ((0x0e)*bits[3][a]);
        a++;
    }
    //Iffy on if this section is working right or not?
    for (int b = 0; b < 4; b++)
    {
    state[b] = (results[b][0] << 24) + (results[b][1] << 16) + (results[b][2] << 8) + (results[b][3]);
    std::cout << "Results for row " << b << ": " << std::hex << state[b] << "\n";
    }
    //Return state
    return state;
}

//Implementation of Key Expansion
//long KeyExpansion(long key[], int Nr, int NK)
std::vector<long> KeyExpansion(std::vector<long> key, int Nr, int NK)
{
    int i = 0;
    //Define w as a temporary Vector which will be returned.
    //std::vector<long> w = {0x00};
    std::vector<long> w;
    std::vector<long> temp;
    std::vector<long> words;
    do
    {
        // long addValue = key[(4*i)] + key[(4*i) + 1] + key[(4*i) + 2] + key[(4*i) + 3];
        // //std::cout << "addValue: " << std::hex << addValue << " \n";
        // w.push_back(addValue);
        w.push_back(key[i]);
        //std::cout << "Current I: " << i << " \n";
        i++;
    }
    while (i <= (NK -1));
    std::cout << "+++++++First Do while loop exited+++++++\n";
    do
    {
        unsigned temp = w[i-1];
        if (i % NK == 0)
        {
        temp = subWord(rotWord(temp)) ^ Rcon[i/NK];
        }
        else if ((NK > 6) and ((i % NK) == 4))
        {
        temp = subWord(temp);
        }
        //std::cout << "w[" << i << "] should be: " << std::hex << (w[i- NK] ^ temp) << std::endl;
        //w[i] = w[i- NK] ^ temp;
        w.push_back(w[i- NK] ^ temp);
        //std::cout << "w[" << i << "] is: " << std::hex << w[i] << std::endl;
        //std::cout << "Edited w[i] \n" <<"Current I: " << i << " \n";
        i++;
    } while (i <= ((4*Nr) +3));
    for (int a = 0; a < i; a++)
    {
    std::cout << "w[" << a << "] is: " << std::hex << w[a] << std::endl;
    }
    std::cout << "Returning w" << "\n";
    return w;
}

//Alternative implementation of Key Expansion
long KeyExpansionEIC(long key[], int Nr, int NK)
{
    std::vector<long> w = {1};
    int i =0;
    std::vector<long> dw;
    do
    {
        //Pull key from 4i to 4i+3
        w[i] = key[(4*i)*((4*i)+3)];
        dw.push_back(w[i]);
        i++;
    }
    while (i <= (NK -1));
    std::cout << "+++++++First Do while loop exited+++++++\n";
    do
    {
        unsigned temp = w[i-1];
        if (i % NK == 0)
        {
        temp = subWord(rotWord(temp)) ^ Rcon[i/NK];
        }
        //Havbing issues with iterator i in this section.
        else if ((NK > 6) and (i % NK == 4))
        {
        temp = subWord(temp);
        }
        w[i] = w[i- NK] ^ temp;
        i++;
    } while (i <= (Nr +3));
    return 1;
}


std::vector<long> AEScipher (std::vector<long> input,int NumRounds, std::vector<long> w, int NK)
{
    std::cout << "\n+++++++Entering AESCipher Function+++++++\n" << std::endl;
    //Gets state from input byte array to encrypt
    //long state[NumRounds] = input;
    //State is implemented as a vector of ints, each int holds 4 bytes
    //std::vector<long>state;
    //Push_back

    std::vector<long>state = input;

    std::vector<long> wordSection = {0x01, 0x02, 0x03, 0x04};

    // Run state through the add roundkey function
    //Arguments for this call are from w[0] to w[3]
    std::cout << "+++++++Selecting Word Chunk+++++++\n";
    for (int GetVals = 0; GetVals < 4; GetVals++)
    {
        wordSection[GetVals] = w[GetVals];
    }
    std::cout << "+++++++Adding RoundKey+++++++\n";
    state = AddRoundKey(state, wordSection);
    //For loop included in Cipher, state is plugged into SubBytes, ShiftRows, MixColumns, and AddRoundKey again.
    //Need to Implement SubBytes, ShiftRows, and MixColumns
    //Currently Function seems to not be calling values correctly
    //I is the current round of the for loop
    for (int i = 1; i < (NumRounds-1); i++)
    {
        state =   SubBytes(state);
        std::cout << "+++++++Running SubBytes+++++++\n";
        outputToConsole(state);
        state =  ShiftRows(state);
        std::cout << "+++++++Running ShiftRows+++++++\n";
        outputToConsole(state);
        state = MixColumns(state);
        std::cout << "+++++++Running MixColumns+++++++\n";
        outputToConsole(state);
        //Gets section of word key based off of the current round
        for (int GetVals = (i*4); GetVals < ((4*i) + 3); GetVals++)
        {
            wordSection[GetVals] = w[GetVals];
        }
        state = AddRoundKey(state,wordSection);
        std::cout << "+++++++Running AddRoundKey+++++++\n";
        outputToConsole(state);
    }
    state = SubBytes(state);
    state = ShiftRows(state);
    for (int GetVals = (NumRounds*4); GetVals < ((4*NumRounds) + 3); GetVals++)
        {
            wordSection[GetVals] = w[GetVals];
        }
    state = AddRoundKey(state,wordSection);
    outputToConsole(state);
    return state;
}

std::vector<long> InvCipher (int input[],int NumRounds, std::vector<long> w, long key, int NK)
{
    //Gets state from input byte array to encrypt

    /*
    TODO, Continue work on functions.
    */

    //long state[NumRounds] = input;
    //State is implemented as a vector of ints, each int holds 4 bytes
    // std::vector<long>state = input;
    std::vector<long>state = {0x000000AA, 0x0000AA00, 0x00AA0000, 0xAA000000};
    //Get iterator value corrected
    //Input Whole Key, iterator will be selected in function
    state = AddRoundKey(state, w);

    for (int i = (NumRounds -1); i == 0; i--)
    {
        state = InvShiftRows(state);
        state = invSubBytes(state);
        state = AddRoundKey(state, w);
        state = InvMixColumns(state);
    }
    state = InvShiftRows(state);
    state = invSubBytes(state);
    state = AddRoundKey(state, w);

    return state;
}

//Alternative implementation of Inverse Cipher
std::vector<long> EqInvCipher (int input[],int NumRounds, std::vector<long> w, long key, int NK)
{
    //Gets state from input byte array to encrypt
    /*
    TODO, Continue work on functions.
    */

    //long state[NumRounds] = input;
    //State is implemented as a vector of ints, each int holds 4 bytes
    // std::vector<long>state = input;
    std::vector<long>state = {0x000000AA, 0x0000AA00, 0x00AA0000, 0xAA000000};
    //Get iterator value corrected
    state = AddRoundKey(state, w);

    for (int i = (NumRounds -1); i == 0; i--)
    {
        state = InvShiftRows(state);
        state = invSubBytes(state);
        state = AddRoundKey(state, w);
        state = InvMixColumns(state);
    }
    state = InvShiftRows(state);
    state = invSubBytes(state);
    state = AddRoundKey(state, w);

    return state;
}

//Key length is 128 bits, Block size is 128 bits, Number of rounds is 10, NK = 4
std::vector<long> AES128(std::vector<long> input, std::vector<long> key)
{
    int NK = 4;
    //std::vector<long> output = AEScipher(input, 10, key, NK);
    std::vector<long> output = AEScipher(input, 10, KeyExpansion(key, 10, NK), NK);
    return output;
}

//Key length is 192 bits, Block size is 192 bits, Number of rounds is 12, NK = 6
std::vector<long> AES192(std::vector<long> input, std::vector<long> key)
{
    int NK = 6;
    std::vector<long> output = AEScipher(input, 12, key, NK);
    return output;
}

//Key length is 256 bits, Block size is 256 bits, Number of rounds is 14, NK = 8
std::vector<long> AES256(std::vector<long> input, std::vector<long> key)
{
    int NK = 8;
    std::vector<long> output = AEScipher(input, 14, key, NK);
    return output;
}

