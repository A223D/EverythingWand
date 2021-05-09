from time import sleep
import pyrebase
import os
import soco
flag=0

#speaker = soco.discovery.any_soco()
#device = soco.discovery.any_soco()
#speakers = list(soco.discover())
#speaker = speakers[0]
speaker = soco.SoCo('192.168.137.58')
print(speaker)
#print(device)


print("Discovered Sonos")
speaker.get_current_track_info()
config = {
  "apiKey": "MyAUTH",
  "authDomain": "projectId.firebaseapp.com",
  "databaseURL": "https://everythingwand-default-rtdb.firebaseio.com/",
  "storageBucket": "projectId.appspot.com",
}


def stream_handler(message):
    global flag
    global speaker
    if (flag==0):
        flag=1
        print("Ignored first iteration")
        return 6
    print("Command " + str(message['data']))
    if message['data'] == 3:
        print("Netflix request")
        attNum = db.child("Attribute").get().val()
        #print(attNum)
        if os.path.exists("attribute.txt"):
            #print("It exists")
            os.remove("attribute.txt")
            f=open("attribute.txt", "w")
            f.write(str(attNum))
            f.close()
        exec(open("./openNetflix.py").read())
    elif message['data'] == 0:
        print("Text Boss")
        exec(open("./sms.py").read())
    elif message['data'] == 1:
        print("Switch Lights on/off")
    elif message['data'] == 2:
        global speaker
        print("Play/pause music")
        speaker.get_current_transport_info()
        if speaker.get_current_transport_info()['current_transport_state'] == "PLAYING":
            speaker.pause()
        else:
            speaker.play()



firebase = pyrebase.initialize_app(config)

db = firebase.database()
my_stream=db.child("Command").stream(stream_handler)
