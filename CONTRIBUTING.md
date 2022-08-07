# Contribution Guide

Thanks for sparing your time to improve `identity.h`!

## Before we start

Let's understand [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) first to keep our community healthy. Make sure you understand how to use:

-   UNIX-like platform, Linux and MacOS are recommended
-   [Shell](https://www.geeksforgeeks.org/basic-shell-commands-in-linux/)
-   [git](https://github.com/git-guides)
-   [GitHub](https://docs.github.com/en/get-started/quickstart/contributing-to-projects)
-   [GNU Make](https://www.gnu.org/software/make/manual/make.html)
-   [C Language](https://www.w3schools.com/c/c_intro.php)
-   Basics of [PHP Language](https://www.w3schools.com/php/php_syntax.asp)

In concept, we use PHP language to generate a long and repetitive C header (\*.h file). The reason of using PHP because it's the most convenient way to do that kind of job.

## Requirements

When you have enough knowledge to start, make sure your computer has these installed:

-   [git](https://github.com/git-guides/install-git)
-   [PHP](https://www.php.net/downloads.php)
-   [GNU Make](http://ftp.gnu.org/gnu/make/)
-   [Clang](https://clang.llvm.org/get_started.html)

Also note that this project **only works on UNIX-like platform!** If you're a Windows user, try install either [WSL](https://docs.microsoft.com/en-us/windows/wsl/install) or [Cygwin](https://www.cygwin.com/install.html) then install those requirements in WSL or Cygwin, **not natively**.

## Preparation

You can either download the source code directly from GitHub site, or using git to clone (recommended):

```bash
git clone https://github.com/Thor-x86/identity.h
```

## Directory Structure

We somewhat follow [The Pitchfork Layout](http://www.max-sperling.bplaced.net/?p=10296) convention for structuring project directory. In short:

-   **src**: a Directory where source code lives, this is the main part.
-   **out**: Compilation output, this is your build result.
-   **test**: For testing the main source code at **src**.
-   **examples**: Examples of what you can do with this project.

## Code Style

[Allman style](https://en.wikipedia.org/wiki/Indentation_style#Allman_style) is the reference of this project's code style, with **tab** indentation.

## Build

Entire build procedures in this project already automated with GNU Make. So you just have to run this:

```bash
make
```

If you want to increase string limit for some reason, replace `<number>` of this to your desired limit:

```bash
MAX_ITERATION=<number> make
```

## Install

Whenever you want to use your custom build of `identity.h`, you have to install it right after build. Installation procedures also automated with GNU Make. So you just have to run:

```bash
sudo make install
```

If you want to install at different directory (such as install to on going C project locally), replace this `<path_to_dir>` to your desired directory path. **DO NOT** put trailing slash or it spits errors.

```bash
PREFIX=<path_to_dir> make install
```

...or with root privilege

```bash
sudo PREFIX=<path_to_dir> make install
```

## Deployment

This section is intended to share ready-to-use form of `identity.h` to other developers and users. Replace this `<version>` to currently working version:

```bash
VERSION=<version> make deploy
```
