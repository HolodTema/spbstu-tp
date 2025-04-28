#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>
#include <iostream>
#include <complex>

namespace holodilov
{
    struct DataStruct
    {
    public:
        unsigned long long key1;
        std::complex< double > key2;
        std::string key3;
    };

    std::ostream& operator<<(std::ostream& os, const DataStruct& dataStruct);

    std::istream& operator>>(std::istream& is, DataStruct& dataStruct);

    bool operator<(const DataStruct& lhs, const DataStruct& rhs);
}

#endif //DATA_STRUCT_H
