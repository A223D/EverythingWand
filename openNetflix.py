import webbrowser

f = open("attribute.txt", "rt")
attribute = f.read()
f.close()

f = open("links.txt")

for i in range(0, int(attribute)):
    fullLine = f.readline()
f.close()

#print(fullLine)
fullLine = fullLine[3:]
#print(fullLine.split("!"))

url = fullLine.split("!")[0]
name = fullLine.split("!")[1][:-1]

print("Opening "+name)

webbrowser.open(url)
