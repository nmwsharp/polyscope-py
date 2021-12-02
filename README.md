# polyscope-py
Python bindings for Polyscope. https://polyscope.run/py

[![Linux](https://github.com/nmwsharp/polyscope-py/workflows/Test%20Linux/badge.svg)](https://github.com/nmwsharp/polyscope-py/actions)
[![macOS](https://github.com/nmwsharp/polyscope-py/workflows/Test%20macOS/badge.svg)](https://github.com/nmwsharp/polyscope-py/actions)
[![Windows](https://github.com/nmwsharp/polyscope-py/workflows/Test%20Windows/badge.svg)](https://github.com/nmwsharp/polyscope-py/actions)
[![PyPI](https://img.shields.io/pypi/v/polyscope?style=plastic)](https://pypi.org/project/polyscope/)
[![Conda](https://img.shields.io/conda/v/conda-forge/polyscope)](https://anaconda.org/conda-forge/polyscope)

This library is a python wrapper and deployment system. The core library lives at https://github.com/nmwsharp/polyscope. See documentation at https://polyscope.run/py.

To contribute, check out the [instructions here](https://polyscope.run/about/contributing/).

### Installation

```
python -m pip install polyscope
```

or

```
conda install -c conda-forge polyscope
```

polyscope-py should work out-of-the-box on any combination of Python 3.5-3.9 and Linux/macOS/Windows. Your graphics hardware must support OpenGL >= 3.3 core profile.

## For developers

This repo is configured with CI on github actions. 

- By default, all commits to the main branch build & run tests. Use `[ci skip]` to skip this.
- Tagging a commit with `[ci build]` causes it to also build all precompiled wheels and upload them as artifacts.
- Creating a tagged version like `v1.2.3` will build wheels as above, and ALSO automatically upload them to pypi as described below.

### Deploy a new version

- Commit the desired version to the `master` branch, be sure the version string in `setup.py` corresponds to the new version number. Use the `[ci build]` tag in the commit message to trigger builds, which should take about an hour.
- Watch the github actions builds to ensure all wheels build successfully. The resulting binaries will be saved as artifacts if you want try test with them.
- While you're waiting, update the docs, including the changelog.
- Tag the commit with a tag like `v1.2.3`, matching the version in `setup.py`. This will kick off a new github actions build which deploys the wheels to PyPI after compilation.
- If we are still doing builds with multiple rounds of actions, it may be necessary to manually upload some of the generated wheels. Download from the github actions `Summary/Artifacs` pane, then upload with `twine upload * --skip-existing`
- Update the conda builds by committing to the [feedstock repository](https://github.com/conda-forge/polyscope-feedstock). This generally just requires bumping the version number and updating the hash in `meta.yml`. Since `meta.yml` is configured to pull source from PyPi, you can't do this until after the source build has been uploaded from the github action.
