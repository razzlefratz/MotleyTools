/*====================================================================*
 *
 *   sv_coper.h -
 *
 *.  Motley Tools by Charles Maier
 *:  modified thu 25 nov 04 by user root on host zephir;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SV_COPER_SOURCE
#define SV_COPER_SOURCE

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define COPER_O_NOT                       0
#define COPER_O_NOT_ASSIGN                1
#define COPER_O_MODULO                    2
#define COPER_O_MODULO_ASSIGN             3
#define COPER_O_BITWISE_AND               4
#define COPER_O_LOGICAL_AND               5
#define COPER_O_BITWISE_AND_ASSIGN        6
#define COPER_O_MULT                      7
#define COPER_O_MULT_ASSIGN               8
#define COPER_O_ADD                       9
#define COPER_O_INCREMENT                10
#define COPER_O_ADD_ASSIGN               11
#define COPER_O_SUB                      12
#define COPER_O_DECREMENT                13
#define COPER_O_SUB_ASSIGN               14
#define COPER_O_POINTER_TO               15
#define COPER_O_MEMBER                   16
#define COPER_O_DIV                      17
#define COPER_O_DIV_ASSIGN               18
#define COPER_O_LESS_THAN                19
#define COPER_O_SHIFT_LEFT               20
#define COPER_O_SHIFT_LEFT_ASSIGN        21
#define COPER_O_LESS_THAN_OR_EQUAL       22  
#define COPER_O_ASSIGN                   23
#define COPER_O_LOGICAL_ASSIGN           24
#define COPER_O_MORE_THAN                25
#define COPER_O_MORE_THAN_OR_EQUAL       26
#define COPER_O_SHIFT_RIGHT              27
#define COPER_O_SHIFT_RIGHT_ASSIGN       28
#define COPER_O_EXCLUSIVE_OR             29
#define COPER_O_EXCLUSIVE_OR_ASSIGN      30
#define COPER_O_BITWISE_OR               31
#define COPER_O_BITWISE_OR_ASSIGN        32
#define COPER_O_LOGICAL_OR               33
#define COPER_O_COMPLIMENT               34
#define COPER_O_COMPLIMENT_ASSIGN        35
#define COPER_O_NULL                     36

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define isunary(c) (((c) == COPER_O_INCREMENT) || ((c) == COPER_O_DECREMENT) || ((c) == COPER_O_MEMBER) || ((c) == COPER_O_POINTER_TO) || ((c) == COPER_O_NEGATE) || ((c) == COPER_O_COMPLIMENT))

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

