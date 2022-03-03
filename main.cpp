#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sys/time.h>

#ifdef USE_STD
# include <map>
# include <stack>
# include <vector>
# define LEAKCHECK "leaks std_containers"
# define TIMEFILE "times_std.txt"
	namespace ft = std;
#else
# include "map.hpp"
# include "stack.hpp"
# include "vector.hpp"
# define LEAKCHECK "leaks ft_containers"
# define TIMEFILE "times_ft.txt"
#endif

// This logger class is used to log the execution time of functions to a file.
class Logger
{
	public:
		Logger()
		{
			_timeFile.open(TIMEFILE);
			_timeFile << std::fixed << std::setprecision(0);
		}
		~Logger()
		{
			_timeFile.close();
		}

		void	time(std::string const &name, double time)
		{
			_timeFile << std::setw(30) << std::left;
			_timeFile << name + ":";
			_timeFile << std::setw(10) << std::right;
			_timeFile << time << std::endl;
		}

	private:
		std::ofstream	_timeFile;
};

// This function can be used to check for leaks at the end of the program.
void	checkLeaks()
{
	system(LEAKCHECK);
}

// This function will print a vector
template <typename T>
void	printVector(ft::vector<T> &vec)
{
	std::cout << "Vector size: " << vec.size() << ", capacity: " << vec.capacity() << std::endl;
	std::cout << "Elements: [";
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i];
		if (i != vec.size() - 1)
			std::cout << ",";
	}
	std::cout << "]" << std::endl << std::endl;
}

// This function will print a stack
template <typename T>
void	printStack(ft::stack<T> &st)
{
	std::cout << "Stack size: " << st.size() << ", empty: " << st.empty() << std::endl;
	if (!st.empty())
		std::cout << "Top item: " << st.top() << std::endl << std::endl;
}

// This function will print a map
template <typename T1, typename T2>
void	printMap(ft::map<T1, T2> &m)
{
	typename ft::map<T1, T2>::value_type		pair;
	typename ft::map<T1, T2>::iterator			it;

	it = m.begin();
	std::cout << "Map size: " << m.size() << ", empty: " << m.empty() << std::endl;
	if (m.empty())
		return ;
	std::cout << "Elements: ";
	while (it != m.end())
	{
		std::cout << "[" << it->first << "," << it->second << "]";
		it++;
		if (it != m.end())
			std::cout << ", ";
	}
	std::cout << std::endl << std::endl;
}

// Some basic vector tests, filling a vector with random values, popping most of them,
// clearing, resizing, reserving extra space, accessing individual elements.
void	vectorBasics()
{
	ft::vector<int>				vec;

	for (int i = 0; i < 200; i++)
		vec.push_back(rand());
	printVector(vec);
	for (int i = 0; i < 190; i++)
		vec.pop_back();
	printVector(vec);
	std::cout << vec.empty() << std::endl;
	vec.clear();
	printVector(vec);
	std::cout << vec.empty() << std::endl;

	for (int i = 0; i < 5; i++)
		vec.push_back(i);
	printVector(vec);
	vec.resize(9);
	printVector(vec);
	vec.resize(3);
	printVector(vec);
	vec.reserve(300);
	printVector(vec);
	std::cout << vec[2] << ", " << vec[0] << std::endl;
	try
	{
		int a = vec.at(1);
		std::cout << a << std::endl;
		vec.at(6);
		std::cout << a << std::endl;
	}
	catch (std::out_of_range &e)
	{
		std::cout << "Out of range error caught as expected." << std::endl;
	}
}

// Testing the different kinds of vector constructors.
void	vectorConstructors()
{
	ft::vector<int>				vecEmpty;
	printVector(vecEmpty);
	ft::vector<int>				vecFill(13, 26);
	printVector(vecFill);
	ft::vector<int>::iterator	it1, it2;
	for (int i = 0; i < 20; i++)
		vecEmpty.push_back(i);
	ft::vector<int>				vecCopy(vecEmpty);
	printVector(vecEmpty);
	printVector(vecCopy);
	it1 = vecEmpty.begin() + 2;
	it2 = vecEmpty.end() - 3;
	ft::vector<int>				vecRange(it1, it2);
	printVector(vecRange);
}

// Testing vector assign, insert, erase and swap.
void	vectorModifiers()
{
	ft::vector<int>				vec1, vec2, vec3;
	ft::vector<int>::iterator	it1, it2, it3;
	for (int i = 0; i < 20; i++)
	{
		vec1.push_back(i);
		vec2.push_back(i + 20);
		vec3.push_back(i + 40);
	}
	it1 = vec1.begin() + 1;
	it2 = vec1.end() - 1;
	vec2.assign(it1, it2);
	printVector(vec2);
	vec2.assign(20, 30);
	printVector(vec2);
	it1 = vec1.insert(it1, 42);
	printVector(vec1);
	std::cout << *it1 << std::endl;
	vec1.insert(it1, 3, 144);
	printVector(vec1);
	it2 = vec3.begin();
	it3 = vec3.end();
	vec1.insert(it1, it2, it3);
	printVector(vec1);
	it1 = vec1.begin() + 3;
	it1 = vec1.erase(it1);
	std::cout << *it1 << std::endl;
	printVector(vec1);
	it1 = vec1.begin() + 2;
	it2 = vec1.end() - 2;
	it1 = vec1.erase(it1, it2);
	std::cout << *it1 << std::endl;
	printVector(vec1);
	it1 = vec1.begin();
	it2 = vec3.begin();
	vec1.swap(vec3);
	printVector(vec1);
	printVector(vec3);
	std::cout << *it1 << "," << *it2 << std::endl;
}

// Testing vector iterators.
void	vectorIterators()
{
	ft::vector<int>						vec;
	ft::vector<int>::iterator			it1, it2;
	ft::vector<int>::reverse_iterator	rit1, rit2;

	for (int i = 0; i < 6; i++)
		vec.push_back(i);

	it1 = vec.begin();
	it2 = vec.end();
	while (it1 != it2)
	{
		std::cout << *it1 << std::endl;
		it1++;
	}
	rit1 = vec.rbegin();
	rit2 = vec.rend();
	while (rit1 != rit2)
	{
		std::cout << *rit1 << std::endl;
		rit1++;
	}
	it1 = 2 + vec.begin();
	*it1 = 12;
	rit1 = 1 + vec.rbegin();
	*rit1 = 13;
	printVector(vec);
	rit1 = 3 + vec.rbegin();
	rit2 = vec.rbegin() + 5;
	std::cout << rit2 - rit1 << std::endl;

	it1 = vec.begin() + 5;
	it2 = vec.begin() + 3;
	int a = it1 - it2;
	std::cout << "A: " << a << std::endl;

	ft::vector<std::string>						vec2;
	ft::vector<std::string>::iterator			it3;
	ft::vector<std::string>::reverse_iterator	rit3;

	vec2.push_back("Hello");
	vec2.push_back("Hello");
	it3 = vec2.begin();
	it3->append(" world!");
	printVector(vec2);
	rit3 = vec2.rbegin();
	rit3->append(" world!");
	printVector(vec2);

	ft::vector<int>::const_iterator				cit1;
	ft::vector<int>::const_reverse_iterator		crit1, crit2;

	cit1 = vec.begin();
	std::cout << *cit1 << std::endl;
	crit1 = vec.rbegin();
	crit2 = vec.rbegin() + 4;
	std::cout << *crit1 << std::endl;
	it1 = vec.begin() + 5;
	cit1 = vec.begin() + 2;
	a = it1 - cit1;
	std::cout << "A: " << a << std::endl;
	it1 -= 4;
	a = cit1 - it1;
	std::cout << "A: " << a << std::endl;
	printVector(vec);
	std::cout << *it1 << std::endl;
	std::cout << it1[3] << std::endl;
	std::cout << rit1 - crit2 << std::endl;
	crit1 = vec.rbegin() + 4;
	std::cout << *crit1 << std::endl;
	std::cout << crit1[1] << std::endl;
}

// Testing vector relational operators.
void	vectorRelational()
{
	ft::vector<int>			vec1, vec2, vec3;

	for (int i = 0; i < 5; i++)
	{
		vec1.push_back(i);
		vec2.push_back(i + 1);
		vec3.push_back(i);
	}

	std::cout << (vec1 == vec2) << std::endl;
	std::cout << (vec2 == vec1) << std::endl;
	std::cout << (vec1 == vec3) << std::endl;
	std::cout << (vec2 == vec3) << std::endl;
	std::cout << (vec1 != vec2) << std::endl;
	std::cout << (vec2 != vec1) << std::endl;
	std::cout << (vec1 != vec3) << std::endl;
	std::cout << (vec2 != vec3) << std::endl;
	std::cout << (vec1 < vec2) << std::endl;
	std::cout << (vec2 < vec1) << std::endl;
	std::cout << (vec1 < vec3) << std::endl;
	std::cout << (vec2 < vec3) << std::endl;
	std::cout << (vec1 <= vec2) << std::endl;
	std::cout << (vec2 <= vec1) << std::endl;
	std::cout << (vec1 <= vec3) << std::endl;
	std::cout << (vec2 <= vec3) << std::endl;
	std::cout << (vec1 > vec2) << std::endl;
	std::cout << (vec2 > vec1) << std::endl;
	std::cout << (vec1 > vec3) << std::endl;
	std::cout << (vec2 > vec3) << std::endl;
	std::cout << (vec2 >= vec1) << std::endl;
	std::cout << (vec1 >= vec2) << std::endl;
	std::cout << (vec1 >= vec3) << std::endl;
	std::cout << (vec2 >= vec3) << std::endl;
}

// Vector stress tests.
void	vectorStressTest()
{
	ft::vector<int>				vec;

	for (int i = 0; i < 1000000; i++)
		vec.push_back(rand());
	std::cout << vec[500000] << std::endl;
}

// Some basic stack tests. Pushing, popping. Not much more to it.
void	stackBasics()
{
	ft::stack<int>			st;
	for (int i = 0; i < 5; i++)
		st.push(i);
	printStack(st);
	for (int i = 0; i < 5; i++)
	{
		std::cout << "Current top: " << st.top() << std::endl;
		st.pop();
	}
	printStack(st);
}

// Some stack relational operator tests. Mostly irrelevant, since they really on
// the relational operators of the underlying containers anyway.
void	stackRelational()
{
	ft::stack<int>		s1, s2, s3;

	for (int i = 0; i < 5; i++)
	{
		s1.push(i);
		s2.push(i + 1);
		s3.push(i);
	}

	std::cout << (s1 == s2) << std::endl;
	std::cout << (s2 == s1) << std::endl;
	std::cout << (s1 == s3) << std::endl;
	std::cout << (s2 == s3) << std::endl;
	std::cout << (s1 != s2) << std::endl;
	std::cout << (s2 != s1) << std::endl;
	std::cout << (s1 != s3) << std::endl;
	std::cout << (s2 != s3) << std::endl;
	std::cout << (s1 < s2) << std::endl;
	std::cout << (s2 < s1) << std::endl;
	std::cout << (s1 < s3) << std::endl;
	std::cout << (s2 < s3) << std::endl;
	std::cout << (s1 <= s2) << std::endl;
	std::cout << (s2 <= s1) << std::endl;
	std::cout << (s1 <= s3) << std::endl;
	std::cout << (s2 <= s3) << std::endl;
	std::cout << (s1 > s2) << std::endl;
	std::cout << (s2 > s1) << std::endl;
	std::cout << (s1 > s3) << std::endl;
	std::cout << (s2 > s3) << std::endl;
	std::cout << (s2 >= s1) << std::endl;
	std::cout << (s1 >= s2) << std::endl;
	std::cout << (s1 >= s3) << std::endl;
	std::cout << (s2 >= s3) << std::endl;
}

// Some basic map tests.
void	mapBasics()
{
	ft::map<int, int>								m1, m2;
	ft::map<int, int>::iterator						it, it2;
	ft::pair<int, int>								p1;
	ft::pair<ft::map<int, int>::iterator, bool>		insertReturn;
	ft::map<int, int>::size_type					size;

	// Creating a map with the insert operator
	for (int i = 0; i < 5; i++)
	{
		p1.first = i;
		p1.second = i * 2;
		insertReturn = m1.insert(p1);
		if (insertReturn.second)
		{
			it = insertReturn.first;
			std::cout << "Inserted: [" << it->first << "," << it->second << "]" << std::endl;
		}
	}
	// Trying to insert something with a key that already exists
	p1.first = 3;
	p1.second = 900;
	insertReturn = m1.insert(p1);
	std::cout << "Inserted? " << insertReturn.second << std::endl;
	it = insertReturn.first;
	std::cout << "It points to: [" << it->first << "," << it->second << "]" << std::endl;
	printMap(m1);

	// Creating a second map with the bracket operator
	for (int i = 2; i < 12; i++)
		m2[i] = 1000 + i;
	printMap(m2);
	// Inserting m2 into m1 with some overlapping elements
	m1.insert(m2.begin(), m2.end());
	printMap(m1);
	printMap(m2);

	// Printing an element that doesn't exist (will create an 'empty' entry, so
	// increase the size of the map by 1
	std::cout << m1.size() << std::endl;
	std::cout << m1[900] << std::endl;
	std::cout << m1.size() << std::endl;

	// Use find to get an iterator to an element
	it = m1.find(9);
	std::cout << "[" << it->first << "," << it->second << "]" << std::endl;

	// Use find to try to find something that doesn't exist
	// This will return the end() iterator
	it = m1.find(3000);
	if (it == m1.end())
		std::cout << "Element does not exist" << std::endl;
	else
		std::cout << "[" << it->first << "," << it->second << "]" << std::endl;

	// Use an iterator to erase an element
	printMap(m1);
	it = m1.find(8);
	m1.erase(it);
	printMap(m1);

	// Use a key to erase an element
	size = m1.erase(9);
	std::cout << "We removed " << size << " elements." << std::endl;
	printMap(m1);
	// Now one that does not exist
	size = m1.erase(16);
	std::cout << "We removed " << size << " elements." << std::endl;
	printMap(m1);

	// Now we use a range of iterators to remove a few elements
	it = m1.begin();
	it2 = m1.end();
	for (int i = 0; i < 4; i++)
	{
		it++;
		it2--;
	}
	m1.erase(it, it2);
	printMap(m1);

	// Use count to find how many occurences of an element are in the map.
	// This can be either 0 or 1, since keys in a map are unique.
	std::cout << m1.count(3) << std::endl; // 1, this key is in the map.
	std::cout << m1.count(4) << std::endl; // 0, this key is not in the map.

	// And finally, swap
	it = m1.begin();
	it2 = m2.begin();
	printMap(m1);
	printMap(m2);
	std::cout << "[" << it->first << "," << it->second << "]" << std::endl;
	std::cout << "[" << it2->first << "," << it2->second << "]" << std::endl;
	m1.swap(m2);
	printMap(m1);
	printMap(m2);
	std::cout << "[" << it->first << "," << it->second << "]" << std::endl;
	std::cout << "[" << it2->first << "," << it2->second << "]" << std::endl;
	swap(m1, m2);
	printMap(m1);
	printMap(m2);
	std::cout << "[" << it->first << "," << it->second << "]" << std::endl;
	std::cout << "[" << it2->first << "," << it2->second << "]" << std::endl;
}

// Map relational operators test.
void	mapRelational()
{
	ft::map<int, int>				m1, m2;
	m1[3] = 4;
	m2[4] = 3;
	std::cout << (m1 < m2) << std::endl;
	std::cout << (m2 < m1) << std::endl;
	m2[1] = 5;
	std::cout << (m1 < m2) << std::endl;

	m1[1] = 5;
	m1[4] = 3;
	m2[3] = 4;
	std::cout << (m1 == m2) << std::endl;
	std::cout << (m1 != m2) << std::endl;
	std::cout << (m1 < m2) << std::endl;
	std::cout << (m1 <= m2) << std::endl;
	std::cout << (m1 > m2) << std::endl;
	std::cout << (m1 >= m2) << std::endl;
	m2[3] = 3;
	std::cout << (m1 == m2) << std::endl;
	std::cout << (m1 != m2) << std::endl;
	std::cout << (m1 < m2) << std::endl;
	std::cout << (m1 <= m2) << std::endl;
	std::cout << (m1 > m2) << std::endl;
	std::cout << (m1 >= m2) << std::endl;
}

// Map stress test.
void	mapStressTest()
{
	ft::map<int, int>			m1;
	ft::map<int, int>::iterator	it;

	for (int i = 0; i < 100000; i++)
		m1[rand()] = rand();
	it = m1.begin();
	for (int i = 0; i < 50000; i++)
		it++;
	std::cout << it->first << "," << it->second << std::endl;
}

// This typedefs 'testFunction' as a function that takes and returns nothing.
typedef void (*testFunction)(void);

// This function calculates the time before and after we run a specific
// function, and outputs it with the logger to a file.
void	calculateTimeTaken(testFunction func, std::string const &testName, Logger &logger)
{
	struct timespec		begin;
	struct timespec		end;
	long				seconds;
	long				nanoseconds;
	double				time_taken;

	clock_gettime(CLOCK_REALTIME, &begin);
	func();
	clock_gettime(CLOCK_REALTIME, &end);
	seconds = end.tv_sec - begin.tv_sec;
	nanoseconds = end.tv_nsec - begin.tv_nsec;
	time_taken = seconds * 1e+9 + nanoseconds;
	logger.time(testName, time_taken);
}

int main()
{
	Logger				logger;

	// Uncomment this to check for leaks. Don't use this in the 'test' command
	// for make.
	//atexit(checkLeaks);

	// Print all booleans as 'true' or 'false' for readability.
	std::cout << std::boolalpha;

	// This map will translate the strings in the vector to the
	// corresponding functions.
	ft::map<std::string, testFunction>		tests;
	tests["Vector basics"] = vectorBasics;
	tests["Vector constructors"] = vectorConstructors;
	tests["Vector modifiers"] = vectorModifiers;
	tests["Vector iterators"] = vectorIterators;
	tests["Vector relational operators"] = vectorRelational;
	tests["Vector stress test"] = vectorStressTest;
	tests["Stack basics"] = stackBasics;
	tests["Stack relational operators"] = stackRelational;
	tests["Map basics"] = mapBasics;
	tests["Map relational operators"] = mapRelational;
	tests["Map stress test"] = mapStressTest;

	// This vector of functions is used to iterate over the map and run the
	// right testing functions.
	ft::vector<std::string>		testNames;
	testNames.push_back("Vector basics");
	testNames.push_back("Vector constructors");
	testNames.push_back("Vector modifiers");
	testNames.push_back("Vector iterators");
	testNames.push_back("Vector relational operators");
	testNames.push_back("Vector stress test");
	testNames.push_back("Stack basics");
	testNames.push_back("Stack relational operators");
	testNames.push_back("Map basics");
	testNames.push_back("Map relational operators");
	testNames.push_back("Map stress test");

	std::string		testName;
	for (size_t i = 0; i < testNames.size(); i++)
	{
		testName = testNames[i];
		std::cout << "Now testing: " << testName << std::endl << std::endl;
		calculateTimeTaken(tests[testName], testName, logger);
		std::cout << std::endl;
		std::cout << "=================================================================";
		std::cout << std::endl << std::endl;
	}
}
