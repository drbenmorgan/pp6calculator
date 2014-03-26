//! \file   PP6Cut.hpp
//! \author Tom Latham
//! \brief  Declaration of PP6Cut Pure Abstract Class
#ifndef PP6CUT_HPP
#define PP6CUT_HPP

#include <iostream>
#include <vector>

class Particle;

class Cut {
 public:
  // Need a virtual destructor - just for illustration have it print out
  virtual ~Cut()
  {
    std::cout << "Cut::~Cut(" << this << ")" << std::endl;
  }

  virtual bool select(const Particle& input) const = 0;
  virtual std::vector<Particle> select(const std::vector<Particle>& input) const = 0;
};

#endif // PP6CUT_HPP
