#ifndef FLAC__CALLBACK_H
#define FLAC__CALLBACK_H

#include "ordinals.h"
#include <stdlib.h>     // for size_t

/**
 * This module defines the structures for describing I/O callbacks
 * to the other FLAC interfaces.
 * 
 * The purpose of the I/O callback functions is to create a common way
 * for the metadata interfaces to handle I/O.
 * 
 * Originally the metadata interfaces required filenames as the way of
 * specifying FLAC files to operate on. This is problematic in some
 * environments so there is an additional option to specify a set of
 * callbacks for doing I/O on the FLAC file, instead of the filename.
 * 
 * In addition to the callbacks, a FLAC__IOHandle type is defined as an 
 * opaque structure for a data source.
 * 
 * The callback function prototypes are similar (but not identical) to the
 * stdio functions fread, fwrite, fseek, ftell, feof, and fclose. If you use
 * stdio streams to implement the callbacks, you can pass fread, fwrite, and
 * fclose anywhere a FLAC__IOCallback_Read, FLAC__IOCallback_Write, or
 * FLAC__IOCallback_Close is required, and a FILE* anywhere a FLAC__IOHandle
 * is required.
 * 
 * You generally CANNOT directly use fseek or ftell for FLAC__IOCallback_Seek or
 * FLAC__IOCallback_Tell since on most systems these use 32-bit offsets 
 * and FLAC requires 64 bit offsets to deal with large files. You will have to
 * find a equivalent function (e.g. ftello), or write a wrapper. The same is true
 * for feof() since this is usually implemented as a macro, not as a function
 * whose address can be taken.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This is the opaque handle type used by the callbacks. Typically
 * this is a FILE* or address of a file descriptor.
 */
typedef void* FLAC__IOHandle;

/**
 * Signature for the read callback.
 * The signature and semantics match POSIX fread() implementations
 * and can generally be used interchangeably.
 * 
 * param ptr    The address of the read buffer.
 * param size   The size of the records to be read.
 * param nmemb  The number of records to be read.
 * param handle The handle to the data source.
 * retval size_t    The number of records read.
 */

/**
 * size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
 * The  function  fread()  reads nmemb items of data, each size bytes long, from the stream pointed to by stream,
 * storing them at the location given by ptr.
 */
typedef size_t (*FLAC__IOCallback_Read)(void *ptr, size_t size, size_t nmemb, FLAC__IOHandle handle);

/**
 * Signature for the write callback.
 * The signature and semantics match POSIX fwrite() implementations
 * and can generally be used interchangeably.
 * param ptr    The address of the write buffer.
 * param size   The size of the records to e written.
 * param nmemb  The number of records to be written.
 * param handle The handle to the data source.
 * retval size_t    The number of records written.
 */

/**
 * size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
 * The function fwrite() writes nmemb items of data, each size bytes long, to the stream pointed  to  by  stream,
 * obtaining them from the location given by ptr.
 */
typedef size_t (*FLAC__IOCallback_Write)(const void *ptr, size_t size, size_t nmemb, FLAC__IOHandle handle);


/**
 * Signature for the see callback.
 * The signature and semantics mostly match POSIX fseek() WITH ONEIMPORTANT
 * EXCEPTION: the offset is a 64-bit type whereas fseek() is generally 'long'
 * and 32-bits wide.
 * 
 * param handle     The handle to the data source.
 * param offset     The new position, relative to a whence.
 * param whence     SEEK_SET, SEEK_CUR, or SEEK_END.
 * retval int       0 on success, -1 on error.
 */

/**
 * int fseek(FILE *stream, long offset, int whence);
 * The  fseek() function sets the file position indicator for the stream pointed to by stream.  The new position,
 * measured in bytes, is obtained by adding offset bytes to the position specified by whence.  If whence  is  set
 * to  SEEK_SET,  SEEK_CUR,  or  SEEK_END,  the offset is relative to the start of the file, the current position
 * indicator, or end-of-file, respectively.
 */
typedef int (*FLAC__IOCallback_Seek)(FLAC__IOHandle handle, FLAC__int64 offset, int whence);


/**
 * Signature for the tell callback.
 * The signature and semantics mostly match POSIX ftell() WITH ONE IMPORTANT
 * EXCEPTION: the offset is a 64-bit type whereas ftell() is generally 'long'
 * and 32-bits wide.
 * param handle     The handle to the data source.
 * retval   FLAC__int64
 *      The current position on success, -1 on error.
 */

/**
 * long ftell(FILE *stream);
 * The  ftell()  function  obtains  the current value of the file position indicator for the stream pointed to by
 * stream.
 */
typedef FLAC__int64 (*FLAC__IOCallback_Tell)(FLAC__IOHandle handle);


/**
 * Signature for the EOF callback.
 * The signature and semantics mostly match POSIX feof() but WATCHOUT:
 * on many systems. feof() is a macro, so in this case a wrapper function
 * must be provided instead.
 * 
 * param handle     The handle to the data source.
 * // 特别注意返回的定义
 * retval int       0 if not at end of file, nonzero if at end of file.
 */

/**
 * void clearerr(FILE *stream);
 * int feof(FILE *stream);
 * 
 * The function clearerr() clears the end-of-file and error indicators for the stream pointed to by stream.
 * 如果被设置就是文件的结尾。
 * The  function feof() tests the end-of-file indicator for the stream pointed to by stream, returning nonzero if
 * it is set.  The end-of-file indicator can be cleared only by the function clearerr().
 */
typedef FLAC__int64 (*FLAC__IOCallback_Eof)(FLAC__IOHandle handle);

/**
 * Signature for the close callback.
 * The signature and semantics match POSIX fclose() implementations
 * and can generally be used interchangeably.
 * 
 * param handle     The handle to the data source.
 * retval int       0 on success, EOF on error.
 */

/**
 * int fclose(FILE *stream);
 * The  fclose()  function  flushes  the  stream  pointed  to  by  stream (writing any buffered output data using
 * fflush()) and closes the underlying file descriptor.
 */
typedef int (*FLAC__IOCallback_Close)(FLAC__IOHandle handle);

/**
 * A strutture for holding a set of callbacks.
 * Each FLAC interface that requires a FLAC__IOCallbacks sturcture will
 * describe which of the callbacks are required. The ones that are not
 * reuired may be set to NULL.
 * 
 * IF the seek requirement for an interface is optional, you can signify that 
 * a data source is not seekable be setting a seek field to NULL.
 */
typedef struct {
    FLAC__IOCallback_Read read;
    FLAC__IOCallback_Write write;
    FLAC__IOCallback_Seek seek;
    FLAC__IOCallback_Tell tell;
    FLAC__IOCallback_Eof eof;
    FLAC__IOCallback_Close close;
} FLAC__IOCallbacks;

#ifdef __cplusplus
}
#endif


#endif // !FLAC__CALLBACK_H