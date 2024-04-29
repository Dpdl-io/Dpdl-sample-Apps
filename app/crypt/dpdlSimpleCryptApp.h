# DpdlSimpleCryptApp - a simple sample application written with Dpdl
#
# (c)opyright 2023
# developed by SEE Solutions
#
# File: app/crypt/dpdlSimpleCryptApp.h
#
# Example: Sample Dpdl code 'DpdlSimpleCryptApp' that implements encryption and decryption of strings of data
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

	int test_encrypt(void)
	{
		struct tc_aes_key_sched_struct a;
		uint8_t iv_buffer[16];
		uint8_t encrypted[80];
		uint8_t decrypted[64];
		uint8_t *p;
		unsigned int length;
		int result = 1;

		(void)tc_aes128_set_encrypt_key(&a, key);

		(void)memcpy(iv_buffer, iv, TC_AES_BLOCK_SIZE);

		const uint8_t plaintext[64] = "{{data_to_encrypt}}";

		printf("Data to encrypt: %s\n", plaintext);

		printf("size: %d\n", sizeof(plaintext));

		if (tc_cbc_mode_encrypt(encrypted, sizeof(plaintext) + TC_AES_BLOCK_SIZE,
					plaintext, sizeof(plaintext), iv_buffer, &a) == 0) {
			printf("encryption failed!\n");
			result = -1;
			goto exit_e;
		}

		printf("\n");
		printf("Encrypted data:\n");
		int c;
		for(c = 0; c < 80; c++){
			printf("%u", encrypted[c]);
		}
		printf("\n");

	    char buffer[256];
	    int size =  sizeof(encrypted);
	    for (int i = 0; i < size; i++) {
	         sprintf(buffer + strlen(buffer), "%02x", encrypted[i]);
	    }

	    dpdl_stack_buf_put(buffer);

	exit_e:
		return result;
	}

	int dpdl_main(int argc, char **argv){
		int result = 1;

		printf("----------------------------------------------------------\n");
		printf("encrypting data...\n");

		result = test_encrypt();
		if (result == -1) {
			TC_ERROR("data encryption failed.\n");
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

	int hex2int(char ch)
	{
	    if (ch >= '0' && ch <= '9')
	        return ch - '0';
	    if (ch >= 'A' && ch <= 'F')
	        return ch - 'A' + 10;
	    if (ch >= 'a' && ch <= 'f')
	        return ch - 'a' + 10;
	    return -1;
	}


	int test_decrypt(void)
	{
		struct tc_aes_key_sched_struct a;
		uint8_t iv_buffer[16];
		uint8_t encrypted[80];
		uint8_t decrypted[64];
		uint8_t *p;
		unsigned int length;
		int result = 1;

		(void)tc_aes128_set_encrypt_key(&a, key);

		(void)memcpy(iv_buffer, iv, TC_AES_BLOCK_SIZE);

		char data_in[256] = "{{data_to_decrypt}}";
		char *p_d = data_in;

		printf("Data to decrypt: %s\n", p_d);
		printf("\n");

		int cnt = 0;
		do {
		    uint8_t value = (hex2int(p_d[0]) << 4) + hex2int(p_d[1]);
		    encrypted[cnt] = value;
		    p_d += 2;
		    cnt++;
		} while (*p_d);

		(void)tc_aes128_set_decrypt_key(&a, key);

		p = &encrypted[TC_AES_BLOCK_SIZE];
		length = ((unsigned int) sizeof(encrypted));

		if (tc_cbc_mode_decrypt(decrypted, length, p, length, encrypted, &a) == 0) {
			printf("decryption failed!\n");
			result = -1;
			goto exit_d;
		}

		printf("\n");
		printf("Decrypted data:\n");
		int c;
		for(c = 0; c < 64; c++){
			printf("%u", decrypted[c]);
		}

	    char buffer[256];
	    int size =  sizeof(decrypted);
	    for (int i = 0; i < size; i++) {
	         sprintf(buffer + strlen(buffer), "%02x", decrypted[i]);
	    }
	    printf("\n");

		dpdl_stack_buf_put(buffer);

	exit_d:
		return result;
	}

	int dpdl_main(int argc, char **argv){
		int result = 1;

		printf("----------------------------------------------------------\n");
		printf("decrypting data...\n");

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
	int exit_code = dpdl_exit_code()
	println("embedded C exit code: " + exit_code);

	string buf = dpdl_stack_buf_get("dpdlbuf_myresult")

	return buf
end

# main
println("dpdlSimpleCryptApp()")

dpdl_stack_push("dpdlstack:tcrypt", "dpdl:applyvars", "dpdlbuf_myresult", "dpdl:compile", "dpdl:-I./DpdlLibs/app/crypt/include", "dpdl:-A./DpdlLibs/app/crypt/src")

println("")

return 1
