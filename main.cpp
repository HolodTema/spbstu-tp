#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

#include "DataStruct.hpp"

int main()
{
    using namespace holodilov;

    std::vector<DataStruct> vec;
    while(! std::cin.eof())
    {
        std::copy(std::istream_iterator< DataStruct >(std::cin), std::istream_iterator< DataStruct >(), std::back_inserter(vec));
        if (!std::cin)
        {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        }
    }
    std::sort(vec.begin(), vec.end());
    std::copy(std::begin(vec), std::end(vec), std::ostream_iterator< DataStruct >(std::cout, "\n"));
    return 0;
}
