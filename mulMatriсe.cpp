#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <chrono>
#include <time.h>

using namespace std;
using namespace std::chrono;

vector<vector<float>> readMatrix(const string &name_file)
{
    fstream file;
    vector<vector<float>> vec;
    file.open(name_file);
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string temp;
        vector<float> row;
        while (ss >> temp)
        {
            try
            {
                float value = stof(temp);
                row.push_back(value);
            }
            catch (const std::invalid_argument &e)
            {
                cerr << "Invalid argument in file " << name_file << ": " << temp << endl;
                file.close();
                return {};
            }
            catch (const std::out_of_range &e)
            {
                cerr << "Out of range in file " << name_file << ": " << temp << endl;
                file.close();
                return {};
            }
        }
        if (!row.empty())
        {
            vec.push_back(row);
        }
    }
    file.close();

    return vec;
}

void writeMatrix(vector<vector<float>> vec, const string &name_file)
{
    ofstream file;
    file.open(name_file);
    int size_row = vec.size(), size_column = vec[0].size();

    for (int i = 0; i < size_row; i++)
    {
        for (int j = 0; j < size_column; j++)
        {
            file << vec[i][j] << " ";
        }
        file << "\n";
    }
    file.close();
}

void writeTime(const string &content, const string &name_file)
{
    ofstream file;
    file.open(name_file);
    file << content;
    file.close();
}

vector<vector<float>> mulMatrices(vector<vector<float>> vec1, vector<vector<float>> vec2)
{
    int row1 = vec1.size();
    if (row1 == 0)
    {
        cerr << "Error: Matrix 1 is empty." << endl;
        return {};
    }
    int column1 = vec1[0].size();
    int row2 = vec2.size();
    if (row2 == 0)
    {
        cerr << "Error: Matrix 2 is empty." << endl;
        return {};
    }
    int column2 = vec2[0].size();

    vector<vector<float>> vec_result(row1, vector<float>(column2, 0.0f));

    if (column1 != row2)
    {
        cerr << "Error: Matrix dimensions incompatible for multiplication." << endl;
        return {};
    }

    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < column2; j++)
        {
            float value = 0;
            for (int z = 0; z < column1; z++)
            {
                value += vec1[i][z] * vec2[z][j];
            }
            vec_result[i][j] = value;
        }
    }
    return vec_result;
}

int run(const string &input1, const string &input2, const string &output)
{
    auto start = high_resolution_clock::now();
    vector<vector<float>> vec1 = readMatrix(input1);
    vector<vector<float>> vec2 = readMatrix(input2);

    if (vec1.empty() || vec2.empty())
    {
        cerr << "Error: One or both input matrices are empty. Cannot multiply." << endl;
        return -1;
    }

    vector<vector<float>> result = mulMatrices(vec1, vec2);

    if (result.empty())
    {
        cerr << "Error: Error during multiplication" << endl;
        return -1;
    }
    writeMatrix(result, output);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Times: " << duration.count() << "\n";
    return duration.count();
}

int main()
{
    int time_10 = run("Matrix_1/matrix1_10.txt", "Matrix_2/matrix2_10.txt", "Output/output_10.txt");
    int time_20 = run("Matrix_1/matrix1_20.txt", "Matrix_2/matrix2_20.txt", "Output/output_20.txt");
    int time_30 = run("Matrix_1/matrix1_30.txt", "Matrix_2/matrix2_30.txt", "Output/output_30.txt");
    int time_40 = run("Matrix_1/matrix1_40.txt", "Matrix_2/matrix2_40.txt", "Output/output_40.txt");
    int time_50 = run("Matrix_1/matrix1_50.txt", "Matrix_2/matrix2_50.txt", "Output/output_50.txt");
    int time_60 = run("Matrix_1/matrix1_60.txt", "Matrix_2/matrix2_60.txt", "Output/output_60.txt");
    int time_70 = run("Matrix_1/matrix1_70.txt", "Matrix_2/matrix2_70.txt", "Output/output_70.txt");
    int time_80 = run("Matrix_1/matrix1_80.txt", "Matrix_2/matrix2_80.txt", "Output/output_80.txt");
    int time_90 = run("Matrix_1/matrix1_90.txt", "Matrix_2/matrix2_90.txt", "Output/output_90.txt");
    int time_100 = run("Matrix_1/matrix1_100.txt", "Matrix_2/matrix2_100.txt", "Output/output_100.txt");
    int time_1000 = run("Matrix_1/matrix1_1000.txt", "Matrix_2/matrix2_1000.txt", "Output/output_1000.txt");

    stringstream total_times;
    total_times << time_10 << ", " << time_20 << ", " << time_30 << ", " << time_40 << ", " << time_50 << ", " << time_60 << ", " << time_70 << ", " << time_80 << ", " << time_90 << ", " << time_100 << ", " << time_1000;
    string times = total_times.str();
    writeTime(times, "times.txt");
    return 0;
}