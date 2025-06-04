# Intro to Graphics Programming Workshop
For generations, humankind has wondered, **how do I make the math box put the pretty pictures on the screen?**

But now, they will wonder no longer, for the archvists here at UNSW Computer Graphics Society are hard at work unearthing these ancient secrets and sharing them with you *one workshop at a time.*

Come join us for CGS's first bespoke Computer Graphics workshop: ***Introduction to Graphics Programming with OpenGL***.

:map: Location: Online (Here on this server!)
:calender: Date: Thursday 12th June 2025
:clock: Time: 6-8PM

## Things you'll need to bring

:book: Assumed knowledge
- COMP1511 level knowledge of the **C programming**. This workshop will be in **C++** but we'll avoid using it's advanced language features.
- The ability to clone a git repo

:robot: A c++ Compiler
Depends on your operating system
- Windows
-- You're going to need to install [Visual Studio (VS)](https://visualstudio.microsoft.com/downloads/). Installing VS also involves installing the VS installer. Launch and the the "Desktop development with C++" package
-- Alternatively you can look into MinGW via MSys2 (Not Recommended)
- Linux
-- Most distros have some form of gcc/clang built-in. To check open the terminal and enter `g++ --version` or `clang --version`
- MacOS
-- Most Macs have some form of clang built-in. To check open the terminal and enter `clang --version` 
:C: The CMake build tool
:book: Libraries
- [glew](https://glew.sourceforge.net/) (The latest version should be fine)
- [glm](https://github.com/g-truc/glm)
- [glfw](https://www.glfw.org/download) (The binaries will be fine)

:computer: Developement environment
- [Visual Studio Code (VSCode)](https://visualstudio.microsoft.com/downloads/) (Distinct from Visual Studio)
-- You should also install the C/C++ extensions
- Or your IDE or choice!

If you're using a Unix derived system, your system is probably using a a *package manager* (e.g. *brew* or *apt*). For your long term sanity, it might be worthwhile figuring out how to install the above packages through it. 
Windows also has a package manager specifically for c/c++ packages called [vcpkg](https://github.com/microsoft/vcpkg)

Otherwise if you are downloading the libraries manually, you will have to place them in a place the project will look

### Workshop Repository
TBA

To ensure that your environment is set up correctly, download the workshop repository, cd into `intro-to-gp/workshop_part0_starter` and enter
```
cmake -B build && cmake --build build
```

You should get a message along the lines of "Build Successful"
