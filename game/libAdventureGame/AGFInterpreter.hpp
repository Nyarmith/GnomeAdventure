#include "../util/common.hpp"



namespace agf{
  enum Tokens { SEMI, EQ,  PEQ,  SEQ,   MEQ, DEQ, OR, AND, GT, GEQ, LT, LEQ,
                ISEQ, NEQ, PLUS, MINUS, MUL, DIV, LPAREN, RPAREN, ID, INT, EOF };

  struct Token
  {
    Tokens type;
    string value;
    Token(Tokens t_, string v_) : type(t_), value(v_) { }
    Token() {}
  }

  class NodeVisitor { string visit(); }
  class Visitable { string accept(NodeVisitor visitor); }


  struct AST
  {
  }

  struct BinOp : AST
  {
  }

  struct UnOp : AST
  {
  }
  
  struct Var : AST
  {
  }

  struct Int : AST
  {
  }

  struct Assign : AST
  {
  }

  struct Compound : AST
  {
  }

  struct AGFLexer
  {
  }

  struct AGFParser
  {
  }

  struct AGFInterpreter
  {
  }
}
