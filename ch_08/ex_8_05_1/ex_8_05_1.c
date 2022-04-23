#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <dirent.h>
#include "dirent_z.h"

void fsize(char *);
void dirwalk(char *, void (*fcn)(char *));

/* print file sizes */
int main(int argc, char *argv[])
{
    if (argc == 1) {
        fsize(".");
    } else {
        while (--argc > 0) {
            fsize(*++argv);
        }
    }
    return 0;
}

/* fsize: print size of file "name" */
void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
        dirwalk(name, fsize);
    }
    printf("%8ld %6o %12ld %4d %4d %12ld %s\n",
        stbuf.st_size, stbuf.st_mode, stbuf.st_ino,
        stbuf.st_uid, stbuf.st_gid, stbuf.st_mtime, name);
}

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[PATH_MAX];
    dirent_z *dp;
    DIR_Z *dfd;

    if ((dfd = opendir_z(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir_z(dfd)) != NULL) {
        if (strcmp(dp->name, ".") == 0 ||
            strcmp(dp->name, "..") == 0) {
            continue;
        }
        if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name)) {
            fprintf(stderr, "dirwalk: name %s/%s too long\n",
                dir, dp->name);
        } else {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    closedir_z(dfd);
}

/* opendir: open a directory for readdir calls */
DIR_Z *opendir_z(char *dirname)
{
    int fd;
    struct stat stbuf;
    DIR_Z *dp;

    if ((fd = open(dirname, O_RDONLY, 0)) == -1 ||
        fstat(fd, &stbuf) == -1 ||
        (stbuf.st_mode & S_IFMT) != S_IFDIR ||
        (dp = (DIR_Z *) malloc(sizeof(DIR_Z))) == NULL) {
        return NULL;
    }
    dp->fd = fd;
    return dp;
}

/*
  readdir: read directory entries in sequence, linux version

  glibc has the high level readdir call, but with outer level
  abstraction, we'll use the low level directory access, which
  has poor support in glibc
*/
struct dirent64
{
    __ino64_t d_ino;
    __off64_t d_off;
    unsigned short int d_reclen;
    unsigned char d_type;
    char d_name[256];
};

dirent_z *readdir_z(DIR_Z *dp)
{
    struct dirent64 *dirp;
    ssize_t getdents64 (int fd, void *buffer, size_t length);

    static dirent_z d;
    static char buf[1024];
    static int i = 0;
    static ssize_t n = 0;

    while (i < n ||
        (i = 0, n = getdents64(dp->fd, (void *) buf, sizeof(buf))) > 0) {
        dirp = (struct dirent64 *) (buf + i);
        i += dirp->d_reclen;
        if (dirp->d_ino == 0) {
            continue;
        }
        d.ino = dirp->d_ino;
        strncpy(d.name, dirp->d_name, DIR_MAX);
        d.name[DIR_MAX] = '\0';
        return &d;
    }
    return NULL;
}

/* closedir: close directory opened by opendir */
void closedir_z(DIR_Z *dp)
{
    if (dp) {
        close(dp->fd);
        free(dp);
    }
}

