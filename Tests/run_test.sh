#!/bin/bash

mkdir -p ./Build/Tests
touch Build/.gitignore
echo "*" > Build/.gitignore
rm -f ./Build/Tests/*


path=$(dirname $0)
echo 
for path in $(find $path -name '*.test.c')
do
    file_name=$(basename $path)
    file_name=${file_name%%.*}
    out=./Build/Tests/${file_name%%.*}.o
    `gcc -g -o$out -I. AES.c -x c $path                 
    # \
        # -DEND_TEST=" return 0;}"                        \
        # -DFAIL_TEST=" exit(1); "                        \
        # -DPASS_TEST=" exit(0); "                        \
        # -DSTART_TEST="int main(int argc, char**argv){"`
    if [[ $? -eq 0 ]]
    then
    bash ./Tests/run_file.sh $file_name $out
    else
    echo "Can't launch test: $file_name"
    fi
done