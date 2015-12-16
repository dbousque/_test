file = open("dbousque2.bmp","rb")
data = file.read()
data = bytearray(data)
print data[:14]
file.close()
print len(data)

#top left at 144054
#bottom right at 54
#200 x 240
#width 600 octets
end = 144054
res = []
start = 54
while start < end:
	res.append([])
	i = start
	while i < start + 600:
		res[-1].append(data[i] + data[i + 1] + data[i + 2] - 10)
		i += 3
	start += 600
with open('res3.fdf', 'w') as f:
	for elt in reversed(res):
		for elt2 in reversed(elt):
			f.write(str(elt2) + " ")
		f.write("\n")
#with open('eggs.bmp', 'wb') as f:
#	f.write(data)
