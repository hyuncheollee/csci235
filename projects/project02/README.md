# CSCI 235 - The Directory Daemon:

## Project 2 - From Text to Pixels

### Task 0 - A Disclaimer

There's going to be a few things that you have (almost guaranteed) not seen before so...

1. Start early!
2. Don't stress. These things aren't here to trick you -- they're so you can have a (relatively) safe environment to find resources & teach yourself ways that _help you learn best individually._
3. Look it up. No one is saying don't do that. However, if you're going to use AI here are some guidelines:

   Dos:

   - Ask for examples
   - Ask it to explain what concepts are
   - Cross-reference what it says with other sources

   Don'ts:

   - Do not vibe-code (ie. have it write code for you). When you're taking a technical interview or writing a test, you're not going to have GPT (or Claude, Gemini, Deepseek, etc.) so **don't sabotage yourself**
   - Do not blindly trust what it says -- these things hallucinate

4. Update the Makefile with new class objects to compile (you should see the pattern) as you build out your project.

That's it for the task. I just needed to grab your attention.

### Task 1 - Specializing the `File` class

Ok spiel aside, open your IDE. We'll do some coding.

#### Provided Additions to `File`

You'll notice that `File` has a couple new things.

##### `updateLastModified()` function & `std::shared_ptr<Clock> system_clock_` member

**TLDR: Calling this function updates the last-modified-timestamp to the current time. That's all you NEED to know (you shouldn't interact with this `system_clock_` member at all)**

If you're curious: `std::shared_ptr<Clock>` is a "shared pointer" to a Clock instance. Shared pointers are just automatically managed pointers (an alternative to the "raw" pointers you guys have worked with until now, eg. `int* my_int_ptr`), and their memory is automatically deallocated when the last shared pointer to the object is destroyed.

Why this change? Because testing via dependency injection. [Here's a link with an insanely good explanation of dependency injection.](https://www.jamesshore.com/v2/blog/2006/dependency-injection-demystified) (3 minute read)

Read More:

1. [Geeks for Geeks - Smart Pointers](https://www.geeksforgeeks.org/cpp/smart-pointers-cpp/)
2. [Stack Overflow - When to use smart pointers](https://stackoverflow.com/a/30143936)

#### Part A - Typing up a `TextFile`

This ones simple. Create the `TextFile` class (ie. `TextFile.hpp` & `TextFile.cpp`). Then, make it extend the `File` class.

Add the following member:

```c++
content_ // A string representing the actual text stored within the file
```

Then, implement the following parameterized constructor.

```c++
/**
 * Constructs a new TextFile object.
 *
 * @pre For simplicity, we assume that the filename extension is that of a text file -- you need not validate it.
 *
 * @param filename  A const reference to a string representing the filename of the text file.
 * @param content   A const reference to a string representing the initial file contents (defaults to an empty string if omitted).
 * @param readable  A boolean indicating whether the file is readable (defaults to true if omitted).
 * @param writable  A boolean indicating whether the file is writable (defaults to true if omitted).
 *
 * @post
 * 1. The filename and permissions are initialized via the base File constructor.
 * 2. The file contents are set to the provided string, or remain empty if none is provided.
 *
 * @note You should be initializing the base class explicitly (refer to lecture)
 */
TextFile
```

And then the following getters/setters for the new member:

```c++
/**
 * Retrieves the current contents of the text file.
 * @return A string containing the text file's contents.
 */
TextFile::getContent

/**
 * Updates the content of the text file.
 *
 * @param newContent A const reference to a string representing the new file contents.
 * @post
 * 1. The content_ member variable is updated to match the provided string.
 * 2. The last_modified_timestamp_ of the underlying File is updated to the current time
 * specified by Clock::now.
 *
 * @note Hint: You will need to modify `File` (ie. the base class) to allow you to actually update the last modified timestamp.
 */
TextFile::setContent
```

For _your own_ testing purposes, you can (optionally) implement:

```c++
/**
 * Generates a formatted string representation of the text file.
 *
 * @return A string containing the file's name, permissions, last modified timestamp,
 *         and contents, or "(none)" if the contents are empty.
 */
TextFile::toString
```

#### Part B - Pixels & `ImageFile`

Ok so now that we have text files we'll also want to make a separate class for images.

But first, we'll make a pixel class.

##### Introducing `Pixel` - Seeing Your First Struct

Structs are classes, except all members are public by default instead of private. Use these when you just want to transfer data in a more readable / constructed way. After all `pixel.red` is much better than `pixel[0]`.

We've defined the Pixel struct with the following members:

```c++
red // An integer specifying the red channel of the pixel (defaults to 0)
green // An integer specifying the red channel of the pixel (defaults to 0)
blue // An integer specifying the red channel of the pixel (defaults to 0)
```

**These names must match exactly since we'll be testing the values of your Pixels -- so if we call `p.red` we better have a member named `red`.**

You can initialize a Pixel easily using [structured initialization](https://stackoverflow.com/questions/11516657/c-structure-initialization):

For example, if I want a red Pixel, I can just say `Pixel red_pixel = { 255, 0, 0 }`.

Order matters -- the order in which you've given the parameters must be the order they are defined in the struct as.

**Don't modify anything within the provided `Pixel` struct -- those changes will be disregarded when you submit.**

##### Implementing `ImageFile`

You know the routine by now:

Private members:

```c++
/**
 * A 2D vector of Pixel structs
 * The pixel data is stored in a 2D vector, where pixels_[row][col] corresponds to
 * the pixel at the given row and column of the image.
 *
 * pixels_[0][0] should be the top-left of the image
 * pixels_[YOUR_IMAGE_HEIGHT - 1][YOUR_IMAGE_WIDTH - 1] should be the bottom-right of the image
 */
pixels_
```

Parameterized Constructor:

```c++
/**
 * Constructs a new ImageFile object.
 *
 * The pixel data is stored in a 2D vector, where pixels[row][col] corresponds to
 * the pixel at the given row and column of the image.
 *
 * @pre Assume that the image ends with a valid image extension (i.e. you do not need to validate it).
 *
 * @param filename A const reference to a string representing the filename of the image.
 * @param pixels   A const reference to a 2D vector of Pixel objects representing the image's pixel data.
 *                 Defaults to a grid of 20(width) x 10(height) pixels initialized to black (0,0,0).
 * @param readable A boolean indicating whether the file is readable (defaults to true if omitted).
 * @param writable A boolean indicating whether the file is writable (defaults to true if omitted).
 *
 * @post
 * 1. The filename and permissions are initialized via the base File constructor.
 * 2. The pixel buffer is set to the provided vector, or initialized to the default size with all black pixels if...
 *  - The parameter is omitted (ie. as a default value).
 *  - Or the pixel array's rows are not all the same length.
 *
 * @note It IS allowed to set pixels to an empty 2D vector!
 */
ImageFile
```

By the way, here's a rough example of how you would provide a default `std::vector` parameter:

```c++
// This is a 1D array -- you'll need to adapt this so it's 2D
void myFunction(std::vector<char> someVector = std::vector<char>(2, 'a')); // Vector of 2 integers, each initialized to the letter 'a'
```

Of course, our typical getters and setters:

```c++
/**
 * Updates the pixel buffer of the image if given a valid pixel array; otherwise, returns false.
 *
 * @param pixels A const reference to a 2D vector of Pixel objects representing the new image data.
 * @returns True if the operation was successful, false otherwise.
 * @post
 * 1. If the new pixel array's rows are not all the same length, NO member is updated and false is returned.
 * 2. Otherwise, the pixels_ member variable is updated to match the provided 2D vector.
 *    and the last_modified_timestamp_ of the underlying File is updated to the current time
 *    specified by the Clock class
 *
 * @note It IS allowed to set pixels to an empty 2D vector!
 */
ImageFile::setPixels

/**
 * Retrieves the current pixel buffer of the image.
 *
 * @return A 2D vector of Pixel objects, where pixels[row][col] corresponds to the pixel at
 *         the specified row and column.
 */
ImageFile::getPixels
```

But we'll also have some metadata related getters. You can achieve this in multiple ways:

1. Introduce your own member variables
2. Derive them from the 2D `pixels_` member

Your call! Just make sure that whichever way you choose, these methods do what they're supposed to.

```c++
/**
 * Retrieves the height (number of rows) of the image.
 * @return An integer representing the total number of rows in the pixel buffer.
 */
getHeight

/**
 * Retrieves the width (number of columns) of the image.
 * @return An integer representing the total number of columns in the pixel buffer.
 */
getWidth
```

Because I know this isn't the most trivial, I'll give you the `ImageFile::toString()` implementation to help you test (you're welcome):

```c++

/**
 * Generates a string representation of the image file.
 *
 * @return A string containing the file's name, permissions, last modified timestamp,
 *         and image dimensions (width x height).
 */
std::string ImageFile::toString() const
{
    std::stringstream ss;
    // Call the base class toString()
    ss << File::toString();

    // Display image metadata
    ss << "Resolution: " << getWidth() << "x" << getHeight() << std::endl;

    // Display pixel buffer
    ss << "[" << std::endl;

    for (int i = 0; i < getHeight(); i++) {
        ss << "\t";

        for (int j = 0; j < getWidth(); j++) {
            ss << pixels_[i][j].toString() << " ";
        }
        ss << std::endl;
    }
    ss << "]";
    return ss.str();
}
```

### Task 2 - Loading From Disk

Now that you have your `TextFile` and `ImageFile` classes, we need a way to actually create them from data stored on disk. To do this, you’ll implement the **FileLoader** class.

This class will provide functionality to read from plain text files and image files, and then return corresponding `TextFile` or `ImageFile` objects.

---

#### Throwing Exceptions

For the first time, you’ll need to throw **exceptions**.

- **Why?**  
  When reading from disk, things can go wrong—files might not exist, might not be readable, or might be corrupted. Instead of returning garbage data or silently failing, we “throw an exception” to signal that something went wrong.

- **When?**  
  You should throw exceptions when your function cannot perform its intended job safely or meaningfully. For example, if a file cannot be opened, it doesn’t make sense to keep running as if nothing happened. This is an alternative to returning a sentinel value (eg. returning `false` for a setter).

  _However, you should try to avoid throwing exceptions (and favor using other methods of alerting failure) if possible, since they can be expensive in terms of performance._

- **How?**  
   Exceptions in C++ are thrown with the `throw` keyword. The standard library provides ready-made exception classes inside the `<stdexcept>` header.

  Example:

  ```c++
  #include <stdexcept>

  void doSomething(const std::string& filename) {
      if (filename.empty()) {
          throw std::invalid_argument("Filename cannot be empty.");
      }
  }
  ```

  You can catch exceptions using the `try-catch` block:

  ```c++
  try {
    doSomething("");
  } catch (std::invalid_argument const& ex) {
    // Only runs if `doSomething` throws an invalid_argument
  } catch (...) { // <-- Catches everything else
    // ...
  }
  ```

#### Part A - Loading Text Files

Create the FileLoader class in `FileLoader.cpp` and `FileLoader.hpp` (as per usual).

Here, you'll implement a function in FileLoader that takes in the filename of a text file, reads its contents, and returns a new TextFile object (or throws if it can't proceed).

```c++
/**
 * Loads a text file from disk into a TextFile object.
 *
 * @param str_path_to_file A const reference to a STRING representing the path to the text file.
 * @return A TextFile object containing the file's name and contents.
 * @throws std::invalid_argument if:
 *  1. The file does not exist.
 *  2. The file extension is not ".txt".
 * @post
 * - All boolean File members are set to true
 * - The File filename is explicitly set to the name of the file only -- no directory
 *   information included.
 *   (e.g. "homework/my_file.txt" has a filename of "my_file.txt")
 * - The TextFile contents is set to the text content of the specified file
 *
 * @see Useful Links:
 * 1. C++ Exceptions: https://en.cppreference.com/w/cpp/header/stdexcept.html
 * 2. The std::filesystem::path (from <filesystem> header) type: https://en.cppreference.com/w/cpp/filesystem/path.html
 *    - Contains how to get the extension & filename from the file system path
 *    - How to create a path object: https://stackoverflow.com/questions/43114174/convert-a-string-to-std-filesystem-path
 * 3. Check if file Exists: https://en.cppreference.com/w/cpp/filesystem/exists.html
 * 4. Input File Streams (refresher from 135): https://www.w3schools.com/cpp/ref_fstream_ifstream.asp
 */
FileLoader::loadTextFile
```

#### Part B - Loading Image Files

For image files, your FileLoader should be able to load pixel data from disk and construct an ImageFile. Just like with text files, throw exceptions (std::runtime_error) if something goes wrong (e.g., file missing, unreadable data).

##### Introducing the `stb_image` Library

###### a. Loading Images with `stb_image`

You may or may not know, but MAN, image file formats are not particularly the most trivial to deal with.

So we'll be using the [`stb_image.h`](https://github.com/nothings/stb) library to load image files. This library gives us raw pixel data in a simple format, which we then reshape into our `Pixel` grid.

I'll provide a little bit of exposition, but I am intentionally leaving things out because I want you to know **there is documentation in the `stb_image.h` file itself and that you need to read (some, not all of) it.**

###### b. How to set it up:

- In **only `main.cpp`**, you must define the macro **before** including `stb_image.h`, but:

```c++
// In your main.cpp
// ALL other inclusions (including FileLoader)
// eg. #include "FileLoader.hpp", etc.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
```

```c++
// Then in a class like FileLoader.hpp you would have ONLY (notice the lack of the define guard)
#include "stb_image.h"
```

This step tells the compiler to generate the actual function definitions. If you forget this, your program will not work. Other than that, you should not add this to the Makefile as another class object.

**If you include it in any other file, your code will likely fail to compile.**

###### c. Loading an image:

The function to look for is: `stbi_load`

When trying to load an image file, know that the `stbi_load` takes a **C style** string instead of a `std::string`. So instead of passing a `std::string` you must use `yourFilePathString.c_str()` to do so!

The returned pointer (`data`) is a **1D dynamic array** of `unsigned char`s (_just treat these as integers_) containing the pixel data. You must reshape this into a 2D `Pixel` buffer (see example later).

###### d. Memory cleanup (important!):

After you’re done reshaping and copying the pixel data into your `ImageFile`, you **must** free the dynamic memory using the method specified in the docs. You will **be graded on this** — failing to free the memory is a memory leak!

###### e. In Summary:

1. Define `STB_IMAGE_IMPLEMENTATION` in ONLY your `main.cpp` file after ALL other import statements. You can (and should) include the `stb_image.h` header elsewhere, but this macro (ie. the `define` statement) should only appear in your `main.cpp`.
2. Call `stbi_load()` to read in the raw pixel data.
3. Reshape the data into a 2D `Pixel` array using the width/height.
4. Release the memory once you’re done _using the built-in method_

###### f. A Small Example

Suppose we have a **2x1 image** (width = 2, height = 1) and you read it using 3 channels (RGB):

- Left pixel = white → RGB(255, 255, 255)
- Right pixel = black → RGB(0, 0, 0)

The raw `stb_image.h` array will look like this:

`255 255 255 0 0 0`

Why? Because `stb_image.h` just dumps pixel channel values one after the other in a flat sequence (R, then G, then B, and so on). So this array represents:

1. `255 255 255` → one white pixel
2. `0 0 0` → one black pixel

Your main task is to reshape this **1D array** into a **2D buffer** of `Pixel` structs. For this case:

```
[
    [ Pixel{255, 255, 255}, Pixel{0, 0, 0} ]
]
```

That’s one row (height = 1) with two columns (width = 2).

Importantly: the same array would also appear if the image were **1x2** (width = 1, height = 2).

- In that case, your reshaped data should be:

```
[
    [ Pixel{255, 255, 255} ],
    [ Pixel{0, 0, 0} ]
]
```

That’s two rows (height = 2) with one column each.

The only way to know the correct arrangement is to use the width and height values provided by `stb_image.h`. Don’t just assume — reshape based on those dimensions.

##### Time to Implement

Okay, you've read enough. Here's the function signature!

```c++
/**
 * Loads an image file from disk into an ImageFile object.
 *
 * Supported formats: PNG (.png) and JPEG (.jpg).
 *
 * @param str_path_to_file A const reference to a STRING representing the path to the image file.
 * @return An ImageFile object containing the file's name and pixel data buffer
 * @throws std::invalid_argument if:
 *  1. The file does not exist.
 *  2. The file extension is not ".png" or ".jpg".
 * @post
 * - All boolean File members are set to true
 * - All dynamic memory (that is, pointers) is released (so READ the documentation in stb file please)
 * - The filename of the File is explicitly set to the name of the file only -- no directory
 *   information included.
 *
 * @see stb_image.h Read the documentation section
 * - You will have to reshape the 1D array of RGB channel values
 *   into a 2D array of Pixel structs
 */
FileLoader::loadImageFile
```

##### Sample Inputs

We've provided two sample inputs for you to check your FileLoader with.

`sample_text.txt` - Is a `.txt` text file containing a string. When you read the contents of the file into your code, it should match _exactly_ (including newlines).

`sample_img.png` - Is a `.png` image containing a 4x4 grid with...

1. The first row being black (0,0,0), red (255,0,0), green(0,255,0), blue(0,0,255)
2. The subsequent rows are lighter tints of the colors in the same column
3. The last row is all white (255,255,255)

## Submission, Testing, & Debugging

You will submit your solution to Gradescope via GitHub Classroom. The autograder will grade the following files:

```

1. File.cpp
2. File.hpp
3. FileUtils.cpp
4. FileUtils.hpp
5. FileLoader.cpp
6. FileLoader.hpp
7. ImageFile.cpp
8. ImageFile.hpp
9. TextFile.cpp
10. TextFile.hpp

```

Although Gradescope allows multiple submissions, it is not a platform for testing and/or debugging, and it should not be used for that purpose. You MUST test and debug your program locally.

Before submitting to Gradescope, you MUST ensure that your program compiles using the provided Makefile and runs correctly on the Linux machines in the labs at Hunter College. This is your baseline—if it runs correctly there, it will run correctly on Gradescope. If it does not, you will have the necessary feedback (compiler error messages, debugger, or program output) to guide you in debugging, which you don’t have through Gradescope. “But it ran on my machine!” is not a valid argument for a submission that does not compile. Once you have done all the above, submit it to Gradescope.

### Testing

#### Compiling with the Included `Makefile`

For your convenience, we've included a `Makefile`, which allows you to quickly re-compile your code, instead of writing `g++` over and over again. **It also ensures that your code is being compiled using the correct version of C++. And by correct one, we mean the one the auto-grader uses.**

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

This project is **due on Wednesday, October 8**.
_No late submission will be accepted._

---

### Important Notes

You must start working on the projects as soon as they are assigned to detect any problems and to address them with us well before the deadline so that we have time to get back to you before the deadline.

**There will be no extensions and no negotiation about project grades after the submission deadline.**

---

### Additional Help

Help is available via drop-in tutoring in Lab 1001B (see Blackboard for schedule). You will be able to get help if you start early and go to the lab early. We only a finite number of UTAs in the lab; **the days leading up to the due date will be crowded and you may not be able to get much help then.**

Authors: Daniel Sooknanan
