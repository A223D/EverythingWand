import os
from twilio.rest import Client
sid = "ACda2dccaedb7ae9ae42e8f57d311e69f7"
token = "3426fcbf3b5ffb4efe04786190c97c3d"

client = Client(sid, token)

message = client.messages \
                .create(
                     body="Hi Boss,\n I won't be able to make it to work today, as I'm sick.\n Thanks",
                     from_='+14375006523',
                     to='+14372345534'
                 )

print(message.sid)
