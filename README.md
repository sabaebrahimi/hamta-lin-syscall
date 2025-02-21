# Custom Linux Kernel Syscall - PID Checker  

## Overview  

This projects adds a new system call to the linux kernel which receives a file name and PID number as an input and chech wether the PID number exists in the file or not. If PID number exists, it returns `1`, else it saves the number in the file and returns `0`.

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
4. If the PID exists, the syscall returns `1`.  
5. If the PID is not found, it is appended to the file, and the syscall returns `0`.  

## Directory Structure  
.
 * [linux-6.13.3](./linux-6.13.3)
 * [patches](./patches)
   * [pid.patch](./patches/pid.patch)
   * [0001-Add-syscall.patch](./patches/0001-Add-syscall.patch)
   * [0002-Add-to-table.patch](./patches/0002-Add-to-table.patch)
   * [0003-Add-pid-file.patch](./patches/0003-Add-pid-file.patch)
 * [syscall_tester.c](./syscall_tester.c)

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
Open `syscall_tester.c` and change the file name to your own file name. 
Compile and run the test program:

```bash
gcc -o syscall_tester syscall_tester.c
./syscall_tester 
```
