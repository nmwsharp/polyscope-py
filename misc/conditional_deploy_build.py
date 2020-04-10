import os, subprocess

# print(os.getenv("APPVEYOR_REPO_TAG"))

if os.getenv("APPVEYOR_REPO_TAG") == "true":
    subprocess.Popen(['python','-m', 'twine', 'upload','--skip-existing', 'wheelhouse/*.whl'])
    subprocess.Popen(['python','-m', 'twine', 'upload','--skip-existing', 'wheelhouse/*.tar.gz'])
else:
    print("no deploying, no appveyor tag present")
