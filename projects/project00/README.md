# PROJECT 0: Setup & Hello World

If you're using VsCode you can view this `README` file with better clarity using `Ctrl,Shift,V` at the same time

## A Brief Overview
Welcome to your very first project of the semester! The goal of **Project 0** is simple: ensure you’re fully set up with GitHub Classroom, familiarize yourself with the **Makefile** provided, and compile your a C++ program. 

Please DO NOT SKIP ANY PARTS OF THIS PROJECT, COMPLETE THE ENTIRE THING YOURSELF if you want to make sure that you will be able to solve and debug the other projects by their deadlines.

By the end, you’ll have a firm grasp on the class workflow: from accepting an assignment in GitHub Classroom, to cloning your repository, to writing some code, to compiling via the terminal using `make`. Simple, but crucial steps for your success in future projects!

## Step-By-Step: Setting Up for Success
This project is designed to get you comfortable with the infrastructure of our course. You’ll learn how to clone repositories, compile via a Makefile, and push your code back to GitHub. If you’re new to C++ or haven’t used the command line much, this will give you a great practice run.

---

## Task 1: Getting Started with GitHub Classroom

<span style="color:teal">
<b>[IMPORTANT]</b> Do not skip this step. Otherwise, you’ll be ill-positioned to do this (or future) projects. You should not write and update your code directly on github, you must clone it onto your device first.
</span>

1) If you don’t already have one, [go to GitHub](https://github.com) and create a GitHub account. **You will likely use your GitHub account professionally in the future, so choose a username you will want to keep.**

2) Next, watch or review the following videos if you need a refresher on Git and GitHub:
   * [An Introduction to GitHub](https://www.youtube.com/watch?v=MJUJ4wbFm_A)
   * Or if you're in a rush: [Git Explained in 100 Seconds](https://www.youtube.com/watch?v=hwP7WQkmECE)
   * For a more step-by-step approach: [Using GitHub from start to finish](https://www.youtube.com/watch?v=-RCnNyD0L-s)

3) **Accept the Project 0 GitHub Classroom assignment via this link**: [Link](https://classroom.github.com/a/wjC4jYta)
   * Follow the steps to create a repository under your GitHub account specifically for this project.  
   * Refer to this tutorial if you need help with GitHub Classroom: [GitHub Classroom Tutorial](https://www.youtube.com/watch?v=AHDCokfgcSo)

5) After accepting, **clone the repository** to your local machine. This will give you a local copy where you can edit files, compile your code, and eventually push your changes. Here's a [github guide](./Github.pdf)!

---

#### Additional Resources if You’re Brand-New to C++:
* [TheNewBoston’s C++ Playlist](https://www.youtube.com/playlist?list=PLAE85DE8440AA6B83)  
*(You won’t need all the details from these resources just yet, but they are helpful references.)*

---
### Documentation Requirements

For **ALL** projects, including this one, part of your grade will be points for documentation. These are the requirements:

1. **File-level Documentation**  
   All source files (`.hpp`, `.cpp`, etc.) must have a comment at the top with:
   - Your name  
   - Date  
   - A brief description of what the file does  

2. **Function-level Documentation**  
   Each function should include a brief comment describing its purpose. Later projects will involve param/return tags in the documentation, but this starting project will not.

---
## Task 2: Writing a Simple “Hello, World!” Program

1) In your **cloned** repository, create files named `Greeter.hpp` and `Greeter.cpp`.  
2) Implement the following simple C++ program with separate files for a header (`.hpp`) & source (`.cpp`),.

**Greeter.hpp**  
```c++
// File: Greeter.hpp
// Author: Your Name
// Date: (today's date)
// A header file containing a function declaration for returning "Hello, World!"

#ifndef HELLO_WORLD_HPP
#define HELLO_WORLD_HPP

#include <iostream>
#include <string>

std::string greet();

#endif // HELLO_WORLD_HPP
```

**Greeter.cpp**  
```c++
// File: Greeter.cpp
// Author: Your Name
// Date: (today's date)
// A source file that defines a function to return "Hello, World!"

#include "Greeter.hpp"

std::string greet() {
    return "Hello, World!";
}

```

3) Create a `main.cpp` file and call your newfangled function within it (as you've done in 135).

5) Test your code locally by using `make` to compile (see section below, you'll probably need to install it)

6) **Commit your code** locally, then **push** it to GitHub. 

---

## Task 3: Using the Provided Makefile

Here is a [guide to makefiles](./Make.pdf). This repository comes with a `Makefile` that helps you compile your code more easily. Instead of using g++ in the terminal, you can simply type:

```bash
make
```
This command will look for a `Makefile` in the current directory and compile the project using the rules specified within it. Other useful make commands include:

```bash
# Removes .o files (object files) and clears out old build artifacts
make clean    

# Cleans, then re-runs make
make rebuild  
```

[ENVIRONMENT NOTE] If you have any issues installing or using `make` on your own machine (e.g., if you’re on Windows or macOS without Xcode command-line tools), please see below: 

1. See <a href="https://stackoverflow.com/questions/29592943/makefile-without-xcode-on-mac">(Mac) Make Without Xcode</a>
2. See <a href="https://learn.microsoft.com/en-us/windows/wsl/install">(Windows) Installing Windows Subsystem for Linux (aka WSL)</a>. Then:

a. Open a Powershell or Command Line window on your computer 

b. Run `bash` to use the Linux subsystem

c. Run the following:

```bash
sudo apt-get update # Updates your systems package manager
sudo apt-get install build-essential # Installs make & the compiler
```
(For you Windows users like myself, WSL is a must-have for ANY development nowadays)

By using the `Makefile`, you ensure that your code is built consistently with the same settings our autograder uses. If you do not use the Makefile to verify compilation, then there is a high chance that your code will not compile when you attempt to submit on gradescope.

---

## Task 4: Testing Your Program
This is a trivial program, but testing is still important:

1) **Compile** with `make`.
2) **Run** the resulting binary (which will be named test with the provided Makefile). For example:
    ```
    ./main
    ```
3) Confirm that “Hello, World!” returns from the function, by making a `main.cpp` file that calls your function.

That’s it! You’ve successfully built and run your first program in our environment.

---

## Task 5: Submission
You will submit your solution to Gradescope via GitHub Classroom. The autograder will look for and compile your `Greeter.hpp` and `Greeter.cpp`.  

Although Gradescope allows multiple submissions, it is **not** a platform for testing or debugging. You **MUST** test and debug your program locally.  

**For future projects, only 5 submissions per day** are allowed. This project will be unlimited since it is an introduction.

Before submitting, be sure that:
1. Your code compiles via the provided `Makefile`.
2. It runs correctly on the Linux machines in the labs at Hunter College (if applicable).

**“But it ran on my machine!”** is not a valid argument for broken submissions. [Here](./Common%20Compilation%20Errors.pdf) is an almost exhaustive list of compilation errors. 

Once you have verified all the above, submit to Gradescope.

---

### Grading Rubric

- Please note that submission of this introductory project is required, while the project is worth one point.
- **Correctness:** 100%  
  Your program should compile, run, and the function should return“Hello, World!” exactly.  

---

### Important Notes
- We strongly encourage you to start early, so any issues with setup can be resolved well before the deadline.
- There will be **no extensions** and **no negotiation** about project grades after the submission deadline.

---

### Additional Help
Help is available via drop-in tutoring in Lab 1001B (see Blackboard for the schedule). Remember, the lab can get crowded as due dates approach, so coming early is your best strategy.

Authors: Michael Russo, Daniel Sooknanan, Georgina Woo, Prof. Maryash, Prof. Tojeira

Credit to Prof. Ligorio
