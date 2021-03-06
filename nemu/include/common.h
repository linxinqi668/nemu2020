#ifndef __COMMON_H__
#define __COMMON_H__

#define USE_RAMDISK

/* You will define this macro in PA4 */
//#define HAS_DEVICE

#define DEBUG
#define LOG_FILE

#include "debug.h"
#include "macro.h"

#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <elf.h>

typedef uint8_t bool;
typedef uint32_t hwaddr_t;
typedef uint32_t lnaddr_t;
typedef uint32_t swaddr_t;

typedef uint16_t ioaddr_t;

#pragma pack (1)
typedef union {
	uint32_t _4;
	uint32_t _3	: 24;
	uint16_t _2;
	uint8_t _1;
} unalign;
#pragma pack ()

char * get_strtab();
Elf32_Sym * get_symtab();
int get_symtab_len();
char * get_fun_name(swaddr_t addr);

#define false 0
#define true 1

#endif
