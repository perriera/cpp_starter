## 32bit or 64bit support
> (perriera) extras now supports gcc 7.5.0 and 32bit support.
> at the moment 32bit support is setup in the project
> to switch back to 64bit support
> remove '-m32' frin lines 53 & 54 in CMakeLists.txt 
> and change 6.1.0 to 6.0.0 on line 129 in libextras_cpp.so.0.1.0
> (or whatever version of extras that supports 32 or 64 bit mode)

Now this might change again so you will have to be conscious of this parameter when setting up a project for 32bit support

To check what type of shared library you produced do this:<br/>

cd build$ file libextras_cpp.so.0.1.0<br/><br/>
libextras_cpp.so.0.1.0: ELF 32-bit LSB shared object, Intel 80386, version 1 (SYSV), dynamically linked, BuildID[sha1]=854b1299e523cbac6487e574e009fdafe6193d88, with debug_info, not stripped



