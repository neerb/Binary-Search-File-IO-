/*
    This program takes an input-file name from the user,
    where the data in the input file is in a new-line style
    of format.  The files contain a list of numbers
    from top to bottom in the following format:
        Example input file (sorted array):
            2
            4
            8
            16
            32
            64

    The program will read in the data and store it into
    a one-dimensional array of doubles.  This array cannot
    exceed a size of 100.  It will inform the user to enter
    the file-name of the file.  If the file does not exist,
    the program will notify the user and re-prompt them for
    input.  If the user enter a valid file-name, then it
    will  display to the user the sorted input array.
    It will then ask the user to enter a number within the
    array, it will then display to the user the position of
    that element within the array.  If it is not found in
    the array, it will notify the user of this.
    The program will continue this until the
    user has entered the single asterisk character ('*').

    Nathan Breen
    Binary Search
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
    This function performs a simple binary search
    on a one-dimensional array of doubles.  It returns
    the position/index of the number the user searched
    in the array.  Returns -1 if non-existent.

    Params:
        double arr[]: array being searched
        int arrSize: size of the passed into function
        double target: number being searched for

    Returns:
        Integer variable containing index of searched element
*/
int binarySearch(double arr[], int arrSize, double target)
{
    //Declare position variables
    int m = -1;
    int l = 0, r = arrSize - 1;
    bool found = false;

    while(!found && l <= r)
    {
        //Find middle element using truncation
        m = (l + r) / 2;

        //boolean dictating loop
        found = arr[m] == target;

        //Only executes if not found element yet
        if(!found)
        {
            if(arr[m] > target)
                r = m - 1;
            else// if(arr[m] < target) // Unnecessary condition
                l = m + 1;
        }
    }

    //Whether or not the element was found, return -1
    if(!found)
        m = -1;

    return m;
}

/*
    This function populates an array parameter (passed by reference)
    using the input-filestream (also passed by reference).  It will
    continue to populate each individual element of the array
    until the file has reached its end-of-file marker.  The function
    then finally returns the size of the array that had just been
    populated.

    Params:
        double arr[]: array to be populated
        ifstream &file: input-filestream being read from

    Returns:
        int: Size of populated array
*/
int populateArray(double arr[], ifstream &file)
{
    int i = 0;

    while(file >> arr[i])
        i++;

    return i;
}

/*
    This function simply prints out the contents
    of a one-dimensional array of doubles.  It
    iterates through each individual element, printing
    out its contents and then a comma and a space. It
    will not print the comma and the space for the last
    element in the array for formatting purposes.

    Params:
        double arr[]: array to be printed
        int arrSize: size of array passed above
*/
void printArray(double arr[], int arrSize)
{
    for(int i = 0; i < arrSize; i++)
    {
        cout << arr[i];

        //Only prints a comma and a space if not printing last element
        if(i != arrSize - 1)
            cout << ", ";
    }

    //Newline for formatting
    cout << endl;
}

/*
    This is the driver function for this array searching program.
    It begins by prompting the user and requesting them to enter
    a filename.  If the file-name exists, then this function
    will call the other necessary functions to populate the array,
    print to the user the sorted array input.

    If the user enters an invalid file-name, then the program will notify
    the user that their file does not exist and ask them for a new
    file-name.

    If the user enters a single asterisk character ('*'), then
    the program will display an exit message and close the program.
*/
void driver()
{
    const int MAX_SIZE = 100;
    double *arr = new double[MAX_SIZE];
    double targetNum;
    int pos;
    int arrSize = 0;
    string fileName;
    ifstream file;

    //Loop continues until user enters asterisk character ('*')
    do
    {
        //Prompt and receive data from user
        cout << "Enter the name of the file containing the array of sorted numbers (enter '*' to exit): ";
        getline(cin, fileName);

        //Opening input-file
        file.open(fileName);

        //Confirmation user has not opted to exit
        if(fileName != "*")
        {
            if(file)
            {
                //Populating array and getting/assigning array size
                arrSize = populateArray(arr, file);

                //Print sorted array from file
                cout << "Array being searched from: " << endl;
                printArray(arr, arrSize);

                //Asking user for target number
                cout << endl << "Enter a number to be searched in this array: ";
                cin >> targetNum;
                cin.ignore();

                //Searching and assigning position of element in array.
                pos = binarySearch(arr, arrSize, targetNum);

                //Determines whether to inform user that number does not exist in array
                if(pos != -1)
                    cout << "Number " << targetNum << " found at position " << pos << "." << endl;
                else
                    cout << "The number " << targetNum << " was not found in this array." << endl;
            }
            else
                cout << "File \"" << fileName << "\" does not exist.  Please try again." << endl;
        }

        //Formatting newline
        cout << endl;

        //Closing input-file
        file.close();

    } while(fileName != "*");

    //Exit notification
    cout << "Exiting program... Goodbye!" << endl;

    //Deallocating array memory
    delete [] arr;
}

int main()
{
    driver();

    return 0;
}
