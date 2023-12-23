#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <string>

using namespace std;

float ** createMatr_f(){
    float ** matrix = new float * [10];
    for(int i = 0; i < 10; i++){
        matrix[i] = new float[10];
    }

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            matrix[i][j] = j/tan(exp(i+3));
            //matrix[i][j] = i/5*pow(-1, i);
        }
    }
    return matrix;
}

void print(float** matrix, int i)
{
    if(i == 10){
        return;
    }
    for(int j = 0; j < 10; j++){
        cout << matrix[i][j] << "  |  ";
    }
    cout << endl;
    print(matrix, i+1);
}

void deleteMatr(float** matrix)
{
    int i = 0;
    while(i < 10){
        delete[] matrix[i];
        i++;
    }
    delete[] matrix;
}

int ** createMatr_i(){
    int ** matrix = new int * [10];
    for(int i = 0; i < 10; i++){
        matrix[i] = new int[10];
    }

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            matrix[i][j] = static_cast<int>(tan(abs(i-2*j)));
        }
    }
    return matrix;
}

void print(int** matrix)
{
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cout << matrix[i][j] << "   ";
        }
        cout << endl;
    }
}

void deleteMatr(int** matrix)
{
    for(int i = 0; i < 10; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
}

float ** Sort(float** matrix){
    int rows = 10;
    int cols = 10;
    for(int i = 0; i < cols; i++){
        for(int k = 0; k < rows-1; k++){
            for(int j = 0; j < rows - k - 1; j++){
                if(matrix[j][i]>matrix[j+1][i]){
                    float temp = matrix[j][i];
                    matrix[j][i] = matrix[j+1][i];
                    matrix[j+1][i] = temp; 
                }
            }
        }
    }
    return matrix;
}

float ** Sort(float** matrix, const int num){
    int rows = 10;
    int cols = 10;
    for(int i = 0; i < rows; i++){
        for(int k = 0; k < cols-1; k++){
            for(int j = 0; j < cols - k - 1; j++){
                if(matrix[j][k]<matrix[j][k+1]){
                    float temp = matrix[j][k];
                    matrix[j][k] = matrix[j][k+1];
                    matrix[j][k+1] = temp; 
                }
            }
        }
    }
    return matrix;
}

int * createArr(float ** matrix, int array[]){
    srand(time(NULL));
    for(int i = 0; i < 10; i++){
        float sum = 0;
        for(int j = 0; j < 3; j++){
            int index = rand()%10;
            sum += matrix[index][i];
        }
        int value = static_cast<int>(trunc(sum));
        array[i] = value;
    }
    return array;
}

void printArr(int arr[]){
    for(int i = 0; i < 10; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

bool WriteToFile(const char* filename, int arr[]){
    ofstream oFile(filename);
    if(!oFile.is_open()){
        return false;
    }
    for(int i = 0; i < 10; i++){
        oFile << arr[i] << " ";
    }
    oFile.close();
    return true;
}

int dobutok(const char* filename){
    ifstream iFile(filename);
    if(!iFile.is_open()){
        cout << "error" << endl;
        return 0;
    }
    int dob = 1;
    int number;
    string line;
    while(iFile >> number){
        dob *= number;
    }
    iFile.close();
    return dob;
}

void removeFile(const char* filename){
    if(remove(filename) == 0){
        cout << "Файл видалено успішно" << endl;
    } else {
        cout << "Помилка видалення файлу" << endl;
    }
}

int main(){
    const int request = 872;

    if(request%2==0){
        float ** matr = createMatr_f();
        print(matr, 0);

        matr = Sort(matr);
        cout << endl << "sorted columns:" << endl;
        print(matr, 0);

        matr = Sort(matr, request);
        cout << endl << "sorted rows:" << endl;
        print(matr, 0);

        int arr[10];
        createArr(matr, arr);
        cout << endl;
        printArr(arr);

        deleteMatr(matr);

        char name[15] = "array.txt";
        bool cond = WriteToFile(name, arr);
        if(cond == true){
            cout << "Файл записано успішно" << endl;
        } else {
            cout << "Помилка відкриття файлу" << endl;
        }

        int val = dobutok(name);
        cout << val << endl;

        removeFile(name);
    } else {
        int ** matr = createMatr_i();
        print(matr);
        deleteMatr(matr);
    }
    
    return 0;
}
