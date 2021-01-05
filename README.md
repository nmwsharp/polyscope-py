# polyscope-py
Python bindings for Polyscope. https://polyscope.run/py

[![travis build status](https://travis-ci.com/nmwsharp/polyscope-py.svg?branch=master)](https://travis-ci.com/nmwsharp/polyscope-py)
[![appveyor build status](https://ci.appveyor.com/api/projects/status/epf2tpgc0oarjrrx/branch/master?svg=true)](https://ci.appveyor.com/project/nmwsharp/polyscope-py/branch/master)
[![PyPI](https://img.shields.io/pypi/v/polyscope?style=plastic)](https://pypi.org/project/polyscope/)
[![Conda](https://img.shields.io/conda/v/conda-forge/polyscope)](https://anaconda.org/conda-forge/polyscope)

This library is a python wrapper and deployment system. The core library lives at https://github.com/nmwsharp/polyscope. See documentation at https://polyscope.run/py.

### Installation

```
python -m pip install polyscope
```

or

```
conda install -c conda-forge polyscope
```

polyscope-py should work out-of-the-box on any combination of Python 2.7, 3.5-3.8 and Linux/macOS/Windows. Your graphics hardware must support OpenGL >= 3.3 core profile.

## For developers

This repo is configured with CI on github actions. 

- By default, all commits to the main branch build & run tests. Use `[ci skip]` to skip this.
- Tagging a commit with `[ci build]` causes it to also build all precompiled wheels and upload them as artifacts.
- Creating a tagged version like `v1.2.3` will build wheels as above, and ALSO automatically upload them to pypi as described below.

### Deploy a new version

- Commit the desired version to the `master` branch, be sure the version string in `setup.py` corresponds to the new version number. Use the `[ci build]` tag in the commit message to trigger builds.
- Watch the github actions builds to ensure all wheels build successfully. The resulting binaries will be saved as artifacts if you want try test with them.
- While you're waiting, update the docs, including the changelog.
- Tag the commit with a tag like `v1.2.3`, matching the version in `setup.py`. This will kick off a new github actions build which deploys the wheels to PyPI after compilation.
- Update the conda builds by committing to the [feedstock repository](https://github.com/conda-forge/polyscope-feedstock). This generally just requires bumping the version number and updating the hash in `meta.yml`. Since `meta.yml` is configured to pull source from PyPi, you can't do this until after the source build has been uploaded from the github action.
