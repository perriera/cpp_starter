

## How to install a Linux Platform (Ubuntu 20.04.4)
> While intended to be cross-platform, at this point in time all instructions are based upon a Ubuntu 20.04.4 installation. This can be achived in multiple ways be that a native installation or a virtual machine made possible via a tool such as [Parallels Desktop for the iMac](https://www.parallels.com/ca/pd/general/?gclid=CjwKCAjwjZmTBhB4EiwAynRmD6SV4LdfM_DXaYiwTJhJJBddfc6JM_bDuAuWsUyyHUMj5zEQnC3wjBoCfgcQAvD_BwE) (try it for free).

 1. **GIVEN** we need to have a Linux installation to develop C++11/17 code
 2. **WHEN** we install the latest Ubuntu using Parallels Desktop
 3. **THEN** we can have all the benefits that come with a Linux environment

### Prerequisites
  - [Preferably a late model iMac](https://www.apple.com/ca/imac-24/?afid=p238%7CsOluZynmu-dc_mtid_1870765e38482_pcrid_571348307644_pgrid_125362851562_pntwk_g_pchan__pexid__&cid=aos-ca-kwGO-mac--slid---product-) (with a large screen)
  - [Parallels Desktop installed](https://www.parallels.com/ca/pd/general/?gclid=CjwKCAjwjZmTBhB4EiwAynRmD6SV4LdfM_DXaYiwTJhJJBddfc6JM_bDuAuWsUyyHUMj5zEQnC3wjBoCfgcQAvD_BwE)
  - [How to clone your project (with this template)](https://github.com/perriera/extras_cpp/blob/dev/docs/CLONE.md)

 
### Wish Case
Now that you have your project cloned we need to make sure you have the tools necessary to compile properly:

 - [ ] Install C++11/17 packages for a Linux environment

		sudo apt update
		sudo apt install -y build-essential libtool autotools-dev automake pkg-config git clangd cppcheck clang-tidy python3-pip checkinstall

 - [ ] Install CMake 3.21

		pip install clang-format
		pip install cmake-format
		pip install cmake

 - [ ] Add these enironment variables (aka.  `vi ~/.bashrc `)

		
		export PATH=$HOME/.local/bin:${PATH}
		export CPM_SOURCE_CACHE=$HOME/.cache/CPM
		export LD_LIBRARY_PATH=/usr/local/lib:${LD_LIBRARY_PATH}

 - [ ] Then source it ... 

		source ~/.bashrc

 - [ ] Now install Visual Studio Code

		sudo snap install --classic code # or code-insiders

 - [ ] Now start Visual Studio Code

		cd <into your project directory>
		code .

### Summary 
Now you have all the tools necessary to compile your new C++17 project complete with cmake 3.21 support. Press Ctrl-B (inside Visual Studio Code) to see your first successful compile.

### Next Steps
 - [How to setup your changelog.md](https://github.com/perriera/extras_cpp/blob/dev/docs/CHANGELOG.md)


