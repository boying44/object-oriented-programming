/*
Boying Tang
rec09
Inheritance
*/

#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
public:
  PrintedMaterial( unsigned numPages )
    : numOfPages(numPages)
  {}

  virtual
  void displayNumPages() const = 0;
private:
  unsigned numOfPages;
};

void PrintedMaterial::displayNumPages() const {
  cout << numOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
	Magazine( unsigned numPages )
		: PrintedMaterial(numPages)
	{}

	void displayNumPages() const
	{
		PrintedMaterial::displayNumPages();
	}

protected:
private:
};

class Book : public PrintedMaterial {
public:
	Book( unsigned numPages)
		: PrintedMaterial(numPages)
	{}
protected:
private:
};

class TextBook : public Book {
public:
	TextBook( unsigned numPages, unsigned numIndxPgs  )
		: Book(numPages),
		  numOfIndexPages(numIndxPgs)
	{}

	void displayNumPages() const
	{
		PrintedMaterial::displayNumPages();
		cout << numOfIndexPages << endl; 
	}
protected:
private:
	unsigned numOfIndexPages;
};

class Novel : public Book {
public:
	Novel( unsigned numPages )
		: Book(numPages)
	{}
	void displayNumPages() const
	{
		PrintedMaterial::displayNumPages();
	}
protected:
private:
};

// tester/modeler code
int main()
{
	TextBook t(5430, 23);
	Novel n(213);
	Magazine m(6);

	t.displayNumPages();
	n.displayNumPages();
	m.displayNumPages();

	vector< PrintedMaterial* > allThemPrinties;
	allThemPrinties.push_back(&t);
	allThemPrinties.push_back(&n);
	allThemPrinties.push_back(&m);
	for( size_t ndx=0; ndx < allThemPrinties.size(); ++ ndx ) 
	{
		allThemPrinties[ndx]->displayNumPages();
		cout << endl;
	}
}
