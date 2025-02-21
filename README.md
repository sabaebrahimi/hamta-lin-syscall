# Custom Linux Kernel Syscall - PID Checker  

## Overview  

This project introduces a custom system call to the Linux kernel that checks if a given process ID (PID) is present in a specified file. If the PID is found, the syscall returns `true`; otherwise, it writes the PID to the file and returns `false`.  

This repository contains:  
- A test program (`syscall_tester.c`) to validate the new syscall  
- Kernel patches stored in the `patches/` directory  
- A modified Linux kernel (`linux-6.13.3`) as a Git submodule  

## How It Works  

1. The new syscall takes:  
   - A user-provided PID  
   - A syscall identifier  
   - A filename to check  

2. The syscall attempts to open the specified file in kernel space.  
3. It reads the file contents and checks if the given PID is already present.  
4. If the PID exists, the syscall returns `true`.  
5. If the PID is not found, it is appended to the file, and the syscall returns `false`.  

## Directory Structure  

├── linux-6.13.3
├── patches
└── syscall_tester.c

## Installation  

### 1. Clone the Repository  

```bash
git clone --recurse-submodules https://github.com/sabaebrahimi/hamta-lin-syscall
cd hamta-lin-syscall
```

### 2. Apply Kernel Patches
If not already applied, you can manually patch the kernel:
```bash
cd linux-6.13.3
git apply ../patches/0001-Add-syscall.patch
git apply ../patches/0002-Add-to-table.patch 
git apply ../patches/0003-Add-pid-file.patch
```

### 3. Build the Kernel
Add your .config file and make the kernel:
```bash
cd linux-6.13.3
make -j$(nproc)
```

### 4. Reboot Virtual Machine
### 5. Test the Syscall
Compile and run the test program:

```bash
gcc -o syscall_tester syscall_tester.c
./syscall_tester 
```
