

# perriera/cpp_starter
Welcome to the perriera/cpp_starter project. 

***Why would someone want to use this?***

> This project aims to get you up and running with C++17 based project with a 'git clone' operation. As well, this particular C++ project template comes with builtin [CPM](https://github.com/cpm-cmake/CPM.cmake) support. This means that you can incorporate other [github](https://github.com) projects, (or anything that uses the git tool) into your project with the simple inclusion of a CPM directive in in your CMakeLists.txt file. 

## Prerequisites
To use this template you will need a Linux environment, (Ubuntu is idea).

 1. [Install pip](https://linuxize.com/post/how-to-install-pip-on-ubuntu-18.04/), (either pip 2 or pip 3)
 2. [Install cmake](https://cmake-python-distributions.readthedocs.io/en/latest/installation.html) using pip, (cmake 3.2.1 or better required)
 3. Create project on [Github.com](https://github.com) using **perriera/cpp_starter** as a template.
 
Once you have established these THREE STEPS you may do the following

	git clone https://github.com/<your project>
	cd <your project>
	mkdir build
	cd build
	cmake ..
	make
	cd ..
	build/run-unittests-cpp_starter

If you have done everything correctly, you will see a Catch2 diagnostic with all green, (similar to the following):

	perry@ubuntu:~/Projects/cpp_starter$ build/run-unittests-cpp_starter 
	===============================================================================
	All tests passed (1 assertion in 2 test cases)

However, you not done yet:

Inside your favorite editor, (or search & replace command utility):

 1. Global search and replace **cpp_starter** to <project_name> (case sensitive)
 2. Global search and replace **CPP_STARTER** to <PROJECT_NAME> (case sensitive)
 3. change directory name '**include/cpp_starter**' to '**include/<project_name>**'

Then do the following:

	rm -rf build
	cd build
	make
	cd ..
This will re-create the project now with all references to cpp_starter changed to <your_project_name>. To test this do  the following:

	build/run-unittests-<your_project_name>

## Changelog.md
When you go to make changes to your changelog.md you should maintain the version number of your project using 'include/version.hpp'. For example, in your version.hpp will look something similiar to the following but all referenced to CPP_STARTER will be changed to <YOUR_PROJECT_NAME>

	#ifndef _CPP_STARTER_VERSION_HPP
	#define _CPP_STARTER_VERSION_HPP

	/**
	 * @file version.hpp
	 * @author Matt Williams (matt@perriera.com)
	 * @author Perry Anderson (perry@perriera.com)
	 * @brief Adds version support for Cmake script
	 * @date 2021-08-08
	 */

	#define CPP_STARTER_VER_MAJOR 0
	#define CPP_STARTER_VER_MINOR 5
	#define CPP_STARTER_VER_PATCH 4

	#define CPP_STARTER_VERSION \
	  (CPP_STARTER_VER_MAJOR * 10000 + CPP_STARTER_VER_MINOR * 100 + CPP_STARTER_VER_PATCH)

	#endif// _CPP_STARTER_VERSION_HPP

From here add this to your github project and you are good to go:

	git add .
	git commit -m "Initial content"
	git push

## Conclusion
Your brand new C++ project is now setup and ready for use with **[perriera/extras](https://github.com/perriera/extras)**, (which  comes bundled with [spdlog](https://github.com/gabime/spdlog), [cpr](https://github.com/libcpr/cpr), and [nlohmann json](https://github.com/nlohmann/json) support, plus others). 
