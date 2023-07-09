#include <bits/stdc++.h>

using namespace std;

long long counter = 10000000000; // to maintaing unqiue urls

// using all alphanumeric characters to create more no of unique combinations
string characters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

string base10tobase62(long long x) // coverting and integer(counter) from base 10 to base 62
{
    string ans = "";
    while (x > 0)
    {
        int y = x % 62;
        ans = characters[y] + ans;
        x /= 62;
    }
    while (ans.length() < 7) // if size is less than 7 adding zeros to maintain uniformity of 7 characters
    {
        ans = '0' + ans;
    }
    return ans;
}

string ltos(string big) // coverts long url to short
{
    string base62 = base10tobase62(counter);
    base62 = "https://www.myurl.com/" + base62;
    counter++; // ensuring uniqueness of short url for each long url input
    return base62;
}

int main()
{
    ifstream file2; // to read the last counter
    file2.open("Counter.txt");
    file2 >> counter;
    file2.close();

    while (1)
    {
        cout << "Enter your choice: \n1: To covert long URL to short URL\n2: Obtain original URL from corresponding short URL\n0: To terminate the program" << endl;
        int choice;
        cin >> choice;
        if (choice == 0)
            break;
        if (choice == 1)
        {
            fstream file;
            file.open("Directory.txt", ios::app);
            cout << "Enter the long url." << endl;
            string big;
            cin >> big;
            string ans = ltos(big); // converting the long URL to short URL
            cout << "Short URL : " << ans << endl
                 << endl;
            big = ans.substr(22) + big; // storing together relevant part of the short URL along with the long URL
            file << big << '\n';        // logging the data for the file/database
            file.close();
        }
        else if (choice == 2)
        {
            ifstream file3;
            file3.open("Directory.txt");
            cout << "Enter the short URL" << endl;
            string small;
            cin >> small;
            if (small.size() < 29) // checking valid url by its length
            {
                cout << "Insufficient length. Please enter the complete URL" << endl
                     << endl;
                continue;
            }
            if (small.substr(0, 22) != "https://www.myurl.com/")
            { // checking valid url by the first half
                cout << "Incorrect URL. Please enter the correct URL" << endl
                     << endl;
                continue;
            }
            small = small.substr(22);
            string temp;
            while (file3 >> temp) // reading in the file
            {

                string temp2 = temp.substr(0, 7);
                if (temp2 == small) // checking for the valid match
                {
                    cout << "Original long URL : " << temp.substr(7) << endl
                         << endl;
                    break;
                }
            }
            if (file3.eof() != 0) // if url not fount error msg is printed
            {
                cout << "Invalid URL!" << endl
                     << endl;
            }
            file3.close();
        }
        else
            cout << "Invalid choice. Please enter your choice again." << endl
                 << endl;
    }
    fstream file4; // for updating last counter value
    file4.open("Counter.txt", ios::out);
    file4 << counter << endl;
    return 0;
}