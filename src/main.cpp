#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../ext/json/json.hpp"
#include "colourSpace/ColourSpace.hpp"
#include "colourSpace/OkLCh.h"
#include "colourSpace/sRGB.hpp"
#include "image/Image.h"
#include "maths/Maths.hpp"
#include "misc/Log.h"

using json = nlohmann::json;

const double Maths::Pi = 3.1415926535;
const double Maths::Tau = 6.283185307;
const double Maths::RadToDeg = 180. / Maths::Pi;
const double Maths::DegToRad = Maths::Pi / 180.;

int main() {
  // ----- ENTER CODE HERE -----

  Log::StartLine();
  Log::Write("Hello World!");
  Log::EndLine();

  std::cout << "Press enter to exit...\n";
  std::cin.ignore();

  Log::Save();

  return 0;
}