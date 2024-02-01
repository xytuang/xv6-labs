
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char* fmtname(char *path){
  char *p;
  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;
  return p;
}

void find(char *path, char *fname){
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }


    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
    }
    strcpy(buf, path);

    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      if (strcmp(p, ".") != 0 && strcmp(p, "..") != 0 &&  st.type == T_DIR){
        printf("%s/", path);
        find(p, fname);
      }
      else {
           char * fileName = fmtname(buf);
           if (strcmp(fileName, fname) == 0){
	       printf("%s/%s\n", path, fileName);
           }
      }
    }
  close(fd);
}

int main(int argc, char *argv[]){
	char * path = argv[1];
	char * fname = argv[2];
	find(path, fname);
	exit(0);
}
