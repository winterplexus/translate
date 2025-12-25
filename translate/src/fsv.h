//
//  @(#)fsv.h
//
//  translate utility - field-separated values class
//  ------------------------------------------------
//
//  copyright (c) 2025 Code Construct Systems (CCS)
//
#ifndef __FSV_H
#define __FSV_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class FieldSeparatedValues {
public:
    FieldSeparatedValues(std::ifstream &ifs, std::string field_separator = ",") : ifs(ifs), field_count(0), field_separator(field_separator) {}
    size_t GetTextLine(std::string &);
    std::string GetField(size_t);
    size_t GetFieldCount() const { return (field_count); }
private:
    size_t SplitTextLineIntoFields();
    size_t EndOfTextLine(char);
    size_t GetNextQuotedField(const std::string &, std::string &, size_t);
    size_t GetNextUnquotedField(const std::string &, std::string &, size_t);
private:
    std::ifstream &ifs;
    std::string line;
    std::vector<std::string> field;
    size_t field_count;
    std::string field_separator;
};

#endif // __FSV_H