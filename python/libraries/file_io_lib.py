#! /usr/bin/env python3

import os
import stat

def file_exists(file_path: str) -> bool:
    '''
    file_exists: uses os.path.isfile to verify file exists

    Args:
        file_path (str): file path or file name

    Returns:
        bool: true if file exists, false if file does not exist
    '''
    
    return os.path.isfile(file_path)


def file_size(file_path: str) -> int:
    '''
    file_size: uses os.path.isfile to find size of file in bytes

    Args:
        file_path (str): file path or file name

    Returns:
        int: size of the file in bytes
    '''    
    return os.path.getsize(file_path)


def check_file_type(file_path: str) -> str:
    '''
    check_file_type: uses os.path.splittext to receive file path or file name 
    to retrieve the .filetype

    Args:
        file_path (str): file path or file name

    Returns:
        str: file type as a strnig. for example: test.txt will simply return .txt
    '''    
    return os.path.splitext(file_path)[1]

def file_get_stats(file_path: str) -> None:
    '''
    file_get_stats: uses os.stat to retrieve information from file path or file
    name provided

    Args:
        file_path (str): file path or file name
    '''    
    file_stats = os.stat(file_path)
    print("\nSTATS:")
    # print file size
    print(f"File Size: {file_stats.st_size} bytes")
    
    # print last access time
    print(f"Last Access Time: {file_stats.st_atime}")
    
    # print last modification time
    print("Last Modification Time:", file_stats.st_mtime)
    
    # print file permissions status
    print("File Mode (Permissions):", oct(file_stats.st_mode))
    
    # check if file is a directory
    if stat.S_ISDIR(file_stats.st_mode):
        print("This is a directory.")
    else:
        print("This is not a directory")
