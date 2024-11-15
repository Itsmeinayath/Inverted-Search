Inverted Search
An Inverted Search project written in C. This program allows users to create an inverted index of words from multiple text files, enabling efficient word search across those files. Users can create, print, search, save, and update a word database based on their provided text files.

Table of Contents
Features
File Structure
Setup
Usage
Example Commands
Features
Create an inverted index (word database) from multiple text files.
Print the word database with information such as word count, file name, and file count.
Search for a specific word in the database and display the files containing that word and their respective word counts.
Save the word database to a specified file.
Update the word database with new or modified entries.
File Structure
The main files for this project are:

main.c: Contains the main function and menu display logic.
function.c: Contains the core logic for creating, printing, searching, and saving the database.
header.h: Header file with function prototypes and definitions.
f1.txt, f2.txt, etc.: Sample text files used for testing the inverted index functionality.
makefile: Makefile for compiling the project.
Setup
Clone the repository:

bash
Copy code
git clone https://github.com/yourusername/InvertedSearch.git
cd InvertedSearch
Compile the project: You can use make to compile the project if a Makefile is provided:

bash
Copy code
make
Alternatively, compile all .c files using gcc:

bash
Copy code
gcc *.c -o inverted_search
Usage
To run the program, use:

bash
Copy code
./inverted_search file1.txt file2.txt ...
Replace file1.txt, file2.txt, etc., with the names of the text files you want to analyze.

Example Run
Creating the Database:

Select option 1 to create the database from the provided text files.
The program will output information such as:
rust
Copy code
The database created for f1.txt
The database created for f2.txt
Printing the Database:

Select option 2 to print the database.
Example output:
mathematica
Copy code
Index  Word  File count  File name
[0]    are   1           f2.txt
[7]    hi    2           f1.txt
Saving the Database:

Select option 4 to save the database to a file.
Enter the desired filename (e.g., database.txt) when prompted.
Searching for a Word:

Select option 3 to search for a word.
Enter the word to search for (e.g., hi).
The program will display the files containing the word along with the word count:
vbnet
Copy code
Enter the element to be searched: hi
The element are found in 2 files
f1.txt and the Wordcount is 1
f2.txt and the Wordcount is 1
Updating the Database:

Use option 5 to update the database with new files or modified entries.
Exiting the Program:

Select option 6 to exit.
Example Commands
bash
Copy code
# To compile all .c files and create the executable
gcc *.c -o inverted_search

# To run the executable with text files as input
./inverted_search f1.txt f2.txt
