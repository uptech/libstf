/*
 * Copyright 2008 Andrew De Ponte.
 *
 * This file is part of lib_stf.
 *
 * lib_stf is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or any
 * later version.
 * 
 * lib_stf is distributed in the hopes that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with lib_stf; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#include <stdio.h>

// Include the Spartan Test Framework header file.
#include <stf/stf.h>

// Declare a structure to represent shared data.
struct sdata {
    int shared_val;
};

// Prototype of function we want to test.
int inc_int(int *p_offset);

// Prototype's for the unit test functions.
void test_inc_int_with_local_int(void *p_data);
void test_inc_int_with_shared_int(void *p_data);
void test_inc_int_with_null(void *p_data);

int main(int argc, char *argv[]) {
    struct sdata sd;            // Create instance of my shared data struct
    stf_test_framework_t tf;    // Create instance of a test framework

    sd.shared_val = 2;
    
    // Here I initialize the test framework so I can use it.
    stf_init_test_framework(&tf);
    
    // Here I add the three unit test functions to the test framework
    // in sequence.
    stf_add_unit_test(&tf, &test_inc_int_with_local_int);
    stf_add_unit_test(&tf, &test_inc_int_with_shared_int);
    stf_add_unit_test(&tf, &test_inc_int_with_null);
    
    // Here I run the unit tests in the test framework in sequence.
    stf_run_test_framework(&tf, &sd);
    
    // Here I free the test framework.
    stf_free_test_framework(&tf);
    // Here I re-initialize the test framework.
    stf_init_test_framework(&tf);
    
    return 0;
}

// Function definition of the function we want to test.
int inc_int(int *p_int) {
    if (p_int) {
        *p_int = (*p_int) + 1;
        return 0;
    }
    
    return 1;
}

// Function definitions of the unit test funcitons.
void test_inc_int_with_local_int(void *p_data) {
    int r, i;
    i = 5;

    r = inc_int(&i);
    assert((r == 0));
    assert((i == 6));
}

void test_inc_int_with_shared_int(void *p_data) {
    struct sdata *p_sd;
    int r;
    p_sd = (struct sdata *)p_data;
    
    r = inc_int(&p_sd->shared_val);
    assert((r == 0));
    assert((p_sd->shared_val == 3));
}

void test_inc_int_with_null(void *p_data) {
    int r;
    
    r = inc_int(NULL);
    assert((r == 1));
}