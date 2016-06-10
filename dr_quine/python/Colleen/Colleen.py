
import sys

#first comment

def print_no_real(str):
	res = ""
	for elt in str:
		if elt == "\n":
			res += "\\n"
		elif elt == "\t":
			res += "\\t"
		elif elt == "\"":
			res += "\\\""
		elif elt == "\\":
			res += "\\\\"
		else:
			res += elt
	print res,

str = "\nimport sys\n\n#first comment\n\ndef print_no_real(str):\n\tres = \"\"\n\tfor elt in str:\n\t\tif elt == \"\\n\":\n\t\t\tres += \"\\\\n\"\n\t\telif elt == \"\\t\":\n\t\t\tres += \"\\\\t\"\n\t\telif elt == \"\\\"\":\n\t\t\tres += \"\\\\\\\"\"\n\t\telif elt == \"\\\\\":\n\t\t\tres += \"\\\\\\\\\"\n\t\telse:\n\t\t\tres += elt\n\tprint res,\n\nstr = \"\"\nsys.stdout.write(str[:266])\nprint_no_real(str)\nsys.stdout.write(str[266:])\n#second comment\nsys.stdout.write(\"\\n\")"
sys.stdout.write(str[:266])
print_no_real(str)
sys.stdout.write(str[266:])
#second comment
sys.stdout.write("\n")
