
import os, sys, random

to_replace1 = "--> [0;36;40mNB MOVES[0;37;40m : [0;31;40m"
to_replace2 = "[0;37;40m"

to_test = int(sys.argv[1])
liste = [str(x) for x in range(to_test)]
random.shuffle(liste)

command = "./a.out " + ' '.join(liste) + " -n > test"
os.system(command)
nb = open("test").read().split("\n")[1].replace(to_replace1, "").replace(to_replace2, "")
print "NOMBRE : " + str(nb)
