
import sys
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

str = "\nimport sys\ndef print_no_real(str):\n\tres = \"\"\n\tfor elt in str:\n\t\tif elt == \"\\n\":\n\t\t\tres += \"\\\\n\"\n\t\telif elt == \"\\t\":\n\t\t\tres += \"\\\\t\"\n\t\telif elt == \"\\\"\":\n\t\t\tres += \"\\\\\\\"\"\n\t\telif elt == \"\\\\\":\n\t\t\tres += \"\\\\\\\\\"\n\t\telse:\n\t\t\tres += elt\n\tprint res,\n\nstr = \"\"\nsys.stdout.write(str[:249])\nprint_no_real(str)\nsys.stdout.write(str[249:])\nsys.stdout.write(\"\\n\")"
sys.stdout.write(str[:249])
print_no_real(str)
sys.stdout.write(str[249:])
sys.stdout.write("\n")
