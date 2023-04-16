#pragma once

#include <string>
#include <iostream>
#include <fstream>

class BaseAST {
  public:
    virtual ~BaseAST() = default;
    virtual void Dump(std::ofstream &ofs) const = 0;
};

class CompUnitAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> func_def;

    void Dump(std::ofstream &ofs) const override {
      ofs << "CompUnitAST {";
      func_def->Dump(ofs);
      ofs << "}";
    }
};

class FuncDefAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> func_type;
    std::string ident;
    std::unique_ptr<BaseAST> block;

    void Dump(std::ofstream &ofs) const override {
      ofs << "FuncDefAST {";
      func_type->Dump(ofs);
      ofs << ", " << ident << ", ";
      block->Dump(ofs);
      ofs << "}";
    }
};

class FuncTypeAST : public BaseAST {
  public:
    std::string int_str;

    void Dump(std::ofstream &ofs) const override {
      ofs << "FuncTypeAST {";
      ofs << int_str;
      ofs << "}";
    }
};

class BlockAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> stmt;

    void Dump(std::ofstream &ofs) const override {
      ofs << "BlockAST {";
      stmt->Dump(ofs);
      ofs << "}";
    }
};

class StmtAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> number;

    void Dump(std::ofstream &ofs) const override {
      ofs << "StmtAST {";
      number->Dump(ofs);
      ofs << "}";
    }
};

class NumberAST : public BaseAST {
  public:
    std::string int_const;

    void Dump(std::ofstream &ofs) const override {
      ofs << "NumberAST {";
      ofs << int_const;
      ofs << "}";
    }
};
