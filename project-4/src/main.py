''' Linearization/Salami Attack

Author: Bradley Reeves
Date: May 17, 2021

This program demonstrates how a poorly designed application
can be exploited with a linearization attack. The program
securityclass.exe is flawed in that it validates a serial
number one character at a time. We test each character for each
position and select the one that takes the most time due to
validation. This is known as a linearization attack since we can
attack the serial number in linear time. This can also be classified
as a salami attack because the serial number is determined one
character at a time.

Note: this doesn't work 100% of the time. For more accurate results,
increase the value of EXE_TRIES. Of course, this will increase the
runtime significantly.
'''
from subprocess import check_output
from string import digits
from timeit import timeit

SERNO_LEN = 7
EXE_TRIES = 10
MAX_TRIES = 9


def list_to_str(num_list):
    ''' List to string convenience method
        Paramaters
        ----------
        num_list : list representation of serno

        Returns
        -------
        String representation of num_list
    '''
    return "".join(str(n) for n in num_list)


def execute_app(command, test_serno):
    ''' Run the executable
        Parameters
        ----------
        command : shell command to execute
        test_value : serial number to try

        Returns
        -------
        Executable output
    '''
    return check_output(
        [command + test_serno + "; exit 0"],
        shell=True,
        universal_newlines=True
    )


def get_last_digit(command, num_list):
    ''' Find the remaining digit by brute-force
        Parameters
        ----------
        command : shell command to execute
        test_vlist : list representation of serno

        Returns
        -------
        Serial number as string
    '''
    output = execute_app(command, list_to_str(num_list))
    resume = "\nSerial number is incorrect!\n\n"

    while output == resume and num_list[-1] < MAX_TRIES:
        num_list[-1] += 1
        output = execute_app(command, list_to_str(num_list))
    return list_to_str(num_list)


def main():
    ''' Program driver
    '''
    num_list = [0 for _ in range(SERNO_LEN)]
    test_times = [0 for _ in digits]

    # securityclass.exe works w/ Visual C++ 2015,
    # securityclass-new.exe works w/ Visual C++ 2015-2019
    command = "./securityclass-new.exe "

    # Iterate through each digit for each position
    for i in range(SERNO_LEN - 1):
        for j in range(len(digits)):
            num_list[i] = digits[j]
            test_times[j] = timeit(
                lambda: execute_app(command, list_to_str(num_list)),
                number=EXE_TRIES
            )

        num_list[i] = test_times.index(max(test_times))
        test_times = [0 for _ in digits]

    # Brute force the last digit
    serial_number = get_last_digit(command, num_list)

    # Test the derived solution
    print("Submitting serial number", serial_number + "...")
    print("Result:",  execute_app(command, list_to_str(num_list)))

    return 0


if __name__ == "__main__":
    main()
