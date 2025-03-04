String Analysis and Border Detection

Description

This project implements a program in Assembly that performs string analysis and border detection. It calculates the "maximum border" of a given string, displays the string's border array, and visualizes the results in both simple and fancy formats. It also includes error handling for incorrect arguments or string lengths.

Key Features:
- Max Border Calculation: The program detects the longest border of a string, which is a substring that matches its suffix.
- String Validation: Ensures that the string passed as input has a length of 12 characters or fewer.
- Custom Displays: Outputs the string's border array in simple and fancy formats for better visualization.
- Error Handling: Handles errors for incorrect arguments or excessive string lengths.

Technologies Used

- Assembly: This project is written entirely in x86-64 Assembly Language.
- Simple I/O Library: The program uses an external simple_io.inc for basic input/output operations.

Functions

1. maxbord
The maxbord function calculates the longest border of a string. It compares each possible border with its corresponding suffix and returns the length of the maximum border.

2. simple_display
The simple_display function prints the border array in a simple, comma-separated format. This function displays each value of the array sequentially.

3. fancy_display
The fancy_display function displays the border array in a more complex format with custom string prefixes based on conditions. It iterates over the border array and applies a fancy visualization with the +++, ..., and other patterns.

4. asm_main
The asm_main function is the entry point of the program. It:
- Validates the command line arguments.
- Calculates the length of the input string.
- Calls maxbord to compute the border array.
- Calls simple_display and fancy_display to visualize the results.

5. wrong_args and wrong_len
These functions handle errors in the input:
- wrong_args: Displays an error message when the number of arguments is incorrect.
- wrong_len: Displays an error message when the string length exceeds the allowed limit of 12 characters.

Input and Output

Input:
The program accepts a single string as a command-line argument. The string must be 12 characters or fewer.

Output:
1. Border Array: The program prints the "border array" of the string.
2. Visualizations: The program displays the border array in two formats:
   - Simple Display: A comma-separated list of border values.
   - Fancy Display: A more stylized visualization with custom strings.

Error Messages:
- "Incorrect number of command line arguments"
- "Input string too long"

Example Usage

Command:
$ ./border_detection "ababab"

Output:
border array: 6, 4, 2, 0, 0, 0
+++ ...   ...   +++   ...  

If the string has more than 12 characters or incorrect arguments are provided, appropriate error messages will be shown.

How to Run

1. Clone the repository:
   git clone <repository-url>

2. Assemble and link the code using your preferred assembler and linker (e.g., nasm and ld).

3. Run the program with a string argument:
   ./border_detection "your_string"

Contributing

Feel free to fork the repository, submit issues, and make pull requests. Contributions are welcome!

License

This project is licensed under the MIT License - see the LICENSE file for details.
