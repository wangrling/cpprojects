#ifndef FLAC__ASSERT_H
#define FLAC__ASSERT_H
#include "Config.h"

/**
 * We need this since some compilers (like MSVC) leave assert()s on release code
 * (and we don't want to use their ASSERT)
 */
#ifdef DEBUG
#include <assert.h>
#define FLAC_ASSERT(x) assert(x)
#define FLAC_ASSERT_DECLARTION(x) x 
#else
#define FLAC_ASSERT(x)
#define FLAC_ASSERT_DECLARATION(x)
#endif // DEBUG

#endif // !FLAC__ASSERT_H
