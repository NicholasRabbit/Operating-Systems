### Lecture 1

#### Code examples 

##### copy.c

 `copy.c`. Note that the file descriptors are different in `copy.c` so that the content could be copied from one file to another. 

```c
/*
 * copy input to output
 * Since the console are the default input and output of a process,
 * this program read the arguments input by a user in a console and
 * print it to the same console. 
 */ 
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	char buf[64];
	while (1) {
		// 0 is the file descriptor for reading.
		// the console is attached to 0 by default. 
		int n = read(0, buf, sizeof(buf));	

		if (n <= 0)
			break;
		// 1 is the file descritpor for standard output.
		write(1, buf, n);
	}

	exit(0);

}

```



##### echo.c

(1) Why does the `i` start from 1 in the following `for` loop?

Because the first element `argc[0]` in `char *argc[]` is the name of the file to be executed, namely `echo.c`. The arguments which a user input in CLI start with index 1. (It is definitely necessary to learn C comprehensively.)

(2) How the "echo" redirect to a file when I input `echo hello world > a.txt`?

The `echo` doesn't parse `> < | &` and so forth. It is the shell (`sh.c`) that parses these symbols. When there is a `>`, shell will redirect the standard output to the file name follows it.  

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



#####  open.c

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

##### exec.c

(1) Why is the system call `exec(...)` followed by `printf("exec failed")` immediately without any condition? Does it execute all the time?

Because the system call `exec(...)` will return only if there is an error. Apparently, ` printf("exec failed!\n")` will be executed when it incurs an error in the system call `exec(...)`.

(2) Why is there an `exit(0)` after the `exec(...)` ? 

It is used to terminate the process after `exec` fails to avoid unexpected hazardous. 

```c
// exec.c: replace a process with an executable file
#include "kernel/types.h"
#include "user/user.h"

int
main()
{
  char *argv[] = { "echo", "this", "is", "echo", 0 };
  exec("echo", argv);   // output "this is echo" and the "argv[0]" is not displayed. 
  printf("exec failed!\n"); // This line of code will only run if exec() is failed.
  
  exit(0);
}
```

Note: `exec()` is normally run after a `fork()`, the former will discard all the data a child copied from its parent and replace it with an executable file. The child process will keep the its parents' file descriptor table.

The above program outputs "this is echo" without the first "echo" which is at `argv[0]` that represents the command's name. See the `user/echo.c`  in xv6 and the code about `main` in my C-code.

##### pipe1.c. 

```c

// pipe1.c: communication over a pipe

#include "kernel/types.h"
#include "user/user.h"

int
main()
{
  int fds[2];
  char buf[100];
  int n;

  // create a pipe, with two FDs in fds[0], fds[1].
  pipe(fds);
  
  write(fds[1], "this is pipe1\n", 14);  // "this is pipe1\n" are 14 letters in total.
  n = read(fds[0], buf, sizeof(buf));

  write(1, buf, n);

  exit(0);
}
```

##### pipe2.c 

```c

#include "kernel/types.h"
#include "user/user.h"

// pipe2.c: communication between two processes

int
main()
{
  int n, pid;
  int fds[2];
  char buf[100];
  
  // create a pipe, with two FDs in fds[0], fds[1].
  pipe(fds);

  pid = fork();
  if (pid == 0) {
    write(fds[1], "this is pipe2\n", 14);
  } else {
    n = read(fds[0], buf, sizeof(buf));
    write(1, buf, n);
  }

  exit(0);
}
```



##### redirect.c

See "Pipe" in Notes on Operating Systems for elaboration of this program. 

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
    // 
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

