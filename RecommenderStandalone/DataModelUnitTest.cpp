#include "FileDataModel.h"

#include <iostream>
using namespace std;

int main()
{
	cout << "Begin test" << endl;

	FILE f = FILE();
	RS::FileDataModel dm(f);

	cout << "End test" << endl;
	return 0;
}