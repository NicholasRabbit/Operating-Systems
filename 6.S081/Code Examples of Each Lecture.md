### Lecture 1

#### Code examples 

##### copy.c

 `copy.c`. Note that the file descriptors are different in `copy.c` so that the content could be copied from one file to another. 

```c
// copy.c: copy input to output.

#include "kernel/types.h"
#include "user/user.h"
int
main()
{
  char buf[64];
  while(1){
    int n = read(0, buf, sizeof(buf));  // Read from a file with file descriptor 0.
    if(n <= 0)
      break;
    write(1, buf, n); // Write content from buf to a file whit file descriptor 1.
  }
  exit(0);
}
```

```c
// Here are system calls called by 'copy.c': read(...) and write(...)
int read(int fd, char *buf, int n);
int write(int fd, char *buf, int n);
```

##### echo.c

`echo.c`

Why does the `i` start from 1 in the following `for` loop?

Because the first element `argc[0]` in `char *argc[]` is the name of the file to be executed, namely `echo.c`. The arguments which a user input in CLI start with index 1. (It is definitely necessary to learn C comprehensively.)

```c
#include "kernel/types.h"
#include "user/user.h"
int
main(int argc, char *argv[])
{
  int i;
  for(i = 1; i < argc; i++){
    write(1, argv[i], strlen(argv[i]));
    if(i + 1 < argc){
      write(1, " ", 1);
    } else {
      write(1, "\n", 1);
    }
  }
  exit(0);
}
```



(3) `open.c`

`O_WRONLY | O_CREATE` is from `kernel/fcntl.h`.

```c
// open.c: create a file, write to it.
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main()
{
  int fd = open("output.txt", O_WRONLY | O_CREATE);
  write(fd, "ooo\n", 4);

  exit(0);
}
```

(4) `exec.c`

Why is the system call `exec(...)` followed by `printf(...)` immediately without any condition? Does it execute all the time?

Because the system call `exec(...)` will return only if there is an error. So it doesn't always execute.

Apparently, ` printf("exec failed!\n")` will be executed when it incurs an error in the system call `exec(...)`.

```c
// exec.c: replace a process with an executable file
#include "kernel/types.h"
#include "user/user.h"

int
main()
{
  char *argv[] = { "echo", "this", "is", "echo", 0 };
  exec("echo", argv); 
  printf("exec failed!\n"); // This line of code will only run if exec() is failed.
  
  exit(0);
}
```

Note: `exec()` is normally run after a `fork()`, the former will discard all the data a child copied from its parent and replace it with an executable file. The child process will keep the its parents' file descriptor table.

(5) `redirect.c`  

See "Pipe" in Notes on Operating Systems

```c
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

// redirect.c: run a command with output redirected

int
main()
{
  int pid;

  pid = fork();
  if(pid == 0){
    close(1);  // Close file descriptor 1, namely the output file.
    open("output.txt", O_WRONLY|O_CREATE);

    char *argv[] = { "echo", "this", "is", "redirected", "echo", 0 };
    exec("echo", argv);
    printf("exec failed!\n");
    exit(1);
  } else {
    wait((int *) 0);
  }

  exit(0);
}
```

