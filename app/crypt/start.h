# DpdlSimpleCryptApp - a simple sample application module written with Dpdl
#
# (c)opyright 2023
# developed by SEE Solutions
#
# File: app/crypt/start.h
#
# Example: Dpdl startup script for dpdl sample app 'DpdlSimpleCryptApp' that implements AES-128 encryption and decryption of strings of data
#			via Dpdl embedded C code that makes use of the tinycrypt C library
#
# Author: A.Costa
# e-mail: ac@dpdl.io
#
#

println("starting 'DpdlSimpleCryptApp' ...")
println("")

string KEY = "0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c"

string IV = "0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f"

dpdl_stack_var_glob_put("crypt_key", KEY)
dpdl_stack_var_glob_put("iv", IV)

println("testing encryption/decryption of strings of data with AES-128 using the 'tinycrypt' C library...")

println("")

object simple_crypt = loadCode("app/crypt/dpdlSimpleCryptApp.h")

string msg = "This is my message I want to encrypt:)"

println("message to encrypt: " + msg)

println("")

println("encrypting...");

string enc_msg = simple_crypt.encrypt("dpdlSimpleCryptApp", msg)

println("encrypted message: " + enc_msg)

println("##############################################################################")

println("decrypting...")

string dec_msg = simple_crypt.decrypt("dpdlSimpleCryptApp", enc_msg)

println("decrypted message: " + dec_msg)

