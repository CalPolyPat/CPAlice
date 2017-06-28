import glob

mkColfile=open("mkCol.sh","w")
dirfile = open("dirs.txt","r")

mkColfile.write("createCollection EtagCollection")

for line in dirfile:
	dir = line.strip()
	mkColfile.write("addFileToCollection %s EtagCollection\n"%(dir))
mkColfile.close()
