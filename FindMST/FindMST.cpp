#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename T>
class myVector
{
private:
	T* arr;
	int capacity;
	int currSize;
public:
	myVector()
	{
		arr = new T[1];
		capacity = 1;
		currSize = 0;
	}
	myVector(int size, T defaultVal)
	{
		arr = new T[size];
		capacity = size;
		currSize = size;
		for (int i = 0; i < currSize; i++)
		{
			arr[i] = defaultVal;
		}
	}
	void push_back(T data)
	{
		if (currSize == capacity)
		{
			T* temp = new T[2 * capacity];
			for (int i = 0; i < capacity; i++)
			{
				temp[i] = arr[i];
			}
			delete[] arr;
			capacity *= 2;
			arr = temp;
		}
		arr[currSize] = data;
		currSize++;
	}

	void push(T data, int index)
	{
		if (index == capacity)
		{
			push_back(data);
		}
		else
		{
			arr[index] = data;
		}
	}

	T get(int index)
	{
		return arr[index];
	}

	void changeElem(int index, T val)
	{
		arr[index] = val;
	}

	int size()
	{
		return currSize;
	}

	int getCapacity()
	{
		return capacity;
	}

	void print()
	{
		for (int i = 0; i < currSize; i++)
		{
			cout << arr[i];
		}
	}

	void quickSort(short left, short right)
	{
		T mid;
		short l = left;
		short r = right;
		mid = arr[(l + r) / 2];
		while (l < r)
		{
			while (arr[l] < mid)
				l++;
			while (arr[r] > mid)
				r--;
			if (l <= r)
			{
				T t = arr[l];
				arr[l] = arr[r];
				arr[r] = t;
				//swap(arr[l], arr[r]);
				l++;
				r--;
			}
		}
		if (left < r)
			quickSort(left, r);
		if (right > l)
			quickSort(l, right);
	}
};

struct Edge
{
	int src, dest, weight;
	string srcStr, destStr;
};

ostream& operator <<(ostream& os, Edge e)
{
	os << e.srcStr << " " << e.destStr << "\n";
	return os;
}

bool operator >(Edge edge1, Edge edge2)
{
	return edge1.weight > edge2.weight;
}

bool operator <(Edge edge1, Edge edge2)
{
	return edge1.weight < edge2.weight;
}

bool operator ==(Edge edge1, Edge edge2)
{
	return edge1.weight == edge2.weight;
}

void findMinSpanningTree(myVector<Edge> edges, int numVertices)
{
	edges.quickSort(0, edges.size() - 1);
	myVector<int> parents(numVertices, -1);
	myVector<Edge> mst;
	int numEdgesAdded = 0;
	for (int i = 0; i < edges.size(); i++)
	{
		int srcParent = -1;
		int destParent = -1;

		int src = edges.get(i).src;
		int dest = edges.get(i).dest;

		while (parents.get(src) != -1)
		{
			src = parents.get(src);
		}
		while (parents.get(dest) != -1)
		{
			dest = parents.get(dest);
		}

		srcParent = src;
		destParent = dest;

		if (srcParent != destParent)
		{
			mst.push_back(edges.get(i));
			numEdgesAdded++;
			parents.changeElem(destParent, srcParent);
		}

		if (numEdgesAdded == numVertices - 1)
		{
			break;
		}
	}
	int sumWeight = 0;
	for (int i = 0; i < mst.size(); i++)
	{
		sumWeight += mst.get(i).weight;
	}
	mst.print();
	cout << "Weight: " << sumWeight;
}

myVector<string> splitToMyVectorStr(string s)
{
	myVector<string> res;
	for (int i = 0; i < s.size(); i++)
	{
		string str = "";
		while (s[i] != ' ' && i < s.size())
		{
			str += s[i];
			i++;
		}
		res.push_back(str);
	}
	return res;
}

myVector<int> splitToMyVectorInt(string s)
{
	myVector<int> res;
	for (int i = 0; i < s.size(); i++)
	{
		int num = 0;
		while (s[i] != ' ' && i < s.size())
		{
			num = num * 10 + (s[i] - '0');
			i++;
		}
		res.push_back(num);
	}
	return res;
}

int main()
{
	setlocale(0, "");
	/*int numVertices = 9;
	myVector<Edge> edges;
	edges.push_back({0, 1, 4});
	edges.push_back({ 1, 2, 8 });
	edges.push_back({ 1, 7, 11 });
	edges.push_back({ 2, 3, 7 });
	edges.push_back({ 2, 8, 2 });
	edges.push_back({ 2, 5, 4 });
	edges.push_back({ 3, 4, 9 });
	edges.push_back({ 3, 5, 14 });
	edges.push_back({ 4, 5, 10 });
	edges.push_back({ 5, 6, 2 });
	edges.push_back({ 6, 7, 1 });
	edges.push_back({ 6, 8, 6 });
	edges.push_back({ 7, 8, 7 });
	findMinSpanningTree(edges, numVertices);  */
	myVector<Edge> edges;
	string s;
	ifstream database("input.txt");
	if (!database.is_open())
	{
		cout << "Ошибка открытия файла!\n";
		return 0;
	}
	if (database.eof())
	{
		cout << "Файл пуст!\n";
		return 0;
	}
	getline(database, s);
	myVector<string> verticesNames = splitToMyVectorStr(s);
	int numVertices = verticesNames.size();
	int counterStr = 0;
	while (!database.eof())
	{
		string s1;
		getline(database, s1);
		myVector<int> weights = splitToMyVectorInt(s1);
		for (int i = counterStr + 1; i < weights.size(); i++)
		{
			if (weights.get(i) > 0)
			{
				edges.push_back({ counterStr, i, weights.get(i), verticesNames.get(counterStr), verticesNames.get(i) });
			}
		}
		counterStr++;
	}
	findMinSpanningTree(edges, numVertices);
}