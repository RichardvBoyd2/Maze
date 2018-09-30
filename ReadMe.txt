Project files can also be found at: https://github.com/RichardvBoyd2/Maze

This Project was made in Microsoft Visual Studio 2017, so you may need to import it to that as a project to run.
The ifstream and ofstream used to read and write the input and output files only worked with a full file path, so it will need to be adjusted to point to the local files on your computer once downloaded.
If it is pointed to a different input file, it will overwrite the output_file with the new maze. The code supports mazes up to a size of 20x20 squares. 

Ver 1.3 now finds a path through the maze to the end with an original algorithm that will solve any maze thrown at it. It marks it's path, and upon completion, prints the finished maze underneath the unsolved maze in the same output_file. 

Ver 1.4 uses a queue instead of a stack, so now it finds all possible paths and still solves the maze. Input, output, etc remains the same, just runs differently under the hood. The stack code is still there, just commented out so it doesn't run, so just leave it that way and it will run off the queue code instead of the stack code.