#include <fstream>
#include <iostream>// std::cout
#include <sstream>// std::stringstream
#include <string>// std::string

#include "../include/chessmind/game/ChessBoard.hpp"
#include "../include/chessmind/pgn/PGNGame.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify ChessGame can replay a PGN file", "[ChessGame]")
{
  ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  REQUIRE(game.parameters().size() == 12);
  REQUIRE(game.pgnmoves().size() == 32);
}

SCENARIO("Verify ChessGame can replay a PGN file (kasparov_smyslov_1988.pgn)",
  "[PGNGane]")
{
  ifstream myfile("data/pgn/kasparov_smyslov_1988.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;

  cout << game.parameters().size() << endl;
  cout << game.pgnmoves().size() << endl;

  REQUIRE(game.parameters().size() == 12);
  REQUIRE(game.pgnmoves().size() == 20);
}

static string d1 =
"1.e4 {Notes by Stockfish 9 v010218 (minimum 6s/ply)} e5 2.Nf3 Nc6 3.Bb5 "
"a6 4.Ba4 Nf6 5.d4 exd4 6.e5 Ne4 7.O-O Be7 8.Re1 Nc5 9.Bxc6 dxc6 10.Nxd4 "
"O-O 11.Nc3 Ne6 12.Nf5 Bg5 13.Qg4 Nd4 {? 13...g6 14.Ng3 h5 15.Bxg5 Qxg5 "
"16.Qxg5 Nxg5 17.h4 Ne6 = +0.18 (21 ply)} 14.Bxg5 {+/= +1.06 (22 ply)} "
"Bxf5 15.Qg3 {better is 15.Qh4 Qd7 16.Rad1 c5 17.Be7 Bxc2 18.Bxc5 Ne2+ "
"19.Kh1 +/= +0.60 (23 ply)} Qc8 {= -0.09 (21 ply) after 15...Qd7 16.Rad1 "
"c5 17.Rd2 Rae8 18.Ne2 Bg6 19.Be3 Nxe2+ } 16.Rad1 Nxc2 {better is 16...Ne6 "
"17.Rd2 Nxg5 18.Qxg5 h6 19.Qh4 Rd8 20.Red1 Rxd2 = -0.13 (21 ply)} 17.Re2 "
"{= +0.43 (21 ply)} Qe6 18.Bf6 Bg6 19.Bxg7 Kxg7 20.Rxc2 Rad8 21.Rcd2 Qe7 "
"{better is 21...Rxd2 22.Rxd2 h6 23.f4 f6 24.Re2 fxe5 25.Rxe5 Qd6 = +0.18 "
"(19 ply)} 22.h4 {+/= +0.80 (19 ply) after 22.f4 Rxd2 23.Rxd2 Kh8 24.Qe3 "
"h5 25.Ne2 Rd8 26.Rxd8+ } Kh8 23.Qg5 Qxg5 {better is 23...Rde8 24.Qf6+ "
"Qxf6 25.exf6 h5 26.Rd7 b5 27.Re7 Rd8 +/= +0.51 (24 ply)} 24.hxg5 {+/= "
"+1.22 (27 ply)} Rxd2 25.Rxd2 Bf5 26.f4 Kg7 27.Kf2 h5 28.gxh6+ {better is "
"28.Nd1 Kg6 29.Ne3 Be6 30.b3 h4 31.Kf3 b6 32.b4 Ra8 33.Ke4 +/= +1.12 (23 "
"ply)} Kxh6 {+/- +1.70 (25 ply)} 29.Kf3 Rg8 30.Ne4 Bg4+ 31.Ke3 Kg6 {? "
"31...Bf5 32.Nf6 Rg3+ 33.Kf2 Rd3 34.Rxd3 Bxd3 35.g4 Bc4 +/- +1.62 (26 "
"ply)} 32.Nf6 {+- +7.20 (23 ply); 32...Rh8 33.Nxg4 b5 34.Rd7 c5 35.Rxc7 c4 "
"36.Ke4 b4 37.Ne3 +- +6.95 (20 ply)} 1-0 ";
static string d2 =
"1. e4 { Notes by Raymond Keene. } e6 2. d4 d5 3. Nc3 Bb4 4. e5 b6 5. a3 "
"Bf8 {Black has chosen an anti-intuitive system in which he not only "
"postpones the development of his pieces, but also retreats to the back "
"rank the only piece he has so far developed. This is the kind of defence "
"calculated to enrage the classically minded Kasparov. The virtues of "
"Black's system are its solidity and the potential mobility of his "
"queenside pawn mass. } 6. Nf3 Ne7 7. h4 h6 8. h5 {Played to cramp Black's "
"kingside, but Black, following the Nimzowitsch example, has not yet "
"committed himself to castling on either flank. } 8...a5 9. Bb5+ c6 10. "
"Ba4 {An artificial decision. In the further course of play this bishop "
"becomes a target for Black's advancing pawns thus involving White in a "
"serious loss of time and space. It seems more sensible to play 10 Bd3 "
"with the plan of Ne2 and c3. After 10 Bd3 White can meet 10...c5 with 11 "
"Nb5 Nec6 12 dxc5 bxc5 13 c4, exploiting his lead in development. Black's "
"best after 10 Bd3 is doubtless 10...Ba6 when White could try 11 Bf4 Bxd3 "
"12 cxd3 sacrificing pawn structure for dynamic chances in the c-file. } "
"10...Nd7 11. Ne2 b5 12. Bb3 c5 13. c3 Nc6 14. O-O Qc7 {In spite of his "
"lack of development, Black's position is rich in resources. He clearly, "
"for example, possesses the initiative on the queen's flank. Kasparov's "
"next move is a further waste of time. His plan should be to attack "
"Black's position by utilising the White f-pawn as a battering ram. To "
"that end White's most promising course is 15 Nh2 followed immediately by "
"f4 and f5 when White's knights, after due preparation with Be3, can then "
"gallop directly to aggressive squares such as f4 and g4. } 15. Re1 c4 16. "
"Bc2 Nb6 17. Bf4 Be7 18. Bg3 Rb8 19. Nh2 {At last, but the force of the "
"f4-advance has been weakened by White's displacement of his queen's rook. "
"} 19...Qd8 {A mysterious defensive move. The only justification I can see "
"for it is that Black wishes to remove his queen from the potential long "
"term range of White's dark-squared bishop.} 20. Ng4 b4 21. axb4 axb4 22. "
"cxb4 {White could still eliminate all risk by playing 22 b3 at once when "
"22...bxc3 23 Nxc3 Bb4 can be met by 24 Re3. } 22...Nxb4 23. Bb1 Bd7 {The "
"critical moment. White now mistimes his effort to eliminate his one "
"queenside weakness, the b-pawn. By playing instead 24 Qd2 he would "
"maintain the balance of the position. In particular, Black could not then "
"complete his mobilisation with 24...O-O on account of possible sacrifices "
"against the h6-pawn introduced with 25 Bf4. Note, however, that White "
"cannot sacrifice at once with 25 Nxh6+ gxh6 26 Qxh6 on account of "
"26...Nd3. } 24. b3 Ra8 25. Rxa8 Qxa8 26. bxc4 Nxc4 {Black's knights have "
"seized dominating posts. } 27. Nc1 Ba4 {White's pieces are in a terrible "
"tangle and it suddenly transpires that he cannot defend his pawn on d4. } "
"28. Qe2 Qa7 29. Ne3 Qxd4 30. Nxc4 dxc4 31. Qf1 {A counsel of despair. } "
"31...O-O {At long last Black completes his mobilisation. This is one of "
"the later instances of castling in a grandmaster game and with Black's "
"king now in safety, Kasparov decided to resign. White is only a pawn "
"down, but the advance of Black's passed c-pawn will inevitably cost White "
"a piece.} 0-1 ";

string filter(const string& line);
string removeDots(const string& line);

SCENARIO("Verify PGNGame can filter properly", "[PGNGane]")
{
  auto ud1 = filter(d1);
  cout << ud1 << endl;
  ud1 = removeDots(ud1);
  cout << ud1 << endl;
  auto ud2 = filter(d2);
  cout << ud2 << endl;
  ud2 = removeDots(ud2);
  cout << ud2 << endl;
  REQUIRE(d1.find("...") != string::npos);
  REQUIRE(ud1.find("...") == string::npos);
  REQUIRE(d2.find("...") != string::npos);
  REQUIRE(ud2.find("...") == string::npos);
}

SCENARIO("Verify ChessGame can replay a PGN file (kasparov_ivanchuk_1995.pgn)",
  "[PGNGane]")
{
  ifstream myfile("data/pgn/kasparov_ivanchuk_1995.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  REQUIRE(game.parameters().size() == 12);
  REQUIRE(game.pgnmoves().size() == 31);
}

SCENARIO("Verify ChessGame can replay kasparov_muratkuliev_1973",
  "[PGNGane]")
{
  ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  ChessBoard board;
  try {
    board = game.playGameUntil(board, "dxc6");
    REQUIRE(board.symbolAt("d7") == 'P');
    REQUIRE(board.symbolAt("c6") == 'b');
    board.moveBlackSymbol("dxc6");
    cout << board.draw();
    REQUIRE(board.symbolAt("d7") == ' ');
    REQUIRE(board.symbolAt("c6") == 'P');
  }
  catch (std::exception& ex) {
    cout << ex.what() << endl;
  }
}

SCENARIO("Verify ChessGame can replay rafael_sarkisov_kasparov_1974 ('Rfb8')",
  "[PGNGane]")
{
  ifstream myfile("data/pgn/rafael_sarkisov_kasparov_1974.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  ChessBoard board;
  try {
    board = game.playGameUntil(board, "Rfb8");
    REQUIRE(board.symbolAt("f8") == 'R');
    REQUIRE(board.symbolAt("b8") == ' ');
    board.moveBlackSymbol("Rfb8");
    cout << board.draw();
    REQUIRE(board.symbolAt("f8") == ' ');
    REQUIRE(board.symbolAt("b8") == 'R');
  }
  catch (std::exception& ex) {
    cout << ex.what() << endl;
  }
}

SCENARIO("Verify ChessGame can replay rafael_sarkisov_kasparov_1974",
  "[PGNGane]")
{
  ifstream myfile("data/pgn/rafael_sarkisov_kasparov_1974.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  ChessBoard board;
  board = game.playGameEnd(board);
  cout << "thank you" << endl;
}