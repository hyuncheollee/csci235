# Project 5: The Transformation Pipeline: Linked Lists & Queues

## Project Overview

In previous projects, we built the `Vector3D` class to represent points in 3D space and explored inheritance through a `Transformation` hierarchy. You have been provided with two concrete transformations: `Translation` (moves a point by an offset) and `Scale` (multiplies a point by a scalar factor), both of which derive from the abstract `Transformation` base class.

You are also provided with an implementation of `LinkedList`, a linked-list-based container using the `Node` class. Your job is to build a `TransformPipeline` that manages an ordered sequence of `Transformation` objects using the `LinkedList`, applying them to 3D points in order.

## Project Setup

Accept the project on GitHub Classroom through this link: [https://classroom.github.com/a/T1ILmAxi](https://classroom.github.com/a/T1ILmAxi).

> Note: If prompted, please select your name from the roster list.

Upon accepting the assignment, a repository will be automatically made for you. In it, you will find starter code and files provided. You will build your project in this repository, push changes to it, and submit this repository on Gradescope.

- Unsure about the workflow? https://www.youtube.com/watch?v=AHDCokfgcSo.
- Beginner to Git? https://www.youtube.com/watch?v=MJUJ4wbFm_A.

> Note: Make sure to run `make clean` before committing your changes. You should never see `.o` files in your version control.

## Task 0: Create `TransformPipeline`

The `TransformPipeline` class will **publicly inherit** from `LinkedList<Transformation*>`. It stores **pointers** to `Transformation` objects, allowing it to hold any of the concrete transformation subclasses polymorphically.

> **Note:** Recall that a publicly-derived class inherits all public and protected members from its base class. The `TransformPipeline` will therefore have access to all of `LinkedList`'s functionality (e.g., `insert`, `remove`, `getEntry`, `getLength`, `isEmpty`, etc.) as well as its `protected` members (`headPtr_` and `itemCount_`). It is helpful to review these functions before proceeding.

## Task 1: Implement `enqueueTransform`

The `enqueueTransform` function adds a new transformation to the **end** of the pipeline, preserving the order in which transformations were added.

```cpp
/**
 * @param transform: A pointer to a Transformation object.
 * @post: The transformation is appended to the end of the pipeline.
 */
enqueueTransform
```

## Task 2: Implement `processNextTransform`

The `processNextTransform` function applies the **first** transformation in the pipeline to a given point, removes it from the pipeline, and **deletes** the transformation to free its memory. If the pipeline is empty, the function does nothing.

```cpp
/**
 * @param point: A reference to a Vector3D to be transformed.
 * @post: The first transformation is applied to the point, removed from the pipeline, and deleted.
 *        If the pipeline is empty, the point is unchanged.
 */
processNextTransform
```

> **Note:** `LinkedList::remove` deletes the `Node`, but **not** the item it stores when that item is a pointer. You must manually `delete` the `Transformation` object to prevent a memory leak.

## Task 3: Implement `runFullPipeline`

The `runFullPipeline` function applies **all** transformations in the pipeline to a given point, in order from first to last, **without** removing them.

```cpp
/**
 * @param point: A reference to a Vector3D to be transformed.
 * @post: All transformations are applied to the point sequentially.
 *        The pipeline remains unchanged.
 */
runFullPipeline
```

## Task 4: Implement `reversePipeline`

The `reversePipeline` function reverses the order of all transformations in the pipeline in-place.

```cpp
/**
 * @post: The order of all transformations in the pipeline is reversed.
 *        Example: [T1 -> T2 -> S1] becomes [S1 -> T2 -> T1]
 */
reversePipeline
```

> **Hint:** This is the classic linked-list reversal problem. Use three pointers (`prev`, `current`, `next`) to reverse the direction of the `next` pointers, then update `headPtr_` to point to what was the last node. Don't forget to handle edge cases (empty list, single element).

## Task 5: Implement `removeTransformationsOfType`

The `removeTransformationsOfType` function removes and deletes **all** transformations of a given type from the pipeline.

```cpp
/**
 * @param type: The string type to remove (e.g., "SCALE" or "TRANSLATE").
 * @post: All transformations matching the given type are removed from the pipeline and deleted from memory.
 * @return: The number of transformations removed.
 */
removeTransformationsOfType
```

> **Hint:** Remember to `delete` each removed `Transformation` pointer to avoid memory leaks.

### Makefile

The provided `Makefile` already lists the source files that need to be compiled:

```makefile
SRCS = Vector3D.cpp Translation.cpp Scale.cpp TransformPipeline.cpp
```

Note that `LinkedList.cpp` is **not** in this list because it is included via the header. Your `TransformPipeline.cpp` will be compiled as its own object file.

For your reference, the Makefile comes with the following commands:

- `make` or `make all`: Compile the project, only recompiling modified source code.
- `make clean`: Delete all object files (`.o`).
- `make rebuild`: Freshly recompile the entire project from scratch.
  - Equivalent to `make clean && make`.

## Submission Details

You will submit your solution to Gradescope through GitHub Classroom.

The following files must be submitted:

- `TransformPipeline.hpp`
- `TransformPipeline.cpp`

All other files (`Vector3D`, `Node`, `LinkedList`, `Transformation`, `Translation`, `Scale`) are provided and will **not** be changed for grading. Do not modify them.

Although Gradescope allows multiple submissions, it is NOT a platform for testing and/or debugging, and it should not be used for that purpose.

You MUST test and debug your program locally. This means creating your own tests and ensuring your project behaves as expected. To help prevent over-reliance on Gradescope for testing, only **5 submissions per day** will be allowed.

## Grading Rubric

- **Correctness (85%)**: The program behaves as defined by the project specifications. Your points are determined by Gradescope unit testing.
  - Enqueue Transform (10 pts)
  - Process Next Transform (14 pts)
  - Run Full Pipeline (22 pts)
  - Reverse Pipeline (18 pts)
  - Remove Transformations Of Type (17 pts)
  - Compilation (4 pts)
- **Documentation (15%)**: Provide function preambles in `.hpp` AND `.cpp` files, in the `@pre`, `@param`, `@post` format.
  - All files have preambles.
  - All class member functions have preambles.
- **Extra Credit (5%)**: To encourage students to begin projects early, we will award extra credit to students who get their project to **compile within the first 3 days**.
  - To compile quickly, you should **stub** your entire project. This means defining your functions but implementing them with some dummy code to temporarily satisfy compilers. This way, you ensure you have the right interface before implementing. Go to TA hours for guidance with this.

---

Authors: Tedd Lee, Prof. Wole
