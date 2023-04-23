#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class BaseAST {
  public:
    virtual ~BaseAST() = default;
    virtual void DumpAST(std::ofstream &ofs) const = 0;
    virtual void DumpKoopaIR(std::ofstream &ofs) const = 0;
    virtual void DumpKoopaIR(std::stringstream &ofs) const = 0;
};

class CompUnitAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> func_def;

    void DumpAST(std::ofstream &ofs) const override {
      ofs << "CompUnitAST {";
      func_def->DumpAST(ofs);
      ofs << "}";
    }

    void DumpKoopaIR(std::ofstream &ofs) const override {
      func_def->DumpKoopaIR(ofs);
    }

    void DumpKoopaIR(std::stringstream &ofs) const override {
      func_def->DumpKoopaIR(ofs);
    }

};

class FuncDefAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> func_type;
    std::string ident;
    std::unique_ptr<BaseAST> block;

    void DumpAST(std::ofstream &ofs) const override {
      ofs << "FuncDefAST {";
      func_type->DumpAST(ofs);
      ofs << ", " << ident << ", ";
      block->DumpAST(ofs);
      ofs << "}";
    }

    void DumpKoopaIR(std::ofstream &ofs) const override {
      ofs << "fun ";
      ofs << "@main(): ";
      func_type->DumpKoopaIR(ofs);
      ofs << "{" << std::endl;
      block->DumpKoopaIR(ofs);
      ofs << "}" << std::endl;
    }

    void DumpKoopaIR(std::stringstream &ofs) const override {
      ofs << "fun ";
      ofs << "@main(): ";
      func_type->DumpKoopaIR(ofs);
      ofs << "{" << std::endl;
      block->DumpKoopaIR(ofs);
      ofs << "}" << std::endl;
    }

};

class FuncTypeAST : public BaseAST {
  public:
    std::string int_str;

    void DumpAST(std::ofstream &ofs) const override {
      ofs << "FuncTypeAST {";
      ofs << int_str;
      ofs << "}";
    }

    void DumpKoopaIR(std::ofstream &ofs) const override {
      if (int_str == "int") {
        ofs << "i32 ";
      }
    }

    void DumpKoopaIR(std::stringstream &ofs) const override {
      if (int_str == "int") {
        ofs << "i32 ";
      }
    }
};

class BlockAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> stmt;

    void DumpAST(std::ofstream &ofs) const override {
      ofs << "BlockAST {";
      stmt->DumpAST(ofs);
      ofs << "}";
    }

    void DumpKoopaIR(std::ofstream &ofs) const override {
      ofs << "\%entry:" << std::endl;
      stmt->DumpKoopaIR(ofs);
    }

    void DumpKoopaIR(std::stringstream &ofs) const override {
      ofs << "\%entry:" << std::endl;
      stmt->DumpKoopaIR(ofs);
    }
};

class StmtAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> exp;
    std::string number;

    void DumpAST(std::ofstream &ofs) const override {
      ofs << "StmtAST {";
      if (exp) {
        exp->DumpAST(ofs);
      } else {
        ofs << number;
      }
      ofs << "}";
    }

    void DumpKoopaIR(std::ofstream &ofs) const override {
      std::string indent_space = "  ";
      ofs << indent_space;
      ofs << "ret ";
      // ofs << number << std::endl;
    }

    void DumpKoopaIR(std::stringstream &ofs) const override {
      std::string indent_space = "  ";
      ofs << indent_space;
      ofs << "ret ";
      // ofs << number << std::endl;
    }
};

class ExpAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> unaryexp;

    void DumpAST(std::ofstream &ofs) const override {
      ofs << "ExpAST {";
      unaryexp->DumpAST(ofs);
      ofs << "}";
    }

    void DumpKoopaIR(std::ofstream &ofs) const override {
    }

    void DumpKoopaIR(std::stringstream &ofs) const override {
    }

};

class UnaryExpAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> primaryexp;
    std::unique_ptr<BaseAST> unaryop;
    std::unique_ptr<BaseAST> unaryexp;

    void DumpAST(std::ofstream &ofs) const override {
      ofs << "UnaryExpAST {";
      if (primaryexp) {
        primaryexp->DumpAST(ofs);
      } else {
        unaryop->DumpAST(ofs);
        unaryexp->DumpAST(ofs);
      }
      ofs << "}";
    }

    void DumpKoopaIR(std::ofstream &ofs) const override {
    }

    void DumpKoopaIR(std::stringstream &ofs) const override {
    }

};

class PrimaryExpAST : public BaseAST {
  public:
    std::string number;
    std::unique_ptr<BaseAST> exp;

    void DumpAST(std::ofstream &ofs) const override {
      ofs << "PrimaryExpAST {";
      if (exp) {
        ofs << "(";
        exp->DumpAST(ofs);
        ofs << ")";
      } else {
        ofs << number;
      }
      ofs << "}";
    }

    void DumpKoopaIR(std::ofstream &ofs) const override {
    }

    void DumpKoopaIR(std::stringstream &ofs) const override {
    }

};

class UnaryOpAST : public BaseAST {
  public:
    std::string op;

    void DumpAST(std::ofstream &ofs) const override {
      ofs << "UnaryOpAST {";
      ofs << op;
      ofs << "}";
    }

    void DumpKoopaIR(std::ofstream &ofs) const override {
    }

    void DumpKoopaIR(std::stringstream &ofs) const override {
    }

};

