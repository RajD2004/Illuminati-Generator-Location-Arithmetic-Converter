//Illuminati Generator
#include <iostream>
#include <string>
#include <cmath>
using std::cout, std::cin, std::endl, std::string; 


string InsertEye(string asterisks){
    //Helper function to insert an eye into a row of asterisks 
    //Input: Row of asterisks    Output: Row of asterisks with eye in center

    string modified_asterisk = "";
    //Including asterisks and spaces, all rows have an odd number of characters, initializes 1 index to the left of the center position
    int init_val = floor((asterisks.length())/2) -1;

    //Iterate through row adding characters in corresponding positions
    for(int position = 0; position < asterisks.length(); position++){
        //Place less than character at the position 1 index to the left of center
        if (position == init_val){
            modified_asterisk += "<";
            continue;
        }
        //Place O at the center position
        else if (position == init_val + 1){
            modified_asterisk += "O";
            continue;
        }
        //Place > one index to the right of center position
        else if (position == init_val + 2){
            modified_asterisk += ">";
            continue;
        }
        //If any other position, simply copy the corresponding character
        else{
            modified_asterisk += asterisks[position];
            continue;
        }
    }
    return modified_asterisk;
    
}
void GenImg(int height){
    //Generates triangle with eye in the middle 
    //Inputs: height (int)   Output: void

    string total_output = "";
    int num_spaces_left = 0;

    int middle_line = 0;
    //middle line depends on if height is odd or even
    //When height is even, there is one more line above the middle line than below
    if (height % 2 == 0){
        middle_line = (height/2);
    }
    //Equal number of lines above and below middle line
    else if(height % 2 != 0){
        middle_line = std::ceil(height/2);
    }
    //Generate each line
    for(int line = 0; line < height; line++){
        //Number of left spaces depends on which line we are one
        num_spaces_left = height-line;
        string space(num_spaces_left, ' ');
        string asterisks = "*";
        //each line has 'line' number of asterisks, and there is a space for each asterisk, except the last one, hence total number of characters per line is 2 * line - 1.
        for(int ch_num = 1; ch_num <= 2*line;ch_num++){
            //if previous character asterisk, then add space
            if(asterisks[ch_num - 1] == '*'){
                asterisks += " ";
            }
            //if previous character space, then add asterisk
            else if(asterisks[ch_num -1] == ' '){
                asterisks += "*";
            }
        }
        //When creating the middle row, call Insert eye function to insert the eye in the middle of the line 
        if (line == middle_line){ 
            asterisks = InsertEye(asterisks);
        }
        string line_output = (space + asterisks + '\n');
        total_output += line_output;
        
    }
    cout << total_output;
}


int main(){
    int height{0};
    cin >> height;
    GenImg(height);
    return 0;    
}