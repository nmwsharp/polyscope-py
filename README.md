# polyscope-py
Python bindings for Polyscope. https://polyscope.run

[![Build Status](https://travis-ci.com/nmwsharp/polyscope-py.svg?branch=master)](https://travis-ci.com/nmwsharp/polyscope-py)

This library is a python wrapper and deployment system. The core C++ library lives at https://github.com/nmwsharp/polyscope.

### Installation

```
pip install polyscope
```

polyscope-py should work out-of-the-box on any combination of Python 2.7-3.7 and Linux/macOS/Windows. Your graphics hardware must support OpenGL >= 3.3 core profile.

## For developors

### Deploy a new version

- Commit the desired version to the `master` branch, be sure the version string in `setup.py` corresponds to the new version number.
- Watch the travis builds to ensure the `build` stage succeeds and all wheels are compiled (takes ~45 min).
- While you're waiting, update the docs, including the changelog.
- Tag the commit with a tag like `v1.2.3`, matching the version in `setup.py`. This will kick off a new travis build which includes a `deploy` stage, uploading all of the compiled wheels to pypi on success (takes ~90 minutes).
