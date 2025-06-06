# Dpdl-sample-Apps

![Dpdl](https://www.dpdl.io/images/dpdl-io.png)

				www.dpdl.io
				


This repository contains some sample applications implemented with: **`Dpdl`** **(Dynamic Packet Definition Language)**

https://github.com/Dpdl-io/DpdlEngine

The purpose of the small applications listed here is to serve as demonstrators to show some features and language constructs of Dpdl as well as to
prove the compliace to the techologies supported.

Therefore the apps listed here are considered to be small prototype applications written with Dpdl.


## Dpdl sample Apps:

## 3D visualization and animation of chemical molecules

[Dpdl3DMolecules](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/Dpdl3DMolecules.md)

<img src="https://www.dpdl.io/images/platform/examples/Dpdl_3D_Example2_with_JavaFX.png" width="70%" height="70%">

[VIDEO of Dpdl3DMolecule app in action](https://youtu.be/82SRI_L3vLc)


## DpdlSHA-1 - implementation of SHA-1 hash algorithm

SHA-1 hash algorithm implementation entirely written in Dpdl

[DpdlSHA-1](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/dpdlSHA-1.md)


## DpdlWebsBrowseApp - an embedded Web-server with a web-browser UI

[DpdlWebsBrowseApp](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/DpdlWebsBrowseApp.md)

<img src="https://www.dpdl.io/images/platform/examples/dpdlwebsbrowseapp/DpdlWebsBrowseApp_screen2.png" width="70%" height="70%">

[VIDEO of DpdlWebsBrowserApp in action](https://youtu.be/qP-F1kF_-_c)

## DpdlMQTTApp - an embedded MQTT server and MQTT client with simple UI

[DpdlMQTTApp](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/DpdlMQTTApp.md)

<img src="https://www.dpdl.io/images/platform/examples/dpdlmqttapp/DpdlMQTTApp_screen.png" width="55%" height="55%">

## DpdlSimpleCryptApp - a simple application module for AES-128 encryption/decryption of strings of data

This Dpdl application module provides two basic functions for encryption/decryption of strings of data with AES-128 using the open source 'TinyCrypt' C library from Intel

[DpdlSimpleCryptApp](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/DpdlSimpleCryptApp.md)

## DpdlCodeGenAI - generating and executing AI generative code (example: a simple console SNAKE Game)

A simple console SNAME Game automatically AI generated using the Dpdl language plugin 'DpdlAINerd' which is than executed right away on the 'DpdlEngine'

[DpdlCodeGenAI](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/DpdlCodeGenAI.md)

<img src="https://www.dpdl.io/images/platform/examples/dpdlcodegenai/dpdlcodegenai_game_snake.png" width="65%" height="65%">

## DpdlCryptoTransactionApp - a simple application to create and sign Ethereum (ETH) transactions

Simple Dpdl sample application that used the 'libethc' C library to create and sign transaction that can than be sumitted to the network

<img src="https://www.dpdl.io/images/platform/examples/dpdlcryptotransactionapp/eth_logo.png" width="20%" height="20%">

[DpdlCryptoTransactionApp](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/DpdlCryptoTransactionApp.md)

## DpdlWeb3DApp - a 3D visualization in the web browser

Dpdl sample application that creates a 3D visualization in the web browser with WebGL

[DpdlWeb3DApp](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/DpdlWeb3DApp.md)

<img src="https://www.dpdl.io/images/platform/examples/dpdlweb3dapp/DpdlWeb3DApp_screen.png" width="70%" height="70%">

[VIDEO of DpdlWeb3DApp in action](https://youtu.be/kdXKmScT3ZI)

## DpdlSoundAudioApp - a sample Dpdl application to emit sound audio waves via various audio backends available

Dpdl sample application that emits audio waves via various audio backends implemented with embedded C code using the cross-platform 'libsoundio' C library

[DpdlSoundAudioApp](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/DpdlSoundAudioApp.md)

## DpdlCelsiusConverterApp - a simple Celsius to Fahrenheit converter app with UI

Dpdl sample application that creates a simple UI to convert degree values from Celsius to Fahrenheit. The app makes use of embedded 'Clojure' code

[DpdlCelsiusConverterApp](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/DpdlCelsiusConverterApp.md)

<img src="https://www.dpdl.io/images/platform/examples/Dpdl_example_Celsius_Fahrenheit_UI.png" width="40%" height="40%">

## DpdlTrainLLM - a compact lightweight method for training and reproducing the GPT-2 model mini series

Performs LLM training in 40 steps to generate a GTP-2 model (124 Mb) from a data source that consists of 'tinystories' and 'tinyshakespeare' which are avaialbe as already tokenized datasets.

[DpdlTrainLLM](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/DpdlTrainLLM.md)

## DpdlLLMInference - sample console app that performs inference on Llama-2 LLM models via embedded C code

Dpdl sample console application that allows to input a prompt about a story to be written, it will than generate by inference
on a LLM model Llama-2 a simple story based on the content provided in the input prompt

[DpdlLLMInference](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/DpdlLLMInference.md)


---
----------------------------------------------------------------------------------------------------

## here some <ins>OLD</ins> projects developed using Dpdl

## Dynamic Skiing Location System (DSLS) - developed in year 2006

This mobile phone application have been developed by SEE Solutions in 2006, and was the sucessor of an earlier prototype application named MSLS (Mobile Skiiing Location System) developed in 2003.

The DSLS mobile application is a J2ME compiant navigation system for skiers that used Bluetooth(tm) technology to derive the skier's location, either via bluetooth gateways positioned at the lifts, or via and external bluetooth GPS receiver.

<ins>Dpdl existed already as a lightweight embedded scripting language</ins> and has been used in the project to handle blueooth connections, data and to perform dynamic drawings of the map canvas. <ins>The bluetooth client and server (gateway) and all data handling was entirely developed with Dpdl</ins>.

(DSLS running on old Nokia 6600 mobile phone CDLC 2.0)
<img src="http://www.seesolutions.it/images/products/DSLS.png" width="70%" height="70%">

More info about DSLS can be found here: [Dynamic Skiing Location System DSLS.pdf](http://www.seesolutions.it/documents/Dynamic%20Skiing%20Location%20System%20DSLS.pdf)












