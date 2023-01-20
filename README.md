# Bank-Software

## Description
This is a program that simulates a basic set of activities in a given bank.

When starting the program, user profiles are loaded from the "users.txt" file, which are stored in the following format:

                username:hashed_password:balance
                
## Functionalities

### is username and password valid
int containsUppercase(std::string str);

int containsDowncase(std::string str);

int containsSymbol(std::string str);

int containsDigit(std::string str);

bool length(std::string str);

bool isValidPassword(std::string password);

bool isValidUsername(std::string username);

### My Menu

int myMenu(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances);

int Login(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances) ;

int Register(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances) 

int Quit(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances);
 
### Menu 2 if Register()/Login() is successful 
int nextStep(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances, 
            double X, std::string username ); // if Login() or Register() are successfull we call nextStep()

 void cancelAccount(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances,
                    std::string username, double balance);

int Deposit(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances,
            std::string username) ;

void Logout(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances);

int Transfer(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances,
            std::string username) 

int Withdraw(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances,
                std::string username) {

## Write and Read data to/from file
  
void readData(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances) // read data from file and store in different vectors

void writeData(std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances); // write data to "users.txt" file
  
## Hash password
  
size_t hash_password(const std::string password); to hash a string into size_t variable
  
std::string toString(size_t hashed_password); // cast the hashed password from size_t to std::string
  
## Round number to two decimals

void roundToTwoDecimals(double &amount);
  
## get index position
  
int getIndex(std::vector<std::string> usernames, std::string username); // gets index position
