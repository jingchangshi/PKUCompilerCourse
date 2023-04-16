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
    std::unique_ptr<BaseAST> number;

    void DumpAST(std::ofstream &ofs) const override {
      ofs << "StmtAST {";
      number->DumpAST(ofs);
      ofs << "}";
    }

    void DumpKoopaIR(std::ofstream &ofs) const override {
      std::string indent_space = "  ";
      ofs << indent_space;
      ofs << "ret ";
      number->DumpKoopaIR(ofs);
    }

    void DumpKoopaIR(std::stringstream &ofs) const override {
      std::string indent_space = "  ";
      ofs << indent_space;
      ofs << "ret ";
      number->DumpKoopaIR(ofs);
    }
};

class NumberAST : public BaseAST {
  public:
    std::string int_const;

    void DumpAST(std::ofstream &ofs) const override {
      ofs << "NumberAST {";
      ofs << int_const;
      ofs << "}";
    }

    void DumpKoopaIR(std::ofstream &ofs) const override {
      ofs << int_const << std::endl;
    }

    void DumpKoopaIR(std::stringstream &ofs) const override {
      ofs << int_const << std::endl;
    }
};
