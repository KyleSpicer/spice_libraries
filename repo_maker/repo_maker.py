#!/usr/bin/env python3

import os
import shutil


def add_git_ignore(repo_name: str) -> None:
    gitignore_path = os.path.join(".", ".gitignore")

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


def generate_dirs() -> None:
    # directory structure
    dirs = ["src",
            "test",
            "doc"]

    # generate directories
    for dir in dirs:
        os.makedirs(os.path.join(os.getcwd(), dir))


def add_makefile(repo_name) -> None:
    home_dir = os.path.expanduser("~")
    makefile_path = os.path.join(
        home_dir,
        "Desktop",
        "github",
        "spice_libraries",
        "repo_maker",
        "c_repo",
        "Makefile")
    shutil.copyfile(makefile_path, os.path.join(".", "Makefile"))

    # read the contents of the Makefile
    with open(makefile_path, "r") as f:
        makefile_contents = f.read()

    # modify the repo_name variable in the Makefile
    new_makefile_contents = makefile_contents.replace(
        "BIN := ", f"BIN := {repo_name}")

    # write the modified contents back to the Makefile
    with open("Makefile", "w") as f:
        f.write(new_makefile_contents)


def add_project_driver(repo_name) -> None:
    # set the path to the src file template file in the root directory
    home_dir = os.path.expanduser("~")
    template_file_path = os.path.join(
        home_dir,
        "Desktop",
        "github",
        "spice_libraries",
        "repo_maker",
        "c_repo",
        "driver.c"
    )

    # set the destination path for the template file in the src folder
    dest_file_path = os.path.join(".", f"{repo_name}_driver.c")

    # copy the template file to the src folder
    shutil.copy2(template_file_path, dest_file_path)


def add_py_unittest_template(repo_name: str) -> None:
    # set the path to the test folder
    test_path = os.path.join(".", "test")

    # create the test folder if it doesn't exist
    if not os.path.exists(test_path):
        os.makedirs(test_path)

    # set the path to the unittest template file in the root directory
    home_dir = os.path.expanduser("~")
    template_file_path = os.path.join(
        home_dir,
        "Desktop",
        "github",
        "spice_libraries",
        "repo_maker",
        "py_repo",
        "test_driver.py"
    )

    # set the destination path for the template file in the test folder
    dest_file_path = os.path.join(test_path, f"test_{repo_name}.py")

    # copy the template file to the test folder
    shutil.copy2(template_file_path, dest_file_path)


def add_py_src_template(repo_name: str) -> None:

    # set the path to the src file template file in the root directory
    home_dir = os.path.expanduser("~")
    template_file_path = os.path.join(
        home_dir,
        "Desktop",
        "github",
        "spice_libraries",
        "repo_maker",
        "py_repo",
        "driver.py"
    )

    # set the destination path for the template file in the src folder
    dest_file_path = os.path.join(".", f"{repo_name}.py")

    # copy the template file to the src folder
    shutil.copy2(template_file_path, dest_file_path)


def add_c_unittest_template(repo_name: str) -> None:
    # set the path to the test folder
    test_path = os.path.join(".", "test")

    # create the test folder if it doesn't exist
    if not os.path.exists(test_path):
        os.makedirs(test_path)

    # set the path to the unittest template file in the root directory
    home_dir = os.path.expanduser("~")
    template_file_path = os.path.join(
        home_dir,
        "Desktop",
        "github",
        "spice_libraries",
        "repo_maker",
        "c_repo",
        "check.c"
    )

    # set the destination path for the template file in the test folder
    dest_file_path = os.path.join(test_path, f"check_{repo_name}.c")

    # copy the template file to the test folder
    shutil.copy2(template_file_path, dest_file_path)


def update_c_unittest_template(repo_name: str) -> None:
    # set the path to the test folder
    test_path = os.path.join(".", "test")

    # set the path to the unittest template file in the test folder
    template_file_path = os.path.join(test_path, f"check_{repo_name}.c")

    # open the template file and read its content
    with open(template_file_path, "r") as f:
        content = f.read()

    # replace all instances of "PROJECT_NAME" with the repo_name argument
    content = content.replace("PROJECT_SUITE", f"check_{repo_name}_suite")

    # open the template file again, but this time in write mode
    with open(template_file_path, "w") as f:
        # write the updated content back to the file
        f.write(content)


def make_py_repo(repo_name: str):

    generate_dirs()

    src_path = os.path.join(".", "src")
    test_path = os.path.join(".", "test")

    add_py_unittest_template(repo_name)
    add_py_src_template(repo_name)

    # set the paths to the src and test folders
    src_path = os.path.join(".", "src")
    test_path = os.path.join(".", "test")

    # create empty __init__.py files in each folder
    init_file_path = os.path.join(src_path, "__init__.py")
    with open(init_file_path, "w") as init_file:
        pass

    init_file_path = os.path.join(test_path, "__init__.py")
    with open(init_file_path, "w") as init_file:
        pass


def make_c_repo(repo_name: str):
    # create dirs
    generate_dirs()

    # add custom makefile
    add_makefile(repo_name)

    # add driver to project root directory
    add_project_driver(repo_name)

    # add unit test file
    add_c_unittest_template(repo_name)
    update_c_unittest_template(repo_name)


def main():

    # prompt user for repo name
    repo_name = get_repo_name()

    # prompt user for type of repo
    repo_type = get_repo_type()

    if repo_type == 'c':
        make_c_repo(repo_name)

    elif repo_type == 'py':
        make_py_repo(repo_name)

    # add git ignore
    add_git_ignore(repo_name)

    ending_message(repo_type, repo_name)


if __name__ == "__main__":
    try:
        main()
    except (KeyboardInterrupt):
        print("Exiting Program.")
