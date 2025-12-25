################################################################################
#                                                                              #
# makefile.os                                                                  #
#                                                                              #
# translate text file utility                                                  #
#                                                                              #
# version 1.0.0 release 1                                                      #
#                                                                              #
# copyright (c) 2025 Code Construct Systems (CCS) [CONFIDENTIAL]               #
#                                                                              #
################################################################################

# Open Systems OS/OE port

#
# translate text file utility application name
#
TARGET = translate

#
# Application installation location
#
INSTALLATION = ../bin

#
# C++ compiler flags
#
CC = g++
CFLAGS = -c

#
# C++ compiler definitions flags
#
CDEFINITIONS =

#
# C++ compiler debug and optimize flags
#
CDEBUG = -g
COPTIMIZE = -O3

#
# List of object files
#
OBJECTS = \
	translate.o \
	fs.o \
	fsv.o

#
# Rule for default targets
#
all: $(TARGET)

#
# Rule for creating translate text file utility application file
#
$(TARGET): $(OBJECTS)
	@echo "building application: $@"
	@$(CC) $(OBJECTS) -lstdc++ -o $@

#
# Rule for creating object files
#
.cpp.o:
	@echo "building: $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CDEBUG) $(COPTIMIZE) $(CDEFINITIONS) -o $@ $<

#
# Rule for deploying application and other files
#
deploy: $(TARGET)
	cp -f $(TARGET) $(INSTALLATION)
	cp -f $(TARGET).doc $(INSTALLATION)

#
# Rule for cleaning out generated files
#
clean:
	@rm -f *.o
	@rm -f $(TARGET)
