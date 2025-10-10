# CSCI 235 - The Directory Daemon:

## Project 3

### Disclaimer

Obligatory disclaimer.

Yes, Linked List implementations are common and easily-accessible. We are keenly aware of that. For _your_ benefit, I would encourage you to work through the insert / delete algorithms **on pen & paper** and **code them up yourself**. Trust me, technical interviews are expecting that you know how to work _with the nodes of LinkedLists_ -- while it's not the most riveting of tasks, it's essential. I'm being serious, like literally look up on Leetcode (this is one of the standard technical question practice platforms) they have an entire category for just LinkedLists.

TLDR: Don't copy/GPT this! If you're having trouble, spend the time now, so you can get the job later!

### New Additions & Constructs

Here are some things we've added in the givens, to help you.

#### File `operator<<`

In a sentence, allows you to print files, instead of using a `toString()` method. That is, you can do the following:

```c++
File a;
std::cout << a << std::endl; // Prints "New_Text_Document.txt"
```

#### Usage of `size_t`

Surely, you've gotten a compiler warning like:

```bash
conversion from 'size_t' to 'int', possible loss of data
```

or...

```bash
warning: comparison between signed and unsigned integer expressions
```

when you're using a loop like `for (int i = 0; i < vector.size(); i++)`.

That's because integers are the wrong type of variable when you're iterating through containers.

Unlike Python (guh), in C++ you can't access with negative numbers (eg. `vector[-1]`). But `int` in C++ can very easily hold values like -1.

So the solution is to use "unsigned" numbers. Hence we introduce `size_t` (from the `<cstddef>` header). There's a little bit more than that but...

TLDR: Use these when you're making variables for indicies of a container.

Learn more here: https://stackoverflow.com/questions/1951519/when-to-use-stdsize-t

#### LinkedList Copy Constructor & Assignment Operator

In a nutshell they're to prevent errors with shallow copies, since we use pointers. Don't worry about the syntax as much as the reason they're there,
which is outlined nicely in this article: https://www.geeksforgeeks.org/cpp/shallow-copy-and-deep-copy-in-c/

#### MOST IMPORTANTLY -- ADDRESS SANITIZATION

You will be working with raw pointers (unfortunately). Programmers are human, so we build tools to make up for the more human error side to it. ASan is one of those tools.

That is, ASan (or Address Sanitization) is a tool so you can detect memory-related errors (eg. double-frees, leaks, etc.). **Use it.**

To do so:

1. Add the following flag to the `CXXFLAGS` variable in the `Makefile`: `-fsanitize=address`
2. Run `make` as usual
3. Profit

Write a two-liner in a `main.cpp` that has a memory leak, and you'll see what I'm talking. Thank me later!

Read a more robust explanation here: https://www.osc.edu/resources/getting_started/howto/howto_use_address_sanitizer

#### Imports

Because I know some people will do this, don't include the Text, Image, or Loader headers, unless in your `main.cpp`. You're not working with them-it's just solution code from the previous project.

### Task 1 - The Most Linked of Lists

You've seen Linked Lists, so do the ask is pretty straightforward (though insert and erase are easier said than done).

The Node struct & constructors are setup for you, so to prevent errors with the code that's already been given, don't rename the private members.

Anywho, go wild:

```c++
/**
 * @brief Returns the number of elements in the list.
 * @return The number of elements (size_t).
 */
size

/**
 * @brief Checks if the list is empty (ie. contains no elements).
 * @return true if the list is empty, false otherwise.
 */
empty

/**
 * @brief Access the node pointing to the head of the linked list
 * @return A pointer to the head node (or nullptr if the list is empty)
 */
head

/**
 * @brief Access the first element.
 * @return The first element's value (of type T, NOT the node).
 * @throws std::runtime_error if the list is empty.
 */
front

/**
 * @brief Access the last element.
 * @return The last element's value (of type T, , NOT the node).
 * @throws std::runtime_error if the list is empty.
 */
back

/**
 * @brief Access an element at a specific index.
 * @param index The zero-based index of the element (size_t).
 * @return The element's value at the given index (of type T).
 *
 * @throws std::out_of_range if the index is invalid (eg. too large).
 */
at

/**
 * @brief Adds an element to the end of the list.
 * @param value A const reference to the value (of type T)
 * to add to the end of the list
 */
push_back

/**
 * @brief Inserts an element at a specific index.
 * @param index The zero-based index to insert at (as a size_t).
 * @param value A const reference to the value (of type T) to insert.
 *
 * @throws std::out_of_range if the index is strictly greater than the size
 * @note That is, if we insert at index 1 when we have a list of length 1,
 *    that's fine! We just insert at the end. Inserting at index 2 would raise
 *    an error though.
 */
insert

/**
 * @brief Erases an element at a specific index.
 * @param index The zero-based index of the element to erase (as asize_t).
 *
 * @throws std::out_of_range if index is greater than or equal to the size
 */
erase

/**
 * @brief Removes all elements from the list.
 */
clear

/**
 * @brief Destructor: cleans up all nodes to prevent memory leaks.
 */
~LinkedList
```

As usual, some helpful links:

1. [C++ Destructors](https://www.geeksforgeeks.org/cpp/destructors-c/) for syntax
2. [Throwing Errors](https://www.geeksforgeeks.org/cpp/how-to-throw-an-exception-in-cpp/)

### Task 2 - Origami

I lied. It's not origami. We're making a _fold_ er (get it? ...no? fine, whatever).

#### VectorFolder

Ok so, we're going to take a breather from the LinkedLists and go back to vectors for a brief moment. We use it as the underlying container to implement a type of collection for our `File` objects called a `VectorFolder`.

First add your private member:

```c++
/// A vector of files added to this folder
std::vector<File> files_;
```

Then implement the constructor:

```c++
/**
 * @brief Default constructor.
 *
 * Initializes an empty VectorFolder with no files.
 */
VectorFolder
```

Now introduce a private helper function, to use within your accessors.

```c++
/**
 * @brief Finds the index of a file with the given filename.
 * @param filename The name of the file to search for.
 *
 * @return The zero-based index of the file if found;
 * otherwise, returns the size of the internal vector
 * (i.e. an index which is out of bounds of the actual vector).
 */
VectorFolder::indexOf
```

And now, finally, your accessors & add/delete operations.

```c++
/**
 * @brief Gets the total number of files currently in the folder.
 * @return The count of files as a size_t.
 */
VectorFolder::getFileCount

/**
 * @brief Searches for a file by its name.
 * @param filename The name of the file to find, as a const reference to a string
 *
 * @throw std::runtime_error If the file is not found in the folder.
 * @return The file whose filename matches exactly, within the folder's files.
 */
VectorFolder::findFile

/**
 * @brief Adds a new file to the folder.
 *
 * The file will not be added if a file with the same name already exists.
 *
 * @param file The File object to be added as a const reference.
 * @return True if the file was successfully added, false otherwise.
 */
VectorFolder::addFile

/**
 * @brief Removes a file from the folder by its name.
 *
 * The file will not be removed if a file with the same name does NOT exist in the collection.
 *
 * @param filename The name of the file to remove, as a const. ref. to a string
 * @return True if the file was found and removed, false otherwise.
 */
VectorFolder::removeFile

/**
 * @brief Access the underlying files vector
 * @return A vector of File objects representing the files in the VectorFolder
 */
VectorFolder::getFiles
```

#### LinkedFolder

Now, do the same, but this time using your freshly-baked LinkedList for `files_` within the `LinkedFolder`.

**Importantly:** If you designed your `VectorFolder` using `getIndexOf` for all of your internal accesses, you can effectively just `CTRL+F` & `replace` `VectorFolder` with `LinkedFolder` (with like 2 more line changes), after implementing the `indexOf` method for `LinkedFolder`.

So code up this private member:

```c++
/**
 * @brief Finds the index of a file with the given filename.
 * @param filename The name of the file to search for.
 *
 * @return The zero-based index of the file if found;
 * otherwise, returns the size of the internal LinkedList
 * (i.e. an index which is out of bounds of the actual LinkedList).
 */
LinkedFolder::indexOf
```

And implement the rest of the class:

```c++
/**
 * @brief Gets the total number of files currently in the folder.
 * @return The count of files as a size_t.
 */
LinkedFolder::getFileCount

/**
 * @brief Searches for a file by its name.
 * @param filename The name of the file to find, as a const reference to a string
 *
 * @throw std::runtime_error If the file is not found in the folder.
 * @return The file whose filename matches exactly, within the folder's files.
 */
LinkedFolder::findFile

/**
 * @brief Adds a new file to the folder.
 *
 * The file will not be added if a file with the same name already exists.
 *
 * @param file The File object to be added as a const reference.
 * @return True if the file was successfully added, false otherwise.
 */
LinkedFolder::addFile

/**
 * @brief Removes a file from the folder by its name.
 *
 * The file will not be removed if a file with the same name does NOT exist in the collection.
 *
 * @param filename The name of the file to remove, as a const. ref. to a string
 * @return True if the file was found and removed, false otherwise.
 */
LinkedFolder::removeFile

/**
 * @brief Access the underlying files linked list
 * @return A LinkedList of File objects representing
 * the files in the LinkedFolder
 */
LinkedFolder::getFiles
```

## Submission, Testing, & Debugging

You will submit your solution to Gradescope via GitHub Classroom. The autograder will grade the following files:

```

1. LinkedFolder.cpp
2. LinkedFolder.hpp
3. VectorFolder.cpp
4. VectorFolder.hpp
5. LinkedList.cpp
6. LinkedList.hpp

```

Although Gradescope allows multiple submissions, it is not a platform for testing and/or debugging, and it should not be used for that purpose. You MUST test and debug your program locally.

**To help prevent over-reliance on Gradescope for testing, only 5 submissions per day will be allowed.**

Before submitting to Gradescope, you MUST ensure that your program compiles using the provided Makefile and runs correctly on the Linux machines in the labs at Hunter College. This is your baseline—if it runs correctly there, it will run correctly on Gradescope. If it does not, you will have the necessary feedback (compiler error messages, debugger, or program output) to guide you in debugging, which you don’t have through Gradescope. “But it ran on my machine!” is not a valid argument for a submission that does not compile. Once you have done all the above, submit it to Gradescope.

### Testing: Compiling with the Included `Makefile`

\*For your convenience, we've included a `Makefile`, which allows you to quickly re-compile your code, instead of writing `g++` over and over again. **It also ensures that your code is being compiled using the correct version of C++. And by correct one, we mean the one the auto-grader uses.\***

In the terminal, in the same directory as your `Makefile` and your source files, you can use the following commands:

```bash
make # Compiles all recently modified files specified by the OBJs list
make clean # Removes all files ending in .o from your directory, ie. clears your folder of old code
make rebulild # Performs clean and make in one step
```

This assumes you did not rename the Makefile and that it is the only one in the current directory.

### Debugging

_Here are some quick tips, in case you run into the infamous "It compiles on my machine, but not on Gradescope"_

1. Ensure your filenames are correct (case-sensitive), and don't contain leading / trailing spaces
2. Ensure that your function signatures are correct (ie. function name spelling, order/type of the parameters, return type).
   **This also includes `const` declarations. Remember, if a function does _not_ modify the underlying object, it must be declared `const`.**

---

### Grading Rubric

- **Correctness:** 80% (distributed across unit testing of your submission)
- **Documentation:** 15%
- **Style and Design:** 5% (proper naming, modularity, and organization)

---

### Due Date

This project is **due on October 21**.
_No late submission will be accepted._

---

### Important Notes

You must start working on the projects as soon as they are assigned to detect any problems and to address them with us well before the deadline so that we have time to get back to you before the deadline.

**There will be no extensions and no negotiation about project grades after the submission deadline.**

---

### Additional Help

Help is available via drop-in tutoring in Lab 1001B (see Blackboard for schedule). You will be able to get help if you start early and go to the lab early. We only a finite number of UTAs in the lab; **the days leading up to the due date will be crowded and you may not be able to get much help then.**

Authors: Daniel Sooknanan (amogus??)
