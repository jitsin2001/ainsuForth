// Fri Jun 23 20:27:20 UTC 2017
// 4735-a0r-00-

#include <Arduino.h>
#include "../../yaffa.h"
#include "../../flashDict.h"  // required?
#include "../../Dictionary.h" // provides: #include "iasmd.h"
// #include "../../Error_Codes.h"

/*******************************************************************************/
/**                          Core Forth Words                                 **/
/*******************************************************************************/
const char store_str[] = "!";
// ( x a-addr --)
// Store x at a-addr
void _store(void) { 
  cell_t* address = (cell_t*)dStack_pop();
  *address = dStack_pop();
}


const char c_store_str[] = "c!";
// ( char c-addr -- )
void _c_store(void) {
  uint8_t *addr = (uint8_t*) dStack_pop();
  *addr = (uint8_t)dStack_pop();
}

// comma_str -- see flashDict.cpp


#ifdef NEVER_DEFINED_ANYWHERE
const char c_comma_str[] = "c,";
// ( char -- )
void _c_comma(void) {
  *(char*)pHere++ = (char)dStack_pop();
}


const char plus_store_str[] = "+!";
// ( n|u a-addr -- )
// add n|u to the single cell number at a-addr
void _plus_store(void) {
  cell_t* address = (cell_t*)dStack_pop();
  if (address >= &forthSpace[0] &&
      address < &forthSpace[FORTH_SIZE])
      *address += dStack_pop();
  else {
    dStack_push(-9);
    _throw();
  }
}


const char two_store_str[] = "2!";
// ( x1 x2 a-addr --)
// Store the cell pair x1 x2 at a-addr, with x2 at a-addr and x1 at a-addr+1
void _two_store(void) {
  cell_t* address = (cell_t*)dStack_pop();
  if (address >= &forthSpace[0] &&
      address < &forthSpace[FORTH_SIZE - 4]) {
    *address++ = dStack_pop();
    *address = dStack_pop();
  } else {
    dStack_push(-9);
    _throw();
  }
}


const char fill_str[] = "fill";
// ( c-addr u char -- )
// if u is greater than zero, store char in u consecutive characters of memory
// beginning with c-addr.
void _fill(void) {
  char ch = (char)dStack_pop();
  cell_t limit = dStack_pop();
  char* addr = (char*)dStack_pop();
  for (int i = 1; i < limit; i++) {
    *addr++ = ch;
  }
}
#endif



const char fetch_str[] = "@";
// ( a-addr -- x1 )
// Fetch cell x1 at a-addr.
void _fetch(void) {
  cell_t* address = (cell_t*)dStack_pop();
  dStack_push(*address);
}



#ifdef NEVER_DEFINED_ANYWHERE
const char two_fetch_str[] = "2@";  // \x40 == '@'
// ( a-addr -- x1 x2 )
// Fetch cell pair x1 x2 at a-addr. x2 is at a-addr, and x1 is at a-addr+1
void _two_fetch(void) {
  cell_t* address = (cell_t*)dStack_pop();
  cell_t value = *address++;
  dStack_push(value);
  value = *address;
  dStack_push(value);
}


const char c_fetch_str[] = "c@";
// ( c-addr -- char )
void _c_fetch(void) {
  uint8_t *addr = (uint8_t *) dStack_pop();
  dStack_push(*addr);
}


const char r_fetch_str[] = "r@";
// Interpretation: undefined
// Execution: ( -- x ) (R: x -- x)
// Copy x from the return stack to the data stack.
void _r_fetch(void) {
  dStack_push(rStack_peek(0));
}


const char r_from_str[] = "r>";
// Interpretation: undefined
// Execution: ( -- x ) (R: x -- )
// move x from the return stack to the data stack.
void _r_from(void) {
  dStack_push(rStack_pop());
}


const char to_r_str[] = ">r";
// ( x -- ) (R: -- x )
void _to_r(void) {
  rStack_push(dStack_pop());
}

#endif

/******************************************************************************/
/**  YAFFA - Yet Another Forth for Arduino                                   **/
/**                                                                          **/
/**  File: Dictionary.ino                                                    **/
/**  Copyright (C) 2012 Stuart Wood (swood@rochester.rr.com)                 **/
/******************************************************************************/
