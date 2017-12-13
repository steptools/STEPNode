
# Building the Package

When new commits are pushed to GitHub, the STEPNode package is built on
Windows, Mac, and Linux by Jenkins. For local building on your machine,
install node from [nodejs.org](https://nodejs.org). At the time of
writing we use Node 8.x. This also installs \"npm\" into your path.

Next, install node-gyp globally.

``` {.code}
npm install -g node-gyp
```

Python must also be present, as discussed in the [node-gyp
documentation](https://github.com/nodejs/node-gyp#configuration).
Currently this requires python 2.7 from
[python.org](https://www.python.org/downloads/) and you need to
manually add it to your path.

The package uses the full STEP Tools software stack, so you must have
previously installed the `stdev_core`, `stdev_stpstack`, and
`stdev_ncstack` packages.  The config files assume a particular
compiler configuration, so you must set the STEP Tools library version
(ROSE_LIB) as follows:


``` {.code}
WINDOWS:   %ROSE%\lib\x64_win64_vc14_md  (OR usearea -win64 -vc14)
LINUX:     default
MAC:       default
```

Build by calling npm or node-gyp directly.

``` {.code}
cd STEPNode
npm install   # first time to download all packages

# subsequent times to rebuild
node-gyp rebuild --msvs_version=2015

# another way, if project config files do not change.
node-gyp configure --msvs_version=2015
node-gyp build
```

You can avoid the msvs flag if you set the environment variable
npm\_config\_msvs\_version to 2015 in your shell init.

The output of the build will be in the `build/Release` directory.  To
use a locally built module with NC.js, copy the StepNode.node file
into your NC.js project\'s `node_modules/STEPNode/Win` directory.
