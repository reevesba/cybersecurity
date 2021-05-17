''' Linearization Attack

Author: Bradley Reeves
Date: May 17, 2021

'''
import subprocess

def main():
    test_number = "0000000"

    subprocess.check_output(["./securityclass.exe", test_number], universal_newlines=True)

if __name__ == "__main__":
    main()