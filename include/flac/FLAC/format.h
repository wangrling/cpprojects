#ifndef FLAC__FORMAT_H
#define FLAC__FORMAT_H

#include "export.h"
#include "ordinals.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This module contains structure definitions for the representation 
 * of FLAC format components in memory. These are the basic 
 * structures used by the rest of the interfaces.
 * 
 * Fisrt, you should be familiar with the FLAC format.
 * Many of the values here follow directly from the specification. 
 * As the user of libFLAC, the interesting parts really are the structures
 * that describe the frame header and metadata blocks.
 * 
 * The format structures here are very primitive, designed to store
 * information in an efficient way. Reading information from the
 * structures is easy but creating or modifying them directly is more complex.
 * For the most part, as a user of a library, editing is not necessary;
 * however, for metadata blocks it is, so there are conveniece functions
 * provided in the flac_metadata metadata module to simplify the 
 * manpulation of metadata blocks.
 * 
 * It's not the se convention, but symbols ending in _LEN are in bits
 * and _LENGTH are in bytes. _LENGTH symbols are #defines instead of global
 * variables because they are usually used when declaring byte arrays
 * and some compilers require compile-time knowledge of array
 * sizes when declared on the stack.
 */

/**
 * Most of the values described in this file are defined by the FLAC format
 * specification. There is nothing to tune there.
 */

/** The largest legal metadata type code. */
/**
 * BLOCK_TYPE
 * 0: STREAMINFO
 * 1: PADDING
 * 2: APPLICATION
 * 3: SEEKTABLE
 * 4: VORBIS_COMMENT
 * 5: CUESHEET
 * 6: PICTURE
 * 7-126: reserved
 * 127: invalid, to avoid confusion with a frame sync code
 */
// 通常是以bit为单位计算。
#define FLAC__MAX_METADATA_TYPE_CODE (126u)

/** The munimum block size, in samples, permitted by the format. */
// block表示原始数据
// In order to simplify encoder/decoder design, FLAC imposes a minimum block size of 
// 16 samples, and a maximum block size of 65535 samples.
#define FLAC__MIN_BLOCK_SIZE (16u)

/** The maximum block size, in samples, permitted by the format. */
#define FLAC__MAX_BLOCK_SIZE (65535u)

/**
 * The maximum block size, in samples, permitted by the FLAC subset for 
 * sample rates up to 48kHz.
 */
// FLAC定义subset,把一些参数的范围缩小。
// FLAC specifies a subset of itself as the Subset format.
// The blocksize bits in the frame header must be 0001-1110.
// The blocksize must be <= 16384; if the sample rate is <= 48000, the blocksize must be <=4608.
#define FLAC__SUBSET_MAX_BLOCK_SIZE_48000Hz (4608u)

/** The maximum number of channels permitted by the format. */
// 最多支持8声道
// 0000-0111
/**
 * 1: mono
 * 2: left, right
 * 3: left, right, center
 * 4: front left, front right, back left, back right
 * 5: front left, front right, front center, back/surround left, back/surround right
 * 6: front left, front right, front center, LFE, back/surround left, back/surround right
 * 7: front left, front right, front center, LFE, back center, side left, side right
 * 8: front left, front right, front center, LFE, back left, back right, side left, side right
 */
#define FLAC__MAX_CHANNELS (8u)

/** The minimum sample resolution permitted by the format. */
// METADATA_BLOCK_STREAMINFO
// FLAC supports from 4 to 32 bits per sample.
// Currently the reference encoder and decoders only support up to 24 bits per sample.
#define FLAC__MIN_BITS_PER_SAMPLE (4u)

/** The maximum sample resolution permitted by the format. */
#define FLAC__MAX_BITS_PER_SAMPLE (32u)

/**
 * FLAC__MAX_BITS_PER_SAMPLE is the limit of the FLAC format. However,
 * the reference encoder/decoder is currently limited to 24 bits because
 * of prevalent 32-bit math, so make sure and use this value when
 * appropriate.
 */
#define FLAC__REFERENCE_CODEC_MAX_BITS_PER_SAMPLE (24u)

/**
 * The maximum sample rate permitted by the format. The value is ((2 ^ 16) - 1) * 10;
 */
/**
 * 0000: get from STREAMINFO metadata block 
 * 0001: 88.2kHz
 * 0010: 176.4kHz
 * 0011: 192kHz
 * ....
 * 1110: get 16 bit sample rate (in tens of Hz) from end of header.
 * 1111: invalid, to prevent sync-fooling string 1s
 */
#define FLAC__MAX_SAMPLE_RATE (655350u)

/** The maximum LPC order permitted by the format. */
#define FLAC__MAX_LPC_ORDER (32u)

// LPC QLP两个目前还不清楚。

/** The maximum LPC order permitted by the FLAC subset for sample rates
 * up to 48kHz. */
// If the sample rate is <= 48000Hz, the filter order in LPC subframes must be 
// less than or equal to 12.
#define FLAC__SUBSET_MAX_LPC_ORDER_48000HZ (12u)

/** The minimum quantized linear predictor coefficient precision
 * permitted by the format.
 */
#define FLAC__MIN_QLP_COEFF_PRECISION (5u)

/** The maximum quantized linear predictor coefficient precision
 * permitted by the format.
 */
#define FLAC__MAX_QLP_COEFF_PRECISION (15u)

/** The maximum order the fixed predictors permitted by the format. */
#define FLAC__MAX_FIXED_ORDER (4u)

/** The maximum Rice partition order permitted by the format. */
#define FLAC__MAX_RICE_PARTITION_ORDER (15u)

/** The maximum Rice partition order permitted by the FLAC Subset. */
// The Rice partition order in a Rice-coded residual section must be less than or equal to 8.
#define FLAC__SUBSET_MAX_RICE_PARTITION_ORDER (8u)

/**
 * The version string of the release, stamped onto the libraries and binaries.
 * 
 * This does not correspond to the shared library version number, which
 * is used to determined binary compatibility.
 */
extern FLAC_API const char *FLAC__VERSION_STRING;

/**
 * The vendor string inserted by the encoder into the VORBIS_COMMNET block.
 * This is a NUL-terminated ASCII string; when inserted into the VORBIS_COMMENT
 * the trailing null nis tripped.
 */
extern FLAC_API const char *FLAC__VENDOR_STRING;

/** The byte string representation of the beginning of a FLAC stream. */
/* = "fLaC" */
extern FLAC_API const FLAC__byte FLACT__STREAM_SYNC_STRING[4];

/**
 * The 32-bit integer big-endian representation of the beginning of  a FLAC stream.
 */
// ascii f = 66
extern FLAC_API const unsigned FLAC__STREAM_SYNC;   /* = 0x664C6143 */

/** The length of the FLAC signature in bits */
extern FLAC_API const unsigned FLAC__STREAM_SYNC_LEN;   /* = 32 bits */

/** The length of the FLAC signature in bytes. */
#define FLAC__STREAM_SYNC_LENGTH (4u)


/********************************************************************
 * 
 * Subframe structures
 * 
 ********************************************************************/
/** An emueration of the available entropy coding methods. */
// FLAC currently defines two similar methods for the coding of the error signal
// from the prediction stage.
// RESIDUAL_CODING_METHOD_PARTITIONED_RICE
// RESIDUAL_CODING_METHOD_PARTITIONED_RICE2
typedef enum {
    /** Residual is coded by partitioning into contexts, each with it's own
     * 4-bit Rice parameter. */
    FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE = 0,
    
    /** Residual is coded by partitioning into contexts, each with it's own
     * 5-bit Rice parameter. */
    FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE2 = 1
} FLAC__EntropyCodingMethodType;

/**
 * Map a FLAC__EntropyCodingMethodType to a C string.
 * 
 * Using a FLAC__EntropyCodingMethodType as the index to this array will give
 * the string equivalent. The contents should not be modified.
 */
// 使用字符串表示
extern FLAC_API const char * const FLAC__EntropyCodingMethodTypeString[];

/**
 * Contents of a Rice partitioned residual (残余)
 */
// RICE_PARTITION
// <4+(5)> Encoding paramter:
        // 0000-1110:   Rice parameter.     使用parameters表示
        // 1111: Escape code    使用raw_bits表示
// <?> (需要的位数未确定) Encoded residual   // capacity_by_order表示指针的大小。    
typedef struct {
    
    /** The Rice parameters for each context. */
    unsigned *parameters;

    /** Widths for escape-coded partitions. Will be non-zero for escaped
     * partitions and zero for unescaped partitions.
     */
    unsigned *raw_bits;

    /**
     * The capacity of the parameters and raw_bits arrays 
     * specified as an order, i.e. the number of array elements
     * allocated is 2^capacity_by_order.
     */
    unsigned capacity_by_order;
} FLAC__EntropyCodingMethod_PartitionedRiceContents;


// RESIDUAL_CODING_METHOD_PARTITIONED_RICE
// <4>                  Partition order
// RICE_PARTITION+      There will be 2^order partitions
// 或者
// RESIDUAL_CODING_METHOD_PARTITIONED_RICE2
/** Header for a Rice partitioned residual. */
typedef struct {
    /** The partition order, i.e. # of contexts = 2^order. */
    unsigned order;

    /** The context's Rice parameters and/or raw bits. */
    const FLAC__EntropyCodingMethod_PartitionedRiceContents *content;
} FLAC__EntropyCodingMethod_PartitionedRice;

// RESIDUAL_CODING_METHOD_PARTITIONED_RICE || RESIDUAL_CODING_METHOD_PARTITIONED_RICE
// <4> Partition order.
extern FLAC_API const unsigned FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE_ORDER_LEN; /** == 4 (bits) */
// RICE_PARTITION
// <4+(5)>  前面的4
extern FLAC_API const unsigned FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE_PARAMETER_LEN; /** == 4 (bits) */
// RICE2_PARTITION
// <5+(5)>  前面的5
extern FLAC_API const unsigned FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE2_PARAMETER_LEN; /** == 5 (bits) */
// 后面的5
extern FLAC_API const unsigned FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE_RAW_LEN;    /** == 5 (bits) */


#ifdef __cplusplus
}
#endif

#endif // !FLAC__FORMAT_H