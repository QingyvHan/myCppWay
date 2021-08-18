#include <array>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
using std::cout;
using std::cin;
using std::endl;
using std::string;

const long ASIZE = 500000L; 

long get_a_target_long(){
    long target = 0;

    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    return target;
}

string get_a_target_string() {
    long target = 0;
    char buf[10];

    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    snprintf(buf, 10, "%d", target);
    /*
    int snprintf ( char * s, size_t n, const char * format, ... );
    1. 将...以format格式拷贝n个字节到s中
    2. 成功时返回将要写入的字符串长度，否则返回负值
    */
    return string(buf);
}

int compareLongs(const void* a, const void* b) {
    return ( *(long*)a - *(long*)b);                // Attention!!!
}

int compareStrings(const void* a, const void* b) {  // Attention!!!
    if ( *(string*)a > *(string*)b)
        return 1;
    else if (*(string*)a < *(string*)b)
        return -1;
    else
        return 0;
}

namespace jj01
{
void test_array(){
    cout << "Test_array()...........\n";
    
    std::array<long, ASIZE> c;

    clock_t timeStart = clock();
    for (long i = 0; i < ASIZE; i++) {
        c[i] = rand();
    }
    cout << "milli-seconds: " << (clock() - timeStart) << endl;
    cout << "array.size(): " << c.size() << endl;
    cout << "array.front(): " << c.front() << endl;     // array第一个元素
    cout << "array.back(): " << c.back() << endl;       // array最后一个元素
    cout << "array.data(): " << c.data() << endl;       // returns a pointer of array's first ele

    long target = get_a_target_long();

    timeStart = clock();
    qsort(c.data(), ASIZE, sizeof(long), compareLongs);
    long* pItem = (long*)bsearch(&target, (c.data()), ASIZE, sizeof(long), compareLongs);

    cout << "qsort() + bsearch(), milli-seconds: " << (clock() - timeStart) << endl;
    if (pItem != NULL)
        cout << "found, " << *pItem << endl;
    else
        cout << "not found! " << endl; 
}   
}

#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>

namespace jj02
{
void test_vector(long &value) {
    cout << "\ntest_vector()......\n";

    std::vector<string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; i++) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.push_back(string(buf));
        }
        catch (std::exception& p) {
            cout << "i= " << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "milli-seconds: " << (clock() - timeStart) << endl;
    cout << "vector.size(): " << c.size() << endl;
    cout << "vector.front(): " << c.front() << endl;
    cout << "vector.back(): " << c.back() << endl;
    cout << "vector.data(): " << c.data() << endl;
    cout << "vector.capacity(): " << c.capacity() << endl;

    string target = get_a_target_string();
    {
    timeStart = clock();
    auto pItem = find(c.begin(), c.end(), target);
    cout << "::find(), milli-seconds: " << (clock() - timeStart) << endl;
    if (pItem != c.end())
        cout << "found, " << *pItem << endl;
    else
        cout<<"not found! " << endl;
    }

    {
    timeStart = clock();
    sort(c.begin(), c.end());
    string* pItem = (string*)bsearch(&target, (c.data()), c.size(), sizeof(string), compareStrings);
    cout << "sort+bsearch, milli-seconds: " << (clock() - timeStart) << endl;

    if (pItem != NULL)
        cout << "found, " << *pItem << endl;
    else
        cout << "not found! " << endl;
    }
}
}

#include <list>

namespace jj03
{
void test_list(long &value)
{
    cout << "\ntest_list()..........\n";

    std::list<string> c;
    
}
}

namespace jjxx
{
void test_containers()
{
    int choice;
    long value;
    srand(time(NULL));

    cout << "\n\ntest_containers()......... \n";
	cout << "select: \n";
	cout << "       (1)array (2)vector (3)list (4)forward_list (5)deque (6)multiset \n";
	cout << "       (7)multimap (8)unordered_multiset (9)unordered_multimap (10)slist \n";
	cout << "       (11)hash_multiset (12)hash_multimap (13)set (14)map (15)unordered_set \n";
	cout << "       (16)unordered_map (17)stack (18)queue \n";	
	cout << " (2),(3),(5),(6),(8) will test also moveable elements. \n";
    cin >> choice;

    if (choice != 1) {          // 1 == array, use ASIZE
        cout << "how many elements: " ;
        cin >> value;
    }

    switch(choice){
        case 1 : 	jj01::test_array();		
		 			break;
		case 2 : 	jj02::test_vector(value);	
		 		 	//jj02::test_vector_with_move(value);	
		 			break;	

    }
}
}

int main(int argc, char** argv) {
    
    jjxx::test_containers();

    return 0;
}