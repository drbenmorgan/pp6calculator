//! \file   PP6MassCut.hpp
//! \author Tom Latham
//! \brief  Declaration of PP6MassCut concrete class
#ifndef PP6MASSCUT_HPP
#define PP6MASSCUT_HPP

#include <vector>

#include "PP6Cut.hpp"

class Particle;


class MassCut : public Cut {
 public:
  // Enumeration for expressing the types of comparison in the cuts
  enum CutType { LessThan, GreaterThan, Range };

  // Constructors
  MassCut( const double lowerValue, const double upperValue );
  MassCut( const CutType type, const double value );

  virtual ~MassCut()
  {
    std::cout << "MassCut::~MassCut(" << this << ")" << std::endl;
  }

  // Member functions
  virtual bool select(const Particle& input) const;
  virtual std::vector<Particle> select(const std::vector<Particle>& input) const;

 private:
  void checkValidity();

  bool rangeCut(const Particle& input) const;
  bool lessThanCut(const Particle& input) const;
  bool greaterThanCut(const Particle& input) const;

  CutType type_;

  double lowerValue_;
  double upperValue_;
};

#endif // PP6MASSCUT_HPP
