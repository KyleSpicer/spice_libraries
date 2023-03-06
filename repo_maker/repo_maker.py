#!/usr/bin/env python3

import os
import shutil


def add_git_ignore(repo_name: str) -> None:
    gitignore_path = os.path.join(".", repo_name, ".gitignore")

    # Write the contents of the .gitignore file
    with open(gitignore_path, "w") as gitignore_file:
        gitignore_file.write(
            "# Ignore compiled object files and executables\n")
        gitignore_file.write("*.exe\n")


def ending_message(repo_type, repo_name) -> None:
    print(
        f"Successfully created {repo_type.upper()} repository named '{repo_name}'.")


def get_repo_name() -> str:
    while True:
        try:
            repo_name = input("Enter name of repo: ")
            result = input(f"Is '{repo_name}' correct? (y/n): ")
            if result.lower() == 'y':
                return repo_name
            elif result.lower() == 'n':
                continue

        except KeyboardInterrupt:
            print("\nExiting program.")
            exit(0)

        except (ValueError, TypeError):
            print("Error occured while creating repo.")


def get_repo_type() -> str:
    # prompt user for type of repo
    while True:
        try:
            repo_type = input("Enter type of repo (py or c): ")
            if repo_type.lower() == 'py':
                return 'py'
            elif repo_type.lower() == 'c':
                return 'c'
        except KeyboardInterrupt:
            print("\nExiting program.")
            exit(0)
        except (ValueError, TypeError):
            print("Error occured while creating repo.")


def generate_dirs(repo_name: str) -> None:
    # directory structure
    dirs = [os.path.join(repo_name, "src"),
            os.path.join(repo_name, "test"),
            os.path.join(repo_name, "doc")]

    # create directories
    for dir in dirs:
        os.makedirs(dir)


def make_c_repo(repo_name: str):
    generate_dirs(repo_name)

    home_dir = os.path.expanduser("~")
    makefile_path = os.path.join(
        home_dir,
        "Desktop",
        "github",
        "spice_libraries",
        "repo_maker",
        "c_repo",
        "Makefile")
    shutil.copyfile(makefile_path, os.path.join(".", repo_name, "Makefile"))


def add_py_src_and_unittest(repo_name: str) -> None:
    repo_path = '.'
    test_path = "test"

    root_path = os.path.join(repo_path, repo_name)
    test_path = os.path.join(root_path, "test")

    # copy files
    root_file_path = "/home/kylespicer/Desktop/github/spice_libraries/repo_maker/py_repo/driver.py"
    shutil.copy(root_file_path, root_path)

    test_file_path = "/home/kylespicer/Desktop/github/spice_libraries/repo_maker/py_repo/test_driver.py"
    shutil.copy(test_file_path, test_path)


def make_py_repo(repo_name: str):
    generate_dirs(repo_name)

    src_path = os.path.join(".", repo_name, "src")
    test_path = os.path.join(".", repo_name, "test")

    add_py_src_and_unittest(repo_name)

    # create empty init files
    init_file_path = os.path.join(src_path, "__init__.py")
    with open(init_file_path, "w") as init_file:
        pass

    init_file_path = os.path.join(test_path, "__init__.py")
    with open(init_file_path, "w") as init_file:
        pass


def main():

    # prompt user for type of repo
    repo_type = get_repo_type()

    # prompt user for repo name
    repo_name = get_repo_name()

    # add git ignore

    if repo_type == 'c':
        make_c_repo(repo_name)

    elif repo_type == 'py':
        make_py_repo(repo_name)

    add_git_ignore(repo_name)

    ending_message(repo_type, repo_name)


if __name__ == "__main__":
    try:
        main()
    except (KeyboardInterrupt):
        print("Quitting")
