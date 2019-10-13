#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
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

//step1&6&7: print the first three lines of stat
void printFirstThreeLine(char * file, struct stat statbuf, char * fileType) {
  if (S_ISLNK(statbuf.st_mode)) {  //check if the file is a symbolic link
    //get the target of the link
    char linktarget[256];
    ssize_t len = readlink(file, linktarget, 256);
    linktarget[len] = '\0';
    printf("  File: %s -> %s\n", file, linktarget);
  }
  else {
    printf("  File: %s\n", file);  //print filename
  }
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         statbuf.st_size,     //print Total size, in bytes
         statbuf.st_blocks,   //print Number of 512B blocks allocated
         statbuf.st_blksize,  //print Block size for filesystem I/O
         fileType);           //print fileType got by the function getFileType
  if (S_ISCHR(statbuf.st_mode) || S_ISBLK(statbuf.st_mode)) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           (long)statbuf.st_dev,     //print ID of device containing file
           (long)statbuf.st_dev,     //print ID of device containing file
           statbuf.st_ino,           //print Inode number
           statbuf.st_nlink,         //print Number of hard links
           major(statbuf.st_rdev),   //"major" numbers of the file's device ID
           minor(statbuf.st_rdev));  //"minor" numbers of the file's device ID
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           (long)statbuf.st_dev,  //print ID of device containing file
           (long)statbuf.st_dev,  //print ID of device containing file
           statbuf.st_ino,        //print Inode number
           statbuf.st_nlink);     //print Number of hard links
  }
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

//get the ten characters readable permissions
void getReadablePermission(char permission[], struct stat statbuf) {
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
}

//get the ownerName from struct passwd
void getOwnerName(char ** ownerName, struct stat statbuf) {
  *ownerName = strdup(getpwuid(statbuf.st_uid)->pw_name);
}

//get the groupName from struct group
void getGroupName(char ** groupName, struct stat statbuf) {
  *groupName = strdup(getgrgid(statbuf.st_gid)->gr_name);
}

//step2&3: print the  forth line of stat
void printForthLine(struct stat statbuf) {
  char permission[11];
  getReadablePermission(permission, statbuf);
  char * ownerName;
  getOwnerName(&ownerName, statbuf);
  char * groupName;
  getGroupName(&groupName, statbuf);
  //struct passwd * ownerStruct =  getpwuid(statbuf.st_uid);
  //char * ownerName = ownerStruct->pw_name;
  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         statbuf.st_mode & ~S_IFMT,  //The permissions in octal.
         permission,                 //The human readable description of the permissions
         statbuf.st_uid,             //The user ID of the owner, as a number.
         ownerName,                  //name of the owner
         statbuf.st_gid,             //The group ID of the owning group, as a number.
         groupName);                 //the group name of the owning group
  free(ownerName);
  free(groupName);
}

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
}

//step4: print the last four lines of stat
void printStep4(struct stat statbuf) {
  char * accessTime = time2str(&statbuf.st_atime, statbuf.st_atim.tv_nsec);
  char * modifyTime = time2str(&statbuf.st_mtime, statbuf.st_mtim.tv_nsec);
  char * changeTime = time2str(&statbuf.st_ctime, statbuf.st_ctim.tv_nsec);
  printf("Access: %s\n", accessTime);
  printf("Modify: %s\n", modifyTime);
  printf("Change: %s\n", changeTime);
  printf(" Birth: -\n");
  free(accessTime);
  free(modifyTime);
  free(changeTime);
}
int main(int argc, char * argv[]) {
  struct stat statbuf;
  //check if mystat onlu take at least one filename as command line argument
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i < argc; i++) {
    //check if lstat works properly
    if (lstat(argv[i], &statbuf) == -1) {
      perror("lstat");
      exit(EXIT_FAILURE);
    }
    char * fileType;
    fileType = getFileType(statbuf);  //get fileType by the function getFileType
    printFirstThreeLine(argv[i],
                        statbuf,
                        fileType);  //print step1&6&7: print first three lines of stat
    printForthLine(statbuf);        //print step2&3: print the forth line of stat
    printStep4(statbuf);            //print step4: print the last four lines of stat
  }
}
