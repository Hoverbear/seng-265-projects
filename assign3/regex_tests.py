import re

def test_control_sequences():
    print "Testing Control Sequence Matcher (top 4 should match)"
    
    # Should match control sequences.
    tests = [
        # These should match
        "?fmt 20",          # Good
        "?fmt +20",         # Good
        "?mrgn 20",         # Good
        "?mrgn -20",        # Good
        # These shouldn't match
        "?fmt bad",         # Bad
        "?fmt 20+",         # Bad
        "?mrgn ++2",        # Bad
        "?fmt ++2",         # Bad
        "Not valid",        # Bad
        "?almost valid",    # Bad
    ]

    regex = re.compile(r"(\?mrgn|\?fmt|\?pgwdth) (\-|\+)?(\d+)\s*$")
    for test in tests:
        match = regex.search(test)
        if match:
            print "+ MATCH: " + str(match.groups())
        else:
            print "- MATCH: " + test
          
def test_line_length():
    print "Testing Line Length Matcher (top 2 should match)"
    
    # Should manipulate line lengths.
    tests = [
        "There is a hard linebreak here\n\nEnding here",
        "This is a potato with\ncake.",
        "Awordlongerthenmaxlength",
        "test."
    ]
    
    # Remove all singleton \n symbols
    cut = re.compile('\n{1}(?!\n)', re.MULTILINE)
    # Cut into desired length
    split = re.compile(r".*[\s\n$]", re.MULTILINE)
    for test in tests:
        print "Next test"
        test = cut.sub(' ',test) # Replace singleton \n's with a space.
        match = split.findall(test)
        print match
        if match:
            print '\n'.join(match)
            
def play():
    control = re.compile(r"(\?mrgn|\?fmt|\?pgwdth) (\-|\+)?(\d+)\s*$")
    split = re.compile(r".*[\s\n$]", re.MULTILINE)
    linesplit = re.compile(r"[^\s].{0,32}[^\s]\b[.,"\(\)$]?", re.MULTILINE)
    
          
def main():
    #test_control_sequences()
    #test_line_length()
    play()
  
if __name__ == "__main__":
    main()