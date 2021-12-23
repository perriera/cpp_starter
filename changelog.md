# Changelog

> All notable changes to this project will be documented in this file.</br>
> The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), </br>
> and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).</br>
> To add a tag to the git repository do:
>
> > git tag -a v0.17.0 -m "Using MAKE_EXTRAS_CPP_LIBRARY_TOOLS (Link)"</br>
> > git push origin v0.17.0

IMPORTANT:

- Manually keep the changelog version number in sync with CMakeLists.txt project version.<br>
- Keep the changelog.md up to date, neat and tidy, (as it is a convenient tool for code maintenance).<br>
- Use [Semantic Versioning](https://semver.org/spec/v2.0.0.html) such that<br>
- Given a version number MAJOR.MINOR.PATCH, increment the:<br>
- MAJOR version when you make incompatible API changes,<br>
- MINOR version when you add functionality in a backwards compatible manner, and<br>
- PATCH version when you make backwards compatible bug fixes. <br>
- But there is no need to change the version number for correcting spelling errors, (etc).<br>
- MAKE SURE to tag and update the tag compare list below, (for quick code comparison purposes).<br>

## [Unreleased]

Detailed test cases</br>
Detailed class descriptions in README.md</br>
Correct URL for github, (for source compare)</br>

## [Next Steps]

Adding mock test cases </br>
Adding unit test cases </br>
Updated README.md accordinging</br>

#### 0.17.0 (2021-12-22)

### Changed

- main to extras_cpp_app

* (for the benefit of templated apps)

#### 0.16.1 (2021-12-21)

### Changed

- Added Link

#### 0.16.0 (2021-12-21)

### Changed

- Using MAKE_EXTRAS_CPP_LIBRARY_TOOLS

#### 0.15.0 (2021-12-21)

### Changed

- Using v5.22.0

#### 0.14.0 (2021-12-15)

### Changed

- Using v5.18.1

#### 0.13.0 (2021-12-01)

### Changed

- Using v5.8.0

#### 0.12.0 (2021-11-30)

### Changed

- Renamed project

#### 0.11.0 (2021-11-29)

### Changed

- Using extras 5.5.1

#### 0.10.0 (2021-11-29)

### Changed

- Using extras 5.4.0
- Added LICENSE.md

#### 0.9.0 (2021-11-15)

### Changed

- Added MAKE_EXTRAS_CPP_LIBRARY_ONLY
- Added MAKE_EXTRAS_CPP_LIBRARY_EXECUTABLES

#### 0.8.0 (2021-11-14)

### Changed

- Updated README.md

#### 0.7.0 (2021-11-14)

### Changed

- Updated README.md

#### 0.6.0 (2021-11-8)

### Changed

- Now using perroera/extras 5.0.9

#### 0.5.6 (2021-11-8)

### Changed

- Now using perroera/extras 5.0.8
- Added additional VSC docs
- Added additional CPM docs

#### 0.5.5 (2021-11-8)

### Changed

- Now using perroera/extras 5.0.7

#### 0.5.4 (2021-11-8)

### Changed

- Updated to use perriera/extras v5.0.4

#### 0.5.3 (2021-11-8)

### Changed

- Updated to use perriera/extras v4.19.0

#### 0.5.2 (2021-11-8)

### Changed

- Updated to use perriera/extras v4.16.0

#### 0.5.1 (2021-10-17)

### Changed

- Fixed Link issue

#### 0.5.0 (2021-10-17)

### Changed

- Update for use with perriera/extras 3.22

#### 0.4.2 (2021-09-07)

### Changed

- Added instances/ directory

#### 0.4.1 (2021-09-07)

### Changed

- CMakeLists.txt entry for runtime instances

### Removed

- Unnecessary file

#### 0.4.0 (2021-09-03)

### Moved

- Vendor files

#### 0.3.1 (2021-09-03)

### Removed

- Renamed identifier

#### 0.3.0 (2021-09-03)

### Removed

- extras_cpp source code

#### 0.2.0 (2021-09-03)

### Added

- SHARED library support
- (perriera) extras library support, (3.11.0)
- CPM.cmake support
  - [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake/blob/master/LICENSE)
  - This allows us to include other Github packages with the ability
    to add package OPTIONS
- FakeIt Mock Library support
  - [FakeIt](https://github.com/eranpeer/FakeIt)
  - This gives us the ability to mock C++ interfaces, (before implementation)
- Catch2 support
  - [Catch2](https://github.com/catchorg/Catch2)
  - This gives us the ability to test C++ classes, (during implementation)

### Changed

- CMakeLists.txt
  - [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter/blob/master/LICENSE)
- spdlog is now used as a shared library, (libspdlog.so)
- cpr is now used as a shared library, (libcpr.so)
- placed all source into /src
- placed all headers into /include/extras_cpp

#### 0.1.0 (2021-08-26)

### Added

- Fetch_Content support
- changelog.md
- Project VERSION inside CMakeLists.txt & changelog.md
- Adopted new changelog format.
- sudo make install parameters
- shared library support
- sudo checkinstall support
- GoF: Abstract design pattern support
- Debian package support
- extra/interfaces.hpp support
- Unit test casses support, (Catch2)
- Mock framework support, (FakeIt)

### Changed

- CMakeLists.txt revamped & streamlined
- README.md revamped & streamlined
- Added documentation on code
- cxx_std_17 on all targets
- std::filesystem on all targets

### Maintained

- @brief style formatting
- Doxygen support

### Removed

- Conan package manager deprecated

[unreleased]: https://github.com/perriera/extras_cpp/compare/v0.17.0...HEAD
[0.17.0]: https://github.com/perriera/extras_cpp/compare/v0.16.1...v0.17.0
[0.16.1]: https://github.com/perriera/extras_cpp/compare/v0.16.0...v0.16.1
[0.16.0]: https://github.com/perriera/extras_cpp/compare/v0.15.0...v0.16.0
[0.15.0]: https://github.com/perriera/extras_cpp/compare/v0.14.0...v0.15.0
[0.14.0]: https://github.com/perriera/extras_cpp/compare/v0.13.0...v0.14.0
[0.13.0]: https://github.com/perriera/extras_cpp/compare/v0.12.0...v0.13.0
[0.12.0]: https://github.com/perriera/extras_cpp/compare/v0.11.0...v0.12.0
[0.11.0]: https://github.com/perriera/extras_cpp/compare/v0.10.0...v0.11.0
[0.10.0]: https://github.com/perriera/extras_cpp/compare/v0.9.0...v0.10.0
[0.9.0]: https://github.com/perriera/extras_cpp/compare/v0.8.4...v0.9.0
[0.8.0]: https://github.com/perriera/extras_cpp/compare/v0.7.0...v0.8.4
[0.7.0]: https://github.com/perriera/extras_cpp/compare/v0.6.6...v0.7.0
[0.6.6]: https://github.com/perriera/extras_cpp/compare/v0.5.6...v0.6.0
[0.5.6]: https://github.com/perriera/extras_cpp/compare/v0.5.5...v0.5.6
[0.5.5]: https://github.com/perriera/extras_cpp/compare/v0.5.4...v0.5.5
[0.5.4]: https://github.com/perriera/extras_cpp/compare/v0.5.3...v0.5.4
[0.5.3]: https://github.com/perriera/extras_cpp/compare/v0.5.2...v0.5.3
[0.5.2]: https://github.com/perriera/extras_cpp/compare/v0.5.1...v0.5.2
[0.5.1]: https://github.com/perriera/extras_cpp/compare/v0.5.0...v0.5.1
[0.5.0]: https://github.com/perriera/extras_cpp/compare/v0.4.2...v0.5.0
[0.4.2]: https://github.com/perriera/extras_cpp/compare/v0.4.1...v0.4.2
[0.4.1]: https://github.com/perriera/extras_cpp/compare/v0.4.0...v0.4.1
[0.4.0]: https://github.com/perriera/extras_cpp/compare/v0.3.1...v0.4.0
[0.3.1]: https://github.com/perriera/extras_cpp/compare/v0.3.0...v0.3.1
[0.3.0]: https://github.com/perriera/extras_cpp/compare/v0.2.0...v0.3.0
[0.2.0]: https://github.com/perriera/extras_cpp/compare/v0.1.0...v0.2.0
[0.1.0]: https://github.com/perriera/extras_cpp/releases/tag/v0.1.0
