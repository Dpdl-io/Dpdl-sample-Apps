# DpdlMQTTApp

![Dpdl](https://www.dpdl.io/images/dpdl-io.png)

				www.dpdl.io

    
##  DpdlMQTTApp - An embedded MQTT server and MQTT client with simple UI

**Dpdl source code**:
[app/dpdlmqttapp/](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/app/dpdlmqttapp/)


### Description

The Dpdl app '**DpdlMQTTApp**' serves as a demonstrator for some of the features provided by Dpdl.

This is a full working prototype of an <ins>embedded **MQTT server**</ins> and an <ins>embedded **MQTT client**</ins> implementation with a simple <ins>**User Interface (UI)**</ins>
that enables to interact with the mqtt protocol thanks to the Mongoose C library.

The sample app implements a full featured MQTT Server that accepts and handles mqtt connections from multiple clients at the following address: **mqtt://127.0.0.1:1883**

An embedded MQTT Client is implemented to publish and receive messages via mqtt registered on given topic.

A simple User Interface (UI) allows to display the received messages and to write new messages to be published via the MQTT server.

Screenshot of simple UI for sending and visualizing messages:

<img src="https://www.dpdl.io/images/platform/examples/dpdlmqttapp/DpdlMQTTApp_screen.png" width="57%" height="57%">

As Dpd allows the embedding of other programming languages, this Dpdl sample app can make use of the powerful 'Mongoose' C library to
implement the mqtt protocol layer components (server/client). The whole C library is compiled at runtime and linked with the ebmedded
Dpdl C code which is than dynamically executed at runtime.

Hence this Dpdl code is portable to all platforms without the need to compile the library.


### Modules

The app consists of 3 modules:

- Embedded **MQTT Server**
- Embedded **MQTT Client** that receives and sends messages via mqtt protocol
- **User Interface (UI)** to display received messages and send new messages

<img src="https://www.dpdl.io/images/platform/examples/dpdlmqttapp/DpdlMQTTApp_desc.png" width="75%" height="75%">
	
The components related to the Mqtt protocol are implemented using the Mongoose embedded library, a very compact and established C library (https://mongoose.ws/)

The main application entry point is the Dpdl module [dpdlmqttapp/start.h](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/app/dpdlmqttapp/start.h) which performs the following:

- creates a UI using the Java JRE swing libraries via the include code [dpdlmqttapp/dpdlMqttUI.h](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/app/dpdlmqttapp/dpdlMqttUI.h)
- creates a dedicated Dpdl thread instance to run the MQTT server code [dpdlmqttapp/dpdlMqttServer.h](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/app/dpdlmqttapp/dpdlMqttServer.h)
- creates a dedicated Dpdl thread isntance to run the MQTT client code [dpdlmqttapp/dpdlMqttClient.h](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/app/dpdlmqttapp/dpdlMqttClient.h)
  The client connection is put on the dpdl stack, so that it can be reused in the 'start.h' module. Messages received are also put on the dpdl stack.
- creates a thread which calls the funciton 'clientMqttPublish(..)' every 5 seconds. The function embeds the C code for publishing
a queue of messages via Mqtt and retrieves and lists the messages received.

By using a third party mqtt client (eg. Mosquitto), you can register to the message topic with the following command:

```
mosquitto_sub -v -h 127.0.0.1 -p 1883 -t 'a/#' -t 'dpdl/+/test'
```


NOTE: This Dpdl app requires a full registered version of 'DpdlEngine lite' to run successfully 












