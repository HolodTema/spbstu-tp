#include "DataStruct.hpp"
#include "StreamGuard.hpp"


std::istream& holodilov::operator>>(std::istream& is, DataStruct& dataStruct)
{
    std::istream::sentry s(is);
    if (!s)
    {
        return is;
    }
    StreamGuard streamGuard(is);

    manipulator::CharIO openingBracketCharIO{ '(' };
    manipulator::CharIO closingBracketCharIO{ ')' };
    manipulator::CharIO colonCharIO{':' };
    manipulator::KeyNameIO keyNameIO { ' ' };

    is >> openingBracketCharIO;
    is >> colonCharIO;

    bool isFirstKeyGot = false;
    bool isSecondKeyGot = false;
    bool isThirdKeyGot = false;

    for (int i = 0; i < 3; ++i) {
        is >> keyNameIO;

        if (!isFirstKeyGot && keyNameIO.keyNameNumber == '1') {
            isFirstKeyGot = true;
            manipulator::UllOctIO ullOctIO{ 0ull };
            is >> ullOctIO;
            dataStruct.key1 = ullOctIO.value;
        }
        else if (!isSecondKeyGot && keyNameIO.keyNameNumber == '2') {
            isSecondKeyGot = true;
        }
        else if (!isThirdKeyGot && keyNameIO.keyNameNumber == '3') {
            isThirdKeyGot = true;
            manipulator::StringIO stringIO { dataStruct.key3 };
            is >> stringIO;
            dataStruct.key3 = stringIO.value;
        }
        else {
            is.setstate(std::ios::failbit);
            return is;
        }
        is >> colonCharIO;
    }
    is >> closingBracketCharIO;
    return is;
}

std::istream& holodilov::operator>>(std::istream& is, manipulator::CharIO& charIO) {
    std::istream::sentry s(is);
    if (!s) {
        return is;
    }
    StreamGuard streamGuard(is);

    char ch = '\0';
    is >> ch;
    if (is && (ch != charIO.ch)) {
        is.setstate(std::ios::failbit);
    }
    return is;
}

std::istream& holodilov::operator>>(std::istream& is, manipulator::KeyNameIO& keyNameIO) {
    std::istream::sentry s(is);
    if (!s) {
        return is;
    }
    StreamGuard streamGuard(is);

    std::string strKeyName;
    is >> strKeyName;
    if (is && strKeyName.substr(0, 3) == "key" && strKeyName.size() == 4) {
        keyNameIO.keyNameNumber = strKeyName[3];
        if (keyNameIO.keyNameNumber != '1' && keyNameIO.keyNameNumber != '2' && keyNameIO.keyNameNumber != '3') {
            is.setstate(std::ios::failbit);
        }
    }
    else {
        is.setstate(std::ios::failbit);
    }
    return is;
}

std::istream& holodilov::operator>>(std::istream& is, manipulator::UllOctIO& ullOctIO) {
    std::istream::sentry s(is);
    if (!s) {
        return is;
    }
    StreamGuard streamGuard(is);

    unsigned long long ull = 0ull;
    is >> ull;
    if (!is) {
        is.setstate(std::ios::failbit);
        return is;
    }
    std::stringstream strStream;
    strStream << ull;
    std::string strUll = strStream.str();
    if (strUll.size() <= 1 || strUll[0] != '0') {
        is.setstate(std::ios::failbit);
        return is;
    }
    std::string allowedDigits = "01234567";
    for (int i = 1; i < strUll.size(); ++i) {
        bool isAllowed = false;
        for (const char digit: allowedDigits) {
            if (strUll[i] == digit) {
                isAllowed = true;
                break;
            }
        }
        if (!isAllowed) {
            is.setstate(std::ios::failbit);
            return is;
        }
    }
    ullOctIO.value = ull;

    return is;
}

std::istream& holodilov::operator>>(std::istream& is, manipulator::CmpLspIO& cmpLspIO) {
    std::istream::sentry s(is);
    if (!s) {
        return is;
    }
    StreamGuard streamGuard(is);

    manipulator::CharIO hashCharIO{ '#' };
    manipulator::CharIO cCharIO{ 'c' };
    manipulator::CharIO openingBracketCharIO{ '(' };
    manipulator::CharIO closingBracketCharIO{ ')' };
    is >> hashCharIO;
    is >> cCharIO;
    is >> openingBracketCharIO;
    if (!is) {
        return is;
    }

    double double1 = 0.0;
    double double2 = 0.0;
    is >> double1;
    if (!is) {
        return is;
    }
    is >> double2;
    if (!is) {
        return is;
    }
    is >> closingBracketCharIO;

    cmpLspIO.value = std::complex< double >(double1, double2);
    return is;
}

std::istream& holodilov::operator>>(std::istream& is, manipulator::StringIO& stringIO) {
    std::istream::sentry s(is);
    if (!s) {
        return is;
    }
    StreamGuard streamGuard(is);

    manipulator::CharIO quoteCharIO{ '"' };
    is >> quoteCharIO;
    if (!is) {
        return is;
    }

    std::getline(is, stringIO.value, '"');
    return is;
}


std::ostream& holodilov::operator<<(std::ostream& os, const DataStruct& data)
{
    std::ostream::sentry s(os);
    if (!s)
    {
        return os;
    }
    StreamGuard streamGuard(os);
    os << "(:";
    os << manipulator::KeyNameIO{ '1' } << " " << manipulator::UllOctIO{ data.key1 } << ":";
    os << manipulator::KeyNameIO{ '2' } << " " << manipulator::CmpLspIO{ data.key2 } << ":";
    os << manipulator::KeyNameIO{ '3' } << " " << manipulator::StringIO{ data.key3 } << ":)\n";
    os << "(:key1 " << data.key1 << ":key2 " << data.key2 << ":key3 " << data.key3 << ":)\n";
    return os;
}

std::ostream& holodilov::operator<<(std::ostream& os, const manipulator::KeyNameIO& keyNameIO) {
    std::ostream::sentry s(os);
    if (!s)
    {
        return os;
    }
    StreamGuard streamGuard(os);

    os << "key" << keyNameIO.keyNameNumber;
    return os;
}

std::ostream& holodilov::operator<<(std::ostream& os, const manipulator::UllOctIO& ullOctIO) {
    std::ostream::sentry s(os);
    if (!s)
    {
        return os;
    }
    StreamGuard streamGuard(os);
    os << '0' << ullOctIO.value << "ull";
    return os;
}

std::ostream& holodilov::operator<<(std::ostream& os, const manipulator::CmpLspIO& cmpLspIO) {
    std::ostream::sentry s(os);
    if (!s)
    {
        return os;
    }
    StreamGuard streamGuard(os);
    os << "#c(";
    os << cmpLspIO.value.real();
    os << " ";
    os << cmpLspIO.value.imag();
    os << ")";
    return os;
}

std::ostream& holodilov::operator<<(std::ostream& os, const manipulator::StringIO& stringIO) {
    std::ostream::sentry s(os);
    if (!s)
    {
        return os;
    }
    StreamGuard streamGuard(os);
    os << "\"" << stringIO.value << "\"";
    return os;
}


bool holodilov::operator<(const DataStruct& lhs, const DataStruct& rhs)
{
    if (lhs.key1 != rhs.key1)
    {
        return lhs.key1 < rhs.key1;
    }
    if (lhs.key2 != rhs.key2)
    {
        return abs(lhs.key2) < abs(rhs.key2);
    }
    return lhs.key3.length() < rhs.key3.length();
}