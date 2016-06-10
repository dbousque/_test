
import sys
def get_no_real(str):
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
	return res

str = "\nimport sys\ndef get_no_real(str):\n\tres = \"\"\n\tfor elt in str:\n\t\tif elt == \"\\n\":\n\t\t\tres += \"\\\\n\"\n\t\telif elt == \"\\t\":\n\t\t\tres += \"\\\\t\"\n\t\telif elt == \"\\\"\":\n\t\t\tres += \"\\\\\\\"\"\n\t\telif elt == \"\\\\\":\n\t\t\tres += \"\\\\\\\\\"\n\t\telse:\n\t\t\tres += elt\n\treturn res\n\nstr = \"\"\nfich = open(\"Grace_kid.py\", \"w\")\nfich.write(str[:247])\nfich.write(get_no_real(str))\nfich.write(str[247:])\n#comment\nfich.write(\"\\n\")\nfich.close()"
fich = open("Grace_kid.py", "w")
fich.write(str[:247])
fich.write(get_no_real(str))
fich.write(str[247:])
#comment
fich.write("\n")
fich.close()
