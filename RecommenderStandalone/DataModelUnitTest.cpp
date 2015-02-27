#include "FileDataModel.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "Begin test" << endl;
	HANDLE f = NULL;
	RS::FileDataModel dm(f);

	cin.get();
	cout << "End test" << endl;
	return 0;
}


