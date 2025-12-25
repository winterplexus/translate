//
//  @(#)fsv.cpp
//
//  translate utility - field-separated values class
//  ------------------------------------------------
//
//  copyright (c) 2025 Code Construct Systems (CCS)
//
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "fsv.h"

size_t FieldSeparatedValues::GetTextLine(std::string &str) {
    char c;

    for (line = ""; ifs.get(c) && !EndOfTextLine(c);) {
        line += c;
    }

    SplitTextLineIntoFields();

    str = line;

    return (!ifs.eof());
}

std::string FieldSeparatedValues::GetField(size_t n) {
    if (n < 0 || n >= field_count) {
        return ("");
    }
    else {
        return (field[n]);
    }
}

size_t FieldSeparatedValues::SplitTextLineIntoFields() {
    std::string fld;
    size_t i, j;

    field_count = 0;

    if (line.length() == 0) {
        return (0);
    }

    i = 0;

    do {
        if (i < line.length() && line[i] == '"') {
            j = GetNextQuotedField(line, fld, ++i);
        }
        else {
            j = GetNextUnquotedField(line, fld, i);
        }
        if (field_count >= field.size()) {
            field.push_back(fld);
        }
        else {
            field[field_count] = fld;
        }
        field_count++;
        i = j + 1;
    } while (j < line.length());

    return (field_count);
}

size_t FieldSeparatedValues::EndOfTextLine(char c) {
    size_t eol;

    eol = (c == '\r' || c == '\n');

    if (c == '\r') {
        ifs.get(c);
        if (!(ifs.eof() || c == '\n')) {
            ifs.putback(c);
        }
    }

    return (eol);
}

size_t FieldSeparatedValues::GetNextQuotedField(const std::string &s, std::string &fld, size_t i) {
    size_t j;

    fld = "";

    for (j = i; j < s.length(); j++) {
        if (s[j] == '"' && s[++j] != '"') {
            size_t k = s.find_first_of(field_separator, j);
            if (k > s.length()) {
                k = s.length();
            }
            for (k -= j; k-- > 0;) {
                fld += s[j++];
            }
            break;
        }
        fld += s[j];
    }

    return (j);
}

size_t FieldSeparatedValues::GetNextUnquotedField(const std::string &s, std::string &fld, size_t i) {
    size_t j;

    j = s.find_first_of(field_separator, i);
    if (j > s.length()) {
        j = s.length();
    }

    fld = std::string(s, i, j - i);

    return (j);
}