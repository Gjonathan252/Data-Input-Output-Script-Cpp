#include <iostream>
#include <fstream>
#include<string>
#include <vector>
#include<sstream>
#include <iomanip>
using namespace std;


int main()
{
	ifstream indataExcel;
	ifstream indataTxt;
	ofstream outdata;
	const int xSize = 6;
	const int ySize = 3;

	string testP = "CVsmFlight must send ..."; //Test point. For simplicity change to test point.	
	/*reads txt documents and adds it to array
	* if line has spaces it will read as seperate strings
	*/
	indataTxt.open("data.txt");
	string readTxt;
	vector<string> inputTxt;
	vector<int> inputTxt2, inputTxt3;
	bool txtFlag = false;
	int x = 0;
	while (txtFlag != true) {
		indataTxt >> readTxt;
		if (readTxt == "close") {
			txtFlag = true;
		}
		else {
			inputTxt.push_back(readTxt);
			inputTxt2.push_back(x);
			inputTxt3.push_back(x+1);
			x++;
		}
	}

	/*reads data from excel. Excel needs to be consistant on rows to determine eof and string will be entire row1,row2,row3 */
	indataExcel.open("infile.csv");
	string c1,my_str;
	bool excelFlag = false;
	string testData[xSize][ySize]; //size of excel (CHANGE)
	int y = 0;
	while (excelFlag != true) {
		indataExcel >> c1; //inputs excel entire row into c1
		int i = 0;
		if ((c1 == "eof,,")) { //change comma to how ever many rows since it inputs as awhole string to the size of the rows.
			excelFlag = true;
		}
		else {
			//inputExcel.push_back(c1);
			stringstream s_stream(c1); //inputs cell line into substring
			while (s_stream.good()) { //loops intil 
				string substr;
				getline(s_stream, substr, ','); //get first string delimited by comma
				testData[y][i] = substr;
				cout << y << i << " = " << testData[y][i] << endl;
				i++;
			}
		}
		y++;
	}

	/*
	* Outputs data to excel. This is the 2d string array method which is gotten using a excel read method.
	*/
	outdata.open("outData.csv");
	for (int i = 0; i < xSize; i++)
	{
		outdata << testData[i][0] << "," << testData[i][1] << "," << testData[i][2] << endl;
		outdata << endl; //expected results table jumps 1 data cell so we can use this to easily extend table
	}

	/*
	* Outputs data as seperate vecors. This assumes you have all you data types in different vectors
	*/
	for (int i = 0; i < inputTxt.size(); i++)
	{
		outdata << inputTxt.at(i) << "," << inputTxt2.at(i) << "," << inputTxt3.at(i) << endl;
		cout << inputTxt.at(i) << "," << inputTxt2.at(i) << "," << inputTxt3.at(i) << endl;
		outdata << endl; //expected results table jumps 1 data cell so we can use this to easily extend table
	}
	

	//Close you files or they can remain open and code will not execute
	indataExcel.close();
	indataTxt.close();
	outdata.close();
	system("pause");
	return 0;
}