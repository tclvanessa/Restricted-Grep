# Restricted-Grep
Implemented rgrep, which is a restricted grep. The patterns that it matches only support a few regular operators: . (period), + (plus sign), ? (question mark), and \ (backslash). The way rgrep is used is that a pattern is specified on the command line, to which rgrep then reads from its standard input and prints them out on its standard output if the pattern matches the line.
