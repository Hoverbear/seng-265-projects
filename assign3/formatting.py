import re

class InvalidOptionException(Exception):
    """
    Thrown when someone puts in ?fmt 34, or ?pgwdth off, or anything else of the such. Note that this does not trigger on anything other then Ints and 'on'/'off', so ?fmt potato will be silently handled as normal input.
    """
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)
        
class WordTooBigException(Exception):
    """
    Thrown when a word is too big to fit on a line and we can't fit it anywhere else.
    """
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

class seng265_formatter:
    def __init__(self, inputlines=["?fmt on", "?pgwdth 30", "Hello there,", "beautiful world", "Here is a sentence with enough words to require some sort of word wrap. "], strict=False):
        """
        Create and start parsing immediately so that it's ready when asked.
        """
        self.opts = { 
            'fmt'     : False,          # Is formatting on or off?
            'pgwdth'  : 0,              # The Maximum width of any given line. May change throughout processing.
            'mrgn'    : 0,              # Desired page margin. Cannot be less then or equal to pgwdth-20
            'strict' : strict           # Defaults to false, determine if we should output errors.
        }
        self.state = {
            'line_size' : 0,            # The size of our current line so far.
            'last_was_new' : False      # Used to detect multiple carriage returns.
        }
        
        self.control_detect = re.compile(r"\?(mrgn|fmt|pgwdth) (\-|\+)?(\d+|on|off)\s*$")
        
        self.inputlines = inputlines    # Map the input to somewhere we can access.
        self.output = []                # We can store out output here.
        self.parse_inputlines()
        
    def parse_inputlines(self):
        """
        Parse out each line and build the output
        """
        for line in self.inputlines:
            result = self.parse(line)
            if result:
                self.output.extend([result])
        
    def parse(self, line):
        """
        Detect a control sequence, if we don't find one, format the line as needed.
        """
        detection = self.control_detect.match(line)
        if detection:
            match = detection.groups()
            # ?fmt uses on|off
            if match[0] == "fmt":
                if match[2] == "on":
                    self.opts['fmt'] = True
                elif match[2] == "off":
                    self.opts['fmt'] = False
                elif self.opts['strict']:
                    print match
                    raise InvalidOptionException("?fmt called with a non on/off value. Line: " + line)
            # Otherwise we'll do operator based settings
            elif match[1] == "+":
                try:
                    self.opts[match[0]] += int(match[2])
                except ValueError:
                    if self.opts['strict']:
                        raise ValueError("Passed an invalid value after the + sign, most specifically, you passed on/off to a non-?fmt sequence. Line: " + line)
            elif match[1] == "-":
                try:
                    self.opts[match[0]] -= int(match[2])
                except ValueError:
                    if self.opts['strict']:
                        raise ValueError("Passed an invalid value after the - sign, most specifically, you passed on/off to a non-?fmt sequence. Line: " + line)
            else:
                try:
                    self.opts[match[0]] = int(match[2])
                except ValueError:
                    if self.opts['strict']:
                        raise ValueError("Passed an invalid value after the control sequence, most specifically, you passed on/off to a non-?fmt sequence. Line: " + line)
            # Verify after each option change that the margins and pgwdths fit spec.
            if match[0] == "pgwdth":
                self.opts["fmt"] = True
            if self.opts['mrgn'] < 0:
                if self.opts['strict']:
                    raise ValueError("The margins were less then 0, this is against spec. Line: " + line + ", Margin: " + str(self.opts['mrgn']) + ", Page Width: " + str(self.opts['pgwdth']))
                self.opts['mrgn'] = 0
            if self.opts['mrgn'] > self.opts['pgwdth'] - 20:
                self.opts['mrgn'] = self.opts['pgwdth'] - 20
                if self.opts['mrgn'] < 0:
                    self.opts['mrgn'] = 0
                if self.opts['strict'] and self.opts['pgwdth'] > 20:
                    raise ValueError("The margins were greater then pgwdth - 20, this is against spec. Line: " + line)

 
            # Since we got a match, we need to get rid of this string.
            line = None
            
        # Output the line
        if self.opts['fmt'] and line:
            # Special case for empty lines.
            split = line.split()
            if split == []:
                self.state['line_size'] = 0
                if self.state['last_was_new']:
                    return '\n'
                else:
                    self.state['last_was_new'] = True
                    return '\n\n'
            self.state['last_was_new'] = False
        
            # Do we need a margin? (Is this a new line?)
            if self.state['line_size'] == 0:
                out = "".join( [" " for i in range(self.opts['mrgn']) ] )
                self.state['line_size'] = self.opts['mrgn']
            else:
                out = ""
            
            # Gradually add each word, making sure we're not going over the pgwdth
            for word in split:
                # Is the word longer then the max line length?
                if self.opts['strict'] and len(word) > self.opts['pgwdth'] - self.opts['mrgn']:
                    raise WordTooBigException("Your word size was too big to fit on a given line. Word: " + word)
                # Do we need a new line?
                if self.state['line_size'] + len(word) >= self.opts['pgwdth']:
                    margin = "".join( [" " for i in range(self.opts['mrgn']) ] )
                    out = out + '\n' + margin
                    self.state['line_size'] = self.opts['mrgn']
                # Otherwise, add a space
                elif self.state['line_size'] != self.opts['mrgn']:
                    self.state['line_size'] += 1
                    out = out + ' '
                # Concatenate
                out = out + word
                self.state['line_size'] += len(word)
            return out
        else:
            return line
        
    
    def get_lines(self):
        """
        Return the result of processing.
        """
        return self.output
        
if __name__ == "__main__":
    formatter = seng265_formatter()
    lines = formatter.get_lines()
    print '\n'.join(lines)