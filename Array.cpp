// $Id: Array.cpp 820 2011-01-17 15:30:41Z hillj $

// Honor Pledge:
//
// I pledge that I have neither given nor receieved any help
// on this assignment.

#include "Array.h"
#include <stdexcept>






// Kelly, you must implement this method.
//to address this, I initailized all the variables to 0 to implement this default constructor
//common constructor
Array::Array(void)
	:data_(new char[0]),
	cur_size_(0),
	max_size_(0)
{
	
}

//constructor to set the length of the array and allocate the memory for the array
// Kelly, Max size must be equal to the size of the memory allocation.
//To address this, I made max_size_ equal to length
Array::Array(size_t length)
	:data_(new char[length]),
	cur_size_ (length),
	max_size_(length)
{
	
}

//constructor to set the length of the array and fill it with a character
// Kelly, Max size must be equal to the size of the memory allocation.
//To address this, I made max_size_ equal to length
Array::Array(size_t length, char fill)
	:data_(new char[length]),
	cur_size_(length),
	max_size_(length)
{
	//need to allocate the consecutive memory
 // Kelly, this is not required. 
	//To address this, I removed the unncessary lines of code.

	for (size_t i = 0; i < length; i++)
		this->data_[i] = fill;

}

//copy constructor
// Kelly, The copy constructor needs to create a deep copy of the source array. 
// Otherwise, the copy will share a pointer with the original. When one goes out of scope, the other will eventually crash.
//to address this, I made sure all the data is copied over to the new array using the for loop below
Array::Array(const Array & array)
	:data_(new char[array.max_size_]), 
	cur_size_ ( array.cur_size_), 
	max_size_ ( array.max_size_) 
{
	//need to make sure all data is copied over to the new array
	for (size_t i = 0; i < array.cur_size_;i++)
	{
		this->data_[i] = array.data_[i];
	}
}

//destructor will delete off of heap
Array::~Array(void)
{
	delete[] data_;
}

//defines use of "=" with defining the right hand side of the sign
// Kelly, the assignmebt operator needs to create a deep copy of the source array. 
//Otherwise, the copy will share a pointer with the original. When one goes out of scope, the other will eventually crash.
// to address this, I created a deep copy by copying all the correct data over to the array rhs
const Array & Array::operator = (const Array & rhs)
{

	for (int i = 0; i < rhs.cur_size_; i++)
	{
		rhs.data_[i] = this->data_[i];
	}

	return *this;
}

//defines use of "[]" within the use of this class
// Kelly, this method should throw an exception.
//To fix this, I added the exception throw if the index is creater than the current size of the array
char & Array::operator [] (size_t index)
{
	if (index >= this->cur_size_)
		throw std::out_of_range("index out of range");
	else
		return data_[index];
}

// Kelly, this method should throw an exception.
//To fix this, I added the exception throw if the index is creater than the current size of the array
const char & Array::operator [] (size_t index) const
{
	if (index >= this->cur_size_)
		throw std::out_of_range("index out of range");
	else
		return data_[index];
}

//returns the character a specific index
char Array::get(size_t index) const
{
 // Kelly, check your indexing.
	//to fix this, i eliminated the "=" sign. This would cause it to go out of scope
	if (index < cur_size_)
   // Kelly, you can just use data_[i] for easier access.
		//To address this, I am returning the data at the requested index using the preferred notation.
		return this->data_[index];
	else
		throw std::out_of_range("index out of range"); //invalid index location
}

//sets a character at a certain index
void Array::set(size_t index, char value)
{
	if (index < cur_size_)
  // Kelly, you can just use data_[i] for easier access.
  //To address this, I am getting the data at the requested index using the preferred notation.
		this->data_[index] = value;
	else
		throw std::out_of_range("index out of range");
}

//resize the value of cur_size_; make sure it is not greater than max_size_
void Array::resize(size_t new_size)
{
 // Kelly, The resize method should only increase the size of the allocation is larger than the current memory allocation for the array. 
 // If resized, you need to preserve the old data.

//To address this, is made a temporary array to hold the original data. I then resized the cur_size_ and max_size to new_size
	//then, I put the original data back into data_ array to ensure the old data is preserved.

	if(new_size < 0)
		throw std::out_of_range("index out of range");


	if (new_size >= cur_size_)
	{
		char *arr;
		arr= new char[new_size];
		for (int i = 0; i < new_size; i++)
		{
			arr[i] = this->data_[i];
		}

		this->max_size_ = new_size;
		this->cur_size_ = new_size;

		for (int i = 0; i < new_size; i++)
		{
			this->data_[i] = arr[i];
		}

		delete[] arr;
		
	}

	if (new_size < this->cur_size_)
	{
		this->cur_size_ = new_size;
	}
	


}

//find a specific character starting at index 0; return the index of the found character; else return -1
int Array::find(char ch) const
{
	for (int i = 0; i < cur_size_; i++)
  // Kelly, you can just use data_[i] for easier access.
  //To address this, I am getting the data at the requested index using the preferred notation.
		if (this->data_[i] == ch)
			return i;
	return -1; //character not found
}

//find a specific character starting at a certain index; return the index of the found character; else return -1
int Array::find(char ch, size_t start) const
{
 // Kelly, check your indexing.
	//to address this, I added the "=" sign in the following if statement
	if (start >= cur_size_)
		throw std::out_of_range("start index is out of range");
	else
		for (int i = start; i < cur_size_; i++)
			//To address this, I am getting the data at the requested index using the preferred notation.
			if (this->data_[i] == ch)
				return i;

	return -1; //character not found
}

bool Array::operator == (const Array & rhs) const
{
 // Kelly, you are just comparing the pointers. You need to compare the underlying data.
	//To address this, I am comparing each element in the arrays and I am comparing the sizes
	if (this->max_size_ != rhs.max_size_)
		return 0;
	if (this->cur_size_ != rhs.cur_size_)
		return 0;
	for (int i = 0; i < cur_size_; i++)
		if (this->data_[i] != rhs.data_[i])
			return 0;
		
	return 1;
}

bool Array::operator != (const Array & rhs) const
{
	if (this->max_size_ != rhs.max_size_)
		return 1;
	if (this->cur_size_ != rhs.cur_size_)
		return 1;
	for (int i = 0; i < cur_size_; i++)
		if (this->data_[i] != rhs.data_[i])
			return 1;

	return 0;
}

//fill every element of array with character ch
void Array::fill(char ch)
{
	for (int i = 0; i < cur_size_; i++)
  // Kelly, you can just use data_[i] for easier access.
  //To address this, I am getting the data at the requested index using the preferred notation.
		this->data_[i] = ch;
}
