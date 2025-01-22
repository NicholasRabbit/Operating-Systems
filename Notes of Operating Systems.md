## 6.S081 

### 0, Learning Tips

1. Learning pointers in C.
2. Read the [guidance](https://pdos.csail.mit.edu/6.828/2021/labs/guidance.html) before you do any lab.

### 1, What are operating systems? 

##### 1.1 Operating Systems

An operating system is kind of a collection of some basic functions which can share hardware among applications-which are that we, common users, actually use. 

Typically, there are two different spaces in a operating system. See Figure 1.1. Software 

![1730106917551](note-images/1730106917551.png)

##### 1.2 What is a kernel?

A kernel is a special programme which provides services to run programmes in user space. Each running programme, which is called a process, has memory containing instructions, data and a stack.  Normally, an operating system has only one kernel but has many process. 

### 2, Purposes of OS

**What the purposes for which these operating systems are made for?**

- Abstraction of hardware
- Multiply these hardware
  It offers a platform on which many applications such as text editors,  web browsers, and so forth could run at the same time, or likely at the same time.
- Isolated different applications when one of them breaks down others are not affected.
- Sharing data among applications. 
  For instance, we can transfer out file via email on a web browser. 
- Securing the users' data.
- Performance
  To help applications such as games perform well especially when you have bought rather expensive hardware.
- Other usage in wide range.

### 3, What is a Process?

Each application in user space is a process and have a unique process identifier(PID)