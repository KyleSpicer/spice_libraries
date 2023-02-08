#!/usr/bin/env python3

from libraries.file_io_lib import file_exists as fe, file_size, check_file_type as cft, file_get_stats as stats

def main():
    good_file = "./test_files/Movies.txt"
    bad_file = "badfile"
    
    print(f"Testing good file: {(fe(good_file))}")
    print(f"Testing bad file: {(fe(bad_file))}")
    
    print(f"file size = {file_size(good_file)} bytes")
    
    print(f"type of {good_file} is {cft(good_file)}")
    stats(good_file)


if __name__ == "__main__":
    main()