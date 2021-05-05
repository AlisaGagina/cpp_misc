//
//ALISA GAGINA 260770497
//

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int rows = 5;
const int cols = 5;
int timeoffset = 0; //because random is not random if called in the same second

void checkPassword()
{
    cout << "Please enter password: ";
    //get user input
    string password;
    cin >> password;

    bool passwordworks = true;

    const int l = password.length();
    //Make sure that the password is at least 8 characters long
    if (l <= 8)
    {
        cout << "- Password must be at least 8 characters long" << endl;
        passwordworks = false;
    }
    //Make sure that each character does not occur more than 2 times in the word
    int count[256] = {0};

    //Make sure the password contains at least one number
    bool hasnumber = false;
    //Make sure the password contains at least one of the following special characters: *, # or $.
    bool hasspecial = false;

    //got through each character
    int i = 0;
    for (i; i < l; i++)
    {
        count[password[i]]++;
        if (count[password[i]] == 3)
        {
            cout << "- The character " << password[i] << " has occured too many times" << endl;
            passwordworks = false;
        }

        if (password[i] >= '0' && password[i] <= '9')
        {
            hasnumber = true;
        }

        if (password[i] == '*' || password[i] <= '#' || password[i] <= '$')
        {
            hasspecial = true;
        }
    }

    //print warnings if any
    if (!hasnumber)
    {
        cout << "- Password must contain at least one number" << endl;
        passwordworks = false;
    }
    if (!hasspecial)
    {
        cout << "- Password must contain at least one of the following special characters: *, # or $" << endl;
        passwordworks = false;
    }

    //print final verdict
    if (passwordworks){
        cout << "Password accepted!" << endl << endl;
    }else{
        cout << "Please try again" << endl << endl;
    }
    return;
}

void convertPhonetic(){
    cout << "Please enter a word: ";
    string word;
    cin >> word;
    for (int i=0; i < word.length(); i++) { //for every char in word
        switch (word[i]){
            case 'a': case 'A': cout << "Alfa "; break;
            case 'b' : case  'B': cout << "Bravo "; break;
            case 'c' : case  'C': cout << "Charlie "; break;
            case 'd' : case 'D': cout << "Delta "; break;
            case 'e' : case 'E': cout << "Echo "; break;
            case 'f' : case 'F': cout << "Foxtrot "; break;
            case 'g' : case 'G': cout << "Golf "; break;
            case 'h' : case 'H': cout << "Hotel "; break;
            case 'i' : case 'I': cout << "India "; break;
            case 'j' : case 'J': cout << "Juliett "; break;
            case 'k' : case 'K': cout << "Kilo "; break;
            case 'l' : case 'L': cout << "Lima "; break;
            case 'm' : case 'M': cout << "Mike "; break;
            case 'n' : case 'N': cout << "November "; break;
            case 'o' : case 'O': cout << "Oscar "; break;
            case 'p' : case 'P': cout << "Papa "; break;
            case 'q' : case 'Q': cout << "Quebec "; break;
            case 'r' : case 'R': cout << "Romeo "; break;
            case 's' : case 'S': cout << "Sierra "; break;
            case 't' : case 'T': cout << "Tango "; break;
            case 'u' : case 'U': cout << "Uniform "; break;
            case 'v' : case 'V': cout << "Victor "; break;
            case 'w' : case 'W': cout << "Whiskey "; break;
            case 'x' : case 'X': cout << "X-ray "; break;
            case 'y' : case 'Y': cout << "Yankee "; break;
            case 'z' : case 'Z': cout << "Zulu "; break;
            default: cout << "? "; //if not a char
        } 
        if(i==word.length()-1){
            cout <<endl << endl;
        }
    }
     return;   
}

void fillMatrix(int matrix[rows][cols])
{
    srand(time(0) + timeoffset);
    timeoffset += 1; //increase timeoffset each time this function is run
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = rand() % 26; //from 0-25 inclusive
        }
    }
    return;
}

void printMatrix(int matrix[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << matrix[i][j]; 
            if (j != cols - 1)
            {
                cout << " | "; //if last num, don't print this
            }
        }
        cout << endl << "---------------------" << endl;
    }
    cout << endl;
    return;
}

void multiplyMatrices(int matrix_left[rows][cols],
                      int matrix_right[rows][cols],
                      int matrix_result[rows][cols])
{

    //the logic i wrote before i reread the instructions and noticed the 'recursive' part of it :')

    // for(int i= 0; i<rows; i++){
    //     for (int j=0; j < cols; j++){
    //         int sum = 0;
    //         for (int k=0; k < rows; k++){
    //             sum += matrix_left[i][k] * matrix_right[k][j];
    //         }
    //         matrix_res2[i][j]=sum;
    //     }
    // }

    //It's the above code , but written in a recursive way

    static int i = 0, j = 0, k = 0;

    if (i == 0 && j == 0 && k == 0)
    {

        //matrix result is not initialized in main, so it was filled with random numbers
        //therefore, in the first run, clear it off and make it full of 0's
        // printMatrix(matrix_result)
        for (int z = 0; z < rows; z++)
        {
            for (int x = 0; x < cols; x++)
            {
                matrix_result[z][x] = 0;
            }
        }
    }

    if (i >= rows)
    {
        return;
    }
    else
    {
        if (j < cols)
        {
            if (k < cols)
            {
                matrix_result[i][j] += matrix_left[i][k] * matrix_right[k][j];
                k++;
                multiplyMatrices(matrix_left, matrix_right, matrix_result);
            }
            k = 0;
            j++;
            multiplyMatrices(matrix_left, matrix_right, matrix_result);
        }
        j = 0;
        i++;
        multiplyMatrices(matrix_left, matrix_right, matrix_result);
    }

    return;
}

int main()
{
    checkPassword();
    convertPhonetic();
    int matrix[rows][cols];
    int matrix2[rows][cols];
    int matrix_result[rows][cols];
    fillMatrix(matrix);
    fillMatrix(matrix2);
    printMatrix(matrix);
    //printMatrix(matrix2);
    multiplyMatrices(matrix, matrix2, matrix_result);
    printMatrix(matrix_result);
    return 0;
}