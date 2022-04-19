#define NULL        0
#define EOF         (-1)
#define BUFSIZ      1024
#define OPEN_MAX    20

struct _flags {
    unsigned int _READ : 1;
    unsigned int _WRITE : 1;
    unsigned int _UNBUF : 1;
    unsigned int _EOF : 1;
    unsigned int _ERR : 1;
};

typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    struct _flags flag;
    int fd;
} FILE;

static const struct _flags _rd_flag = {1, 0, 0, 0, 0};
static const struct _flags _wr_flag = {0, 1, 0, 0, 0};
static const struct _flags _wr_unbuf_flag = {0, 1, 1, 0, 0};
static const struct _flags _unused_flag = {0, 0, 0, 0, 0};

FILE _iob[OPEN_MAX] = {
    {0, (char *) 0, (char *) 0, _rd_flag, 0},
    {0, (char *) 0, (char *) 0, _wr_flag, 1},
    {0, (char *) 0, (char *) 0, _wr_unbuf_flag, 2}
};

#define stdin       (&_iob[0])
#define stdout      (&_iob[1])
#define stderr      (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
int fflush(FILE *);

#define feof(p)     ((p)->flag._EOF)
#define ferror(p)   ((p)->flag._ERR)
#define fileno(p)   ((p)->fd)

#define getc(p)     (--(p)->cnt >= 0 ? \
                    (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p)  (--(p)->cnt >= 0 ? \
                    *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()   getc(stdin);
#define putchar(x)  putc((x), stdout);

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define PERMS 0666

/* fopen: open file, return file ptr */
FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL;
    }
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if ((fp->flag._READ | fp->flag._WRITE) == 0) {
            break;
        }
    }
    if (fp > _iob + OPEN_MAX) {
        return NULL;
    }

    if (*mode == 'w') {
        fd = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1) {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    }
    if (fd == -1) {
        return NULL;
    }
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _rd_flag : _wr_flag;
    return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
    int bufsize;

    if (!(fp->flag._READ & ~fp->flag._EOF & ~fp->flag._ERR)) {
        return EOF;
    }
    bufsize = fp->flag._UNBUF ? 1 : BUFSIZ;
    if (fp->base == NULL) {
        if ((fp->base = (char *) malloc(bufsize * sizeof(char))) == NULL) {
            return EOF;
        }
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flag._EOF = 1;
        } else {
            fp->flag._ERR = 1;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

/* _flushbuf: allocate and flush output buffer */
int _flushbuf(int c, FILE *fp)
{
    int bufsize;

    if (!(fp->flag._WRITE & ~fp->flag._EOF & ~fp->flag._ERR)) {
        return EOF;
    }
    bufsize = fp->flag._UNBUF ? 1 : BUFSIZ;
    if (fp->base != NULL) {
        fp->ptr = fp->base;
        fp->cnt = write(fp->fd, fp->ptr, bufsize);
    }
    if (fp->base == NULL) {
        if ((fp->ptr = fp->base = (char *) malloc(bufsize * sizeof(char))) == NULL) {
            return EOF;
        }
        fp->cnt = bufsize;
    }
    if (--fp->cnt != bufsize - 1) {
        fp->flag._ERR = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) (*fp->ptr++ = c);
}

int _fflush(FILE *fp)
{
    if (fp->flag._ERR | fp->flag._EOF) {
        return EOF;
    }
    if (fp->flag._WRITE && !fp->flag._UNBUF && fp->base != NULL) {
        int size = BUFSIZ - fp->cnt;
        if (write(fp->fd, fp->base, size) != size) {
            return EOF;
        } else {
            fp->ptr = fp->base;
            fp->cnt = BUFSIZ;
            return 0;
        }
    }
    return 0;
}

/* fflush: flush output buffer to file */
int fflush(FILE *fp)
{
    int i;
    int _fflush(FILE *);

    if (fp == NULL) {
        for (i = 0; i < OPEN_MAX; ++i) {
            if (_fflush(&_iob[i]) != 0) {
                return EOF;
            }
        }
        return 0;
    }
    return _fflush(fp);
}

/* fclose: close file pointed by fp */
int fclose(FILE *fp)
{
    if (!fp->flag._READ && !fp->flag._WRITE) {
        return 0;
    }
    if (fflush(fp) != 0) {
        return EOF;
    }
    fp->cnt = 0;
    if (fp->base != NULL) {
        free(fp->base);
    }
    fp->ptr = NULL;
    fp->flag = _unused_flag;
    return close(fp->fd);
}

/* cat: with customed stdio */
int main(int argc, char *argv[])
{
    FILE *fp;
    int c;

    if (argc == 2) {
        if ((fp = fopen(*++argv, "r")) == NULL) {
            return 1;
        }
    } else {
        fp = stdin;
    }

    while ((c = getc(fp)) != EOF) {
        putc(c, stdout);
    }
    fclose(stdout);
    return 0;
}

