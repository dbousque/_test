

import sys

fich = open(sys.argv[1]).read()
print "len",len(fich)
str = ""
for car in fich:
	if car == "\n":
		str += "\\n"
	elif car == "\t":
		str += "\\t"
	elif car == "\\":
		str += "\\\\"
	elif car == "\"":
		str += "\\\""
	else:
		str += car
print str
