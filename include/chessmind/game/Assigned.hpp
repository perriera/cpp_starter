#ifndef _ASSIGNED_HPP
#define _ASSIGNED_HPP

#include <extras/interfaces.hpp>
#include <iostream>
#include <vector>

//
// AssignedInterface
// Determines if a ChessPosition or ChessMove
// has been assigned.
//

interface AssignedInterface {
  virtual bool assigned() const pure;
};

#endif // _NEXTMOVE_HPP
