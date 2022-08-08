#ifndef LIBK_GABALLOCPP_H
#define LIBK_GABALLOCPP_H 1

#include "gaballoc.h"

class Cache {
  private:
    cache_t* cache;

  public:
    inline Cache(size_t size, size_t align,
		 void (*constructor)(void* ptr, size_t size),
		 void (*destructor)(void* ptr, size_t size) = NOCONSTRUCT) {
	cache = cache_create(size, align, constructor, destructor);
    }

    inline ~Cache() { cache_destroy(cache); }

    inline void* alloc() { return cache_alloc(cache); }

    inline void free(void* ptr) { cache_free(cache, ptr); }
};

#endif
