# Tsk-file
Header-only lib for creating, editing and readin '.tsk' file.
Created for my own use.

## The file structure:
```
1. [METADATA]
2.   format version
3.   key for encrypting
4.   username
5.   file creation date
6.   file last edit date
7.   type of the task (important, default...)

8. [MAIN-PART]
9.   title of the task
10.  text of the task (to EOF)
```

_'key for encrypting'_ encrypts only **Main Part** of file.
Whole file will be encrypting using **another key**. Now for encrypting uses a **XOR**.
