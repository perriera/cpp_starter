#ifndef _CHESSMIND_VERSION_HPP
#define _CHESSMIND_VERSION_HPP

/**
 * @file version.hpp
 * @author Matt Williams (matt@perriera.com)
 * @author Perry Anderson (perry@perriera.com)
 * @brief Adds version support for Cmake script
 * @date 2021-08-08
 */

#define CHESSMIND_VER_MAJOR 0
#define CHESSMIND_VER_MINOR 3
#define CHESSMIND_VER_PATCH 0

#define CHESSMIND_VERSION \
  (CHESSMIND_VER_MAJOR * 10000 + CHESSMIND_VER_MINOR * 100 + CHESSMIND_VER_PATCH)

#endif// _CHESSMIND_VERSION_HPP
