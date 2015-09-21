#kats Makefile
#Copyright Daniel Selmes 2015
#This file is part of King and the Serf (or kats).
#-----------------------------------------------------------------------
#kats is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#kats is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with kats.  If not, see <http://www.gnu.org/licenses/>.
#-----------------------------------------------------------------------

#Compiler Settings
CC = gcc
CFLAGS = -std=c99 -g

#Binary Directory
BIN_DIR = bin

#Build Directory
BUILD_DIR = build

#Sources Directory
SRC_DIR = src

#Main Target
all: $(BIN_DIR)/kats

#Definitions for file groups
OBJECTS = \
$(BUILD_DIR)/kats.o \
$(BUILD_DIR)/cardops.o \
$(BUILD_DIR)/cards.o

$(BIN_DIR)/kats: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/kats $(OBJECTS) 

$(BUILD_DIR)/kats.o: $(SRC_DIR)/kats.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/kats.c -o $(BUILD_DIR)/kats.o

$(BUILD_DIR)/cardops.o: $(SRC_DIR)/cardops.c $(SRC_DIR)/cardops.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cardops.c -o $(BUILD_DIR)/cardops.o

$(BUILD_DIR)/cards.o: $(SRC_DIR)/cards.c $(SRC_DIR)/cards.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cards.c -o $(BUILD_DIR)/cards.o

#Debug Target
debug:
	gdb $(BIN_DIR)/kats

#Cleaning Target
clean:
	rm -fv build/*
	rm -fv bin/*
