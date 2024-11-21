import os, sys, json, shutil, subprocess

# =============================================================
# ==== Step 0: Path management and other setup
# =============================================================

PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
IMGUI_ROOT = os.path.join(PROJECT_ROOT, "deps", "polyscope", "deps", "imgui", "imgui")
CIMGUI_ROOT = os.path.join(PROJECT_ROOT, "deps", "cimgui")
CIMGUI_IMGUI_ROOT = os.path.join(PROJECT_ROOT, "deps", "cimgui", "imgui")
DEFINITIONS_PATH = os.path.join(CIMGUI_ROOT, "generator", "output", "definitions.json")


# =============================================================
# ==== Step 1: Make sure we have the right version of the 
# ====         cimgui repo available
# =============================================================

# Make sure the cimgui repo been cloned
if not os.path.isdir(CIMGUI_ROOT):
    raise ValueError("Please clone https://github.com/cimgui/cimgui into deps/cimgui. Checkout the commit which matches the current imgui version.")

# Helper to test versions
def check_git_repo_commit(repo_path):
    if not os.path.isdir(os.path.join(PROJECT_ROOT, "deps", "cimgui")):
        raise ValueError(f"No directory at {repo_path}")

    cmd = "git -C {} rev-parse HEAD && git -C {} describe --tags".format(repo_path, repo_path)
    print(f"Testing git repo with cmd: {cmd}")

    result = subprocess.check_output(cmd, shell=True, text=True)
    commit_hash, tag = result.strip().split('\n')

    print(f"\nRepo at {repo_path} has:")
    print(f" commit: {commit_hash}")
    print(f"    tag: {tag}")

    return commit_hash, tag

# Test that the proper versions are checked out
imgui_commit, imgui_tag = check_git_repo_commit(IMGUI_ROOT)
cimgui_commit, cimgui_tag = check_git_repo_commit(CIMGUI_IMGUI_ROOT)
if imgui_commit != cimgui_commit:

    print(f"""\nThe cimgui library maintains its own copy of imgui, which must match polyscope's verion of imgui. 
    cimgui/imgui commit: {cimgui_commit}  
    imgui commit: {imgui_commit}. 
Please check out the correct version of cimgui to {CIMGUI_ROOT}

cimgui tags its branchs with names matching imgui versions. You can probably 
get the correct one with something like `git checkout 1.90.4`.  Don't forget 
`git submodule update --recursive` after.  Exiting.
    """)
    sys.exit()


# =============================================================
# ==== Step 2: Setup and grab the spec
# =============================================================

with open(DEFINITIONS_PATH, 'r') as file:
    definitions = json.load(file)

print(definitions)

# =============================================================
# ==== Step 3: Emit bindings code
# =============================================================