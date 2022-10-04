#include <fstream>
#include <iomanip>
#include <string.h>
#include "iobuffer.h"
#include "delim.h"
#include "zippy.h"

using namespace std;

Zippy AmherstMA;
Zippy WindsorCT;

template <class IOB>
void testBuffer (IOB & Buff, const char * myfile)
{
	Zippy zippy;
	int result;
	int recaddr1, recaddr2, recaddr3, recaddr4;

	// Test writing
	//Buff . Print (cout);
	ofstream TestOut (myfile,ios::out);
	result = Buff . WriteHeader (TestOut);
	cout << "write header "<<result<<endl;
	AmherstMA . Pack (Buff);
	//Buff . Print (cout);
	recaddr1 = Buff . Write (TestOut);
	cout << "write at "<<recaddr1<<endl;
	WindsorCT. Pack (Buff);
	//Buff . Print (cout);
	recaddr2 = Buff . Write (TestOut);
	cout << "write at "<<recaddr2<<endl;
	TestOut . close ();

	// test reading
	ifstream TestIn (myfile, ios::in);
	result = Buff . ReadHeader (TestIn);
	cout <<"read header "<<result<<endl;
	Buff . DRead (TestIn, recaddr1);
	zippy . Unpack (Buff);
	zippy . Print (cout);
	Buff . DRead (TestIn, recaddr2);
	zippy . Unpack (Buff);
	zippy . Print (cout);
}

void InitZippy()
{
	cout << "Initializing 3 zippys"<<endl;
	strcpy (AmherstMA.ZipCode, "1002");//
	strcpy (AmherstMA.PlaceName, "Amherst");
	strcpy (AmherstMA.State, "MA");
	strcpy (AmherstMA.County, "Hampshire");
	strcpy (AmherstMA.Lat, "42.3671");
	strcpy (AmherstMA.Long, "-72.4646");
	AmherstMA . Print (cout);
	strcpy (WindsorCT.ZipCode, "6006");
	strcpy (WindsorCT.PlaceName, "Windsor");
	strcpy (WindsorCT.State, "CT");
	strcpy (WindsorCT.County, "Hartford");
	strcpy (WindsorCT.Lat, "41.8526");
	strcpy (WindsorCT.Long, "-72.6437");
	WindsorCT.Print (cout);
}

void testDelim ()
{
	cout << "\nTesting DelimTextBuffer"<<endl;
	DelimFieldBuffer::SetDefaultDelim ('|');
	DelimFieldBuffer Buff;
	Zippy :: InitBuffer (Buff);
	testBuffer (Buff, "delim.dat");
}

int main(int argc, char ** argv)
{
	InitZippy();
	testDelim ();
}