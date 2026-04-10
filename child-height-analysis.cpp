/*
Name: Thanik Bharani
Lab #: 7
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

/* Function Prototypes */

int getData(ifstream& inFile,
            int familyNum[],
            double fatherHt[],
            double motherHt[],
            int childNum[],
            string gender[],
            double childHt[],
            double parentMidHt[],
            double difference[]);

void outputData(ofstream& outFile,
                int familyNum[],
                double parentMidHt[],
                int childNum[],
                string gender[],
                double childHt[],
                double difference[],
                int count);

double avgHeight(string gender[],
                 double childHt[],
                 int count,
                 string choice);

int findChild(int familyNum[],
              int childNum[],
              int count,
              int targetFamily,
              int targetChild);

void tallerThan(ofstream& outFile,
                int familyNum[],
                double parentMidHt[],
                int childNum[],
                double childHt[],
                int count);

double stdDeviation(double difference[],
                    int count);

void sortSelect(int familyNum[],
                double fatherHt[],
                double motherHt[],
                int childNum[],
                string gender[],
                double childHt[],
                double parentMidHt[],
                double difference[],
                int count);



int main()
{
    const int MAX = 100;

    ifstream inFile;
    ofstream outFile;

    string inputFileName;

    int familyNum[MAX];
    double fatherHt[MAX];
    double motherHt[MAX];
    int childNum[MAX];
    string gender[MAX];
    double childHt[MAX];
    double parentMidHt[MAX];
    double difference[MAX];

    int count;
    string choice;
    int targetFamily;
    int targetChild;
    int location;
    double avg;
    double stdDev;

    // Read the input file name from the user.
    cin >> inputFileName;

    // Open the input file and verify that it opened successfully.
    inFile.open(inputFileName);
    if (inFile.fail())
    {
        cout << "No such file" << endl;
        return 1;
    }

    // Open the output file in main and keep it open until the end of execution.
    outFile.open("Lab7Output.txt");
    if (outFile.fail())
    {
        cout << "Output file failed to open." << endl;
        return 1;
    }

    // Print the required identifying information to the screen.
    cout << "Name: Thanik Bharani" << endl;
    cout << "Email: thanik.bharani2020@gmail.com" << endl;
    cout << "Lab #: 7" << endl << endl;

    // Print the required identifying information to the output file.
    outFile << "Name: Thanik Bharani" << endl;
    outFile << "Email: thanik.bharani2020@gmail.com" << endl;
    outFile << "Lab #: 7" << endl << endl;

    // Input the data into the first six arrays, compute the last two arrays,
    // and return the actual number of children.
    count = getData(inFile, familyNum, fatherHt, motherHt, childNum,
                    gender, childHt, parentMidHt, difference);

    // Output all data in the original order directly to the output file.
    outputData(outFile, familyNum, parentMidHt, childNum,
               gender, childHt, difference, count);

    // Prompt for male, female, or All, compute the average height,
    // and output the average only from main.
    cout << "Enter male, female, or All: ";
    cin >> choice;

    avg = avgHeight(gender, childHt, count, choice);

    cout << fixed << setprecision(2);
    cout << "Average height = " << avg << endl;

    // Prompt for a family number and child number, search for that child,
    // and output either the height or the required message.
    cout << "Enter family number: ";
    cin >> targetFamily;
    cout << "Enter child number: ";
    cin >> targetChild;

    location = findChild(familyNum, childNum, count, targetFamily, targetChild);

    if (location == -1)
    {
        cout << "NO SUCH CHILD" << endl;
    }
    else
    {
        cout << "Child height = " << childHt[location] << endl;
    }

    // Prompt for a child height inside the function and output all children
    // taller than that value directly to the output file.
    tallerThan(outFile, familyNum, parentMidHt, childNum, childHt, count);

    // Compute the standard deviation of the difference array
    // and output that result to the screen.
    stdDev = stdDeviation(difference, count);
    cout << "Standard deviation = " << stdDev << endl;

    // Sort all eight parallel arrays by child height in descending order
    // using selection sort.
    sortSelect(familyNum, fatherHt, motherHt, childNum,
               gender, childHt, parentMidHt, difference, count);

    // Call the same output function again to write the sorted data to the file.
    outputData(outFile, familyNum, parentMidHt, childNum,
               gender, childHt, difference, count);

    inFile.close();
    outFile.close();

    return 0;
}



/* Pre:  inFile - open input file stream
         familyNum[] - array of family numbers
         fatherHt[] - array of father heights
         motherHt[] - array of mother heights
         childNum[] - array of child numbers
         gender[] - array of child genders
         childHt[] - array of child heights
         parentMidHt[] - array of parent midpoint heights
         difference[] - array of parent midpoint height minus child height
   Post: Returns the actual number of children read from the file
   Purpose: Read the file data into the first six arrays, compute the last two arrays,
            and skip the seven header words at the top of the input file */
int getData(ifstream& inFile,
            int familyNum[],
            double fatherHt[],
            double motherHt[],
            int childNum[],
            string gender[],
            double childHt[],
            double parentMidHt[],
            double difference[])
{
    string head1;
    string head2;
    string head3;
    string head4;
    string head5;
    string head6;
    string head7;

    int numChildren;
    int count;

    count = 0;

    inFile >> head1 >> head2 >> head3 >> head4 >> head5 >> head6 >> head7;

    while (count < 100 &&
           inFile >> familyNum[count]
                  >> fatherHt[count]
                  >> motherHt[count]
                  >> numChildren
                  >> childNum[count]
                  >> gender[count]
                  >> childHt[count])
    {
        parentMidHt[count] = (fatherHt[count] + motherHt[count]) / 2.0;
        difference[count] = parentMidHt[count] - childHt[count];
        count++;
    }

    return count;
}



/* Pre:  outFile - open output file stream
         familyNum[] - array of family numbers
         parentMidHt[] - array of parent midpoint heights
         childNum[] - array of child numbers
         gender[] - array of child genders
         childHt[] - array of child heights
         difference[] - array of parent midpoint height minus child height
         count - number of valid child records
   Post: Nothing
   Purpose: Output all child data to the output file in aligned columns */
void outputData(ofstream& outFile,
                int familyNum[],
                double parentMidHt[],
                int childNum[],
                string gender[],
                double childHt[],
                double difference[],
                int count)
{
    int i;

    outFile << left
            << setw(10) << "Family#"
            << setw(14) << "ParentHtMid"
            << setw(10) << "Child#"
            << setw(10) << "Gender"
            << setw(10) << "ChildHt"
            << setw(12) << "Difference"
            << endl;

    outFile << fixed << setprecision(2);

    for (i = 0; i < count; i++)
    {
        outFile << left
                << setw(10) << familyNum[i]
                << setw(14) << parentMidHt[i]
                << setw(10) << childNum[i]
                << setw(10) << gender[i]
                << setw(10) << childHt[i]
                << setw(12) << difference[i]
                << endl;
    }

    outFile << endl;
}



/* Pre:  gender[] - array of child genders
         childHt[] - array of child heights
         count - number of valid child records
         choice - gender choice entered by the user
   Post: Returns the average height for the selected gender or for all children
   Purpose: Compute the average child height for male, female, or All */
double avgHeight(string gender[],
                 double childHt[],
                 int count,
                 string choice)
{
    double sum;
    int total;
    int i;

    sum = 0.0;
    total = 0;

    for (i = 0; i < count; i++)
    {
        if (choice == "All")
        {
            sum = sum + childHt[i];
            total++;
        }
        else
        {
            if (gender[i] == choice)
            {
                sum = sum + childHt[i];
                total++;
            }
        }
    }

    if (total > 0)
    {
        return sum / total;
    }
    else
    {
        return 0.0;
    }
}



/* Pre:  familyNum[] - array of family numbers
         childNum[] - array of child numbers
         count - number of valid child records
         targetFamily - family number entered by the user
         targetChild - child number entered by the user
   Post: Returns the subscript of the matching child or -1 if not found
   Purpose: Search for one child using the combination of family number and child number */
int findChild(int familyNum[],
              int childNum[],
              int count,
              int targetFamily,
              int targetChild)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (familyNum[i] == targetFamily && childNum[i] == targetChild)
        {
            return i;
        }
    }

    return -1;
}



/* Pre:  outFile - open output file stream
         familyNum[] - array of family numbers
         parentMidHt[] - array of parent midpoint heights
         childNum[] - array of child numbers
         childHt[] - array of child heights
         count - number of valid child records
   Post: Nothing
   Purpose: Prompt for a child height and output each child taller than that height
            to the output file */
void tallerThan(ofstream& outFile,
                int familyNum[],
                double parentMidHt[],
                int childNum[],
                double childHt[],
                int count)
{
    double targetHeight;
    int i;
    int found;

    found = 0;

    cout << "Enter child height: ";
    cin >> targetHeight;

    for (i = 0; i < count; i++)
    {
        if (childHt[i] > targetHeight)
        {
            outFile << familyNum[i]
                    << " "
                    << fixed << setprecision(2) << parentMidHt[i]
                    << " "
                    << childNum[i]
                    << " "
                    << childHt[i]
                    << endl;
            found++;
        }
    }

    if (found == 0)
    {
        outFile << "No children with height greater than "
                << fixed << setprecision(1) << targetHeight << endl;
    }

    outFile << endl;
}



/* Pre:  difference[] - array of parent midpoint height minus child height
         count - number of valid child records
   Post: Returns the standard deviation of the difference array
   Purpose: Compute the standard deviation of the difference values */
double stdDeviation(double difference[],
                    int count)
{
    double mean;
    double sum;
    double sumSquares;
    double deviation;
    int i;

    sum = 0.0;
    for (i = 0; i < count; i++)
    {
        sum = sum + difference[i];
    }

    mean = sum / count;

    sumSquares = 0.0;
    for (i = 0; i < count; i++)
    {
        deviation = difference[i] - mean;
        sumSquares = sumSquares + deviation * deviation;
    }

    return sqrt(sumSquares / count);
}



/* Pre:  familyNum[] - array of family numbers
         fatherHt[] - array of father heights
         motherHt[] - array of mother heights
         childNum[] - array of child numbers
         gender[] - array of child genders
         childHt[] - array of child heights
         parentMidHt[] - array of parent midpoint heights
         difference[] - array of parent midpoint height minus child height
         count - number of valid child records
   Post: Nothing
   Purpose: Sort all parallel arrays by child height in descending order
            using selection sort */
void sortSelect(int familyNum[],
                double fatherHt[],
                double motherHt[],
                int childNum[],
                string gender[],
                double childHt[],
                double parentMidHt[],
                double difference[],
                int count)
{
    int start;
    int maxIndex;
    int i;

    int tempFamilyNum;
    double tempFatherHt;
    double tempMotherHt;
    int tempChildNum;
    string tempGender;
    double tempChildHt;
    double tempParentMidHt;
    double tempDifference;

    for (start = 0; start < count - 1; start++)
    {
        maxIndex = start;

        for (i = start + 1; i < count; i++)
        {
            if (childHt[i] > childHt[maxIndex])
            {
                maxIndex = i;
            }
        }

        tempFamilyNum = familyNum[start];
        familyNum[start] = familyNum[maxIndex];
        familyNum[maxIndex] = tempFamilyNum;

        tempFatherHt = fatherHt[start];
        fatherHt[start] = fatherHt[maxIndex];
        fatherHt[maxIndex] = tempFatherHt;

        tempMotherHt = motherHt[start];
        motherHt[start] = motherHt[maxIndex];
        motherHt[maxIndex] = tempMotherHt;

        tempChildNum = childNum[start];
        childNum[start] = childNum[maxIndex];
        childNum[maxIndex] = tempChildNum;

        tempGender = gender[start];
        gender[start] = gender[maxIndex];
        gender[maxIndex] = tempGender;

        tempChildHt = childHt[start];
        childHt[start] = childHt[maxIndex];
        childHt[maxIndex] = tempChildHt;

        tempParentMidHt = parentMidHt[start];
        parentMidHt[start] = parentMidHt[maxIndex];
        parentMidHt[maxIndex] = tempParentMidHt;

        tempDifference = difference[start];
        difference[start] = difference[maxIndex];
        difference[maxIndex] = tempDifference;
    }
}
