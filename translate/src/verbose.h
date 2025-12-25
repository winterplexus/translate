//
//  @(#)verbose.h
//
//  translate utility - verbose macros
//  ----------------------------------
//
//  copyright (c) 2025 Code Construct Systems (CCS)
//
#ifndef __VERBOSE_H
#define __VERBOSE_H

#define VERBOSE_DISPLAY_FORMATS \
    if (verbose) { \
        std::cout << "input data format: " << files.if_format << " output file data format: " << files.of_format << std::endl << std::endl; \
    }

#define VERBOSE_DISPLAY_INPUT_LINE(line) \
    if (verbose) { \
        std::cout << "line#[" << lines_count << "] = " << line << std::endl; \
    }

#define VERBOSE_DISPLAY_INPUT_FIELD(i) \
    if (verbose) { \
        std::cout << "field[" << i << "] = " << fsv->GetField(i) << " "; \
    }

#define VERBOSE_END_OF_LINE \
    if (verbose) { \
        std::cout << std::endl << std::endl; \
    }

#endif // __VERBOSE_H