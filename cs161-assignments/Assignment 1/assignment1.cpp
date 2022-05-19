/* Program: Signed and Unsigned Calculator
 * Author: Logan Saso
 * Date: 1/11/2017
 * Description: Prints the maximum and minimum values for an inputed signed and unsigned number of bits
 * Input: An integer number describing a size of bits.
 * Output: The maximum unsigned, signed, and minimum signed values for input number of bits.
 */

#include <iostream>
#include <cmath>
#include <climits>
#include <string>

using namespace std;

int main()
{

    int; double; float; short; 
    
    char; string;
    char oa = 'a';
    string James = "Jamess Name";
    
    
    
    std::cout << "Maximum Signed Int: " << INT_MAX << std::endl;
    std::cout << "Minimum Signed Int: " << INT_MIN << std::endl;
    std::cout << "Maximum Unsigned Int: " << UINT_MAX << std::endl;
    std::cout << "Minimum Unsigned Int: 0" << std::endl;
    std::cout << "Maximum Signed Long: " << LONG_MAX << std::endl;
    std::cout << "Minimum Signed Long: " << LONG_MIN << std::endl;
    std::cout << "Maximum Unsigned Long: " << ULONG_MAX << std::endl;
    std::cout << "Minimum Unsigned Long: 0" << std::endl;
    std::cout << "Maximum Signed Short: " << SHRT_MAX << std::endl;
    std::cout << "Minimum Signed Short: " << SHRT_MIN << std::endl;
    std::cout << "Maximum Unsigned Short: " << USHRT_MAX << std::endl;
    std::cout << "Minimum Unsigned Short: 0" << std::endl;

    std::cout << "Maximum Signed 8Bit: " << std::pow(2,7) - 1 << std::endl;
  	std::cout << "Minimum Signed 8Bit: -" << std::pow(2,7) << std::endl;
    std::cout << "Maximum Unsigned 8Bit: " << std::pow(2,8) - 1 << std::endl;

	/*
	 * Extra Credit:
	 * Create a variable for the number of bits and read that.
	 * Then print max and min from the user.
	 */

    int bits = 0;
    std::cout << "Please input bits as a number: ";
    std::cin >> bits;

    std::cout << std::fixed;
    std::cout << "Maximum Unsigned " << bits << "Bit: " << std::pow(2,bits) - 1 << std::endl;
    std::cout << "Maximum Signed " << bits << "Bit: " << std::pow(2,bits-1) - 1 << std::endl;
    std::cout << "Minimum Signed " << bits << "Bit: -" << std::pow(2,bits-1) << std::endl;

	return 0;
}
