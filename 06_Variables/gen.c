#include "defs.h"
#include "data.h"
#include "decl.h"

// Generic code generator
// Copyright (c) 2019 Warren Toomey, GPL3

// Given an AST, generate assembly code recursively.
// Return the register id with the tree's final value
int genAST(struct ASTnode *n)
{
  int leftreg, rightreg;

  // Get the left and right sub-tree values
  if (n->left)
    leftreg = genAST(n->left);
  if (n->right)
    rightreg = genAST(n->right);

  switch (n->op)
  {
  case A_ADD:
    return (cgadd(leftreg, rightreg));
  case A_SUBTRACT:
    return (cgsub(leftreg, rightreg));
  case A_MULTIPLY:
    return (cgmul(leftreg, rightreg));
  case A_DIVIDE:
    return (cgdiv(leftreg, rightreg));
  case A_INTLIT:
    return (cgloadint(n->v.intvalue));
  case A_IDENT: //m 表示值存在变量里，需要取出来
    return (cgloadglob(Gsym[n->v.id].name));
  case A_LVIDENT: //m 赋值语句，需要把值存进变量里
    return n->v.id;
  case A_ASSIGN:
    // The work has already been done, return the result
    return (cgstorglob(leftreg, Gsym[rightreg].name));
  default:
    fatald("Unknown AST operator", n->op);
  }
}

void genpreamble()
{
  cgpreamble();
}
void genpostamble()
{
  cgpostamble();
}
void genfreeregs()
{
  freeall_registers();
}
void genprintint(int reg)
{
  cgprintint(reg);
}

void genglobsym(char *s)
{
  cgglobsym(s);
}
