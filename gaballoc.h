#ifndef LIBK_GABALLOC_H
#define LIBK_GABALLOC_H 1
#include<stdbool.h>
#include<stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct BUFCTL_S
{
	struct SLAB_S* backptr;
	struct BUFCTL_S* prev;
	struct BUFCTL_S* next;
	void* mem;
	bool free;
} __attribute__((packed)) bufctl_t;

typedef struct SLAB_S
{
	struct SLAB_S* prev;
	struct SLAB_S* next;
	bufctl_t* firstbuf;
	size_t refcount;
	size_t maxrefs;
} __attribute__((packed)) slab_t;

typedef struct CACHE_S
{
	bool large;
	slab_t* slabs;
	size_t size;
	size_t align;
	void* source;
	void (*destructor)(void* ptr, size_t size);
} cache_t;

cache_t* cache_create(size_t size, size_t align, void (*constructor)(void* ptr, size_t size), void (*destructor)(void* ptr, size_t size));
void cache_destroy(cache_t* cache);
void* cache_alloc(cache_t* cache);
void cache_free(cache_t* cache, void* ptr);

inline void __alloc_noconstr__(void* ptr, size_t size){ (void)ptr; (void)size; }
#define NOCONSTRUCT __alloc_noconstr__

#ifdef __cplusplus
}
#endif

#endif
