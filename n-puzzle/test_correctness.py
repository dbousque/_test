

import subprocess

def system_call(command):
	p = subprocess.Popen([command], stdout=subprocess.PIPE, shell=True)
	return p.stdout.read()

def get_puzzle(size):
	out = system_call("python puzzle_gen.py 3")
	out = out.decode('utf-8')
	tiles = out.split("\n")
	solvable = tiles[0]
	solvable = "unsolvable" not in solvable
	tiles = tiles[2:-1]
	return tiles, solvable

def is_solved(tiles):
	fil = open("out", "w")
	fil.write(str(len(tiles)) + "\n")
	for row in tiles:
		fil.write(row + "\n")
	fil.close()
	res = system_call("./n-puzzle out")
	res = res.decode('utf-8')
	res = res.split('\n')
	res = res[-2]
	return "unsolvable" not in res

for i in range(100):
	tiles, solvable = get_puzzle(3)
	if solvable != is_solved(tiles):
		print("not ok !")
	else:
		print("ok")
