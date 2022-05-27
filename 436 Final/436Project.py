#print all off txt
with open ('test.txt', 'r') as f:
    for line in f:
        print(line, end='')
#print out each word
with open('GFG.txt', 'r') as file:
    # reading each line
    for line in file:

        # reading each word
        for word in line.split():
            # displaying the words
            print(word)
#edit txt file
my_file = open("data.txt")
string_list = my_file.readlines()

my_file.close()
print(string_list)
string_list[1] = "Edit the list of strings as desired\n"

my_file = open("data.txt", "w")
new_file_contents = "".join(string_list)

my_file.write(new_file_contents)
my_file.close()

readable_file = open("data.txt")
read_file = readable_file.read()
print(read_file)