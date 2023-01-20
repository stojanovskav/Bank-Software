#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

int myMenu(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances);

int containsUppercase(std::string str) {
    int counter = 0;
    for(int i = 0; i < str.size(); i++) {
        if (str[i] >= 'A' and str[i] <= 'Z') {
            counter++;
        }
    }
    return counter;
}

int containsDowncase(std::string str) {
    int counter = 0;
    for(int i = 0; i < str.size(); i++) {
        if (str[i] >= 'a' and str[i] <= 'z') {
            counter++;
        }
    }
    return counter;
}

int containsSymbol(std::string str) {
    int counter = 0;
    for(int i = 0; i < str.size(); i++) {
        if (str[i] == '!' or str[i] == '@' or str[i] == '#' or str[i] == '$' or
            str[i] == '%' or str[i] == '^' or str[i] == '&' or str[i] == '*') {
            counter++;
        }
    }
    return counter;
}

int containsDigit(std::string str) {
    int counter = 0;
    for(int i = 0; i < str.size(); i++) {
        if (str[i] >= '0' and str[i] <= '9') {
            counter++;
        }
    }
    return counter;
}

bool length(std::string str) {
    if (str.size() >= 5) {
        return true;
    }
    return false;
}

bool isValidPassword(std::string password) {
    if (containsUppercase(password) >= 1 and containsDowncase(password) >= 1 and
        containsSymbol(password) >= 1 and length(password) == true) {
            int result = 0;
            result = containsUppercase(password) + containsDowncase(password) + containsSymbol(password) + containsDigit(password);

            if (result == password.size()) {
                return true;
            }
        }

    return false;
}

bool isValidUsername(std::string username) {
    int result = 0;
    result = containsUppercase(username) + containsDowncase(username) + containsSymbol(username) + containsDigit(username);

    if (result == username.size()) {
        return true;
    }
    return false;
}

size_t hash_password(const std::string password) { // to hash a string into size_t variable
    std::size_t hashed = std::hash<std::string>{}(password);

    return hashed;
}

// cast the hashed password from size_t to std::string
std::string toString(size_t hashed_password) {  //
    std::string hash_password;

    hash_password = std::to_string(hashed_password);

    return hash_password;
}

// read data from file and store in different vectors
void readData(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances) {
    std::string line;
    std::ifstream file("users.txt");

    /* If the file is open, it reads each line of the file one at a time and 
    uses the stringstream object and the getline() method to extract the 
    username, password, and balance from each line and store them in the vectors */
    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::string username;
            std::string password;
            double balance;

            /* extracts the first piece of data from the stringstream and store it in the username variable. 
            The first argument of the method is the stringstream (ss), 
            the second argument is the variable where the data is stored (username), 
            and the third argument is the delimiter character (':') which separates the different fields in the line.

            It does the same thing again to extract the password and store it in the password variable.

            >> operator extracts the balance value in double format, 
            the ss object point at the position right after the last ':' and 
            the >> operator reads the next double value and store it in the variable balance.*/
            std::stringstream ss(line);
            std::getline(ss, username, ':');
            std::getline(ss, password, ':');
            ss >> balance;

            usernames.push_back(username);
            passwords.push_back(password);
            balances.push_back(balance);
    }
        file.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
}

// write data to "users.txt" file
void writeData(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances) {
    ofstream outfile("users.txt");
    for(int i = 0; i < usernames.size(); i++){
        outfile << usernames[i] << ":" << passwords[i] << ":" << balances[i] << endl;
    }

    outfile.close();
}

int getIndex(std::vector<std::string> usernames, std::string username) {
    int index = 0;

    for(int i = 0; i < usernames.size(); i++){
        if (usernames[i] == username) { // check if the entered username exists get the index position 
            index = i;
        }
    }

    return index;
}

// if the third digit is greater than or equal to 5 calls floor() function to round the amount
// else calls round() function to round the amount
void roundToTwoDecimals(double &amount) {
    int decimal = (int)(amount*100) % 100;

    if(decimal % 10 >= 5) {
        amount = floor(amount*100 + 0.5) / 100;
    } else {
        amount = round(amount*100) / 100;
    }
}

void cancelAccount(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances,
                    std::string username, double balance) {
    std::string password;
    std::cout << "Enter your password: ";
    std::cin >> password;

    // hashes the entered password and later casts it to string type 
    // to be able to compare the entered and the hashed password
    size_t hashed_password = hash_password(password);
    std::string hashed_pass = toString(hashed_password);

    int index = getIndex(usernames, username);
    
    if (hashed_pass == passwords[index] and balance == 0) { 
        // delete this data from vectors and from txt file
        usernames.erase(usernames.begin() + index);
        passwords.erase(passwords.begin() + index);
        balances.erase(balances.begin() + index);

        writeData(usernames, passwords, balances);
        std::cout << "Your account has been deleted." << std::endl;

    } else {
        myMenu(usernames, passwords, balances);  
    }  
}

int Deposit(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances,
            std::string username) {
    double amount = 0.0;
    std::cout << "Enter the amount you want to deposit: ";
    std::cin >> amount;

    int index = getIndex(usernames, username);

    if (amount < 0) {
        return -1;
    } else {
        roundToTwoDecimals(amount);
    }

    balances[index] += amount;
     
    writeData(usernames, passwords, balances);
    std::cout << "Deposit successful. " << endl;
    std::cout << "Your new balance is " << balances[index] << endl;
}

void Logout(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances) {
    //calls the myMenu() function
    myMenu(usernames, passwords, balances);
}

int Transfer(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances,
            std::string username) { 
                
    int senderIndex = getIndex(usernames, username);

    std::string recipient = "";
    std::cout << "Enter the recipient's username: ";
    std::cin >> recipient;

    // check if the recipient exists
    bool recipientFound = false;
    int recipientIndex = -1;
    for(int i = 0; i < usernames.size(); i++){
        if (usernames[i] == recipient) {
            recipientFound = true;
            recipientIndex = i;
            break;
        }
    }

    if (!recipientFound) {
        std::cout << "Recipient not found. " << std::endl;
        return -1;
    }

    double amount = 0.0;
    std::cout << "Enter the amount you want to transfer: ";
    std::cin >> amount;

    if (amount < 0) {
        std::cout << "Invalid amount." << std::endl;
        return -1;
    } else {
        roundToTwoDecimals(amount);
    }

    // check if user has enough funds
    if (balances[senderIndex] - amount < -10000) { // user can overdraft to 10000 BGN
        std::cout << "Insufficient funds. You can overdraft to 10000 BGN" << std::endl;
        return -1;
    }

    // transfer the money and update the sender and recipient's data
    if(balances[senderIndex] - amount >= -10000) {
        balances[senderIndex] -= amount;
        balances[recipientIndex] += amount;
    } else {
        return -1;
    }

    writeData(usernames, passwords, balances);
    std::cout << "Transfer successful." << std::endl;
    std::cout << "Your new balance is " << balances[senderIndex] << std::endl;
}

int Withdraw(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances,
                std::string username) {
    
    cout << "Enter the amount you want to withdraw: ";
    double amount = 0.0;
    std::cin >> amount;

    if (amount < 0) {
        std::cout << "Invalid amount." << std::endl;
        return -1;
    } else {
        roundToTwoDecimals(amount);    
    }

    int index = getIndex(usernames, username);
    if(balances[index] - amount >= -10000) { // user can overdraft to 10000 BGN
        balances[index] -= amount;
    } else {
        std::cout << "Withdrawal unsuccessful. You can overdraft to 10000 BGN" << std::endl;
        std::cout << "Your balance is " << balances[index] << endl;
        return -1;
    }

    writeData(usernames, passwords, balances);
    std::cout << "Withdrawal successful. " << std::endl;
    std::cout << "Your new balance is " << balances[index] << endl;
}

// if Login() or Register() are successfull we call nextStep()
int nextStep(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances, 
            double X, std::string username ) {

    char option;

    std::cout << "You have " << X << "BGN. Choose one of the following options: \n";
    std::cout << "  C - Cancel Account \n";
    std::cout << "  D - Deposit \n";
    std::cout << "  L - Logout \n";
    std::cout << "  T - Transfer \n";
    std::cout << "  W - Withdraw \n";

    std::cin >> option; 

    if(option == 'C') {
        cancelAccount(usernames, passwords, balances, username, X);
    } else if (option == 'D') {
        Deposit(usernames, passwords, balances, username);
    } else if (option == 'L') {
        Logout(usernames, passwords, balances);
    } else if (option == 'T') {
        Transfer(usernames, passwords, balances, username);
    } else if (option == 'W') {
        Withdraw(usernames, passwords, balances, username);
    } else {
        return -1;
    }
}

int Login(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances) {
    std::string username, password;
    double balance;
    bool login = false;

    std::cout << "Enter your username: ";
    std::cin >> username;

    // check if the entered username exists
    bool found = false;
    int index = 0;
    for(int i = 0; i < usernames.size(); i++){
        if (usernames[i] == username) {
            found = true;
            index = i;
            break;
        }
    }

    if (!found) {
        std::cout << "Username not found." << std::endl;
        return -1;
    }

    std::cout << "Enter your password: ";
    std::cin >> password;

    int hashed_password = hash_password(password);
    std::string hashed_pass = toString(hashed_password);

    if (hashed_pass == passwords[index]) {
        balance = balances[index];
        std::cout << "User is valid." << std::endl;
        login = true;

    } else {
        std::cout << "Incorrect password." << std::endl;
    }

    if(login) {
        nextStep(usernames, passwords, balances, balance, username);
    }
}

int Register(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances) {
    string username, password;
    std::cout << "Enter a new username: ";
    std::cin >> username;

    // Check if the entered username is valid
    bool validUsername = isValidUsername(username);

    if (!validUsername) {
        std::cout << "Invalid username." << std::endl;
        return -1;
    }

    // check if the entered username already exists
    bool found = false;
    for(int i = 0; i < usernames.size(); i++){
        if (usernames[i] == username) {
            found = true;
            break;
        }
    }

    if (found) {
        std::cout << "Username already exists." << std::endl;
        return -1;
    }

    std::cout << "Enter a new password: ";
    std::cin >> password;

    // Check if the entered password is valid
    bool validPassword = isValidPassword(password);

    if (!validPassword) {
        std::cout << "Invalid password." << std::endl;
        return -1;
    }

    // Hash the password and cast it to string type
    size_t hashed_password = hash_password(password);
    std::string hashed_pass = toString(hashed_password);

    double balance = 0.0;

    std::cout << "Registration successful." << std::endl;

    // Open the "users.txt" file and write the new user's data
    ofstream outfile("users.txt");
    outfile << username << ":" << hashed_pass << ":" << balance << endl;
    outfile.close();  

    //read data from file and store the new data in the vectors
    readData(usernames, passwords, balances);
    //call nextStep() function if Registration is successful
    nextStep(usernames, passwords, balances, balance, username);
}

int Quit(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances) {
    
    return 0; //end the program
}

int myMenu(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances) { 
    char option;

    std::cout << "Welcome to Bank Software \n";
    std::cout << "Please choose an option: \n";
    std::cout << "  L - Login \n";
    std::cout << "  R - Register \n";
    std::cout << "  Q - Quit \n";

    std::cin >> option; 

    if (option == 'L') {
        Login(usernames, passwords, balances);
    } else if (option == 'R') {
        Register(usernames, passwords, balances);
    } else if (option == 'Q') {
        Quit(usernames, passwords, balances);
    } else {
        return -1;
    }
}

int main() {
    std::vector<std::string> usernames;
    std::vector<std::string> passwords;
    std::vector<double> balances;
    readData(usernames, passwords, balances);

    myMenu(usernames, passwords, balances);
    
    return 0;
}
