## Inspiration
The theme of this hackathon really had us racking our brains to figure out what we should build. Just like magic, we did not want to limit our project to some specific domain. Hence, we decided to create a magic wand that does everything, from ordering food to calling in sick to work. 

## What it does
EverythingWand is  a device that was built to do **everything**. As a demonstration of everything, we have programmed 4 functions into the wand. 
* Twirl the wand to text you're boss that you're sick and can't come into work today.
 * Twirling action is sensed by the accelerometer at the tip of the wand. 
 * SMS is sent using the Twilio API running on a Linode cloud computer
* Press a button on the wand to play or pause a WiFi speaker.
 * Updates a variable in the Firebase database which is sensed by a local python script to send a play/pause command over the network. 
* Press a button to order Domino's Pizza
  * Upto 3 pre-configured orders selected by subsequent button presses.
  * Uses the pizzapi API to place a real Domino's Pizza order
* Press a button open to open Netflix on computer
  * Three programmable shows selected by pressing subsequent buttons.
  * Updates a variable in the Firebase database which is sensed by a local python script to open the web-browser to the link of the show/movie. 

## How we built it

### 1. Hardware
Here is a look at the wand hardware:
![Wand labelled](https://challengepost-s3-challengepost.netdna-ssl.com/photos/production/software_photos/001/506/051/datas/original.png)
Hardware components and purpose:
1. ESP32
  * Connects to WiFi and sends signals to the Firebase real time database holding the following data fields:
     * Command: tells the receiver scripts what to do(Netflix, Pizza, SMS text, speaker control)
     * Attribute: Holds options for the commands(which Netflix show/movie, which pizza order)
![Firebase](https://challengepost-s3-challengepost.netdna-ssl.com/photos/production/software_photos/001/506/100/datas/original.png)
2. Buttons
  * Selects Netflix, pizza, and speaker control commands
  * Selects options for pizza and Netflix
3. Accelerometer
  * Senses twirling motion of wand. Sends data to ESP32 using I2C.
4. Power bank
   * Provides power to wand circuity
5. Wand
  * Gives wand shape and structure to the device.

### 2. Cloud Software
Using the Linode credit from MLH, we were able to provision a cloud computer to handle ordering the pizza and texting. This cloud computer is running a python script which is continuously listening to the "command" data field in Firebase. Here is the working for those two functions. 
* Ordering pizza **(activated when Command field is 1)**
  * Uses the pizzapi python module. This library helps us create Domino's Pizza orders and place them online using the requests python module as a dependency.
  * Since we have 3 available buttons, we programmed three separate orders into the cloud computer. Pressing any subsequent button after the pizza button will place a different order. 
  * Reads the "Attribute" field in Firebase to determine which order to place.
* Texting the boss **(activated when Command field is 0)**
  * Using Twilio, we are able to text any number. 
  * For this purpose, we are texting "Hi Boss, I won't be able to make it to work today, as I'm sick. Thanks" to our personal number to demonstrate this capability. 

### 3. Local Software
Since opening Netflix and controlling our speaker is a local task, we have a local python script running listening to the Firebase "Command" data field as well, just like the cloud script. It controls the Netflix capability and speaker. Here is how that works:
* Netflix **(activated when Command field is 3)**
  * Any 3 movies or shows or shows can be programmed into the "links.txt" file [(See GitHub)](https://github.com/A223D/EverythingWand) . Which movie is selected is based what button is pressed after the Netflix button(Netflix button updates "Command" field and subsequent button updates "Attribute" field.
  * The local python script checks the "Attribute" field in Firebase to determine which movie to open after it senses that "Command" is equal to 3(which means that the wand user selected Netflix)
  * It uses the webbrowser python module to open a direct Netflix link to the requested show and it starts playing. 
* WiFi Speaker Control **(activated then Command field is 2)**
  * The local Python script is able to send play and pause commands using the soco python module.
     * If the speaker is currently playing, a pause command is sent over the network.
     * If the speaker is currently paused, a play command is sent over the network. 

## Challenges we ran into
* The pizzapi API is unofficial and it only supported USA by default. Since our team is based in Canada, it took some figuring out to make it work in Canada as well. 
* We didn't want to input our credit card details into the API. Hence, it took some more analysis and experimenting to figure out how to place a Cash on Delivery order. 
* None of us had used Linode before. Thus we had to read up on some documenting to provision our machine and get everything installed and running. 
* It was also our first time using Twilio. However, we were able to get it working quickly. 

## Accomplishments that we're proud of
* Ordering food using hardware was an accomplishment we were especially proud of. **Proof:**
![Bill](https://challengepost-s3-challengepost.netdna-ssl.com/photos/production/software_photos/001/506/161/datas/original.png)


* Shifting 50% of our services on the cloud. Using Linode, we were able to shift our pizza order and sms text service to the cloud. It was an amazing feeling seeing our project work without any of the code running on our own computers. 
* Using an ESP32 to do so many tasks.

## What we learned
* How to provision a machine in the cloud using Linode.
  * Using SSH to use and configure our cloud machine.
* How Firebase data streaming works on a hardware level. 
* Using Twilio to text phone numbers

## What's next for EverythingWand
* Adding more food delivery services. 
* Adding the ability to customize texts and recipients.
* Adding more button and functions to the wand(such as the ability to switch on and off home lights)
