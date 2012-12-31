# !/bin/bash

# This is the program name
PROG_NAME=Xylo
# This is the local folder containing the libraries
LD_LIBRARY_PATH=./lib

# Export information about the local folder containing the libraries
export LD_LIBRARY_PATH

# Execute the program
./"$PROG_NAME"

exit 0
