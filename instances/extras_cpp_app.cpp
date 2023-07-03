/**
 * @file extras_cpp_app.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-21
 *
 * @copyright Copyright (c) 2023, your name (you@domain.com)
 * @ref your url
 *
 */

#include <extras_cpp/game/clazz.hpp>
#include <iostream>

using namespace extras::cpp;

int main(int, const char**) {
   try {
      game::Instance game(1, 2);
      game.moves();
      return 0;
   } catch (const extras::exception& ex) {
      std::cout << ex << std::endl;
   } catch (const std::exception& ex) {
      std::cout << ex.what() << std::endl;
   }
   return -1;
}
