#ifndef _SANINTERFACE_HPP
#define _SANINTERFACE_HPP

#include <iostream>
#include <extras/exceptions.hpp>

/**
 * @brief interface SANInterface
 */

interface SANInterface {
    virtual const std::string& san() const pure;
};

/**
 * @brief interface SANInterface
 */

concrete class SAN implements SANInterface {

    friend std::istream& operator>>(std::istream& in, SAN& obj);
    friend std::ostream& operator<<(std::ostream& out, const SAN& obj);
    friend inline bool operator==(const SAN& a, const std::string& b)
    {
        return a._san == SAN(b);
    }
    friend inline bool operator!=(const SAN& a, const std::string& b)
    {
        return a._san != SAN(b);
    }
    friend inline bool operator==(const SAN& a, const SAN& b)
    {
        return a._san == b._san;
    }
    friend inline bool operator!=(const SAN& a, const SAN& b)
    {
        return !(a == b);
    }

private:
    std::string _san;
public:
    SAN() {};
    SAN(const std::string& san) : _san(san) {};
    virtual const std::string& san() const { return _san; };
    operator std::string() { return _san; }
};


#endif // _SANINTERFACE_HPP
