// PP6Day5Menu.cpp : Definitions for PP6Day5Menu functions
//
#include "PP6Day5Menu.hpp"

// Standard Library
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>

// This Project
#include "PP6Math.hpp"
#include "PP6Particle.hpp"
#include "PP6ParticleInfo.hpp"
#include "PP6MassCut.hpp"
#include "FileReader.hpp"

bool initialize_database()
{
  // As ParticleInfo is a singleton, we only need to initialize it once
  static bool dbIsUninitialized(true);
  if (dbIsUninitialized) {
    std::string dbtFilename;
    std::cout << "Enter path to .dbt file for initializing ParticleInfo: ";
    dbtFilename = getString();

    // Open the ParticleInfo with supplied file
    const ParticleInfo& dataBase = ParticleInfo::Instance(dbtFilename);

    // Check it has entries
    std::cout << "Checking ParticleInfo contains entries... ";
    if (!dataBase.size()) {
      std::cout << "fail" << std::endl;
      return false;
    } else {
      std::cout << "ok" << std::endl;
      dbIsUninitialized = false;
    }
  }

  return !dbIsUninitialized;
}

std::vector<Particle> pp6day5_read_particles_from_file( const std::string& fileName )
{
  // Variables for reading into
  Particle particle;
  std::vector<Particle> particles;

  // Open the file
  FileReader reader(fileName.c_str());
  if (!reader.isValid()) {
    std::cerr << "[pp6day5_read_particles_from_file:error] "
              << fileName
              << " is not a valid file"
              << std::endl;
    return particles;
  }

  // Read all the particles from the file
  while (reader.nextLine()) {
    particle = reader.getLine<Particle>();
    if (reader.inputFailed()) {
      break;
    }
    particles.push_back( particle );
  }

  return particles;
}

int pp6day5_test_masscut()
{
  if (!initialize_database()) {
    return 1;
  }

  // Create list of particles from user supplied text file
  std::string particleListFile;
  std::cout << "Enter path to .dat file for loading particles: ";
  particleListFile = getString();

  // Read from the file
  std::vector<Particle> allParticles = pp6day5_read_particles_from_file( particleListFile );
  if ( allParticles.empty() ) {
    return 1;
  }

  // Create a cut to select particles with mass greater than 0.4 GeV/c2
  MassCut cut( MassCut::GreaterThan, 0.4 );

  // Apply the cut to the list of particles
  std::vector<Particle> selectedParticles = cut.select( allParticles );

  // Print out the ones that pass
  std::vector<Particle>::const_iterator iter = selectedParticles.begin();
  std::vector<Particle>::const_iterator end = selectedParticles.end();
  for ( ; iter != end; ++iter ) {
    std::cout << (*iter) << std::endl;
  }

  return 0;
}

void pp6day5_menu()
{
  // Declare the variables
  // Variables for i/o
  double resultCode(0);
  char op('\0');

  while (true)
  {
    // Ask the user what they want to do
    std::cout << "PP6Calculator - Day 5 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Enter the operation you would like to perform:" << std::endl;
    std::cout << "1)  Test MassCut with kaons and pions" << std::endl;
    std::cout << "q)  Quit" << std::endl;
    std::cout << ">> ";

    std::cin >> op;

    // check for bad input
    if(!std::cin)
    {
      std::cerr << "[error] Error in input" << std::endl;

      // clear the buffer
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    // Handle menu operation
    if (op == 'q')
    {
      break;
    }
    else if (op == '1')
    {
      resultCode = pp6day5_test_masscut();
    }
    else
    {
      std::cerr << "[error] Operation '" << op << "' not recognised."
                << std::endl;
      continue;
    }

    // Handle any errors
    if (resultCode)
    {
      std::cerr << "[error] Operation '" << op
                << "' returned a non-zero code '" << resultCode
                << "'. Please check parameters."
                << std::endl;
      resultCode = 0;
      continue;
    }
  }
}

