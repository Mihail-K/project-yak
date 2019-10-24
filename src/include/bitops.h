#ifndef __BITOPS_H__
#define __BITOPS_H__

#define get_bit(value, bit)   ((value) &  (1 << (bit)))
#define set_bit(value, bit)   ((value) |  (1 << (bit)))
#define clear_bit(value, bit) ((value) & ~(1 << (bit)))

#endif
