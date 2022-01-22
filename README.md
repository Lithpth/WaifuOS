# WaifuOS
Operating system for my waifu ♥

<h2>Introduction</h2>
This operating system is a bit of a joke, as well as an opportunity for me to learn about OS development.

WaifuOS is a x86-64 operating system so make sure you have correct CPU dummy >~<

<h2>Compiling from source</h2>
<h3>Linux Users</h3>

Do the git clone thingy in console haha ok good.

Compilation (Bootloader): 

  1. cd to Bootloader
  2. do make all
  3. wow cool

Compilation (Kernel): 
  
  1. cd to Kernel
  2. Do ./setup
  3. Do ./build
  4. Image can be found in Kernel/bin/WaifuOS.img it can be flashed to a USB and booted as an EFI application

<h3>Windows Users</h3>
<h4>Note: You must have WSL installed</h4>

Clone the repo (Code -> Download ZIP) and extract it somewhere

Compilation (Bootloader): 

  1. cd to Bootloader
  2. Open cmd
  3. Run wsl make all
  4. Wow cool

Compilation (Kernel): 
  
  1. Navigate to Kernel
  2. Run setup.bat
  3. Run build.bat
  4. Image can be found in Kernel/bin/WaifuOS.img it can be flashed to a USB and booted as an EFI application

<h2>Running in QEMU</h2>
Windows users can (assuming you have QEMU installed correctly) simply double click run.bat in the Kernel folder

Linux users:

  1. cd into Kernel
  2. Do make run
  3. waifus (maybe)

# I'm getting tired of writing a readme so im done
