//the code is not working well
/*
In Naive method no output appears [ due to an access validation error]
i traced it a lot but i could not find the problem.

In Prefix method the output is not correct, however i tried a lot of method
to fix it, but either there is an error or could not get the write output
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define DIR "D:\\Iseul\\uni pdf\\(3) 2nd Semester\\Biological Sequence\\Labs\\Assignment1\\IO\\"

char* original = new char[10000];
int seq_size = strlen(original);
char DNA[] = "ACGTAAGCGT$"; // test case;
int it = 0; // iterator on original sequence array element
int*  CharToInt = new int[256];
int oldchar =  1;
int newchar = 0; // character i compare to without old compared char

struct Suffix
{
    int index;
    int order;
};
void Write_in_file(int* output) // write the Naive suffixarray of 10000 char in the file
{
    FILE* outputfile = fopen(DIR "outputfile.txt" , "w");
    for (int i = 0; i < seq_size; i++)
    {
        fprintf(outputfile , "%d" ,output[i]);
        fprintf(outputfile,"%s", " ");
        fclose(outputfile);
    }
}

void Write_in_file2(int* output) // write the Prefix suffixarray of 10000 char in the file
{
    FILE* outputfile = fopen(DIR "outputfile2.txt" , "w");
    for (int i = 0; i < seq_size; i++)
    {
        fprintf(outputfile , "%d" ,output[i]);
        fprintf(outputfile,"%s", " ");
        fclose(outputfile);
    }
}

void InitializeChar() //  initialize the arrange of the character
{
    CharToInt['$'] = 0;
    CharToInt['A'] = 1;
    CharToInt['C'] = 2;
    CharToInt['G'] = 3;
    CharToInt['T'] = 4;
}

int InsertRead(char* readbuf , int bufsize) // insert the readed buffer from the file in the char array;
{
    for (int j = 0; j < bufsize; j++)
    {
        original[it] = readbuf[j];
        it++;
    }
    return strlen(original);
}

bool Naive_Compare(int a , int b) // compare between two suffixes by there characters
{// take indexes of the two suffixes i compare between form suffix array

    int i = 0;
    while (i < seq_size && a < seq_size && b < seq_size)// loop on the char sequence
    {
        // compare between each character
        if (original[a] == original[b]) {a++; b++; i++;} // if equal go to the next

        if (original[a] < original[b]) return true;

        else if (original[a] > original[b]) return false;

    }
return false;
}

void merg(int suffarr[] , int low , int mid , int high)
{// merge two subarrays
    int index1 = mid-low+1; // index for first subarray
    int index2 = high - mid; // index for second subarray
    int sub_index  = low; // index for merged subarray
    int* merged1 =  new int[index1]; //left array
    int* merged2 = new int[index2]; // right array

    for (int i = 0; i < index1 ; i++) merged1[i] = suffarr[low + i];

    for (int j = 0; j < index2; j++) merged2[j] = suffarr[mid + 1 + j];

    int i = 0, j = 0; // index for thre first and second subarray

    while( i <= index1 && j <= index2)
    {// compare on the two parts of the suffix array and put it in the merged array
        if (Naive_Compare(merged1[i], merged2[j]) == 1) {suffarr[sub_index] = merged1[i]; i++;} // if true

        else {suffarr[sub_index] = merged2[j]; j++;}
        sub_index++;
    }

    while(j < index2) { suffarr[sub_index] = merged2[j]; j++; sub_index++;} // put the rest of the array in merged

    while(i < index1) {suffarr[sub_index] = merged1[i]; i++; sub_index++;}

}

void mergsort(int suffarr[] , int low , int high)
{
    if (low < high)
    {
        int mid = low + (high - low) /2;
        mergsort(suffarr,low,mid);
        mergsort(suffarr,mid+1,high);
        merg(suffarr,low,mid,high);
    }

}

void Naive_Suffix_Array()
{
    int* suffixarray = new int[seq_size];

    for(int i = 0; i < seq_size; i++)  //for loop to initialize the suffixes;
    {
        suffixarray[i] = i;
    }

    mergsort(suffixarray,0, strlen(DNA));
    //for(int i = 0; i < strlen(DNA); i++) {cout << suffixarray[i] << " ";}
    Write_in_file(suffixarray);
}

void Swap(int* a , int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition (Suffix* suff, int lb, int ub) // take last element as pivot, place it in it's correct place
{// put the small element before pivot and the greater elements after it.
    int i = lb - 1; // index of smallest element
    int pivot = suff[ub].order;
    for (int j = lb; j <= ub-1; j++)
    {
        if (suff[j].order < pivot)
        {
            i++;
            Swap(&suff[i].order , &suff[j].order);
            Swap(&suff[i].index , &suff[j].index);
        }
    }
    Swap(&suff[i+1].order , &suff[ub].order);
    Swap(&suff[i+1].index , &suff[ub].index);
    return i+1;
}

void Quicksort (Suffix* suff, int lb, int ub)
{
    if (lb < ub)
    {
        int mid = partition (suff , lb , ub); // index at which the array is divided
        Quicksort(suff, lb , mid-1); // sort left partition
        Quicksort(suff, mid+1 , ub); // sort right partition
    }
}

bool Stop_Condition(Suffix* suff)
{
    int check = 0; // check if the suffix is unique or not
    for (int i = 1; i < seq_size; i++)
    {
        if (suff[i].order == suff[i-1].order) check++;
    }
    if (check!=0) return true;
    else return false;
}

bool Prefix_Compare(Suffix s1 , Suffix s2)
{
    if (s1.order != s2.order) return (s1.order < s2.order); //order not equal return the smaller
    else
    {
        int num1 = s1.index + oldchar; // refers to the char in first suffix
        int num2 = s2.index + oldchar; // refer to the char in second suffix

        for (int i = 0; i < newchar; i++)//loop from the shifted char and compare till reach the newchar number
        {
            if(s1.order < s2.order)
            {
                return true;
            }
        }
        return false;
    }
}

int Update_Order_Compare(Suffix* s1) // function to know what order to be updated
{
        int ind1 = s1->index + oldchar; // refers to the index to be updated
        int ind2 = ind1 - 1; // refer to the index before the shifted one
        for (int i = 0; i < newchar; i++)//loop from the shifted char and compare till reach the newchar number
        {
            if(s1[ind1].order < s1[ind2].order) return 1;

            else return 0;
        }
}

int power(int x, int y) {
    int i, power=1;
    if(y == 0)
        return 1;
    for(i=1;i<=y;i++)
        power = power*x;
    return power;
}

void Prefix_Doubling()
{
    Suffix* suffixarray = new Suffix[seq_size];
    int iteration = 1;
    int comparechar = 0; // number of character compare with in each iteration
    InitializeChar();

    // initialize the suffix array in itiration = 0
    for(int i = 0; i < strlen(DNA); i++)
    {
        suffixarray[i].index = i;
        suffixarray[i].order = CharToInt[original[i]];
    }

    /*for(int i = 0; i < strlen(DNA); i++) // ON TEST CASE
    {
        cout << DNA[i] << " " ;
    }
    cout << endl;*/

    Quicksort(suffixarray , 0 , seq_size); // used to sort the first initialization of suffix array

    //cout << endl;
    //cout << "Sorted suffix " << endl;

    /*for(int i = 0; i < strlen(DNA); i++) // Test Case
    {
        cout << suffixarray[i].index << " ";
    }
    cout << endl;
    for(int i = 0; i < strlen(DNA); i++)
    {
        cout << suffixarray[i].order << " ";
    }*/

    while (true)
    {
        if (Stop_Condition(suffixarray) == true)
        {
            comparechar = power(2 , iteration);
            newchar = comparechar - oldchar;
            oldchar = comparechar;
            sort(suffixarray, suffixarray + seq_size, Prefix_Compare);

            int* newsufforder = new int[seq_size];

            for (int i = 1; i < seq_size; i++) // update orders
            {
                if(Update_Order_Compare(suffixarray) == 1) newsufforder[i] = suffixarray[i-1].order + 1;

                else newsufforder[i] = suffixarray[i-1].order + 0;
            }
            for (int j = 1; j < seq_size; j++) suffixarray[j].order = newsufforder[j];

            iteration++;
        }
        else break;

    }

    Write_in_file2(&suffixarray->order);

}

void Compute()
{
    char* buf = new char[seq_size];
    FILE* file=fopen(DIR "genome.fasta.fastq", "r");
    buf[0]=0; fscanf(file, "%[^\n\r] ", buf); // Ignore this line

    int line_reads=0;
    while(line_reads<=143) // Insert the first 70 reads which do not contain invalid characters
    {
        buf[0]=0; fscanf(file, "%[^\n\r] ", buf);

        if(InsertRead(buf, strlen(buf)) <= 10000) line_reads+=1; // to check that it doesn't exceed the 10000 char
        else break;
        //cout<< endl;

    }
    Naive_Suffix_Array();
    //Prefix_Doubling();
    fclose(file);
}

int main() {

    Compute();
    return 0;
}