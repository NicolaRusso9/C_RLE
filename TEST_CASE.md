# Execution TEST after building with make:

1) Compression:
```bash
if [[ ! "./" -ef "build" ]]; then
    echo "Moving to build path"
    cd build
fi

./C_Compressor -c ../test_files/test.txt
```

2) Decompression:
```bash
if [[ ! "./" -ef "build" ]]; then
    echo "Moving to build path"
    cd build
fi

./C_Compressor -d ../test_files/test.rle
```

3) No such file or directory error:
```bash
if [[ ! "./" -ef "build" ]]; then
    echo "Moving to build path"
    cd build
fi

./C_Compressor -c ../test_files/o.txt
./C_Compressor -c ../testFILE/test.txt
```

4) Missing file path argument:
```bash
if [[ ! "./" -ef "build" ]]; then
    echo "Moving to build path"
    cd build
fi

./C_Compressor -c
./C_Compressor ../test_files/o.txt     
```

5) Unknown flag:
```bash
if [[ ! "./" -ef "build" ]]; then
    echo "Moving to build path"
    cd build
fi

./C_Compressor -g ../test_files/o.txt
```