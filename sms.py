import os
from twilio.rest import Client
sid = "SID"
token = "TOKEN"

client = Client(sid, token)

message = client.messages \
                .create(
                     body="Hi Boss,\n I won't be able to make it to work today, as I'm sick.\n Thanks",
                     from_='FROM_NUM',
                     to='TO_NUM'
                 )

print(message.sid)
