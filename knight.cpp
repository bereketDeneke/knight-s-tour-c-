#include "knight.h"

Square::Square(int a, int b) : i(a), j(b){
}
int Square::geti() const{
  return i;
}
int Square::getj() const{
  return j;
}
void Square::seti(int a){
  i=a;
}
void Square::setj(int b){
  j=b;
}
bool operator==(const Square &s, const Square &r){
  return (s.geti()==r.geti()) and (s.getj()==r.getj());
}
Square move(Square s, int d){               //  ith move of square r
  int a=s.geti();
  int b=s.getj();
  switch(d){
    case 1: a+=2; b+=1; break;
    case 2: a+=1; b+=2; break;
    case 3: a-=1; b+=2; break;
    case 4: a-=2; b+=1; break;
    case 5: a-=2; b-=1; break;
    case 6: a-=1; b-=2; break;
    case 7: a+=1; b-=2; break;
    case 8: a+=2; b-=1; break;
  }
  return Square(a,b);
}
Square moveBack(Square s, int d){           //  ith move backwards
  int a=s.geti();
  int b=s.getj();
  switch(d){
    case 1: a-=2; b-=1; break;
    case 2: a-=1; b-=2; break;
    case 3: a+=1; b-=2; break;
    case 4: a+=2; b-=1; break;
    case 5: a+=2; b+=1; break;
    case 6: a+=1; b+=2; break;
    case 7: a-=1; b+=2; break;
    case 8: a-=2; b+=1; break;
  }
  return Square(a,b);
}
int Board::getm() const{
  return m;
}
int Board::getn() const{
  return n;
}
bool Board::inRange(const Square &s) const {
  return s.geti()>=0 and s.getj()>=0 and s.geti()<m and s.getj()<n;
}
int Board::get(Square s) const{
  if(!inRange(s))
    throw runtime_error("square out of range");
  return M[s.geti()][s.getj()];
}
void Board::set(Square s, int v){
 if(!inRange(s))
    throw runtime_error("square out of range");
  M[s.geti()][s.getj()]=v;
}
Board::Board(int u, int v){
  m=u; n=v;
  M=new int*[m];
  for (int i=0; i<m;i++){
    M[i]=new int[n];
    for (int j=0; j<n; j++)
      M[i][j]=0;
  }
}  
Board::Board(string filename){
  ifstream infile(filename);
  int x,y;
  if (infile.is_open()){
    infile >> m;
    infile >> n;
    M=new int*[m];
    for (int i=0; i<m;i++){
      M[i]=new int[n];
      for (int j=0; j<n; j++)
        infile >> M[i][j];
    }
    infile.close();
  }
  else
    throw runtime_error("could not open input file");
}
Board::~Board(){
  for(int i=0; i<m; i++)
    delete[] M[i];
  delete[] M;
}
int Board::nEmpty() const{
  int count=0;
  for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
      if (M[i][j]==0)
        count++;
  return count;
}
Square Board::emptySquare() const{
  for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
      if (M[i][j]==0)
        return Square(i,j);
  return Square(-1,-1);
}
ostream& operator<<(ostream & out, const Board & B){
  out << B.getm() << endl;
  out << B.getn() << endl;
  for(int i=0;i<B.getm();i++)
    for(int j=0; j < B.getn(); j++){
      out << setw(2) << B.get(Square(i,j));
      if (j==B.getn()-1)
        out << endl;
      else
        out << " ";
    }
  return out;
}


bool knightTour(Board  & B){
  int length=B.nEmpty();
  ArrayStack<int> S(length);
  Square start=B.emptySquare();   // starting position
  Square pos=start;
  S.push(0);
  B.set(pos,1);
  while(true){
    int d=S.top();
    if(d<8){          // explore sibling node
      S.pop();
      S.push(++d);
      Square s=move(pos,d);
      if(B.inRange(s) and B.get(s)==0){   // checks if move is feasible
        pos=s;
        S.push(0);
        B.set(s,S.size());
        if (S.size()==length){   // check if it is a complete solution
          Square r;
          for(int d=1;d<9;d++){
            r=move(pos,d);
            if(r==start)
              return true;
          }
        }
      }
    }
    else{            //  back track
      S.pop();
      if (S.empty()==true)
      	return false;
      B.set(pos,0);
      pos=moveBack(pos,S.top());
    }
  }
}


