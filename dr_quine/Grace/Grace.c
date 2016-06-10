

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

/*
   Ugly uh ?
*/

#define write_to_fd(fd, str, len){write(fd,str,len);}
#define write_no_real(str,fd){while(*str){if(*str == '"'){write_to_fd(fd, "\\\"", 2);}else if(*str == '\n'){write_to_fd(fd, "\\n", 2);}else if(*str == '\t'){write_to_fd(fd, "\\t", 2);}else if(*str == '\\'){write_to_fd(fd, "\\\\", 2);}else{write_to_fd(fd, str, 1);}str++;}}
#define FT(x)int main(){int fd;char *str; char *str2;fd=open("Grace_kid.c",O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);if(fd<0){write(1,"Could not open file for writing.\nExiting.\n",42);return(0);}str="\n\n#include <unistd.h>\n#include <fcntl.h>\n#include <sys/stat.h>\n\n/*\n   Ugly uh ?\n*/\n\n#define write_to_fd(fd, str, len){write(fd,str,len);}\n#define write_no_real(str,fd){while(*str){if(*str == '\"'){write_to_fd(fd, \"\\\\\\\"\", 2);}else if(*str == '\\n'){write_to_fd(fd, \"\\\\n\", 2);}else if(*str == '\\t'){write_to_fd(fd, \"\\\\t\", 2);}else if(*str == '\\\\'){write_to_fd(fd, \"\\\\\\\\\", 2);}else{write_to_fd(fd, str, 1);}str++;}}\n#define FT(x)int main(){int fd;char *str; char *str2;fd=open(\"Grace_kid.c\",O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);if(fd<0){write(1,\"Could not open file for writing.\\nExiting.\\n\",42);return(0);}str=\"\";str2=str;write_to_fd(fd, str, 626);write_no_real(str,fd);write_to_fd(fd,str2+626, 110);return (0);}\n\nFT(1);\n";str2=str;write_to_fd(fd, str, 626);write_no_real(str,fd);write_to_fd(fd,str2+626, 110);return (0);}

FT(1);
