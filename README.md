# ToniOS
This Operating System is a minimalistic hobby os make by me and the help of artifacts.
The os has at the moment a keyboard driver (whit one issuse) and the needed functions to print something out on the display.

#### Install Depencis
You can easily install all depencys just run following command:

    sh install.sh
 #### Build
 When you want to build the operating system, you only have to run
 

    make clean
    make
Than the iso image is in the iso/ folder and Qemu (a virtuall machine) starts.

### How to edit
When you want to create your own operating system with the basis of this operating system, you must know the folder structure and what file what does.
All folders are so created that the name say something.
As example, in the libc folder are the c libarys. In there are two subfolders. The in the include subfolder are the header files and in the src subfolder are the .c and .cpp files.