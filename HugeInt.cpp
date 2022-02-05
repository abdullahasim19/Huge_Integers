#include <iostream>
#include <cstring>
using namespace std;
class HugeInteger
{
private:
	char* data;
	int size;
public:
	void trim()
	{
		int length = strlen(data);
		int* arr = toint(data);
		int count = 0;
		for (int i = 0; i < length; i++)
		{
			if (arr[i] == 0)
				count++;
			else
				break;
		}
		if (count > 0)
		{
			int size1 = length - count;
			int* arr1 = new int[size1];
			for (int i = length - 1, j = size1 - 1; j >= 0; i--, j--)
				arr1[j] = arr[i];
			delete[]data;
			this->size = size1;
			data = tochar(arr1, size1);
			delete[]arr1;
			delete[]arr;
		}
	}
	char* tochar(int* ptr, int size)
	{
		char* arr = new char[size + 1];
		int i;
		for (i = 0; i < size; i++)
		{
			arr[i] = ptr[i] + '0';
		}
		arr[i] = '\0';
		return arr;
	}
	int* toint(char* ptr)
	{
		int length = strlen(ptr);
		int* arr = new int[length];
		for (int i = 0; i < length; i++)
		{
			arr[i] = ptr[i] - '0';

		}
		return arr;
	}
	HugeInteger()
	{
		data = NULL;
		size = 0;
	}
	HugeInteger(int length)
	{
		this->size = length;
		data = new char[size + 1];

	}
	HugeInteger(const HugeInteger& obj)
	{
		this->size = obj.size;
		this->data = new char[this->size + 1];
		int i;
		for (i = 0; i < size; i++)
			this->data[i] = obj.data[i];
		this->data[i] = '\0';
	}
	friend istream& operator>>(istream& in, HugeInteger& ob)
	{
		char* arr = new char[200];
		cout << "Enter the number\n";
		in >> arr;
		int size = strlen(arr);
		ob.data = new char[size + 1];
		int i;
		for (i = 0; i < size; i++)
			ob.data[i] = arr[i];
		ob.data[i] = '\0';
		ob.size = strlen(ob.data);
		HugeInteger null(1);
		null.data[0] = '0';
		null.data[1] = '\0';
		if (ob != null)
			ob.trim();
		delete[]arr;
		return in;
	}
	friend ostream& operator<<(ostream& out, HugeInteger& obj)
	{
		out << obj.data << endl;
		return out;
	}
	HugeInteger operator=(HugeInteger obj)
	{
		this->size = obj.size;
		this->data = new char[this->size + 1];
		int i;
		for (i = 0; i < size; i++)
			this->data[i] = obj.data[i];
		this->data[i] = '\0';
		return *this;
	}
	bool operator==(HugeInteger& obj)
	{
		if (this->size != obj.size)
			return false;
		else
		{
			for (int i = 0; i < this->size; i++)
			{
				if (this->data[i] != obj.data[i])
					return false;
			}
			return true;
		}
	}
	bool operator!=(HugeInteger obj)
	{
		int length = 0;
		int size1 = strlen(data);
		int size2 = strlen(obj.data);
		if (size1 != size2)
			return true;
		else
		{
			for (int i = 0; i < size1; i++)
			{
				if (this->data[i] == obj.data[i])
					return false;
			}
			return true;
		}

	}
	bool operator>(HugeInteger obj)
	{
		if (*this == obj)
			return false;
		if (size > obj.size)
			return true;
		else if (size < obj.size)
			return false;
		else
		{
			for (int i = 0; i < size; i++)
			{
				if (data[i] < obj.data[i])
					return false;
			}
			return true;
		}
	}
	bool operator<(HugeInteger obj)
	{
		if (*this == obj)
			return false;
		if (size < obj.size)
			return true;
		else if (size > obj.size)
			return false;
		else
		{
			for (int i = 0; i < size; i++)
			{
				if (data[i] > obj.data[i])
					return false;
			}
			return true;
		}
	}
	bool operator>=(HugeInteger obj)
	{
		if (*this > obj || *this == obj)
			return true;
		else
			return false;
	}
	bool operator<=(HugeInteger obj)
	{
		if (*this < obj || *this == obj)
			return true;
		else
			return false;
	}
	friend HugeInteger operator+(HugeInteger ob, HugeInteger obj)
	{
		if (obj.data[0] == '0' && obj.size == 1)
			return ob;
		int final = 200;
		int size1 = strlen(ob.data);
		int size2 = strlen(obj.data);
		int* first = ob.toint(ob.data);
		int* second = obj.toint(obj.data);
		int temp[200] = { 0 };
		int carry = 0;
		int result = 0;
		int i = size1 - 1;
		int j = size2 - 1;
		int k = final - 1;
		while (i >= 0 && j >= 0)
		{
			result = first[i] + second[j] + carry;
			temp[k] = result % 10;
			carry = result / 10;
			i--;
			j--;
			k--;
		}
		if (size1 > size2)
		{
			while (i >= 0)
			{
				temp[k] = (first[i] + carry) % 10;
				carry = (first[i] + carry) / 10;
				i--;
				k--;
			}
		}
		else if (size2 > size1)
		{
			while (j >= 0)
			{
				temp[k] = (second[j] + carry) % 10;
				carry = (second[j] + carry) / 10;
				j--;
				k--;
			}
		}
		if (temp[k] != carry)
		{
			temp[k] = carry;
			k--;
		}
		char* ans = ob.tochar(temp, final);
		HugeInteger obj2(final);
		int z;
		for (z = 0; z < final; z++)
			obj2.data[z] = ans[z];
		obj2.data[z] = '\0';
		obj2.trim();
		delete[]first;
		delete[]second;
		delete[]ans;
		return obj2;
	}
	HugeInteger operator-(HugeInteger obj)
	{
		if (*this == obj)
		{
			HugeInteger r(1);
			r.data[0] = '0';
			r.data[1] = '\0';
			return r;
		}
		else if (obj.data[0] == '0' && obj.size == 1)
			return *this;
		int* first = toint(data);
		int* second = toint(obj.data);
		int size1 = strlen(data);
		int size2 = strlen(obj.data);
		int final = 0;
		if (size1 > size2)
			final = size1;
		else
			final = size2;
		int i = size1 - 1;
		int j = size2 - 1;
		int k = final - 1;
		int result = 0;
		int borrow = 0;
		int* temp = new int[final];
		while (i >= 0 && j >= 0)
		{
			if (first[i] < second[j])
			{
				borrow = 10 + first[i];
				int a = i - 1;
				while (first[a] == 0)
				{
					first[a] = 9;
					a--;
				}
				first[a]--;
				temp[k] = borrow - second[j];
			}
			else
			{
				temp[k] = first[i] - second[j];
			}
			i--;
			j--;
			k--;
		}
		while (i >= 0)
		{
			temp[k] = first[i];
			i--;
			k--;
		}
		while (j >= 0)
		{
			temp[k] = second[j];
			j--;
			k--;
		}
		char* ans = tochar(temp, final);
		HugeInteger obj2(final);
		int z;
		for (z = 0; z < final; z++)
			obj2.data[z] = ans[z];
		obj2.data[z] = '\0';
		obj2.trim();
		delete[]first;
		delete[]second;
		delete[]ans;
		return obj2;
	}
	friend HugeInteger operator*(HugeInteger obj, HugeInteger obj1)
	{
		if (obj1.data[0] == '1' && obj1.size == 1)
			return obj;
		else if (obj1.data[0] == '0' && obj1.size == 1)
			return obj1;
		int size1 = strlen(obj.data);
		int size2 = strlen(obj1.data);
		int temp[200] = { 0 };
		int final = 200;
		int k = final - 1;
		int a = final - 1;
		int result = 0;
		int carry = 0;
		int* first = obj.toint(obj.data);
		int* second = obj1.toint(obj1.data);
		for (int j = size2 - 1; j >= 0; j--)
		{
			for (int i = size1 - 1; i >= 0; i--)
			{
				result = (first[i] * second[j]) + carry + temp[k];
				temp[k] = result % 10;
				carry = result / 10;
				k--;
			}
			if (temp[k] != carry)
			{
				temp[k] = temp[k]+carry;
			}
			a--;
			k = a;
		}
		char* answer = obj.tochar(temp, final);
		HugeInteger obj2(final);
		int z;
		for (z = 0; z < final; z++)
			obj2.data[z] = answer[z];
		obj2.data[z] = '\0';
		obj2.trim();
		delete[]first;
		delete[]second;
		delete[]answer;
		return obj2;
	}
	friend HugeInteger operator/(HugeInteger obj, HugeInteger obj1)
	{
		if (obj1.data[0] == '1' && obj1.size == 1)
			return obj;
		else if (obj == obj1)
		{
			HugeInteger result(1);
			result.data[0] = '1';
			result.data[1] = '\0';
			return result;
		}
		else if (obj1.data[0] == '0' && obj1.size == 1)
		{
			const char* arr = "Division not possible.";
			int len = strlen(arr);
			HugeInteger err(len);
			int i;
			for (i = 0; i < len; i++)
				err.data[i] = arr[i];
			err.data[i] = '\0';
			return err;
		}
		HugeInteger count(1);
		count.data[0] = '0';
		count.data[1] = '\0';
		HugeInteger inc(1);
		inc.data[0] = '1';
		inc.data[1] = '\0';
		while (obj >= obj1)
		{
			obj = obj - obj1;
			count = (count + inc);
		}
		return count;
	}
	HugeInteger squareRoot()
	{
		HugeInteger null(1);
		null.data[0] = '0';
		null.data[1] = '\0';
		if (*this == null)
			return null;
		HugeInteger inc(1);
		inc.data[0] = '1';
		inc.data[1] = '\0';
		HugeInteger count(1);
		count.data[0] = '0';
		count.data[1] = '\0';
		while ((count * count) < *this)
		{
			count = (count + inc);
		}
		return count;
	}
	~HugeInteger()
	{
		if (data != NULL)
		{
			delete[]data;
			data = NULL;
			size = 0;
		}
	}
};
int main()
{
	HugeInteger h1, h2;
	cin >> h1;
	cout <<"h1: "<< h1;
	cin >> h2;
	cout <<"h2: "<<h2;
	cout << "h1==h2: " << (h1 == h2) << '\n';
	cout << "h1!=h2: " << (h1 != h2) << '\n';
	cout << "h1<h2: " << (h1 < h2) << '\n';
	cout << "h1>h2: " << (h1 > h2) << '\n';
	cout << "h1<=h2: " << (h1 <= h2) << '\n';
	cout << "h1>=h2: " << (h1 >= h2) << '\n';
	cout << "Sum of two huge integers is : ";
	HugeInteger h = (h1 + h2);
	cout << h;
	cout << "Difference of two huge integers is : ";
	h = h1 - h2;
	cout << h;
	cout << "Product of two huge integers is : ";
	h = (h1 * h2);
	cout << h;
	cout << "Division of two huge integers is : ";
	h = (h1 / h2);
	cout << h;
	HugeInteger root = h.squareRoot();
	cout << "Square Root of h: ";
	cout << root;
	system("pause");
	return 0;
}
