# DpdlSimpleCryptApp - a simple sample application module written with Dpdl
#
# (c)opyright 2023
# developed by SEE Solutions
#
# File: app/crypt/dpdlSimpleCryptApp.h
#
# Example: Sample Dpdl code 'DpdlSimpleCryptApp' that implements AES-128 encryption and decryption of strings of data
#			via Dpdl embedded C code that makes use of the tinycrypt C library
#
# Author: A.Costa
# e-mail: ac@dpdl.io
#
#

func encrypt(string data)

	dpdl_stack_var_put("data_to_encrypt", data)

	dpdl_stack_push("dpdlstack:tcrypt", "dpdl:applyvars", "dpdlbuf_myresult")

	setStartTime()
	>>c
	#include <tinycrypt/cbc_mode.h>
	#include <tinycrypt/constants.h>
	#include <test_utils.h>

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>

	extern dpdl_stack_buf_put(char *buf);

	const uint8_t key[16] = {
			{{crypt_key}}
	};

	const uint8_t iv[16] = {
			{{iv}}
	};

	char* convert2hexstr(const unsigned char* data, size_t datalen) {
	  size_t final_len = datalen * 2;
	  char* chrs = (unsigned char *) malloc((final_len + 1) * sizeof(*chrs));
	  unsigned int j = 0;
	  for(j = 0; j<datalen; j++) {
	    chrs[2*j] = (data[j]>>4)+48;
	    chrs[2*j+1] = (data[j]&15)+48;
	    if (chrs[2*j]>57) chrs[2*j]+=7;
	    if (chrs[2*j+1]>57) chrs[2*j+1]+=7;
	  }
	  chrs[2*j]='\0';
	  return chrs;
	}

	int test_encrypt(void)
	{
		struct tc_aes_key_sched_struct a;
		uint8_t iv_buffer[16];
		uint8_t encrypted[80];
		uint8_t *p;
		unsigned int length;
		int result = 1;

		(void)tc_aes128_set_encrypt_key(&a, key);

		(void)memcpy(iv_buffer, iv, TC_AES_BLOCK_SIZE);

		const uint8_t plaintext[64] = "{{data_to_encrypt}}";

		printf("Data to encrypt: %s\n", plaintext);
		printf("size: %d\n", sizeof(plaintext));

		printf("performing encryption...\n");

		if (tc_cbc_mode_encrypt(encrypted, sizeof(plaintext) + TC_AES_BLOCK_SIZE,
					plaintext, sizeof(plaintext), iv_buffer, &a) == 0) {
			printf("encryption failed!\n");
			result = -1;
			goto exit_e;
		}

		printf("done\n");

		printf("\n");

		int size = sizeof(encrypted);
	    char *buffer = convert2hexstr(encrypted, size);

	    dpdl_stack_buf_put(buffer);

	exit_e:
		return result;
	}

	int dpdl_main(int argc, char **argv){
		int result = 1;

		printf("----------------------------------------------------------\n");
		printf("encrypting data with aes-128...\n");

		result = test_encrypt();
		if (result == -1) {
			printf("data encryption failed.\n");
		}else{
			printf("data encrypted successfully\n");
		}

		printf("----------------------------------------------------------\n");

		return result;
	}
	<<
	int exec_time = getEndTime()
	println("embedded C code compiled and executed in " + exec_time + " ms")

	int exit_code = dpdl_exit_code()
	println("embedded C exit code: " + exit_code);

	string buf = dpdl_stack_buf_get("dpdlbuf_myresult")

	return buf
end

func decrypt(string data)

	dpdl_stack_var_put("data_to_decrypt", data)

	dpdl_stack_push("dpdlstack:tcrypt", "dpdl:applyvars", "dpdlbuf_myresult")

	setStartTime()
	>>c
	#include <tinycrypt/cbc_mode.h>
	#include <tinycrypt/constants.h>
	#include <test_utils.h>

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>

	extern dpdl_stack_buf_put(char *buf);

	const uint8_t key[16] = {
			{{crypt_key}}
	};

	const uint8_t iv[16] = {
			{{iv}}
	};


	int hexStringToBytes(const char *hexStr, uint8_t *output, unsigned int *outputLen) {
	  size_t len = strlen(hexStr);
	  if (len % 2 != 0) {
	    return -1;
	  }
	  size_t finalLen = len / 2;
	  *outputLen = finalLen;
	  for (size_t inIdx = 0, outIdx = 0; outIdx < finalLen; inIdx += 2, outIdx++) {
	    if ((hexStr[inIdx] - 48) <= 9 && (hexStr[inIdx + 1] - 48) <= 9) {
	      goto convert;
	    } else {
	      if ((hexStr[inIdx] - 65) <= 5 && (hexStr[inIdx + 1] - 65) <= 5) {
	        goto convert;
	      } else {
	        *outputLen = 0;
	        return -1;
	      }
	    }
	  convert:
	    output[outIdx] = (hexStr[inIdx] % 32 + 9) % 25 * 16 + (hexStr[inIdx + 1] % 32 + 9) % 25;
	  }
	  output[finalLen] = '\0';
	  return 0;
	}


	int test_decrypt(void)
	{
		struct tc_aes_key_sched_struct a;
		uint8_t iv_buffer[16];
		uint8_t encrypted[160];
		uint8_t decrypted[64];
		uint8_t *p;
		unsigned int length;
		int result = 1;

		(void)tc_aes128_set_decrypt_key(&a, key);

		(void)memcpy(iv_buffer, iv, TC_AES_BLOCK_SIZE);

		const char *data_in = "{{data_to_decrypt}}";

		printf("decoding hex string...\n");
		unsigned int nr_bytes;
		int status_dec = hexStringToBytes(data_in, encrypted, &nr_bytes);
		printf("status: %d\n", status_dec);
		if(status_dec != 0){
			printf("error: unable to decode hex string\n");
			return -1;
		}

		printf("decoded data:\n");
		int sizen = sizeof(encrypted);
		int cp;
		for(cp = 0; cp < sizen; cp++){
			printf("%u", encrypted[cp]);
		}

		printf("\n");

		p = &encrypted[TC_AES_BLOCK_SIZE];
		length = ((unsigned int) sizeof(encrypted));

		printf("performing decryption...\n");

		if (tc_cbc_mode_decrypt(decrypted, length, p, length, encrypted, &a) == 0) {
			printf("decryption failed!\n");
			result = -1;
			goto exit_d;
		}

		printf("done\n");

	    char buffer[256];
	    sprintf(buffer, "%s", decrypted);

	    printf("\n");

		dpdl_stack_buf_put(buffer);

	exit_d:
		return result;
	}

	int dpdl_main(int argc, char **argv){
		int result = 1;

		printf("----------------------------------------------------------\n");
		printf("decrypting aes-128 data...\n");

		result = test_decrypt();
		if (result == -1) {
			printf("data decryption failed!\n");
			goto exit;
		}

		printf("data decrypted successfully\n");

		printf("----------------------------------------------------------\n");

	exit:
		return result;
	}
	<<
	int exec_time = getEndTime()
	println("embedded C code compiled and executed in " + exec_time + " ms")

	int exit_code = dpdl_exit_code()
	println("embedded C exit code: " + exit_code);

	string buf = dpdl_stack_buf_get("dpdlbuf_myresult")

	return buf
end

# main
println("init dpdlSimpleCryptApp() dpdl module crypt")

dpdl_stack_push("dpdlstack:tcrypt", "dpdl:applyvars", "dpdlbuf_myresult", "dpdl:compile", "dpdl:-I./DpdlLibs/app/crypt/include", "dpdl:-A./DpdlLibs/app/crypt/src")

println("")

return 1
