//
//  @(#)fs.cpp
//
//  translate utility - field separator class
//  -----------------------------------------
//
//  copyright (c) 2025 Code Construct Systems (CCS)
//
#include <fstream>
#include <iostream>
#include <ostream>
#include "fsv.h"
#include "fs.h"
#include "verbose.h"

static void DisplayInsufficientMemoryError(const std::string &, const char *, int);

void FieldSeparator::ProcessFiles(bool verbose) {
    std::ifstream ifs;

    ifs.open(files.if_name.c_str());
    if (!ifs) {
        DisplayFileOpenError("input file", files.if_name);
        return;
    }

    std::ofstream ofs;
    ofs.open(files.of_name.c_str());
    if (!ofs) {
        DisplayFileOpenError("output file", files.of_name);
        return;
    }

    VERBOSE_DISPLAY_FORMATS;

    FieldSeparatedValues *fsv = new(std::nothrow)FieldSeparatedValues(ifs, GetFieldSeparator(files.if_format));
    if (fsv == nullptr) {
        DisplayInsufficientMemoryError("field separated values object", __FILE__, __LINE__);
        return;
    }

    std::string line;

    while (fsv->GetTextLine(line) != 0 || line.size()) {
        lines_count++;
        fields_count += fsv->GetFieldCount();

        VERBOSE_DISPLAY_INPUT_LINE(line);

        for (int i = 0; i < fsv->GetFieldCount(); i++) {
            VERBOSE_DISPLAY_INPUT_FIELD(i);
            if (i + 1 == fsv->GetFieldCount()) {
                ofs << fsv->GetField(i);
            }
            else {
                ofs << fsv->GetField(i) << GetFieldSeparator(files.of_format);
            }
        }

        if (fields_per_line_count < 1) {
            fields_per_line_count = fsv->GetFieldCount();
        }

        VERBOSE_END_OF_LINE;
        ofs << std::endl;
    };

    ofs << std::flush;
    ofs.close();
    ifs.close();

    delete fsv;
}

std::string FieldSeparator::GetFieldSeparator(structured_file_format_t format) {
    switch (format) {
        case CSV_FILE_FORMAT:
             return (",");
        case TSV_FILE_FORMAT:
             return ("\t");
        case UNDEFINED_FILE_FORMAT:
             return (",");
        default:
             return ("");
    }
    return ("");
}

void FieldSeparator::DisplayFileOpenError(const std::string &argument, const std::string &fname) {
    if (fname.length() < 1) {
        std::cerr << "error-> " << argument << " name is missing" << std::endl;
    }
    else {
        std::cerr << "error-> unable to open file: " << fname << std::endl;
    }
}

static void DisplayInsufficientMemoryError(const std::string &object_name, const char *file_name, int line_number) {
    std::cerr << std::endl << "error-> insufficient memory for " << object_name << "(file name: " << file_name << " line number: " << line_number << ")" << std::endl;
}