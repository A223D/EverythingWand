import os

if os.path.exists("attribute.txt"):
    print("It exists")
    os.remove("attribute.txt")

f = open("attribute.txt", "w")
f.write("1")
f.close()
