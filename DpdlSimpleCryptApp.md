
# DpdlSimpleCryptApp

![Dpdl](https://www.dpdl.io/images/dpdl-io.png)

				www.dpdl.io



## DpdlSimpleCryptApp - a simple Dpdl application for encryption/decryption of strings of data

Dpdl application source code:
[app/crypt](https://github.com/Dpdl-io/Dpdl-sample-Apps/tree/main/app/crypt)

This small Dpdl application implements two functions suitable for encryption and decryption of strings of data.

The routines to encrypt and decrypt the data are implemented with Dpdl embedded C code using the small footprint cryptographic library 'TinyCrypt' https://github.com/intel/tinycrypt

The two functions are implemented in the Dpdl code file 'dpdlSimpleCryptApp.h':

**`func encrypt(string data) return res`**
**`func decrypt(string data) return res`**


The application main entry point 'start.h' loads the Dpdl code 'dpdlSimpleCryptApp.h' as an object an performs encryption/decryption of a test data string.







