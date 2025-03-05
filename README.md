# Tsk-file
Header-only lib for creating, editing and readin '.tsk' file.
Created for my own use.

###The file structure:
```
[METADATA]
format version
key for encrypting
username
file creation date
file last edit date
type of the task (important, default...)
[MAIN-PART]
title of the task
text of the task (to EOF)
```

_'key for encrypting'_ encrypts only **Main Part** of file.
Whole file will be encrypting using **another key**. Now for encrypting uses a **XOR**.
