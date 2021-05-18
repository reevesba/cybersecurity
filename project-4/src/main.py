''' Linearization Attack

Author: Bradley Reeves
Date: May 17, 2021

'''
from subprocess import check_output
from string import digits
from timeit import timeit

def execute_app(command, test_value):
    check_output([command + test_value + "; exit 0"], shell=True)

def main(): 
    test_value = "0000000"
    test_vlist = [0 for _ in test_value]
    test_times = [0 for _ in digits]
    command = "./securityclass.exe "

    for i in range(len(test_vlist) - 1):
        # Iterate through each digit for each position
        for j in range(len(digits)):
            test_vlist[i] = digits[j]
            test_value = "".join(str(n) for n in test_vlist)

            # Time the function call
            test_times[j] = timeit(lambda: execute_app(command, test_value), number=1)

        test_vlist[i] = test_times.index(max(test_times))
        test_times = [0 for _ in digits]

    # Brute force the last digit
    test_value = "".join(str(n) for n in test_vlist)
    output = check_output(["./securityclass.exe " + test_value + "; exit 0"], shell=True)
    while output != b"\r\nSerial number is correct!\r\n\r\n":
        print(output)
        print(test_vlist)
        test_vlist[6] += 1
        test_value = "".join(str(n) for n in test_vlist)
        output = check_output(["./securityclass.exe " + test_value + "; exit 0"], shell=True)
    print(test_value)

if __name__ == "__main__":
    main()