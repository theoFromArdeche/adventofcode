# 🎄 Advent of Code 2022 - Day 5 🎄

This repository contains the code for **Day 5**, written in **Objective-c**.

The code that solves the problem is in `solution.m`.

## 📥 How to Install GCC

To run this project, you need to have GCC with Objective-C support installed on your machine.

1. Visit the official GCC installation website:  
   [https://ftp.gnu.org/gnu/gcc/gcc-14.2.0/](https://ftp.gnu.org/gnu/gcc/gcc-14.2.0/)

2. Ask ChatGPT

3. Once GCC is installed, you can verify it by running:

   ```bash
   gcc -x objective-c -v
   ```
4. If you are on ubuntu install GNUstep to use the Foundation framework

   ```bash
   sudo apt install gnustep gnustep-devel gobjc
   ```
5. Ask ChatGPT if problems

6. Remove everything and don't ever code in Objective-c

## 🚀 How to Compile and Run the Code

1. **Compile the Objective-c code**:
   
   ```bash
   gcc `gnustep-config --objc-flags` -o solution solution.m `gnustep-config --base-libs ` -std=c11
   ```

2. **Run the compiled program**:

   ```bash
   ./solution
   ```