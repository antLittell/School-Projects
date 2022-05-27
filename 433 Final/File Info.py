#print all off txt
with open ('test.txt', 'r') as f:
    for line in f:
        print(line, end='')
# rewrite all data in file
f = open("Balance_A.txt", "w")
f.write('words')
f.close()
#file to list
f = open("Balance_A.txt", "r")
lines = f.read().splitlines()
print(lines)

#deletes all in file
f = open("Balance_A.txt", "w")
f.write('')
f.close()

#list to file
with open('Balance_A.txt', 'w') as filehandle:
    for listitem in lines:
        filehandle.write('%s\n' % listitem)