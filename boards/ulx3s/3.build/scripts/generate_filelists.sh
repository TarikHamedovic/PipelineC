#!/bin/bash

# Default base directory
DEFAULT_BASE_DIR="/home/user"

# Use the provided base directory or default to /home/user
BASE_DIR=${1:-$DEFAULT_BASE_DIR}

# Get the directory where the script is located
SCRIPT_DIR=$(dirname "$(realpath "$0")")

# Define the output directory as the "filelists" folder inside 1.hw
OUTPUT_DIR="$SCRIPT_DIR/../../1.hw/filelists"

# Define the path for Verilog files
VERILOG_DIR="$SCRIPT_DIR/../../1.hw"

# Ensure the output directory exists
mkdir -p "$OUTPUT_DIR"

# Find all .v files in the VERILOG_DIR and its subdirectories and convert to absolute paths
VERILOG_FILES=$(find "$VERILOG_DIR" -type f -name "*.v" -exec realpath {} \;)

# Generate rtl_verilog.filelist in the filelists directory
FILELIST="$OUTPUT_DIR/rtl_verilog.filelist"

# Write absolute file paths to the file list
echo "$VERILOG_FILES" > "$FILELIST"

echo "Generated $FILELIST"

