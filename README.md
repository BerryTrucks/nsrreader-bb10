# NSR Reader

## Development

To build NSR Reader with Momentics SDK, you'll need to compile the `nsrreadercore` library first:

```
git clone https://github.com/BerryTrucks/nsrreadercore
git clone https://github.com/BerryTrucks/nsrreader-bb10
```

Build nsrreadercore:

```
cd nsrreadercore
cmake -DCMAKE_TOOLCHAIN_FILE=../nsrreadercore/platforms/blackberry.cmake -DCMAKE_ASM_NASM_COMPILER=/opt/local/bin/nasm -DCMAKE_BUILD_TYPE=Release
make
```

Copy it into the `nsrreader-bb10` assets subdirectorry:

```
mkdir nsrreader-bb10/assets/lib
cp nsrreadercore.so nsrreader-bb10/assets/lib
```

Switch to the desired NSR Reader version:

```
cd nsrreader-bb10
sh switch_version.sh 10.3 full
```

Then build with the Momentics SDK.

## See also

* https://github.com/BerryTrucks/main/wiki/Building-imported-BB10-projects-in-Momentics
