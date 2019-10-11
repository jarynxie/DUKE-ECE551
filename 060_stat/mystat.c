#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

//get the filetype by AND st_mode with S_IFMT
char * getFileType(struct stat statbuf) {
  char * answer;
  switch (statbuf.st_mode & S_IFMT) {
    case S_IFBLK: {
      answer = "block special file";
      break;
    }
    case S_IFCHR: {
      answer = "character special file";
      break;
    }
    case S_IFDIR: {
      answer = "directory";
      break;
    }
    case S_IFIFO: {
      answer = "fifo";
      break;
    }
    case S_IFLNK: {
      answer = "symbolic link";
      break;
    }
    case S_IFREG: {
      answer = "regular file";
      break;
    }
    case S_IFSOCK: {
      answer = "socket";
      break;
    }
  }
  return answer;
}

//step1: print the first three lines of stat
void printStep1(char * file, struct stat statbuf, char * fileType) {
  printf("  File: %s\n", file);  //print filename
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         statbuf.st_size,     //print Total size, in bytes
         statbuf.st_blocks,   //print Number of 512B blocks allocated
         statbuf.st_blksize,  //print Block size for filesystem I/O
         fileType);           //print fileType got by the function getFileType
  printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
         (long)statbuf.st_dev,  //print ID of device containing file
         (long)statbuf.st_dev,  //print ID of device containing file
         statbuf.st_ino,        //print Inode number
         statbuf.st_nlink);     //print Number of hard links
}

int main(int argc, char * argv[]) {
  struct stat statbuf;
  //check if mystat onlu take one filename as command line argument
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  //check if lstat works properly
  if (lstat(argv[1], &statbuf) == -1) {
    perror("lstat");
    exit(EXIT_FAILURE);
  }
  char * fileType;
  fileType = getFileType(statbuf);  //get fileType by the function getFileType
  printStep1(argv[1],
             statbuf,
             fileType);  //print the requirement of step1: print first three lines of stat
  /*
  //This function is for Step 4
  char * time2str(const time_t * when, long ns) {
    char * ans = malloc(128 * sizeof(*ans));
    char temp1[64];
    char temp2[32];
    const struct tm * t = localtime(when);
    strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
    strftime(temp2, 32, "%z", t);
    snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
    return ans;
  */
}
