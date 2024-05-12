# DpdlCryptoTransactionApp

![Dpdl](https://www.dpdl.io/images/dpdl-io.png)

				www.dpdl.io

    
##  DpdlCryptoTransactionApp - A simple Dpdl application to create a sign Ethereum (ETH) transactions

**Dpdl source code**:
[app/dpdlcryptotransactionapp/](https://github.com/Dpdl-io/Dpdl-sample-Apps/tree/main/app/dpdlcryptotransactionapp)


### Description

The Dpdl app 'DpdlCryptoTransactionApp' serves as demonstrator of how Dpdl can be used to implement some applications.

The application make use of the 'libethc' C library to create and sign Ethereum transactions which can than eventually 
be sent to the Ethereum network for processing. The transaction is Only create, but NOT send to the network.

The following parameters can be adjusted in the Dpdl code (in hex format): 

	- private_key 	-> The private key of the wallet where the transaction takes place
	- to_addr 		-> the address where the amount is sent
	- chain_id		-> Chain ID
	- gas_price		-> the Gas price
	- gas_limit		-> the Gas limit allowed
	- transaction_value -> The amount (value) to be sent in the transaction
	

The parameters mentioned above are than compiled and executed in the defined embedded C code section.

The created transaction is pushed on the Dpdl stack and subsequently retrieved and stored in a Dpdl variable and
printed out to the screen. Very simple but effective;)

The 'libethc' lib is not included (only the include files) but you can find the instructions where to download and how to
deploy in the C library in the './lib/README.txt' file

NOTICE: Do not sent transactions to the address specified in the 'to_addr' parameter, EXCEPT if you want to make a donation to Dpdl-io:)



