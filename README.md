# polyscope-py
Python bindings for Polyscope. https://polyscope.run

[![travis build status](https://travis-ci.com/nmwsharp/polyscope-py.svg?branch=master)](https://travis-ci.com/nmwsharp/polyscope-py)
[![appveyor build status](https://ci.appveyor.com/api/projects/status/epf2tpgc0oarjrrx/branch/master?svg=true)](https://ci.appveyor.com/project/nmwsharp/polyscope-py/branch/master)
[![PyPI](https://img.shields.io/pypi/v/polyscope?style=plastic)](https://pypi.org/project/polyscope/)
[![Conda](https://img.shields.io/conda/v/conda-forge/polyscope)](https://anaconda.org/conda-forge/polyscope)

This library is a python wrapper and deployment system. The core C++ library lives at https://github.com/nmwsharp/polyscope.

### Installation

```
python -m pip install polyscope
```

or

```
conda install -c conda-forge polyscope
```

polyscope-py should work out-of-the-box on any combination of Python 2.7-3.7 and Linux/macOS/Windows. Your graphics hardware must support OpenGL >= 3.3 core profile.

## For developers

This repo is configured with CI on both travis and appveyor. Travis is useful for running tests and quick builds, but appveyor generates final deployment wheels, because it supports a broader combination of platforms.

### Deploy a new version

- Commit the desired version to the `master` branch, be sure the version string in `setup.py` corresponds to the new version number.
- Watch the travis & appveyor builds to ensure the test & build stages succeeds and all wheels are compiled (takes ~1 hr on Travis, ~2 hrs on Appveyor).
- While you're waiting, update the docs, including the changelog.
- Tag the commit with a tag like `v1.2.3`, matching the version in `setup.py`. This will kick off a new Appveyor build which deploys the wheels to PyPI after compilation.
- Update the conda builds with a commit to the feedstock repository (TODO link). This should just require bumping the version number in `meta.yml`.
