#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For write()

// Assume these constants and structures are defined correctly
#define OPEN_MAX 20  // Maximum number of open files
#define BUFSIZ 1024  // Standard buffer size

#define _READ 0x01
#define _WRITE 0x02
#define _ERR 0x04
#define _UNBUF 0x08

extern FILE *_iob;  // Assume _iob is the array of open FILE streams

/* _flushbuf: allocate and flush output buffer */
int _flushbuf(int x, FILE *fp) {
    unsigned nc;   /* # of chars to flush */
    int bufsize;   /* size of buffer allocation */
    
    if (fp < _iob || fp >= _iob + OPEN_MAX) {
        return EOF; /* error: invalid pointer */
    }
    
    if ((fp->flag & (_WRITE | _ERR)) != _WRITE) {
        return EOF; /* error: file is not writable */
    }

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;  // Determine buffer size

    if (fp->base == NULL) {  /* no buffer yet */
        if ((fp->base = (char *)malloc(bufsize)) == NULL) {
            fp->flag |= _ERR;
            return EOF;  /* can't get buffer */
        }
    } else {  /* buffer already exists */
        nc = fp->ptr - fp->base;
        if (write(fp->fd, fp->base, nc) != nc) {
            fp->flag |= _ERR;
            return EOF;  /* error: return EOF */
        }
    }

    fp->ptr = fp->base;  /* beginning of buffer */
    *fp->ptr++ = (char)x;  /* save current char */
    fp->cnt = bufsize - 1;  /* set count to buffer size - 1 */
    return x;
}

/* fflush: flush output buffer to file */
int fflush(FILE *fp) {
    int rc = 0;

    if (fp < _iob || fp >= _iob + OPEN_MAX) {
        return EOF; /* error: invalid pointer */
    }

    if (fp->flag & _WRITE) {
        rc = _flushbuf(0, fp);  // Flush the buffer
    }

    fp->ptr = fp->base;  // Reset the pointer to the beginning of the buffer
    fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;  // Set the count to the buffer size
    return rc;
}

/* fclose: close file */
int fclose(FILE *fp) {
    int rc;  /* return code */

    if ((rc = fflush(fp)) != EOF) {  /* anything to flush? */
        free(fp->base);  /* free allocated buffer */
        fp->ptr = NULL;
        fp->cnt = 0;
        fp->base = NULL;
        fp->flag &= (_READ | _WRITE);  /* reset flags */
    }

    return rc;
}