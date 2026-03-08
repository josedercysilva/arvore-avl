# =========================================================================
# AVL Tree Build Script
#
# This Makefile automates the compilation process for the AVL Tree project.
# It compiles the source files into object files and links them into a
# single executable binary.
# =========================================================================

# --- Compiler Configuration ---
# CC: Specifies the C compiler to use (gcc is standard for Linux/GNU)
CC = gcc

# CFLAGS: Compiler flags for strict error checking and includes
# -Wall -Wextra: Enables all standard and extra warning messages
# -I./include:   Tells the compiler where to find the .h header files
CFLAGS = -Wall -Wextra -I./include

# --- Project Structure ---
# SRC: Lists all the .c source files required for the build
SRC = src/avl_tree.c src/main.c

# OBJ: Dynamically replaces the .c extension with .o for object files
OBJ = $(SRC:.c=.o)

# TARGET: The final executable output path and name
TARGET = build/avl_app

# =========================================================================
# Build Targets
# =========================================================================

# The default target triggered when running `make` with no arguments
all: $(TARGET)

# Rule to link object files and generate the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Rule to clean up the workspace by removing compiled artifacts
# Triggered by running `make clean`
clean:
	rm -f src/*.o $(TARGET)
