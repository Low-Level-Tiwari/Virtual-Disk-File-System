
# Virtual Disk File System (VDFS)

## Overview

**Virtual Disk File System (VDFS)** is a lightweight filesystem designed for managing files on a virtual disk. It supports fundamental operations such as inserting, deleting, viewing files, and defragmenting storage to optimize space utilization.

## Features

- **Insert Files**: Add new files to the virtual disk.
- **Delete Files**: Remove files from the system.
- **View Files**: List stored files and their details.
- **Defragmentation**: Optimize disk space by reorganizing file storage.

## Installation

### Prerequisites

- A Linux-based environment (recommended)
- GCC or Clang for compiling the source code

### Build Instructions

1. **Clone the repository:**

   ```bash
   git clone https://github.com/Low-Level-Tiwari/Virtual-Disk-File-System.git
   cd Virtual-Disk-File-System
   ```

2. **Compile the project:**

   ```bash
   make
   ```

## Usage

After compilation, you can run the VDFS program using:

```bash
./vdfs
```

The system provides a menu-driven interface to interact with the filesystem.

## Commands

### Creating a Virtual Disk

```bash
./vdCreate vdisk 1024
```
This creates a virtual disk named `vdisk` with a size of 1024 units.

### Inserting Files

```bash
./vdAdd vdisk file 25
./vdAdd vdisk context 336
./vdAdd vdisk file2 18
./vdAdd vdisk file3 207
```
These commands insert files into the virtual disk, where the number represents the file size.

### Viewing Files

```bash
./vdls vdisk
```
This lists all files stored in the virtual disk.

### Deleting Files

```bash
./vdDelete vdisk file
```
This removes the specified file from the virtual disk.

## Future Enhancements

- **File Encryption**: Implement encryption for file security.
- **Hierarchical Directories**: Support for directory structures.
- **Cross-Platform Compatibility**: Extend compatibility with different platforms.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.

## Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request.

## Contact

For any inquiries or discussions, reach out via GitHub Issues.

---

Developed by Piyush Tiwari and Meghansh Tyagi.
