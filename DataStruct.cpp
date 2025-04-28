#include "DataStruct.h"

std::ostream& holodilov::operator<<(std::ostream& os, const DataStruct& data)
{

}

std::istream& holodilov::operator>>(std::istream& is, DataStruct& data)
{

}

bool holodilov::operator<(const DataStruct& lhs, const DataStruct& rhs)
{
    if (lhs.key1 != rhs.key1)
    {
        return lhs.key1 < rhs.key1;
    }
    else
    {
        if (lhs.key2 != rhs.key2)
        {
            return abs(lhs.key2) < abs(rhs.key2);
        }
        else
        {
            return lhs.key3.length() < rhs.key3.length();
        }
    }
}