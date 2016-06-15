# BMAS

Notes on nauty:
Included version is 26r5

All "main" containing files have been removed.
Configuration settings have been set manually for a windows, Visual Studio based, environment with the Intel C++ compiler. Most settings are in nauty.h, but I do not remember them all.

Caution: I do not currently know if thread safe is enabled or working.

sorttemplates.c: Has had a check for the definition of "SORT_OF_SORT" commented out. This is required to include the file in to project so it will be added to source control, but it does not really need to be compiled it is just present as an include in another file.

Setup for Visual Studio: (Remember to do this for all configurations)
 - Add a project for the nauty directory to the main BMAS solution
 - Do the following to the nauty project:
  - Switch the project to the Intel Compiler
  - Set the project to static lib type
  - Enable C99 support
  - Set to Compile as C
 - Do the following to the BMAS project
  - Add nauty in the References section
  - Add $(SolutionDir)nauty to the additional includes directory 