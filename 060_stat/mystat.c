#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

//get the filetype by AND st_mode with S_IFMT
char * getFileType(struct stat statbuf) {
  char * answer = NULL;
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
//get the first character of readable permission
//The first is either 'b','c', 'd', 'p', 'l', '-', or 's' depending on the file type
//corresponding to S_IFBLK, S_IFCHR, S_IFDIR, S_IFIFO, S_IFLNK, S_IFREG, S_IFSOCK in that order)
char getFirstPermChar(struct stat statbuf) {
  char answer = ' ';
  switch (statbuf.st_mode & S_IFMT) {
    case S_IFBLK: {
      answer = 'b';
      break;
    }
    case S_IFCHR: {
      answer = 'c';
      break;
    }
    case S_IFDIR: {
      answer = 'd';
      break;
    }
    case S_IFIFO: {
      answer = 'p';
      break;
    }
    case S_IFLNK: {
      answer = 'l';
      break;
    }
    case S_IFREG: {
      answer = '-';
      break;
    }
    case S_IFSOCK: {
      answer = 's';
      break;
    }
  }
  return answer;
}
//get the READ permission character of the readable permission
//If st_mode & checkbit is non-zero,
//the owner has read permission, and you should put 'r' here.
//Otherwise, the owner cannot read it, and you should put '-' here.
char getReadPermChar(struct stat statbuf, mode_t checkbit) {
  return (statbuf.st_mode & checkbit) ? 'r' : '-';
}
//get the WRITE character of the readable permission
//If st_mode & checkbit is non-zero,
//the owner has write permission, and you should put 'w' here.
//Otherwise, the owner cannot read it, and you should put '-' here.
char getWritePermChar(struct stat statbuf, mode_t checkbit) {
  return (statbuf.st_mode & checkbit) ? 'w' : '-';
}
//get the EXECUTE  character of the readable permission
//If st_mode & checkbit is non-zero,
//the owner has execute permission, and you should put 'x' here.
//Otherwise, the owner cannot read it, and you should put '-' here.
char getExecutePermChar(struct stat statbuf, mode_t checkbit) {
  return (statbuf.st_mode & checkbit) ? 'x' : '-';
}
//step2: print "Access" in forth line of stat
void printStep2(struct stat statbuf) {
  char permission[11];
  permission[0] = getFirstPermChar(statbuf);
  permission[1] = getReadPermChar(statbuf, S_IRUSR);
  permission[2] = getWritePermChar(statbuf, S_IWUSR);
  permission[3] = getExecutePermChar(statbuf, S_IXUSR);
  permission[4] = getReadPermChar(statbuf, S_IRGRP);
  permission[5] = getWritePermChar(statbuf, S_IWGRP);
  permission[6] = getExecutePermChar(statbuf, S_IXGRP);
  permission[7] = getReadPermChar(statbuf, S_IROTH);
  permission[8] = getWritePermChar(statbuf, S_IWOTH);
  permission[9] = getExecutePermChar(statbuf, S_IXOTH);
  permission[10] = '\0';
  printf("Access: (%04o/%s)\n", statbuf.st_mode & ~S_IFMT, permission);
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
  printStep1(argv[1], statbuf,
             fileType);  //print step1: print first three lines of stat
  printStep2(statbuf);   //print step2: "Access"
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
