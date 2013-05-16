#!/usr/bin/python

import sys
from optparse import OptionParser
import fileinput
from formatting import seng265_formatter


def main():
    """
    Creates an instance of the formatter and asks it to process the lines for us.
    """
    # Fun stuff to parse args
    parser = OptionParser()
    parser.add_option("-s", "--strict", action="store_true", default=False,
                      help="Throw exceptions on when encountering bad input.")
    (options, args) = parser.parse_args()
    
    # If we are in verbose we need to ignore the first arg.
    if options.strict is True:
        formatter = seng265_formatter( [line for line in fileinput.input(sys.argv[2:])], strict=True )
    else:
        formatter = seng265_formatter( [line for line in fileinput.input()] )
        
    lines = formatter.get_lines()
    
    if lines != []:
        print "".join(lines),
    else:
        return

if __name__ == "__main__":
    main()
