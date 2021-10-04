// #include <string>   // std::string
// #include <iostream> // std::cout
// #include <sstream>  // std::stringstream
// #include <fstream>

// #include "catch.hpp"
// #include "extras/string_support.hpp"
// #include "../include/chessmind/fen/FENReader.hpp"
// #include "../include/chessmind/stat/StatWriter.hpp"
// #include "../include/chessmind/stat/StatHeader.hpp"
// #include "../include/chessmind/masking/DataMask.hpp"
// #include "../include/chessmind/masking/StrippedMask.hpp"

// using namespace std;

// SCENARIO("Verify StrippedMask ('kasparov_tal_1980.fen')", "[StrippedMask]")
// {
//     ifstream myfile("data/fen/kasparov_tal_1980.fen");
//     REQUIRE(myfile.good());
//     FENReader parser;
//     myfile >> parser;
//     cout << parser.lines().size() << endl;
//     REQUIRE(parser.lines().size() == 55);

//     StatWriter statWriter;
//     statWriter.convert(parser.lines());

//     DataMask masker;
//     masker.mask(statWriter.lines());

//     ofstream outfile("data/stripped/kasparov_tal_1980.stripped.csv");
//     REQUIRE(outfile.good());
//     StrippedMask strippedData;
//     strippedData.strip(masker.lines());
//     outfile << StatHeader().stripped() << endl;
//     outfile << strippedData;
// }

// SCENARIO("Verify StrippedMask ('KASPAROV.fen')", "[StrippedMask]")
// {
//     ifstream myfile("data/fen/KASPAROV.FEN");
//     REQUIRE(myfile.good());
//     FENReader parser;
//     while (myfile.good())
//         myfile >> parser;
//     cout << parser.lines().size() << endl;
//     REQUIRE(parser.lines().size() == 375814);

//     int sample = parser.lines().size() / 500;
//     FENLineList limitedSet;
//     for (int i = 0; i < sample; i++)
//         limitedSet.push_back(parser.lines()[i]);

//     StatWriter statWriter;
//     statWriter.convert(limitedSet);

//     DataMask masker;
//     masker.mask(statWriter.lines());

//     ofstream outfile("data/stripped/KASPAROV.stripped.05percent.csv");
//     REQUIRE(outfile.good());
//     StrippedMask strippedData;
//     strippedData.strip(masker.lines());
//     outfile << StatHeader().stripped() << endl;
//     outfile << strippedData;
// }
