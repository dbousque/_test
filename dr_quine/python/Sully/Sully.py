
import sys, os
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

st = "\nimport sys, os\ndef get_no_real(str):\n\tres = \"\"\n\tfor elt in str:\n\t\tif elt == \"\\n\":\n\t\t\tres += \"\\\\n\"\n\t\telif elt == \"\\t\":\n\t\t\tres += \"\\\\t\"\n\t\telif elt == \"\\\"\":\n\t\t\tres += \"\\\\\\\"\"\n\t\telif elt == \"\\\\\":\n\t\t\tres += \"\\\\\\\\\"\n\t\telse:\n\t\t\tres += elt\n\treturn res\n\nst = \""
i = 5
if i <= 0:
	exit(0)
if sys.argv[0].endswith("Sully.py"):
	i += 1
fich = open("Sully_" + str(i - 1) + ".py", "w")
fich.write(st)
fich.write(get_no_real(st))
fich.write("\"")
st = "\ni = XXX\nif i <= 0:\n\texit(0)\nif sys.argv[0].endswith(\"Sully.py\"):\n\ti += 1\nfich = open(\"Sully_\" + str(i - 1) + \".py\", \"w\")\nfich.write(st)\nfich.write(get_no_real(st))\nfich.write(\"\\\"\")\nst = \"\"\nfich.write(st[:188].replace(\"XXX\", str(i - 1)))\nfich.write(get_no_real(st))\nfich.write(st[188:])\nfich.close()\nos.system(\"python Sully_\" + str(i - 1) + \".py\")\n"
fich.write(st[:188].replace("XXX", str(i - 1)))
fich.write(get_no_real(st))
fich.write(st[188:])
fich.close()
os.system("python Sully_" + str(i - 1) + ".py")
