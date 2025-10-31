# CSCI 235 - The Directory Daemon:

## Project 4 - Digital Filters

Do I even need to give an intro? Ok fine, I'll keep it brief.

This time, you'll be implementing different ways to adjust an input image. Think like a very diet Adobe Photoshop or Lightroom.

### What's Provided

Because I'm not mean, there are is a new addition to the FileLoader class:

`FileLoader::saveImage(Image)`
This allows you to save the contents of an `Image` file
to a specific directory, named `<file_stem>.jpg`.

**You can (and should) use this for your own local tests.**

### Task 1 - The Base `ImageFilter`

Ok intro done, but I'm still keeping things brief.

In `ImageFilter.hpp` & `ImageFilter.cpp`, create the `ImageFilter` abstract class as follows:

#### Private Members

```c++
strength_ // A double representing the strength of the Image Filter
```

#### Constructor

```c++
/**
 * Constructs an ImageFilter with a given initial strength.
 *
 * @param initialStrength A double representing the initial filter strength,
 * clamped between 0.0 and 1.0. Default value of 1.0
 *
 * @note Clamped just means that given a range of values [0,1] and value:
 * If the value is...
 * 1. Between [0,1] use the actual value
 * 2. Less than 0 use 0.0
 * 3. Greater than 1, use 1.0
 */
ImageFilter
```

#### Getters & Setters

```c++
/**
 * Sets the strength of the filter.
 *
 * @param strength A double representing the new filter strength,
 * clamped between 0.0 and 1.0
 */
setStrength

/**
 * Getter for the strength_ member
 */
getStrength
```

#### Pure Virtual Functions

Personal choice, but preceding adding these, test the functions before (since you won't be able to instantiate a class with pure virtual functions).

```c++
/**
 * @brief Applies the filter to the given image.
 * @param image A (non-const) reference to the ImageFile object to which the filter will be applied.
 *
 * @post The parameter image's pixel data is modified to reflect the applied filter effect.
 * @note The filter modifies the image directly -- nothing is returned.
 * @note To prevent confusion: NONE of the filter's members should be modified by this
 * (this is one of the few times where we tell you this function is const).
 * @note Pure virtual -- will be implemented later by derived classes
 */
apply

/**
 * @brief Returns the name of the filter as a string
 * @return A string containg the name of the filter
 *
 * @note Pure virtual -- will be implemented later by derived classes
 */
name
```

#### Intellisense + Compiler Warnings

You might run into something like the base class destructor is not virtual. Just add this line to your `ImageFilter` interface as a public member (ie. the class declaration in the `.hpp`), which tells the compiler to make a virtual destructor (ie. how to clean up the object after your code is done with it) that explicitly uses the default implementation.

```c++
virtual ~ImageFilter() = default;
```

### Task 2 - Actual Filters

Also, by now you've written enough classes, so I'll be omitting defining private member variables -- don't worry, you won't need to use too many.

#### Part 0 - Shared Filter Behavior

_Channels_
We'll start simple. By now you should be comfortable with how RGB values range from `[0,255]`. By the way, some terminology: Red, green, and blue are all referred to as "channels." So for a "red" pixel, the red channel is 255, green is 0, and blue is 0. Nothing new, just introducing new lingo.

_Filter Strength_
For _all_ of the filters we implement, we'll introduce the idea of strength. You can think opacity, or intensity -- whatever floats your boat. The concept remains that, sometimes, we may only want to apply the filter at half or quarter strength. This is what we use the `strength` from `ImageFilter` for.

_How to Compute_
We'll be implementing this by using a [weighted average](https://www.rapidtables.com/calc/math/weighted-average-calculator.html) between the old and filtered image's pixels, channel-by-channel.

Generally, your algorithm should:

1. Consider some original pixel within the image pixel array
2. Compute what the pixel should be, disregarding strength
3. Interpolate (ie. average) the two pixel values, weighting based on the strength

```c++
// Since strength is between [0.0,1.0]
int new_channel = (new_value)(strength) + (old_value)(1 - strength)
```

**So everyone uses a consistent rounding format, just perform the calculation as-is above. Do not round, instead just truncate to an `int`.**

Full disclaimer, when we check your output, we give a tolerance of `1` per channel, to account for minor rounding errors with double operations.

_An example_
For example, suppose an image has a `Cyan` pixel `RGB(0,255,255)`.

If we have an InvertFilter (inverts the color of all pixels in an image), then our new pixel will be:
`invert(0,255,255) = (255-0, 255-255,255-255) = (255,0,0)` (ie. a red pixel, btw this is pseudo-code, to represent the concept. You probably don't _need_ to make a dedicated invert function).

If our filter is strength `1.0` then we're done there. If it's _not_, then we begin averaging.

Suppose our filter is at `0.2` (ie. 20%) strength. That means, the final pixel value should be an 80/20 mix of the old/filter value:

```c++
r = 0(0.8) + 255(0.2) = 51
g = 255(0.8) + 0(0.2) = 204
b = 255(0.8) + 0(0.2) = 204
```

#### Part 1 - The `InvertFilter`

Anywho, to invert an RGB color, simply subtract `255 - <channel_value>` for each of the pixels channels. That's it!

So we'll make an `ImageFilter` that does exactly that.

Create `InvertFilter.hpp/.cpp` and create the `InvertFilter` class there.

##### Constructors

Default Constructor:

```c++
/**
 * Constructs an ImageFilter at full strength
 * @post Sets the underlying strength to 1.0
 */
InvertFilter
```

Parameterized:

```c++
/**
 * Constructs an ImageFilter at full strength
 *
 * @param initialStrength The initial filter strength, as a double
 * @post Clamps the given strength to [0.0, 1.0], if necessary
 * and sets the underlying strength of the ImageFilter
 */
InvertFilter
```

##### Overridden Methods

```c++
/**
 * @brief Inverts the pixel colors of the given image, adjusting for the filter's strength
 *
 * @param image A (non-const) reference to the ImageFile object to which the filter will be applied.
 *
 * @post The image's pixel data is modified such that:
 * 1. The pixel colors are inverted using (255 - channel_value)
 * 2. The final pixel value is adjusted for the filter's strength by
 * averaging the inverted pixel color by the filter strength and
 * averaging the original pixel color by (1.0 - strength)
 *
 * @example See specs above for an example.
 */
InvertFilter::apply

/**
 * @brief Returns the name of the filter, that is "Invert Filter"
 * @return A string representing the name of the filter.
 */
InvertFilter::name
```

#### Part 2 - The `ColorFilter`

This filter applies a solid **color overlay** on top of the entire image.

- You provide an RGB color (`r`, `g`, `b`), and the filter blends that color with every pixel in the image.
- As with all filters, the **strength** determines how much of the overlay is visible:
  - `strength = 1.0` → full overlay color
  - `strength = 0.0` → original image (no overlay)
  - Anything in between → weighted average of the two

##### Constructor

Note that we only explicitly will use a parameterized constructor -- it kind of doesn't make sense to have one since realistically you'd probably want to set the color as a user.

```c++
/**
 * Constructs a ColorFilter with a given overlay color and strength.
 *
 * @param red The red channel value of the overlay color
 * @param green The green channel value of the overlay color
 * @param blue The blue channel value of the overlay color
 * @param strength A double between [0.0, 1.0] indicating overlay intensity. Defaults to 1.0 if omitted.
 */
ColorFilter
```

##### Getters & setters

```c++
 /**
 * Sets the overlay color of the filter.
 *
 * @param r the new red channel value, clamped to [0,255]
 * @param g the new green channel value, clamped to [0,255]
 * @param b the new blue channel value, clamped to [0,255]
 */
ColorFilter::setColor

/**
 * Gets the overlay color of the filter.
 *
 * @return The filter's red, green & blue color
 * as a Pixel object
 */
ColorFilter::getColor
```

##### Overridden Methods

```c++
/**
 * @brief Applies the color overlay to each pixel in the image,
 * blended according to strength
 * @param image A (non-const) reference to the ImageFile
 *
 * @post The image's pixel data is modified such that:
 * The final pixel value is adjusted for the filter's strength by
 * averaging the ColorFilter's color by the filter strength and
 * averaging the original pixel color by (1.0 - strength)
 */
ColorFilter::apply

/**
 * @brief Returns the name of the filter
 *
 * @return A string of the form:
 *
 * `Color Filter [<red_channel>, <green_channel>, <blue_channel>]`
 *
 * @example If we have a red filter, this would return:
 * `Color Filter [255,0,0]`
 */
ColorFilter::name
```

#### Part 3 - The `ChannelSwapFilter`

This filter swaps two of the image’s **color channels** across all pixels.

For example, swapping **RED** with **GREEN** will make all red values become green, and all green values become red, while leaving the blue unchanged.

- Like before, the **strength** blends between the swapped result and the original.
- At full strength (1.0), the channels are completely swapped.
- At lower strengths, it’s partially swapped (a weighted mix).
- At 0 strength, nothing happens.

#### Introducing Enums

Before we can build this filter, we need a way to clearly refer to channels (Red, Green, Blue). For this, we’ll use an **enum** (short for “enumeration”).

An `enum` lets you define a small set of named constants that are really just integers under the hood.

**Add the following to your `ImageFilter.hpp`; ensure it's OUTSIDE of the `ImageFilter` class:**

```c++
enum Channel {
   RED = 0, GREEN = 1, BLUE = 2
};
```

Here:

- `RED` is just another name for `0`
- `GREEN` is another name for `1`
- `BLUE` is another name for `2`

**You can use these values like integers (e.g., as indices into an array), but the names make your code much easier to read.** E.g. Instead of writing `values[0]`, you can write `values[RED]`.

##### Constructor

```c++
/**
 * Constructs a ChannelSwapFilter with two channels
 * to swap and an optional strength.
 *
 * @param c1 The first channel as a Channel Enum
 * @param c2 The second channel as a Channel Enum
 * @param strength A double between [0.0, 1.0] indicating overlay intensity. Defaults to 1.0 if omitted.
 */
ChannelSwapFilter
```

##### Getters & Setters

```c++
/**
 * Sets the channels to be swapped by the filter.
 *
 * @param c1 The first channel to swap as a Channel enum
 * @param c2 The second channel to swap as a Channel enum
 */
ChannelSwapFilter::setSwapChannels

/**
 * Getter for swapped RGB channels
 *
 * @return A std::pair of Channels representing the swapped channels
 * @see Pairs in C++: https://www.geeksforgeeks.org/cpp/pair-in-cpp-stl/
 */
ChannelSwapFilter::getSwapChannels
```

##### Overridden Methods

```c++
/**
 * @brief Swaps the values of the filter's channels for every pixel,
 * then blends with the original pixel by strength.
 *
 * @param image A (non-const) reference to the ImageFile
 *
 * @post The image's pixel data is modified such that for each pixel:
 * 1. The desired channel values are swapped
 * 2. The swapped channel version of the pixel color
 * is weighted by the filter strength and
 * the original pixel color by (1.0 - strength)
 */
ChannelSwapFilter::apply

/**
 * @brief Returns the filter name and swap details
 * @return A string like "ChannelSwapper [RED, BLUE]"
 */
ChannelSwapFilter::name
```

### Task 3 - Chaining Filters Together in `FilterList`

Ok so now that we have a bunch of filters, we'll want to use multiple at a time, so we introduce the `FilterList`. Technically, this is more of a stack, and for the scope of this project, we'll keep it pretty barebones for now.

#### Constructors

```c++
/**
 * Default Constructor -- you may initialize whatever members you deem necessary
 *
 * @note Hint: I only have one private member variable; reference the getters.
 */
FilterList::FilterList
```

#### Getters

```c++
/**
 * @brief Gets the number of filters currently in the list.
 *
 * @return The number of filters in the list as an integer
 */
FilterList::size

/**
 * @brief Returns a list of all of the ImageFilters pointers
 * within the FilterList.
 *
 * @return A std::vector<ImageFilter*> containing all the filters
 */
FilterList::getFilters
```

#### Setters

```c++
/**
 * @brief Adds a filter to the end of the filter list.
 *
 * @param f A pointer to the ImageFilter to add
 * @throws std::invalid_argument Thrown if the provided filter pointer is nullptr.
 *
 * @note Don't make a copy of the dereferenced pointer -- just use the pointer value/address itself
 */
FilterList::addLastFilter

/**
 * @brief Removes the last filter from the list.
 *
 * @return Returns true if a filter was successfully removed,
 * otherwise returns false if the list was empty.
 *
 * @note The caller is expected to manage the de-allocation of the pointer.
 * i.e. This function does not release the memory of the removed filter
 */
FilterList::removeLastFilter
```

#### Stringification

```c++
/**
 * @brief Generates a string representation of the filter list of the form:
 *
 * FilterList
 *  1. <filter 1>::name()
 *  ...
 *  N. <filter N>::name()
 *
 * or if no filters have been added:
 *
 * FilterList:
 *    (no filters added)
 *
 *
 * @return A string containing whose first line is "FilterList", and
 * names of all the filters in the list, each numbered on a new line and indented (for readability),
 * as seen in the format above.
 *
 * @example If we had a FilterList, where we add an InvertFilter first, and then
 * a red ColorFilter, we might have something like:
 *
 * FilterList
 *  1. Invert Filter
 *  2. Color Filter [255,0,0]
 */
FilterList::toString
```

#### The Actual Function

And finally, implementing the whole reason for the class:

```c++
/**
 * @brief Applies all filters in the list to an ImageFile in the order
 * they were added (e.g. first to add => first applied, etc.)
 *
 * @param img A (non-const) reference to an ImageFile to apply the filters to
 */
FilterList::applyAll
```

## Submission, Testing, & Debugging

You will submit your solution to Gradescope via GitHub Classroom. The autograder will grade the following files:

```

1. ImageFilter.cpp
2. ImageFilter.hpp
3. InvertFilter.cpp
4. InvertFilter.hpp
5. ColorFilter.cpp
6. ColorFilter.hpp
7. ChannelSwapFilter.cpp
8. ChannelSwapFilter.hpp
9. FilterList.cpp
10. FilterList.hpp
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

This project is **due on Thursday, November 13**.
_No late submission will be accepted._

---

### Important Notes

You must start working on the projects as soon as they are assigned to detect any problems and to address them with us well before the deadline so that we have time to get back to you before the deadline.

**There will be no extensions and no negotiation about project grades after the submission deadline.**

---

### Additional Help

Help is available via drop-in tutoring in Lab 1001B (see Blackboard for schedule). You will be able to get help if you start early and go to the lab early. We only a finite number of UTAs in the lab; **the days leading up to the due date will be crowded and you may not be able to get much help then.**

Authors: Daniel Sooknanan

```

```

```

```
