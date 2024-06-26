
# DpdlSimpleCryptApp

![Dpdl](https://www.dpdl.io/images/dpdl-io.png)

				www.dpdl.io



## DpdlSimpleCryptApp - a simple Dpdl application module for AES-128 encryption/decryption of strings of data

**Dpdl source code**:
[app/crypt](https://github.com/Dpdl-io/Dpdl-sample-Apps/tree/main/app/crypt)

This small Dpdl application module implements two functions suitable for AES-128 encryption and decryption of strings of data.

The Dpdl code that iimplements encryption/decryption is this [dpdlSimpleCryptApp.h](https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/app/crypt/dpdlSimpleCryptApp.h)

```python
encrypt(string data) return string enc_data
decrypt(string data) return string dec_deta
```
The routines to encrypt and decrypt the data are implemented within Dpdl using embedded C code with the small footprint cryptographic C library 'TinyCrypt' https://github.com/intel/tinycrypt

The application main entry point 'start.h' loads the Dpdl code 'dpdlSimpleCryptApp.h' as an object to perform encryption/decryption of a test data string.

The 'TinyCrypt' C library used to implement the embedded C encryption/decryption routines <ins>is compiled in memory at runtime</ins> by the Dpdl runtime (very fast compile time, ca. 55 ms to compile and run the encryption/decryption of a string).

The on-the-fly compilation makes the application module completely cross platform without the need to compile any native components.






