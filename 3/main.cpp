//Location Arithmetic Converter 
#include <iostream>
#include <string>
#include <cmath>
#include <cstdint>
#include <algorithm>
using std::cout, std::cin, std::endl, std::string; 

std::int64_t LocToDec(string const & loc){
    //converts a location string to decimal number 
    //input: loc (const reference to a string)   output: decimal (64-bit int)

    //string of all lowercase alphabets
    string alphabet = "abcdefghijklmnopqrstuvwxyz"; 
    std::int64_t decimal = 0; //64 bit intger intialized to 0 (val of total sum)

    //Iterate through location string, find corresponding position of each character in location string, add 2**position to the total sum to convert to decimal 
    for(auto ch: loc){
        auto num = alphabet.find(ch);
        decimal += std::pow(2,num);
    }
    return decimal;
}

string Abbreviate(string const & loc){
    //abbereviates a location string 
    //input: loc (const reference to a string)        output: loc_copy (string)

    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string loc_copy = loc; //copy of const reference (not const)
    sort(loc_copy.begin(), loc_copy.end()); //sort in alphabetical order 

    //keep iterating when string not completely abbreviated 
    while(true){
        //iterate through each letter in location string and check if it matches its preceeding character, if it does, replace both of them with their alphabetical successor
        for (int i = 0; i < loc_copy.size(); ++i){
            if (loc_copy[i] == loc_copy[i+1]){
                int index_1 = alphabet.find(static_cast<char>(loc_copy[i]));
                loc_copy.replace(i, 2, 1, static_cast<char>(alphabet[index_1 + 1]));
               // sort(loc_copy.begin(), loc_copy.end());
            }
        }

        bool loop_counter = true; //loop breaker initialized to true 
        //iterate through copy of location string to see if any more chars are being repeated
        for(int ind = 0; ind < loc_copy.size() ; ++ind){
            //if 2 consecutive characters are equal after sorting, string is not abbreviated, main loop (while true) iterates again
            if(loc_copy[ind] == loc_copy[ind+1]){
                loop_counter = false;
                break;
            }
            else{
                continue;
            }
        }
        //if no 2 consecutive characters in the location string match after sorting, the abbreviation has been completed, break the main while loop
        if (loop_counter == true){
            break;
        }
    }
    return loc_copy;
}

string int_to_bin(int num){
    //helper function converts a standard decimal integer to a binary number
    //input: num (int)                  Output: binary_str (string)

    string binary_str; //uninitialized string initializes to empty string, not undefined behavior
    
    //iterate till number can't be halved any futher, adsd the modulus by 2 (1 or 0) to binary string in appropriate position
    while (num > 0){
        binary_str = (std::to_string(num % 2) + binary_str);
        num /= 2;
    }
    return binary_str; 
}

string DecToLoc(std::int64_t dec){
    //converts decimal numbers to a location string 
    //Inputs: dec (64 bit int)              Outputs: final_result (string)

    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string loc_str; 
    
    //convert number to binary and reverse it since the for loop goes from left to right (number written right to left)
    string binary_str = int_to_bin(dec);
    reverse(binary_str.begin(), binary_str.end());
    
    //iterate through binary string and add corresponding alphabet if character is 1, ignore if character is 0
    for(int ind = 0; ind < binary_str.size(); ++ind){
        if (binary_str[ind] == '1'){
            loc_str += alphabet[ind];
        }
    }
    sort(loc_str.begin(), loc_str.end()); //sort location string
    return loc_str;
}

std::int64_t AddLoc(string const & loc1, string const & loc2){ 
    //Adds to location strings and returns an integer value 
    //inputs: loc1, loc2 (both const references to strings)            Outputs: final_result (64 bit integer)
    
    string combined_str = loc1 + loc2; //concatnate 2 location strings
    combined_str = Abbreviate(combined_str); //abbereviate the concatnation 
    int final_result = LocToDec(combined_str); //covert concatnated location strings into a decimal number

    return final_result;
}

int main(){
    //Main function 

    //variable intializations
    string location_string; 
    int integer{0}; 
    string loc_str1; 
    string loc_str2; 

    //collect and store user inputs for location string and integer
    cout << "Give me a location string: " << endl;
    cin >> location_string; 
    cout << "Give me an integer: " << endl; 
    cin >> integer;

    //Display the following conversions location string to decimal, abbereviated version of location string, and integer to location string
    cout << location_string << " to dec: " << LocToDec(location_string) << endl;
    cout << location_string << " abbreviated: " << Abbreviate(location_string) << endl;
    cout << integer << " to loc: " << DecToLoc(integer) << endl;

    //prompt for 2 more location strings to add, and ignore one occurance of the newline character when collecting inputs 
    std::cin.ignore();
    cout << "Give me 2 more location strings: " << endl; 
    
    //using getline() member function as it delimits at '/n' character rather than a space character 
    getline(cin, loc_str1);
    getline(cin, loc_str2);

    //Display sum of location strings by calling AddLoc() function
    cout << "Sum of " << loc_str1 << " and " << loc_str2 << " is: " << AddLoc(loc_str1, loc_str2) << endl;  
    
    return 0;
}