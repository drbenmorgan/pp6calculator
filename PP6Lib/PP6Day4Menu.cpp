// PP6Day4Menu.cpp : Definitions for PP6Day4Menu functions
//
#include "PP6Day4Menu.hpp"

// Standard Library
#include <iostream>

// Third party
#include "FileReader.hpp"

// This Project
#include "PP6Math.hpp"

//! Operation to read/display the PDG database read in from a .dbt file
int pp6day4_io_pdg() {
  std::string dbtFilename;
  std::cout << "Enter path to .dbt file to be read: ";
  dbtFilename = getString();

  // Open the FileReader with supplied file
  FileReader dataBase(dbtFilename);

  if (!dataBase.isValid()) {
    std::cerr << "[pp6day4_io_pdg:error] "
              << dbtFilename
              << " is not a valid file"
              << std::endl;
    return 1;
  } else {
    // Create variables to read data into
    std::string particleName("");
    int particlePdgCode(0);
    int particleCharge(0);
    double particleMass(0.0);

    // Read and display data
    while (dataBase.nextLine()) {
      particleName = dataBase.getField<std::string>(1);
      if (dataBase.inputFailed()) {
        std::cout << "Could not get field 1 as std::string" << std::endl;
        continue;
      }

      particlePdgCode = dataBase.getField<int>(2);
      if (dataBase.inputFailed()) {
        std::cout << "Could not get field 2 as int" << std::endl;
        continue;
      }
      particleCharge = dataBase.getField<int>(3);
      if (dataBase.inputFailed()) {
        std::cout << "Could not get field 3 as int" << std::endl;
        continue;
      }

      particleMass = dataBase.getField<double>(4);
      if (dataBase.inputFailed()) {
        std::cout << "Could not get field 4 as double" << std::endl;
        continue;
      }

      std::cout << particleName << " "
                << particlePdgCode << " "
                << particleCharge << " "
                << particleMass
                << std::endl;
    }
  }

  return 0;
}


void pp6day4_menu() {
  // Declare the variables
  // Variables for i/o
  double resultCode(0); 
  char op('\0');

  while (true)
  {
    // Ask the user what they want to do
    std::cout << "PP6Calculator - Day 4 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Enter the operation you would like to perform:" << std::endl;
    std::cout << "1)  Read and display the PDG Textfile Database" << std::endl;
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
      resultCode = pp6day4_io_pdg();
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

