# File: app/crypto/dpdlCreateTransactionETH.h
#
# Example: Dpdl sample app 'DpdlCryptoTransaction' that uses the 'libethc' C library functions via embedded C code execution
#			to create and sign Ethereum (ETH) transactions. The transaction is created ONLY and NOT send to the network.
#
#			The C code has been adapted from the libethc example: https://github.com/mhw0/libethc
#
# Author: A.Costa
# e-mail: ac@dpdl.io
#

# main
println("dpdlCreateTransactionETH()")

println("creating and signing an ETH transaction using the 'libethc' C library...")

string my_private_key = "0xdf, 0x57, 0x08, 0x9f, 0xeb, 0xba, 0xcf, 0x7b, 0xa0, 0xbc, 0x22, 0x7d, 0xaf, 0xbf, 0xfa, 0x9f, 0xc0, 0x8a, 0x93, 0xfd, 0xc6, 0x8e, 0x1e, 0x42, 0x41, 0x1a, 0x14, 0xef, 0xcf, 0x23, 0x65, 0x6e"

dpdl_stack_var_put("private_key", my_private_key)

dpdl_stack_var_put("to_addr", "0x15E5c6533A9b6f516AA66D3B5a6f642f743184C4")
dpdl_stack_var_put("chain_id", "0x7a69")
dpdl_stack_var_put("gas_price", "0x04a817c800")
dpdl_stack_var_put("gas_limit", "0x5208")
dpdl_stack_var_put("transaction_value", "0x0de0b6b3a7640000")

dpdl_stack_push("dpdl:applyvars", "dpdl:compile", "dpdlbuf_myresult", "dpdl:-I./DpdlLibs/app/crypto/include/", "dpdl:-L./DpdlLibs/app/crypto/lib", "dpdl:-lethc")

>>c
#include <stdio.h>
#include "ethc/ecdsa.h"
#include "ethc/rlp.h"
#include "ethc/keccak256.h"

extern void dpdl_stack_buf_put(char *buf);

void assert(int expr){

}

int main(int argc, char **argv){
  printf("creating and signing transaction...\n");

  struct eth_rlp rlp0, rlp1;
  struct eth_ecdsa_signature sign;
  uint8_t privkey[] = {{{private_key}}};

  uint8_t nonce=0x00, zero=0x00, keccak[32], *rlp0bytes, *r, *s;
  char *gasprice = "{{gas_price}}", *gaslimit = "{{gas_limit}}", *value = "{{transaction_value}}";
  char *toaddr = "{{to_addr}}", *txn;
  uint16_t chainid = {{chain_id}}, v;
  size_t rlp0len, rlp1len, siglen=32;

  eth_rlp_init(&rlp0, ETH_RLP_ENCODE);

  eth_rlp_array(&rlp0);                  // [
  eth_rlp_uint8(&rlp0, &nonce);        //   0x00,
  eth_rlp_hex(&rlp0, &gasprice, NULL); //   0x04a817c800,
  eth_rlp_hex(&rlp0, &gaslimit, NULL); //   0x5208,
  eth_rlp_address(&rlp0, &toaddr);     //   0x15E5c6533A9b6f516AA66D3B5a6f642f743184C4,
  eth_rlp_hex(&rlp0, &value, NULL);    //   0x0de0b6b3a7640000,
  eth_rlp_uint8(&rlp0, &zero);         //   0x,
  eth_rlp_uint16(&rlp0, &chainid);     //   0x7a69,
  eth_rlp_uint8(&rlp0, &zero);         //   0x,
  eth_rlp_uint8(&rlp0, &zero);         //   0x,
  eth_rlp_array_end(&rlp0);              // ]

  eth_rlp_to_bytes(&rlp0bytes, &rlp0len, &rlp0);
  eth_rlp_free(&rlp0);

  // compute the keccak hash of the encoded rlp elements
  eth_keccak256(keccak, rlp0bytes, rlp0len);
  free(rlp0bytes);

  // sign the transaction
  eth_ecdsa_sign(&sign, privkey, keccak);

  // calculate v
  v = sign.recid + chainid * 2 + 35;
  r = sign.r;
  s = sign.s;

  eth_rlp_init(&rlp1, ETH_RLP_ENCODE);

  eth_rlp_array(&rlp1);
  eth_rlp_uint8(&rlp1, &nonce);
  eth_rlp_hex(&rlp1, &gasprice, NULL);
  eth_rlp_hex(&rlp1, &gaslimit, NULL);
  eth_rlp_address(&rlp1, &toaddr);
  eth_rlp_hex(&rlp1, &value, NULL);
  eth_rlp_uint8(&rlp1, &zero);
  eth_rlp_uint16(&rlp1, &v);
  eth_rlp_bytes(&rlp1, &r, &siglen);
  eth_rlp_bytes(&rlp1, &s, &siglen);
  eth_rlp_array_end(&rlp1);

  eth_rlp_to_hex(&txn, &rlp1);
  eth_rlp_free(&rlp1);

  char buf[256];
  sprintf(buf, "%s", txn);
  dpdl_stack_buf_put(buf);

  free(txn);

  return 0;
}
<<

int exit_code = dpdl_exit_code()
println("embedded C exit code: " + exit_code);

string buf = dpdl_stack_buf_get("dpdlbuf_myresult")

println("my signed ETH transaction: " + buf)
