//
//  @(#)translate.cpp
//
//  translate utility class
//  -----------------------
//
//  copyright (c) 2025 Code Construct Systems (CCS)
//
#include <exception>
#include <iostream>
#include <string>
#include <string.h>
#include "fs.h"
#include "translate.h"
#include "version.h"

static void DisplayInsufficientMemoryError(const std::string &, const char *, int);

int main(int argc, char **argv) {
    int rc = EXIT_FAILURE;

    Translate *translate = new(std::nothrow)Translate();
    if (translate == nullptr) {
        DisplayInsufficientMemoryError("translate utility object", __FILE__, __LINE__);
        return (rc);
    }

    if (translate->ProcessOptions(argc, argv)) {
        if (translate->ProcessFiles()) {
            rc = EXIT_SUCCESS;
        }
    }

    delete translate;

    return (rc);
}

bool Translate::ProcessOptions(int argc, char **argv) {
    if (argc == 1) {
        DisplayOptionsUsage();
        return (false);
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (!argv[++i]) {
                DisplayInvalidOptionArgumentMessage("input file name");
                return (false);
            }
            files.if_name = argv[i];
        }
        else if (strcmp(argv[i], "-j") == 0) {
            if (!argv[++i]) {
                DisplayInvalidOptionArgumentMessage("input data format");
                return (false);
            }
            files.if_format = GetConversionFileFormat(argv[i]);
        }
        else if (strcmp(argv[i], "-o") == 0) {
            if (!argv[++i]) {
                DisplayInvalidOptionArgumentMessage("output file name");
                return (false);
            }
            files.of_name = argv[i];
        }
        else if (strcmp(argv[i], "-p") == 0) {
            if (!argv[++i]) {
                DisplayInvalidOptionArgumentMessage("output data format");
                return (false);
            }
            files.of_format = GetConversionFileFormat(argv[i]);
        }
        else if (strcmp(argv[i], "-r") == 0) {
            report_statistics = true;
        }
        else if (strcmp(argv[i], "-v") == 0) {
            DisplayVersion();
        }
        else if (strcmp(argv[i], "-x") == 0) {
            verbose = true;
        }
        else if (strcmp(argv[i], "-?") == 0) {
            DisplayOptionsUsage();
            return (false);
        }
        else {
            DisplayInvalidOptionMessage(std::string(argv[i]));
        }
    }

    if (files.if_name.size() < 1) {
        DisplayMissingOptionMessage("input file name");
        return (false);
    }
    if (files.of_name.size() < 1) {
        DisplayMissingOptionMessage("output file name");
        return (false);
    }

    return (true);
}

bool Translate::ProcessFiles() {
    bool status = false;

    FieldSeparator *separator = new(std::nothrow)FieldSeparator(files);
    if (separator == nullptr) {
        DisplayInsufficientMemoryError("field separator object", __FILE__, __LINE__);
        return (status);
    }

    try {
        separator->ProcessFiles(verbose);

        if (report_statistics) {
            DisplayStatistics(separator->GetLinesCount(), separator->GetFieldsCount(), separator->GetFieldsPerLineCount());
        }

        status = true;
    }
    catch (std::exception &e) {
        DisplayErrorMessage(std::string(e.what()));
    }

    delete separator;

    return (status);
}

structured_file_format_t Translate::GetConversionFileFormat(char *argument) {
    structured_file_format_t format = UNDEFINED_FILE_FORMAT;

    if (strcmp(argument, "csv") == 0) {
        format = CSV_FILE_FORMAT;
    }
    else if (strcmp(argument, "tsv") == 0) {
        format = TSV_FILE_FORMAT;
    }
    else {
        DisplayInvalidOptionMessage("expected either csv or tsv");
    }

    return (format);
}

void Translate::DisplayOptionsUsage(void) {
    std::cout << "usage: " << VersionProduct << " (options)" << std::endl << std::endl;
    std::cout << "options: -i <input file name>" << std::endl;
    std::cout << "         -j <input data format: csv|tsv>" << std::endl;
    std::cout << "         -o <output file name>" << std::endl;
    std::cout << "         -p <output data format: csv|tsv>" << std::endl;
    std::cout << "         -r report statistics" << std::endl;
    std::cout << "         -v display version" << std::endl;
    std::cout << "         -x verbose mode" << std::endl;
    std::cout << "         -? print this usage" << std::endl;
}

void Translate::DisplayInvalidOptionMessage(const std::string &option) {
    std::cerr << std::endl << "error-> invalid option: " << option << std::endl;
}

void Translate::DisplayInvalidOptionArgumentMessage(const std::string &argument) {
    std::cerr << std::endl << "error-> missing option value or invalid option argument: " << argument << std::endl;
}

void Translate::DisplayMissingOptionMessage(const std::string &message) {
    std::cerr << std::endl << "error-> " << message << " option is missing" << std::endl;
}

void Translate::DisplayErrorMessage(const std::string &message) {
    std::cerr << "error-> " << message << std::endl;
}

void Translate::DisplayStatistics(const size_t lines_count, const size_t fields_count, const size_t fields_per_line_count) {
    std::cout << "statistics" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "lines count           : " << lines_count << std::endl;
    std::cout << "fields count          : " << fields_count << std::endl;
    std::cout << "fields per line count : " << fields_per_line_count << std::endl << std::endl;
}

void Translate::DisplayVersion(void) {
    std::cout << VersionProduct << " - translate text file utility" << std::endl;
    std::cout << VersionRelease << std::endl << std::endl;
}

static void DisplayInsufficientMemoryError(const std::string &object_name, const char *file_name, int line_number) {
    std::cerr << std::endl << "error-> insufficient memory for " << object_name << "(file name: " << file_name << " line number: " << line_number << ")" << std::endl;
}