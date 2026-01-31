import unittest
import os
import sys
import os.path as path
from collections import defaultdict

# Path to where the bindings live
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "src")))
if os.name == "nt":  # if Windows
    # handle default location where VS puts binary
    sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "build", "Debug")))
else:
    # normal / unix case
    sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "build")))

import polyscope as ps
import argparse


def print_discovered_tests_summary(suite, full_listing=False):
    def summarize_tests(suite):
        summary = defaultdict(list)

        def collect_tests(suite):
            for test in suite:
                if isinstance(test, unittest.TestSuite):
                    collect_tests(test)
                else:
                    test_id = test.id()
                    class_name = ".".join(test_id.split(".")[:-1])
                    method_name = test_id.split(".")[-1]
                    summary[class_name].append(method_name)

        collect_tests(suite)
        return summary

    summary = summarize_tests(suite)

    print(f"Found {sum(len(tests) for tests in summary.values())} tests in {len(summary)} test classes.")

    if full_listing:
        for class_name, methods in sorted(summary.items()):
            print(f"{class_name} ({len(methods)} tests)")
            for method in sorted(methods):
                print(f"  - {method}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--backend", default="openGL_mock", help="Backend to use for testing (default: openGL_mock)")
    parser.add_argument("--verbose", action="store_true", help="Enable verbose output")
    parser.add_argument("--failfast", action="store_true", help="Fail fast")
    args = parser.parse_args()

    ps_backend = args.backend
    print(f"Testing polyscope version: {ps.__version__}  test_backend: {ps_backend}")

    # Really global setup.
    # Note that since these tests depend on the bound object's global state,
    # we generally cannot continue past the first failed test.
    ps.set_errors_throw_exceptions(True)
    ps.set_display_message_popups(False)
    ps.set_warn_for_invalid_values(False)
    ps.set_hide_window_after_show(False)  # (makes tests run faster)
    ps.set_use_prefs_file(False)
    ps.init(ps_backend)

    # Discover tests in the default 'tests' folder
    tests_folder_path = path.join(path.dirname(__file__), "tests")
    loader = unittest.TestLoader()
    suite = loader.discover(start_dir=tests_folder_path, pattern="test*.py")
    print_discovered_tests_summary(suite, full_listing=False)

    # unittest.main()# Run the discovered tests
    runner = unittest.TextTestRunner(verbosity=2 if args.verbose else 1, failfast=args.failfast)
    runner.run(suite)
