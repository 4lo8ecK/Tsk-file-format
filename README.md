# Tsk-file
**Header-only** lib for creating, editing and reading `.tsk` file. Is created for my own use.

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

Data from `key for encrypting` encrypts only `[MAIN-PART]`.
Whole file will be encrypted using **another key**.

## Versions
Curent one is `0.1`
If is opened a file with older version of the format and this file is edited -> data saves in newer version of the format.
Also there is an `Encode version` exept format version
### Format versions
```
0.1 - There is no encrypting
0.2 - For encrypting uses a XOR
0.3 - For encrypting uses an AES
0.4 - Text saves as RTF
```
### Encryption versions
```
1 - no encryption       - format ver 0.1
2 - XOR encryption      - format ver 0.2
3 - AES encryption      - format ver 0.3+
```
