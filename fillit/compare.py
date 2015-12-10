import os,time

def ft_error(fich, fich2):
	print "hbeaujou :"
	print fich
	print ""
	print "dbousque :"
	print fich2

def go():
	x = 0
	while (True):
		os.system("python gen.py 4 > test5")
		debut = time.time()
		os.system("./a.out test5 > res_hbeaujou")
		print "hbeaujou : " + str(time.time() - debut) 
		debut = time.time()
		os.system("./fillit test5 > res_dbousque")
		print "dbousque : " + str(time.time() - debut) 
		fich = open("res_hbeaujou").read()
		fich2 = open("res_dbousque").read()
		if len(fich) != len(fich2):
			ft_error(fich, fich2)
			break
		for i,c in enumerate(fich):
			if c != fich2[i]:
				ft_error(fich, fich2)
				break
		x+=1
		print x
go()
