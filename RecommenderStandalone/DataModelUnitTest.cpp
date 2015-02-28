#include "FileDataModel.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "Begin test" << endl;
	HANDLE f = CreateFile(L"C:\\Users\\USER007\\Desktop\\kits\\RecommenderStandalone\\a.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	RS::FileDataModel dm("C:\\Users\\USER007\\Desktop\\kits\\RecommenderStandalone\\a.txt", f);

	cout << "End test" << endl;
	cin.get();
	return 0;
}


