# Project 3
Obtain the file stego.zip from the textbook website (also on Canvas).

1. First Problem

    a. Use the program stegoRead to extract the hidden file contained in aliceStego.bmp.
        
        gcc -o stegord.out stegord.c stegoutil.c
        ./stegord.out '../img/aliceStego.bmp' '../out/aliceStego.pdf'

    ![Stego Read Output](img/stegord-run.PNG?raw=true "Title")

    b. Use the programs to insert another file into a different (uncompressed) image file and extract the information.

        gcc -o stegomk.out stegomk.c stegoutil.c
        ./stegomk.out '../img/animal-farm.bmp' '../img/animal-farm-stego.bmp' '../dat/animal-farm.pdf'

    ![Stego Make Output](img/stegomk-run.PNG?raw=true "Title")

    c. Provide screen snapshots of the image file from part b, both with and without the hidden information. They should be indistinguishable.

    *Original Image*
    ![Animal Farm Original](img/animal-farm.bmp?raw=true "Title")

    *Image Containing Hidden Data*
    ![Animal Farm Stego](img/animal-farm-stego.bmp?raw=true "Title")


2. Second Problem

    a. Write a program, stegoDestroy.c, that will destroy any information hidden in a file, assuming that the information hiding method in stego.c might have been used. Your program should take a bmp file as input, and produce a bmp file as output. Visually, the output file must be identical to the input file.

        gcc -o stegods.out stegods.c stegoutil.c
        ./stegods.out '../img/aliceStego.bmp' '../img/aliceDestroyed.bmp'

    ![Stego Destroy Output](img/stegods-run.PNG?raw=true "Title")

    b. Test your program on aliceStego.bmp. Verify that the output file image is undamaged. What information does stegoRead.c extract from your output file?

    *Image Containing Hidden Data*
    ![Stego Read Output](img/aliceStego.bmp?raw=true "Title")

    *Image Containing Corrupted Data*
    ![Stego Read Output](img/aliceDestroyed.bmp?raw=true "Title")

    The first piece of information that stegoRead.c attempts to read is a flag indicating whether or not the image contains embedded data. If the image file contains this flag, the program extracts the data from the low order bits. We could easily make the program run to error by corrupting the initial flag. I think it's a bit more covert to corrupt the image in such a way that stegoRead.c runs with no issues. This is accomplished by initially skipping the first 64 bits where the flag is embedded. This keeps in in tact. After that I randomly modify the low order bits of the actual embedded message. The stegoRead program will run to success, but the pdf will be unreadable. 