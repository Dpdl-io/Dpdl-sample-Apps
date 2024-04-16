/*
 * This file is part of DpdlEngine release V1.0
 *
 * (c)opyright 2003 SEE Solutions
 *
 *  https://www.dpdl.io
 *
 *
 */
#ifndef DPDL_D_H
#define DPDL_D_H

#include "uthash.h"

struct dpdl_stack_data {
	int id;
	char name[10];
	void *data;
	int data_len;
	UT_hash_handle hh;
};

extern struct dpdl_stack_data *dpdl_data;

extern void dpdl_stack_data_put(struct dpdl_stack_data *d);

extern struct dpdl_stack_data *dpdl_stack_data_get(int id_data);

#endif
