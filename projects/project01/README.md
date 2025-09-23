# CSCI 235 - The Directory Daemon:

## Project 1: Filing our Data

This time, we'll be doing a recap of 135 & OOP, with a little bit of a twist.

**This project may get a little involved. Be sure you work incrementally and do _not_ wait until the deadline to start.**

In this project you will:

1. Implement the File class to get you back in the swing of C++ coding
2. Work a little with the STL & the `<chrono>` library (don't worry!)

---

### Before You Continue

Work through the tasks sequentially (implement AND test). Only move on to a task when you are positive that the previous one has been completed correctly.

**Be sure to _read the specs clearly and pay special attention to the links_ (they shouldn't take very long). If you're just winging it, you might have a harder time. Trust me!**

#### Don't Forget!

1. Names of classes and methods must exactly match those in this specification
2. Functions that _do not_ modify the object must be declared `const`.
3. Use constant references if the function calls for it! If you don't know what that means, see [here](https://www.geeksforgeeks.org/cpp/const-reference-vs-normal-parameter-passing-in-cpp/).
4. Document your code! The doc requirements still apply!
5. Do NOT use namespace `std`.

---

## Task 1: Creating `FileUtils`

Boot up your IDE of choice, we're coding now. We'll start by making some utility functions to make your life easier later.

**In this task you'll be modifying the following provided files:**

1. `FileUtils.hpp`
2. `FileUtils.cpp`

Since this is just for utility, we don't need a class. However, we do want to keep things organized. That's why we'll define all such functions in the `FileUtils` namespace (instead of just leaving them out and about).

**Important**: That means that whenever calling these functions, you must use the `FileUtils::` namespace (e.g. `FileUtils::myFunction()`), instead of just `myFunction()`.

### Part A: Implementing `findFileExtension`

All you need to do is use the spec to write the function header in the `.hpp` file and then implement it in the `.cpp`. See below on the behavior.

**Remember the function name must match entirely, case and all.**

```c++
/**
 * Extracts the file extension from a given filename.
 *
 * We define the file extension as the string containing:
 * 1. The last period within the filename
 * 2. All characters after that period
 *
 * @pre Assume the given filename has no spaces
 * @param filename A const reference to a string representing the filename from which to find the extension.
 * @return A string containing the extracted file extension or an empty string if:
 *  1. No extension is found
 *  2. The filename is empty.
 */
FileUtils::findFileExtension
```

Once you're done, write a `main` file to test your code! Remember you should call this function by saying `FileUtils::findFileExtension("whatever_your_test_case_is")`.

### Part B: Implementing `hasWhitespaces`

Same thing here. Add the function signature to the `.hpp` and implement it within the `.cpp`.

You will find the link I've attached with `@see` to be VERY helpful. Just make sure to include the correct library in your `FileUtils.hpp` file.

```c++
/**
 * Checks if a given filename contains any whitespace characters.
 *
 * A whitespace character is any character matching the STL documentation in the link below.
 *
 * @param filename A const reference to a string representing the filename to check for spaces.
 * @return true if the filename contains one or more whitespace characters, false otherwise.
 * @see https://en.cppreference.com/w/cpp/string/byte/isspace.html
 */
FileUtils::hasWhitespaces
```

## Task 2: Creating the `File` class

Ok so we have these utilities. Now we gotta use them.

Before we get into this, I'm just going to put these here for you, because I'm nice (you're welcome):

1. [Default Parameters](https://www.geeksforgeeks.org/cpp/default-arguments-c/)
2. [Default & Parameterized Constructors](https://www.geeksforgeeks.org/cpp/constructors-c/)
3. [The Best Way to Make a Constructor (initializer lists)](https://www.geeksforgeeks.org/cpp/when-do-we-use-initializer-list-in-c/)
4. [Const Functions](https://www.geeksforgeeks.org/cpp/const-member-functions-c/)

### Part A: Setting Up the Class

#### Basic Private Members

Ok since you're experts on making classes by now (or idk maybe you're rusty -- that's fine, I was on summer break too, just reference the links above), setup the `File` class with the following private members.

```c++
filename_ // A string containing the filename of the File object
readable_ // A boolean containing the `read` permission of the File
writeable_ // A boolean containing the `write` permission of the File
```

#### Constructors

##### Default Constructor

This ones super simple:

```c++
/**
 * Constructs a new File object.
 *
 * @post
 * Sets the File's filename_ to "New_Text_Document.txt"
 * Sets all boolean members to true.
 */
```

##### Parameterized Constructor

This one's a little more involved, but just make sure to use the utility functions we made before. It should be pretty short -- just make sure to test!

```c++
/**
 * Constructs a new File object.
 *
 * @param filename   A const reference to a string for the initial filename
 * @param isReadable A const reference to a boolean for the readable permission
 * @param isWritable A const reference to a boolean for the writable permission
 *
 * @post
 * All booleans should have a default value of true (ie. use true if they are omitted).
 *
 * Sets the File's filename_ such that:
 * 1. If the parameter contains spaces or has no characters at all, the default filename is used
 * 2. If the parameter has no extension (no `period` characters whatsoever), .txt is appended to the filename & used
 * 3. If the parameter has an empty extension (a `period` characters followed by no characters), txt is appended to the filename & used
 * 4. Otherwise, the parameter filename is used as is
 * Note: A filename like `.env` or `.log` IS allowed (ie. filenames containing only the extension)!
 */
```

### Part B: Getters & Setters for Trivial Data Types

Now that we have private members, you'll need to get and set them.

**Remember:**

1. Getters _don't_ modify the object, so we declare the function const (see the links above if you don't know what I'm talking about).
2. If a function doesn't have a return it returns `void`.

#### `readable_` & `writable_` Getters & Setters

We'll start simple. Just make two basic getters & setters for `readable_` and `writable_`. Nothing fancy.

```c++
 /**
 * Retrieves the current readable permission as a boolean.
 * @return The value stored in `readable_`
 */
isReadable

/**
 * Sets the readable permission of the File object.
 *
 * @param new_permission A const reference to a boolean for the new readable permission
 * @post
 * 1. The readble member is set to the value of the parameter
 * 2. (more to come in a later task)
 */
setReadable

/**
 * Retrieves the current writable permission as a boolean.
 * @return The value stored in `writable_`
 */
isWritable

/**
 * Sets the writable permission of the File object.
 *
 * @param new_permission A const reference to a boolean for the new writable permission
 * @post
 * 1. The writable member is set to the value of the parameter
 * 2. (more to come in a later task)
 */
setWritable
```

#### Getting & Setting the Filename

Now we'll move onto something a little more difficult:

```c++
/**
 * Retrieves the current filename as a string.
 */
getFilename

/**
 * Attempts to set a new filename for the File object.
 * The operation FAILS if:
 * 1. The passed filename is empty or contains spaces
 * 2. The extension of the old and new filenames are not equal.
 * Note: Do not append a default extension to the parameter!
 *
 * @param filename A const reference to a string for the new filename.
 * @return true if the filename was successfully updated, false otherwise.
 * @post
 * 1. If possible, the filename variable is set to that of the parameter
 * 2. If the filename was modified, the last modified attribute is updated to the current system time
 */
setFilename
```

#### Helping You Test (Optional)

At this point you _should_ be testing your code.

We're not checking that you have this -- but hey you never know what might be on a test. You might find it useful to write a `toString()` method for File.

You could totally use string concatenation, but using [string streams](https://www.geeksforgeeks.org/cpp/stringstream-c-applications/) is cleaner.

```c++
std::string File::toString() const
{
    std::stringstream ss;
    ss << "Filename: " << filename_ << std::endl;
    ss << "Read: " << (readable_ ? "y" : "n") << std::endl;
    ss << "Write: " << (writeable_ ? "y" : "n") << std::endl;

    return ss.str();
}
```

### Part C: Time to Make it Interesting

Okay now we're at the final part.

Quick Disclaimer: This isn't supposed to trick you -- just to get you used to using the STL (Standard Template Library) & reading documentation.

In the `FileUtils.hpp` you'll see that we've created a namespace alias `cr` for `std::chrono` and a type alias `timestamp` for `cr::time_point<cr::system_clock>`. This allows us to use `cr` instead of `std::chrono` and `timestamp` instead of the full type name, making the code more readable.

#### Useful Links

1. [How to Get the Current Time](https://en.cppreference.com/w/cpp/chrono/time_point.html) (see the code block)

#### 1. Adding the `last_modified` Member

Now we'll add a private member to the File class of type `timestamp`. Do NOT modify any of your constructor's function signatures -- only add to the body and initialize it to the current time on the system.

##### Defining the Member

```c++
timestamp last_modified_timestamp_
// or use type: cr::time_point<cr::system_clock>
// or use type: std::chrono::time_point<std::chrono::system_clock>
```

##### Setting via Constructor

So now, BOTH of your constructors should have an additional post condition:

```c++
/**
 * @post
 * <the other post conditions / default conditions>
 * NEW: `last_modified_timestamp_` is set to the current system time.
```

##### Making a Getter

Of course, you need to be able to access this -- but we won't make the setter public, because there's no reason to.

So just make your getter as you normally would:

```c++
/**
 * Retrieves the last modified timestamp of the File object.
 * @return The timestamp stored within `last_modified_timestamp_`
 */
getLastModified
```

##### Updating `File::toString()` (optional)

Of course, at this point you'll need to test your code. The code for converting a timestamp to a string is rather unpleasant, so we've provided `FileUtils::timestampToString` for you.

By now, you can figure out how to modify the `toString` method. Do so to check your work!

#### 2. Modifying your Setters

Finally, we'll need to modify our setters. Since technically we _are_ modifying the object by renaming the filename, or revising permissions, we'll update the last modified timestamp to the current time everytime we:

1. Have a successful filename update operation (ie. using the setter)
2. Set the read/write permissions (even if the initial/new values are the same, e.g. setting `readable_`: `true` to `true`)

As such, we'll post the revised setter docs:

```c++
/**
 * Attempts to set a new filename for the File object.
 * The operation FAILS if:
 * 1. The passed filename is empty or contains spaces
 * 2. The extension of the old and new filenames are not equal.
 * Note: Do not append a default extension to the parameter!
 *
 * @param filename A const reference to a string for the new filename.
 * @return true if the filename was successfully updated, false otherwise.
 * @post
 * 1. If possible, the filename variable is set to that of the parameter
 * 2. If the filename was modified, the last modified attribute is updated to the current system time
 */
setFilename

/**
 * Sets the readable permission of the File object.
 *
 * @param new_permission A const reference to a boolean for the new readable permission
 * @post
 * 1. The readble member is set to the value of the parameter
 * 2. The last modified attribute is updated to the current system time
 */
setReadable

 /**
 * Sets the writable permission of the File object.
 *
 * @param new_permission A const reference to a boolean for the new writable permission
 * @post
 * 1. The writable member is set to the value of the parameter
 * 2. The last modified attribute is updated to the current system time
 */
setWritable
```

## Submission, Testing, & Debugging

You will submit your solution to Gradescope via GitHub Classroom. The autograder will grade the following files:

```

1. File.cpp
2. File.hpp
3. FileUtils.cpp
4. FileUtils.hpp

```

Although Gradescope allows multiple submissions, it is not a platform for testing and/or debugging, and it should not be used for that purpose. You MUST test and debug your program locally.

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

### Important Notes

You must start working on the projects as soon as they are assigned to detect any problems and to address them with us well before the deadline so that we have time to get back to you before the deadline.

**There will be no extensions and no negotiation about project grades after the submission deadline.**

---

### Additional Help

Help is available via drop-in tutoring in Lab 1001B (see Blackboard for schedule). You will be able to get help if you start early and go to the lab early. We only a finite number of UTAs in the lab; **the days leading up to the due date will be crowded and you may not be able to get much help then.**

Authors: Daniel Sooknanan
