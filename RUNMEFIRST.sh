#!/usr/bin/env bash

if test -z "$(type -p)" ; 
then 
    echo "bash shell detected" ; 
else 
    echo "bash shell required" ; 
    exit;
fi

git add .; git commit -m "Added 0.0.0"; git push
git tag -a v0.0.0 -m "created from extras_cpp"
git push origin v0.0.0
git log
git tag

FILE=$PWD
# basename "$PWD"
f="$(basename -- $PWD)"
readarray -d _ -t splitNoIFS<<< "$f"
n1=${splitNoIFS[0]}
n2=${splitNoIFS[1]}
f1=$(echo "$f" | tr '[:upper:]' '[:lower:]')
f2=$(echo "$f" | tr '[:lower:]' '[:upper:]')
echo $f1
echo $f2
n1=$(echo "$n1" | tr '[:upper:]' '[:lower:]')
n2=$(echo "$n2" | tr '[:upper:]' '[:lower:]')
echo $n1
echo $n2

s=""
if [ "$n2" = "" ];
then
    echo "no sub namespace detected"
    echo "adding a 'reassign' namespace"
    n2="reassign"
fi

rm -rf build

find . -type f -name *.h* -print0 | xargs -0 sed -i "s/EXTRAS_CPP/$f2/g"
find . -type f -name *.c* -print0 | xargs -0 sed -i "s/EXTRAS_CPP/$f2/g"
find . -type f -name *.t* -print0 | xargs -0 sed -i "s/EXTRAS_CPP/$f2/g"
find . -type f -name '*.md' -print0 | xargs -0 sed -i "s/EXTRAS_CPP/$f2/g"
find . -type f -name *.h* -print0 | xargs -0 sed -i "s/extras_cpp/$f1/g"
find . -type f -name *.c* -print0 | xargs -0 sed -i "s/extras_cpp/$f1/g"
find . -type f -name *.t* -print0 | xargs -0 sed -i "s/extras_cpp/$f1/g"
find . -type f -name '*.md' -print0 | xargs -0 sed -i "s/extras_cpp/$f1/g"

find . -type f -name '*.h*' -print0 | xargs -0 sed -i "s/namespace extras/namespace $n1/g"
find . -type f -name '*.h*' -print0 | xargs -0 sed -i "s/namespace cpp/namespace $n2/g"
find . -type f -name '*.c*' -print0 | xargs -0 sed -i "s/namespace extras/namespace $n1/g"
find . -type f -name '*.c*' -print0 | xargs -0 sed -i "s/namespace cpp/namespace $n2/g"

find . -type f -name '*.c*' -print0 | xargs -0 sed -i "s/extras::cpp/$n1::$n2/g"
find . -type f -name '*.c*' -print0 | xargs -0 sed -i "s/cpp::game/$n2::game/g"
find . -type f -name '*.c*' -print0 | xargs -0 sed -i "s/$n1::cpp/$n1::$n2/g"

find . -type f -name launch.json -print0 | xargs -0 sed -i "s/cpp::game::/$n2::game::/g"

mv include/extras_cpp include/$f1

mkdir build
cd build
cmake ..
make
cd ..
build/run-unittests-$f1

rm RUNMEFIRST.sh

git add .; git commit -m "Added 0.1.0"; git push
git tag -a v0.1.0 -m "$f1 created using (perriera)/extras (8.x.x series)"
git push origin v0.1.0
git log
git tag

clear

ls -la 

cd docs
git clone https://github.com/perriera/for_extras.git
cd ..

echo $f1 now setup and committed as tag "(v0.1.0)"
git tag -n

bin/update_docs.sh

echo NEXT STEPS:
echo you may now open your favorite text editor and set a breakpoint
echo on line 60 of test/interfaces/chessgame/mold_interfaces  
echo for those of you using Visual Studio Code merely type 'code .'
