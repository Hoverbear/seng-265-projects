#! /usr/bin/python
import fileinput

# Global opts
opts = { 
    'fmt'     : False,      # Is formatting on or off?
    'pgwdth'  : 0,          # The Maximum width of any given line. May change throughout processing.
    'mrgn'    : 0,          # Desired page margin. Cannot be less then or equal to pgwdth-20
}

state = {
    'line_size' : 0,
    'last_was_new' : False
}

def main ():
    """
    Format according to given control sequences.
    """
    # Define our variables.
    # The currently calculated output.
    output = ""

    # Process each line. If we detect a control sequence on the line, return none. If we detect [], add an extra newline. Otherwise just check for paragraph size and margin. The output will be joined with 'output'
    lines =  [ line for line in fileinput.input() ]
    processed = [ process(line) for line in lines]
    no_empty = [ line for line in processed if line != None ]
    
    if len(no_empty) == 0:
        return
    else:
        output = "".join(no_empty)
        print output,
    
def process (line):
    """ 
    Process the line. Check for control sequences, set any flags required. Format appropriately.
    """
    global opts, state

    split = line.split()
    # Detect control sequences.
    if len(split) is not 0:
        if split[0] == "?fmt":
            if split[1] == "off":
                opts['fmt'] = False
            elif split[1] == "on":
                opts['fmt'] = True
            return None
        elif split[0] == "?pgwdth": # Also turns on fmt
            if isinstance(int(split[1]), int):
                opts['pgwdth'] = int(split[1])
                opts['fmt'] = True
            elif split[1][0] == '-':
                opts['pgwdth'] -= int(split[1][1:])
                opts['fmt'] = True
            elif split[1][0] == '+':
                opts['pgwdth'] += int(split[1][1:])
                opts['fmt'] = True
            return None
        elif split[0] == "?mrgn":
            if split[1][:1] == "-":
                opts['mrgn'] -= int(split[1][1:])
                if opts['mrgn'] < 0:
                    opts['mrgn'] = 0
            elif split[1][:1] == "+":
                opts['mrgn'] += int(split[1][1:])
            else:
                opts['mrgn'] = int(split[1])
            # Restriction on margins.
            if opts['mrgn'] > opts['pgwdth'] - 20:
                opts['mrgn'] = opts['pgwdth'] - 20
            return None
            
    # Output the line
    if opts['fmt']:
        # Special case for empty lines.
        if split == []:
            state['line_size'] = 0
            if state['last_was_new']:
                return '\n'
            else:
                state['last_was_new'] = True
                return '\n\n'
        state['last_was_new'] = False
        
        # Do we need a margin? (Is this a new line?)
        if state['line_size'] == 0:
            out = "".join( [" " for i in range(opts['mrgn']) ] )
            state['line_size'] = opts['mrgn']
        else:
            out = ""
            
        # Gradually add each word, making sure we're not going over the pgwdth
        for word in split:
            # Do we need a new line?
            if state['line_size'] + len(word) >= opts['pgwdth']:
                margin = "".join( [" " for i in range(opts['mrgn']) ] )
                out = out + '\n' + margin
                state['line_size'] = opts['mrgn']
            # Otherwise, add a space
            elif state['line_size'] != opts['mrgn']:
                state['line_size'] += 1
                out = out + ' '
            # Concatenate
            out = out + word
            state['line_size'] += len(word)
        return out
    else:
        return line
    
# Detect if we're running via ./ or if we're called.
if __name__ == "__main__":
    main()