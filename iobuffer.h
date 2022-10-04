// iobuffer.h
#ifndef IOBUFFER_H
#define IOBUFFER_H
#include <stdlib.h>
#include <iostream>

using namespace std;

#ifndef FALSE
#define FALSE (0)
#define TRUE (1)
#endif

class IOBuffer 
// An abstract base class for file buffers
// Record variables can be packed into and extracted from a buffer.
// Input and Output of packed buffers 
// When each field has a value, the buffer can be written into an ostream.
// 
// operations are provided to allow values to be associated with the fields (Pack)
//	and to fetch the values of fields (Unpack)
// 
{  public:
	IOBuffer (int maxBytes = 1000); // a maximum of maxBytes
	IOBuffer & operator = (const IOBuffer &);
	virtual void Clear (); // clear fields from buffer
	virtual int Pack (const void * field, int size = -1) = 0; // set the value of the next field of the buffer;
	virtual int Unpack (void * field, int maxbytes = -1) = 0; // extract the value of the next field of the buffer
	virtual void Print (ostream &) const;
 	int Init (int maxBytes);
	// the read and write operations return the address of the record
	// sequential read and write operations
	virtual int Read (istream &) = 0; // read a buffer from the stream
	virtual int Write (ostream &) const = 0; // write a buffer to the stream

	// these are the direct access read and write operations
	virtual int DRead (istream &, int recref); // read specified record
	virtual int DWrite (ostream &, int recref) const; // write specified record

	// these header operations return the number of bytes in the header
	virtual int ReadHeader (istream &); 
	        // read from the stream and write to a buffer 
	virtual int WriteHeader (ostream &) const; // write a buffer to the stream

 protected:
	int Initialized; // TRUE if buffer is initialized
	char * Buffer; // character array to hold field values
	int BufferSize; // sum of the sizes of packed fields
	int MaxBytes; // maximum number of characters in the buffer
	int NextByte; // index of next byte to be packed/unpacked
	int Packing; // TRUE if in packing mode, FALSE, if unpacking
};

// field packing operations
// pack a field into a buffer
int PackFixed (char * buffer, void * field, int size = -1);
int PackDelimeted (char *buffer, void * field, int size = -1);
int PackLength (char * buffer, void * field, int size = -1);

#include <string.h>

IOBuffer::IOBuffer (int maxBytes)
// construct with a maximum of maxFields
{
	Init (maxBytes);
}

IOBuffer & IOBuffer :: operator = (const IOBuffer & buffer)
{
	if (MaxBytes < buffer . BufferSize) return *this; // fails
	Initialized = buffer . Initialized;
	BufferSize = buffer . BufferSize;
	memcpy (Buffer, buffer.Buffer, buffer . BufferSize);
	NextByte = buffer . NextByte;
	Packing = Packing;
	return *this;
}

void IOBuffer::Clear ()
// clear field values from buffer
{
	NextByte = 0;
	Packing = TRUE;
}

void IOBuffer::Print (ostream & stream) const
{
	stream<<"MaxBytes "<<MaxBytes<<" BufferSize "<<BufferSize;
}

int IOBuffer::Init (int maxBytes)
{
	Initialized = FALSE;
	if (maxBytes < 0) maxBytes = 0;
	MaxBytes = maxBytes;
	Buffer = new char[MaxBytes];
	BufferSize = 0;
	Clear ();
	return 1;
}

int IOBuffer::DRead (istream & stream, int recref)
// read specified record
{
	stream . seekg (recref, ios::beg);
	if (stream . tellg () != recref) return -1;
	return Read (stream);
}

int IOBuffer::DWrite (ostream & stream, int recref) const
// write specified record
{
	stream . seekp (recref, ios::beg);
	if (stream . tellp () != recref) return -1;
	return Write (stream);
}

static const char * headerStr = "IOBuffer";
static const int headerSize = strlen (headerStr);

int IOBuffer::ReadHeader (istream & stream) 
//See how file header is created in WriteHeader function
{
	char str[headerSize+1];
	stream . seekg (0, ios::beg);
	stream . read (str, headerSize); //read to str from the stream
	if (! stream . good ()) return -1;
	if (strncmp (str, headerStr, headerSize)==0) return headerSize;
	else return -1;
}

int IOBuffer::WriteHeader (ostream & stream) const
{
	stream . seekp (0, ios::beg);//set put pointer to the begining of stream
	stream . write (headerStr, headerSize);
	if (! stream . good ()) return -1;
	return headerSize;
}
#endif
