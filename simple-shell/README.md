# Simple-Shell

source: 

Operating Systems Concepts, 10th edition -- Silberchatz

Chapter 3 (pg. P-12) -- Programming Project 1


## Problem

This project is organized into several parts: 
1. Creating the child process and executing the command in the child 
2. Providing a history feature
3. Adding support of input and output redirection
4. Allowing the parent and child processes to communicate via a pipe

see Silberchatz pg P-12 for further details




## Relevant Information

### Unix and Operating Systems Concepts

#### 1. Child Process and Parent Process
+ fork()
+ wait() or waitpid() -- used by parent
+ pid - process id

#### 2. History Feature

#### 3. Input and Output Redirection
+ open()
+ close()
+ fd[] - file descriptor
+ dup2()

see also -- file permissions O_RDONLY, 0644

#### 4. Piping

+ buffer - read end and write end


### C Library

#### String Functions

+ strtok or strtok_r. -- used to parse input string
+ strcmp -- compare string values


## Known Issues

+ does not compile. still implementing.
+ did not implement history at all
