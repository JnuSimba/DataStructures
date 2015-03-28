#ifndef _HASH_LINK_H_
#define _HASH_LINK_H_
#include "common.h"

/* 给定关键码key，经过哈希函数计算得到的是关键码对应的数据项在数组中的存储下标index/bucket
 * 数据项所存储的表用数组实现，即hash table 
 */

typedef struct hash hash_t;
typedef unsigned int (*hashfunc_t)(unsigned int, void*);

hash_t* hash_alloc(unsigned int buckets, hashfunc_t hash_func);
void* hash_lookup_entry(hash_t *hash, void* key, unsigned int key_size);
void hash_add_entry(hash_t *hash, void *key, unsigned int key_size, void *value, unsigned int value_size);
void hash_free_entry(hash_t *hash, void *key, unsigned int key_size);


#endif
