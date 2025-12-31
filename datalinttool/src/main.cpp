#include <fstream>
#include <iostream>
// #include <csv/reader.h>

int main(int argc, char** argv) {
  // 1. The consuming application is responsible for providing
  // - the manner in which we conclude which name and version number to use from
  // the input file
  // - the manner in which we parse the input file to a dictionary of key value
  // pairs
  // 2. Parse the input file, gathering
  // - name

  // - version number
  // - dictionary of key value pairs
  // 3. Given name and version number, build layout expectation
  // 4. Given layout expectation and dictionary of key value pairs, observe that
  // expected keys are present
  // 5. Given name and version number, build validation rules
  // 6. Given validation rules and dictionary of key value pairs, observe that
  // expected keys have valid values
  // 7. Report results of observations to user
  std::cout << "datalinttool executed successfully.\n";
  return 0;
}
