#include "StaticVariable.h"

namespace StaticVariable
{
    //This place contains global variable
    int BYTES_PER_CLUSTER = 4;
}




uint64_t Utils::Convert2LitleEndian(byteArrayPointer offset, int numBytes)
{
    if (numBytes <= 0 || numBytes > 8)
        return 0;

    uint64_t res = 0;
    for (int i = 0; i < numBytes; i++)
    {
        res |= (*offset) << (i * 8);
        offset++;
    }
    return res;
}