#ifndef _PGNPARAMETERS_HPP
#define _PGNPARAMETERS_HPP

#include <iostream>
#include <string>
#include <map>
#include <extras/exceptions.hpp>

//
// GameParameter
// Encapsulates all behaviour unique to a chess parameter 
//

class PGNParameter
{
    friend std::ostream& operator<<(std::ostream& out, const PGNParameter& obj);
    friend std::istream& operator>>(std::istream& in, PGNParameter& obj);
    friend inline bool operator==(const PGNParameter& a, const PGNParameter& b)
    {
        return a.name == b.name && a.value == b.value;
    }
    friend inline bool operator!=(const PGNParameter& a, const PGNParameter& b)
    {
        return !(a == b);
    }

    std::string name;
    std::string value;

public:
    inline const std::string& key() { return name; };
};

class PGNParameters : public std::map<std::string, PGNParameter>
{

    friend std::ostream& operator<<(std::ostream& out, const PGNParameters& obj);

};

/**
 * @brief PGNParametersMismatchException
 *
 */

concrete class PGNParametersMismatchException extends extras::AbstractCustomException {
public:
    PGNParametersMismatchException(const extras::WhereAmI& whereAmI)
        : AbstractCustomException("Parameters do not match", whereAmI._file.c_str(),
            whereAmI._func.c_str(), whereAmI._line) {}
    static void assertion(const PGNParameters& a, const PGNParameters& b, const extras::WhereAmI& ref);
};


#endif // _PGNPARAMETERS_HPP
