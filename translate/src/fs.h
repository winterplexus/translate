//
//  @(#)fs.h
//
//  translate utility - field separator class
//  -----------------------------------------
//
//  copyright (c) 2025 Code Construct Systems (CCS)
//
#ifndef __FS_H
#define __FS_H

#include <string>

typedef enum structured_file_format {
    UNDEFINED_FILE_FORMAT = 0,
    CSV_FILE_FORMAT,
    TSV_FILE_FORMAT,
} structured_file_format_t;

typedef struct conversion_files {
    std::string if_name;
    structured_file_format_t if_format;
    std::string of_name;
    structured_file_format_t of_format;
} conversion_files_t;

class FieldSeparator {
public:
    FieldSeparator(conversion_files_t &files) : files(files) { verbose = false; lines_count = 0; fields_count = 0; fields_per_line_count = 0; }
    void ProcessFiles(bool);
    size_t GetLinesCount() const { return (lines_count); }
    size_t GetFieldsCount() const { return (fields_count); }
    size_t GetFieldsPerLineCount() const { return (fields_per_line_count); }
private:
    std::string GetFieldSeparator(structured_file_format_t);
    void DisplayFileOpenError(const std::string &, const std::string &);
private:
    conversion_files_t files;
    bool verbose = false;
    size_t lines_count;
    size_t fields_count;
    size_t fields_per_line_count;
};

#endif // __FS_H