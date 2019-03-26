#include "Conversion.h"

string intToStr(int n)
{
    string tmp, ret;
    if(n < 0)
    {
        ret = "-";
        n = -n;
    }

    do
    {
        tmp += n % 10 + 48;
        n -= n % 10;
    }while(n /= 10);

    for(int i = tmp.size()-1; i >= 0; i--)
    {
        ret += tmp[i];
    }

    return ret;
}

float B2DtoSF(float n)
{
    return n * 50.0f;
}

float SFtoB2D(float n)
{
    return n / 50.0f;
}
