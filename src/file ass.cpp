#include <iostteam>
using namespace std;
struct Books
{
    char Author_ID[15];
    char ISBN[15];
    char Book_Title[30];
}

struct Authors
{
    char Author_ID[15];
    char Author_Name[30];
    char Address[30];
}

class Library
{
    Books books = new Books();
    Authors authors = new Authors();
    void add();
    void update();
    void Delete();
    void print();
    void query();

}

int
main()
{
}
