#include "StreamGuard.hpp"

holodilov::StreamGuard::StreamGuard(std::basic_ios< char >& ios):
    ios_(ios),
    precision_(ios.precision()),
    fmtFlags_(ios.flags())
{

}

holodilov::StreamGuard::~StreamGuard()
{
    ios_.precision(precision_);
    ios_.flags(fmtFlags_);
}

