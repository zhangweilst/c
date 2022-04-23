/*
  Outer level abstraction
  All declarations here are suffixed with _z/_Z in case of conflict
*/

#define NAME_MAX    255
#define DIR_MAX     255
#define PATH_MAX    4096

typedef struct {
    long ino;
    char name[NAME_MAX + 1];
} dirent_z;

typedef struct {
    int fd;
    dirent_z d;
} DIR_Z;

DIR_Z *opendir_z(char *dirname);
dirent_z *readdir_z(DIR_Z *dfd);
void closedir_z(DIR_Z *dfd);

