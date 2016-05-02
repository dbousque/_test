def print_no_real(str):
	for elt in str:
		if elt == "\n":
			print "\\n"
		elif elt == "\t":
			print "\\t"
		elif elt == "\"":
			print "\\\""
		elif elt == "\\":
			print "\\\\"
		else:
			print elt

str = "def print_no_real(str):\n\tfor elt in str:\n\t\tif elt == \"\\n\":\n\t\t\tstr = \"\""
