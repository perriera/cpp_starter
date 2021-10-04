
# Changelog
> All notable changes to this project will be documented in this file.</br>
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).</br>
> To add a tag to the git repository do:
> > git tag -a v0.10.0 -m "CHES-11"</br>
> > git push origin v0.10.0
> 

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

#### 0.10.0 (2021-09-01)
### Resolved
- CHES-11: ChessBoard

#### 0.9.0 (2021-09-01)
### Resolved
- CHES-10: ChessBoard

#### 0.8.0 (2021-09-01)
### Resolved
- CHES-9: ChessMoves
### Added
- SANInterface added, (CHES-9)

#### 0.7.0 (2021-09-01)
### Resolved
- CHES-8: PGN to FEN format
### Added
- PGNGameInterface added, (CHES-8)
* The ability to properly read a PGN file now 
* using FEN files, (to determine missing PGN data)

#### 0.6.0 (2021-08-26)
### Added
- ChessGameInterface, (CHES-6)

#### 0.5.0 (2021-08-26)
### Added
- FENLineInterface

#### 0.4.0 (2021-08-26)
### Changed
- Updated README.md

#### 0.3.0 (2021-08-26)
### Changed
- Added PGN data
- Correct changelog

#### 0.2.0 (2021-08-26)
### Added
- SHARED library support
- (perriera) extras library support, (3.2.1)
- CPM.cmake support
  * [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake/blob/master/LICENSE) 
  * This allows us to include other Github packages with the ability
    to add package OPTIONS
- FakeIt Mock Library support
  * [FakeIt](https://github.com/eranpeer/FakeIt) 
  * This gives us the ability to mock C++ interfaces, (before implementation)
- Catch2 support
  * [Catch2](https://github.com/catchorg/Catch2)
  * This gives us the ability to test C++ classes, (during implementation)
### Changed
- CMakeLists.txt
  * [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter/blob/master/LICENSE) 
- spdlog is now used as a shared library, (libspdlog.so)
- cpr is now used as a shared library, (libcpr.so)
- placed all source into /src
- placed all headers into /include/chessmind

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

[Unreleased]: https://github.com/perriera/chessmind.git/compare/v0.10.0...HEAD
[0.10.0]: https://github.com/perriera/chessmind.git/compare/v0.9.0...v0.10.0
[0.9.0]: https://github.com/perriera/chessmind.git/compare/v0.8.0...v0.9.0
[0.8.0]: https://github.com/perriera/chessmind.git/compare/v0.7.0...v0.8.0
[0.7.0]: https://github.com/perriera/chessmind.git/compare/v0.6.0...v0.7.0
[0.6.0]: https://github.com/perriera/chessmind.git/compare/v0.5.0...v0.6.0
[0.5.0]: https://github.com/perriera/chessmind.git/compare/v0.4.0...v0.5.0
[0.3.0]: https://github.com/perriera/chessmind.git/compare/v0.3.0...v0.4.0
[0.3.0]: https://github.com/perriera/chessmind.git/compare/v0.2.0...v0.3.0
[0.2.0]: https://github.com/perriera/chessmind.git/compare/v0.1.0...v0.2.0
[0.1.0]: https://github.com/perriera/chessmind.git/releases/tag/v0.1.0
