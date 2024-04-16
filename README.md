# Dpdl-sample-Apps

![Dpdl](https://www.dpdl.io/images/dpdl-io.png)

				www.dpdl.io
				


This repository contains some sample Apps implemented with Dpdl (Dynamic Packet Definition Language)


## Dpdl sample Apps:

**1) Embedded MQTT server and MQTT client with simple UI**

**2) 3D visualization and animation of chemical molecules**


### 1) Embedded MQTT server and MQTT client with simple UI

Dpdl source code in folder:
./app/dpdlmqttapp/


#### Description

The Dpdl app '**dpdlmqttapp**' serves as a demonstrator for some of the features provided by Dpdl.

This is a full working prototype of a of an embedded MQTT server, an MQTT client implementation with a simple User Interface (UI)
that enables to interact with the mqtt protocol.

The sample app implements a MQTT Server that can accept and handle mqtt connections from multiple clients, an MQTT Client that can publish and receive messages registered on given topic, and a simple User Interface (UI) to display the received messages and to write new messages to be published.

Screenshot of simple UI for sending and visualizing messages:
<img src="https://www.dpdl.io/images/platform/examples/dpdlmqttapp/DpdlMQTTApp_screen.png" width="75%" height="75%">

As Dpd allows the embedding of other programming languages, this Dpdl sample app can make use of the 'Mongoose' C library to
implement the mqtt protocol layer components (server/client). The whole C library is compiled at runtime and linked with the ebmedded
C code which is than dynamically executed at runtime.



#### Modules

The app consists of 3 modules:

- Embedded **MQTT Server**
- Embedded **MQTT Client** that receives and sends messages via mqtt protocol
- **User Interface (UI)** to display received messages and send new messages

<img src="https://www.dpdl.io/images/platform/examples/dpdlmqttapp/DpdlMQTTApp_desc.png" width="75%" height="75%">
	
The components related to the Mqtt protocol are implemented using the Mongoose embedded library, a very compact and established C library (https://mongoose.ws/)

The main application entry point is the Dpdl module '**start.h**' which performs the following:

- creates a UI using the Java JRE swing libraries via the include code '**dpdlMqttGUI.h**'
- creates a dedicated Dpdl thread instance to run the MQTT server code '**dpdlMqttServer.h**'
- creates a dedicated Dpdl thread isntance to run the MQTT client code '**dpdlMqttClient.h**'. The client connection is put on the dpdl stack, so that it can be reused in the 'start.h' module. Messages received are also put on the dpdl stack.
- creates a thread which calls the funciton 'clientMqttPublish(..)' every 5 seconds. The function embeds the C code for publishing
a queue of messages via Mqtt and retrieves and lists the messages received.




















