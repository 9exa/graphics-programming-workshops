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
-- You're going to need to install [Visual Studio (VS)](https://visualstudio.microsoft.com/downloads/). Installing VS also involves installing the VS installer. Launch it and add the "Desktop development with C++" package
-- Alternatively you can look into MinGW via MSys2 (Not Recommended)
- Linux
-- Most distros have some form of gcc/clang built-in. To check open the terminal and enter `g++ --version` or `clang --version`
- MacOS
-- Most Macs have some form of clang built-in. To check open the terminal and enter `clang --version` 
:C: The CMake build tool
:book: Libraries
For the sake of your sanity long term, I would recommend you actually use a packagemanager to install the libraries below.
- If you are using a UNIX based OS, chances are you're already familiar with the built-in package manager
```brew install glew glfw glm```
```sudo apt install libglew-dev libglfw3-dev libglm-dev```
```sudo pacman install glew glfw glm```
ect.

On Windows you can install [vcpkg](https://github.com/microsoft/vcpkg?tab=readme-ov-file). 
1. Clone the [repo](https://github.com/microsoft/vcpkg?tab=readme-ov-file)
2. Enter it and run `.\bootstrap-vcpkg.bat` (or `.sh`). 
3. Add the *path_to_vcpkg_repo* to your [PATH environment variable]("https://www.thewindowsclub.com/how-to-add-edit-a-path-variable-in-windows"). 
4. While there, set the environment variable VCPKG_ROOT to *path_to_vcpkg_repo*

Otherwise you'll have to download the libraries manually.
- [glew](https://glew.sourceforge.net/) (The latest version should be fine)
- [glm](https://github.com/g-truc/glm)
- [glfw](https://www.glfw.org/download) (The binaries will be fine)

You then need to copy the contents of glew and glfw's `include` folder and the glm repos `glm` folder into `third-party/include`.
Next copy the copy the contents of glew and glfw's `lib` folder into `third-part/lib`.

:computer: Developement environment
- [Visual Studio Code (VSCode)](https://visualstudio.microsoft.com/downloads/) (Distinct from Visual Studio)
-- You should also install the C/C++ extensions
- Or your IDE or choice!


### Workshop Repository
TBA

To ensure that your environment is set up correctly, download the workshop repository, cd into `intro-to-gp/workshop_part0_starter` and enter
```
cmake -B build && cmake --build build
```

You should get a message along the lines of "Build Successful"
