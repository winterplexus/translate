//
//  @(#)translate.h
//
//  translate utility class
//  -----------------------
//
//  copyright (c) 2025 Code Construct Systems (CCS)
//
#ifndef __TRANSLATE_H
#define __TRANSLATE_H

#include <algorithm>
#include <string>
#include "fs.h"

class Translate {
public:
    Translate() { report_statistics = false; verbose = false; }
    bool ProcessOptions(int, char **);
    bool ProcessFiles(void);
private:
    structured_file_format_t GetConversionFileFormat(char *);
    void DisplayOptionsUsage(void);
    void DisplayInvalidOptionMessage(const std::string &);
    void DisplayInvalidOptionArgumentMessage(const std::string &);
    void DisplayMissingOptionMessage(const std::string &);
    void DisplayErrorMessage(const std::string &);
    void DisplayStatistics(const size_t, const size_t, const size_t);
    void DisplayVersion(void);
private:
    conversion_files_t files;
    bool report_statistics;
    bool verbose;
};

#endif // __TRANSLATE_H