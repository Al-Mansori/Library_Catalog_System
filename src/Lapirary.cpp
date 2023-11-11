#include <iostteam>
#include "Aother.cpp"
#include "Book.cpp"
using namespace std;

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