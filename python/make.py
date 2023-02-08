import argparse
import sys
import subprocess

loop_dir = "for filename in $(find . -name '*.py'); do "
end = "; done"


def make_text_bold(text: str) -> str:
    return f"\033[1m{text}\033[0m"


commands = {
    "test": [f"python3 -m unittest discover test"],

    "clean": ["rm -rf venv __pychache__/*"],
    
    "mypy": [loop_dir + 'echo $filename; mypy $filename' + end],
    
    "format": [loop_dir + 'autopep8 --in-place --aggressive $filename' + end],
    
    "style": [loop_dir + 'do pycodestyle $filename' + end]
}


def run_command(command, arg):
    match arg:
        case 'run':
            print(f"Running {sys.argv[0]}")
        case 'test':
            print(make_text_bold('----- RUNNING UNITTEST -----\n'))
        # case:
        #     print(f'{arg} on directory')

    subprocess.run(command, shell=True, check=True)


def arg_parse():
    parser = argparse.ArgumentParser(
        description="Run commands similar to a make file.")
    parser.add_argument("command", choices=commands.keys(),
                        help="The command to run.")

    args = parser.parse_args()

    for cmd in commands[args.command]:
        run_command(cmd, args.command)


def main():
    arg_parse()


if __name__ == "__main__":
    main()