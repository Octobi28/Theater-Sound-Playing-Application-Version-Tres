/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== next.png ==================
static const unsigned char temp_binary_data_0[] =
{ 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,8,0,0,0,8,8,6,0,0,0,196,15,190,139,0,0,0,1,115,82,71,66,0,174,206,28,233,0,0,0,59,73,68,65,84,24,149,125,143,65,10,0,48,8,195,82,255,255,231,238,48,4,21,183,92,68,90,177,21,23,179,35,1,182,119,93,18,
81,151,58,147,152,23,211,212,12,27,205,144,89,106,166,248,137,0,249,236,89,243,0,200,242,18,13,65,218,12,130,0,0,0,0,73,69,78,68,174,66,96,130,0,0 };

const char* next_png = (const char*) temp_binary_data_0;

//================== pause.png ==================
static const unsigned char temp_binary_data_1[] =
{ 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,8,0,0,0,8,8,6,0,0,0,196,15,190,139,0,0,0,1,115,82,71,66,0,174,206,28,233,0,0,0,50,73,68,65,84,24,149,99,100,128,128,255,12,216,1,35,35,3,3,195,255,255,255,177,203,51,50,50,50,48,33,115,176,177,153,24,
8,0,42,42,64,118,40,50,27,230,26,156,222,4,0,213,72,12,13,54,200,247,132,0,0,0,0,73,69,78,68,174,66,96,130,0,0 };

const char* pause_png = (const char*) temp_binary_data_1;

//================== play.png ==================
static const unsigned char temp_binary_data_2[] =
{ 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,8,0,0,0,8,8,6,0,0,0,196,15,190,139,0,0,0,1,115,82,71,66,0,174,206,28,233,0,0,0,54,73,68,65,84,24,149,133,143,49,18,0,32,12,194,66,255,255,103,28,60,23,90,53,35,112,133,138,141,153,145,0,219,179,47,137,
74,33,169,20,50,212,2,223,11,185,167,94,38,192,41,188,190,185,0,55,145,12,13,38,69,78,52,0,0,0,0,73,69,78,68,174,66,96,130,0,0 };

const char* play_png = (const char*) temp_binary_data_2;

//================== prev.png ==================
static const unsigned char temp_binary_data_3[] =
{ 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,8,0,0,0,8,8,6,0,0,0,196,15,190,139,0,0,0,1,115,82,71,66,0,174,206,28,233,0,0,0,58,73,68,65,84,24,149,117,143,65,14,0,48,8,194,202,254,255,103,119,88,220,166,65,46,38,210,40,136,163,192,75,2,34,194,251,
146,88,125,241,79,224,1,206,44,192,164,11,100,142,158,167,92,112,80,62,28,107,110,200,242,18,13,139,27,108,2,0,0,0,0,73,69,78,68,174,66,96,130,0,0 };

const char* prev_png = (const char*) temp_binary_data_3;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x54ebbadd:  numBytes = 129; return next_png;
        case 0x31751c60:  numBytes = 120; return pause_png;
        case 0x7000b29e:  numBytes = 124; return play_png;
        case 0xb40f321d:  numBytes = 128; return prev_png;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "next_png",
    "pause_png",
    "play_png",
    "prev_png"
};

const char* originalFilenames[] =
{
    "next.png",
    "pause.png",
    "play.png",
    "prev.png"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
        if (strcmp (namedResourceList[i], resourceNameUTF8) == 0)
            return originalFilenames[i];

    return nullptr;
}

}
