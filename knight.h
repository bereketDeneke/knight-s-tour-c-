//  DO NOT MODIFY THIS FILE

#ifndef KNIGHT
#define KNIGHT

#include <iostream>
#include <iomanip>
#include <fstream>
#include "arraystack.h"

using namespace std;

class Square {
public:
  Square(int a=0,int b=0);  // constructor
  int geti() const;     // returns i
  int getj() const;     // returns j
  void seti(int a);     // sets i=a
  void setj(int b);     // sets i=b
private:
  int i;
  int j;
};

bool operator==(const Square &s, const Square &r);
Square move(Square s, int d);               //  dth move of square r
Square moveBack(Square s, int d);           //  dth move backwards

class Board {
public:
  Board(int u, int v);  // creates an empty mxn board (i.e. M[i][j]=0 for all i,j)
  Board(string filename);  // creates board from input file
  ~Board();             // Destructor
  int getm() const;                 // returns m
  int getn() const;                 // returns n
  int get(Square s) const;          // gets M[s.x][s.y]
  void set(Square s,int v);         // sets M[s.x][s.y]=v
  bool inRange(const Square &s) const;       // checks whether s is a square in B
  int nEmpty() const;                  // number of empty squares
  Square emptySquare() const;           // returns an empty square of B
  friend ostream& operator<<(ostream& out, const Board& B);
private:
  int m;        // number of rows
  int n;        // number of columns 
  int** M;      // matrix recording the m*n squares of the board
};

ostream& operator<<(ostream & out, const Board & B);  // prints board B

bool knightTour(Board & B);
  // Returns true if there is a knight tour, and false otherwise.
  // If there is a knight tour, board B is updated and contains
  // this knight tour

#endif

