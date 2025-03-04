# String Manupilation

Welcome to the Border Detection project! This guide will walk you through the steps to run the program and understand its features.

## How to Run

1. **Clone the Repository:**
   - Clone the project repository from GitHub to your local machine.
   - Example:
     ```
     git clone <repository-url>
     ```

2. **Assemble the Code:**
   - Use an assembler (e.g., `nasm`) to assemble the Assembly code.
   - Example:
     ```
     nasm -f elf64 -o border_detection.o border_detection.asm
     ```

3. **Link the Code:**
   - Link the object file to create an executable.
   - Example:
     ```
     ld -o border_detection border_detection.o
     ```

4. **Run the Program:**
   - Run the executable with a string argument (maximum 12 characters).
   - Example:
     ```
     ./border_detection "ababab"
     ```

## Features

### String Border Detection

1. **Max Border Calculation:**
   - The program computes the longest "border" of a string. A border is a substring that matches its suffix.

2. **String Validation:**
   - The program checks if the string length is greater than 12 characters. If it exceeds the limit, an error message is displayed.

### Output Displays

3. **Simple Display:**
   - The program outputs the border array in a simple comma-separated format.

4. **Fancy Display:**
   - A stylized display of the border array with custom prefixes and patterns like `+++` and `...`.

### Error Handling

5. **Error Messages:**
   - If the number of command line arguments is incorrect, the program displays an error message: "Incorrect number of command line arguments".
   - If the input string is too long (more than 12 characters), an error message is shown: "Input string too long".
