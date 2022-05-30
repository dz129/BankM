#include <iostream>
#include <fstream>
#include <random>
#include <regex>
#include <string>

//might need to consider adding a pin feature but this is easily replaceable, need to add a password feature first

// The bank owner information will be accessible with a node structure
// the way to implement is to create a cypher through nodes when reading data, you dont need to store a whole tree for a single account
/* THIS IS THE NODE STRUCTURE
// The ** and **** denote the node that will be used and O denotes a node
        O  head node: Username, username will be the identifier for the line in the file **
        |  
        O  root node: Password, If the password for that line is the same one as the user enters, then access to the next nodes will be granted **
      / | \
    O   O  O  roots: The paths to information ****
    |   |   |
    O   O   O Based on a use input, the tree will span out
*/
// BIG NOTE FOR THE FILE, JUST STORE THE MAIN INFORMATION THAT DOESTN CHANGE, WE WILL CREATE A VECTOR THAT CONTAINS BALANCES AFTERWARD
// WE WILL HAVE A LINE COUNTER THAT WILL TELL US WHICH BALANCE TO PULL AND EDIT
//NOT MUCH CHANGE, JSUT THE IMPLEMENTATION OF THE VECTOR: MAKE THIS GLOBAL TOO
std::vector<double> balances; //global variable

struct root{
    // takes the account owner to the transactions as the "root node", although not technically a root node ****
    int data;
    struct root* pass1;
    struct root* pass2;
    struct root* pass3;
    // requires password for every access, the next passx node includes the password, after the password node, the data node is there
};
struct nodeI{
    int data;
    struct nodeI* next;
};
struct node{
    std::string datas;
    int datai;
    struct node* nextp;
    struct root* next;
};
void dataTrav(root* rootx, int balance, int ssn){
        std::cout<< "Would you like to see your balance, account number, or social security number?[B/AN/SSN]";
        std::string want, status;
        std::cin >> want;
        root* pub;
        root* priv;
        pub = rootx;
        priv = rootx;
        status = "y";
        while (status == "y"){
        if (want =="b"){
            priv -> pass1 = pub;
            pub -> data = balance;
            std::cout << pub->data;
            pub = priv;
            std::cout << "Are you done?[y/n]";
            std::cin >> status;
            }
        if (want =="ssn"){
            priv -> pass2 = pub;
            pub -> data = ssn;
            std::cout << pub->data;
            pub = priv;
            std::cout << "Are you done?[y/n]";
            std::cin >> status;
        }
        }
}
std::string raccnum(){
    //random account number
    //placed in new account
    std::string information, direct, accnumx;
    int accnum;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(10000,99999); // distribution in range [1, 6]
    accnum = dist6(rng);
    // check if account number already exists
    std::ifstream MAP;
    MAP.open("banking.txt");
        if ( MAP.is_open() ) {
        MAP >> information;
        std::cout << "rn";
        MAP.close();
        if (information.find(accnum) != std::string::npos) {
            // This recursion makes sure that there will always be a valid account number
            raccnum();
        }
    }
    std::stringstream ss;
    // needed this as a string for the array in newAccount() function
    ss << accnum;
    ss >> accnumx;
    return accnumx;    

}

std::string pwdx(){
    //placed in new acccount
    std::string pwd, pwd1;
    std::cout << "Create a pasword" << "\n";
    std::cin >> pwd;
    std::cout << "confirm your password" << "\n";
    std::cin >> pwd1;
    if (pwd != pwd1){
        std::cout << "Try again!\n";
        // recursion for password confirmation
        pwdx();
    }
    return pwd;
}

std::string pinx(){
    //placed in new account
    std::string pin, pin1;
    std::cout << "Create a pin using four numbers: " << "\n";
    std::cin >> pin;
    std::cout << "confirm your pin: " << "\n";
    std::cin >> pin1;
    if (pin != pin){
        std::cout << "Try again!\n";
        // recursion for password confirmation
        pinx();
    }
    return pin;
}







void transactions(){
    //hopefully this will be a central function for the transactions, there may be a need to have a deposit and withdraw function
    //MIGHT NEED TO CHANGE THIS FUNCTION TO WORK WITH NODES
    //password authenticfication is in different funciton (passwordAuth)
    //Lets use the pin to build transactions
    int count = 0;
    std::string accnum,DorW, upwd,pwd,balance,ssn,pin,pinu,done;
    int amount;
    std::cout<< "Account Number:";
    std::cin >> accnum;
    std::cout<< "What type of transaction would you like to make? Deposit or Withdraw?[D/W]";
    std::cin >> DorW;
    std::ifstream infile;
    infile.open("banking.txt");
    int indexcount = 0;
    if (infile.is_open()){
        std::string tp;
        // tp is the line that the account number is in
        while (getline(infile,tp)){
            indexcount += 1;
            if (tp.find(accnum) != std::string::npos){
                std::string arr1[7];
                int i = 0;
                std::stringstream ssin(tp);
                // the next while loop puts the string tp into a list, we can probably delete the count variable since it's not needed
                while(ssin.good() && i < 7){
                    ssin >> arr1[i];
                    i++;
                }
                //password from the line
                pwd = arr1[4];
                balance = arr1[5];
                ssn = arr1[2];
                pin = arr1[6];
            }
        }
    }
    infile.close();
    int Ibalance = balances[indexcount - 1];
    if (DorW == "w"){
        std::cout << "How much would you like to withdraw?";
        std::cin >> amount;
        Ibalance -= amount;
        std::cout<< "Your balance is now: "<< Ibalance;
    }
    else if (DorW == "d"){
        std::cout << "How much would you like to deposit?";
        std::cin >> amount;
        Ibalance += amount;
        std::cout<< "Your balance is now: "<< Ibalance;
    }
    std::stringstream ss;
    ss << Ibalance;
    std::string bal;
    ss >> bal;
    infile.open("banking.txt");
    if (infile.is_open()){
        std::string tp;
        // tp is the line that the account number is in
        while (getline(infile,tp)){
            if (tp.find(accnum) != std::string::npos){
                int i = 0;
                std::regex e;
                e = ("[0-9]* [0-9][0-9][0-9][0-9] ");
                std::string final;
                final = bal + " " + pin;
                tp = std::regex_replace(tp,e,final);
                std::cout << tp;
                std::stringstream ssin(tp);
}
        }
    }
}

void passwordAuth(std::string accnum){
    //password authentification
    //we will call the entire main menu here including transactions
    //assumes that the account number that was inputed is a valid one
    //This means that tp can stay as it is and we can try to convert tp into a string without authenticating the account number
    std::string upwd,pwd,balance,ssn,pin,pinu,done, TorI;
    int Ibalance;
    std::ifstream infile;
    infile.open("banking.txt");
    int lineCount = 0;
    if (infile.is_open()){
        std::string tp;
        // tp is the line that the account number is in
        while (getline(infile,tp)){
            lineCount += 1;
            if (tp.find(accnum) != std::string::npos){
                std::string arr[7];
                int i = 0;
                std::stringstream ssin(tp);
                // the next while loop puts the string tp into a list, we can probably delete the count variable since it's not needed
                while(ssin.good() && i < 7){
                    ssin >> arr[i];
                    i++;
                }
                //password from the line
                pwd = arr[4];
                balance = arr[5];
                ssn = arr[2];
                pin = arr[6];
            }
        }
    }

    std::cout << "Enter your password:";
    std::cin >> upwd;
    int iaccnum = std::stoi(accnum);
    node* username = new node;
    username -> datai = iaccnum;
    node* password = new node;
    username -> nextp = password;
    password -> datas = pwd;
    if ((password -> datas) != upwd){
        // we'll make a recursive function to take a password in, for now just type the right one
        std::cout << "wrong password:";
    }
    else{
        std::cout << "Would you like to make a transaction or just see information?[t/i]";
        std::cin >> TorI;
        if (TorI == "t"){
            transactions();
        }
        else{
        Ibalance = balances[lineCount -1];
        int Issn = std::stoi(ssn);
        root* tree = new root;
        password -> next = tree;
        dataTrav(tree,Ibalance,Issn);
        }
    }
    //maybe we can do a pin entry for every information entered
    // lets make a more interactive traversal by using the public and private node pointers

}


void checkIdentity(std::string num){
    // Makes sure that there is not a user already with the same SSN number
    //placed in new account
    std::string information, direct, accnum;
    std::ifstream infile;
    infile.open("banking.txt");
    if ( infile.is_open() ) {
        infile >> information;
        std::cout << "CI";
        infile.close();
        if (information.find(num) != std::string::npos) {
            std::cout << "You already have an account!\nWould you like to log in? [Y/N]";
            std:: cin >> direct;
                if (direct == "y"){
                std::cout << "What is your account number?";
                std::cin >> accnum;
                passwordAuth(accnum);
                }
                else if (direct =="n"){
                std::cout << "Have a great day!";
            }
        }
    }
    
}
void newAccount (){
    // information collection
    std::string balance = "0";
    std::string info[6];
    std::string fname, lname, ssn, information, direct, pwd, pwd1, accnum, pin;
    std::cout << "What is your first name?";
    std::cin >> fname;
    info[0] = fname;
    std::cout << "What is your last name?";
    std::cin >> lname;
    info[1] = lname;
    std::cout << "Enter your social security number";
    std::cin >> ssn;
    while (ssn.size() != 9){
        std::cout<< "Wrong amount of digits, retry: ";
        std::cin >> ssn;
    }
    info[2] = ssn;
    // read file to see if ssn is in the system
    checkIdentity(ssn);
    std::cout << "Ok lets get started!\n";
    accnum = raccnum();
    info[3] = accnum;
    std::cout<< "Your account number is: " << accnum << "\n";
    pwd = pwdx();
    pin = pinx();
    info[4] = pwd;
    info[5] = balance;

    int Ibalance = 0;
    balances.push_back(Ibalance);
    info[6] = pin;
    //final information display
    std::cout << "Here is the information being submitted:" << fname << "," << lname << "," << ssn << "," << accnum << "," << pwd << "," << pin;
    // file section
    std::ofstream outfile;
    outfile.open("banking.txt", std::ios_base::app);
    if (outfile.is_open()){
        std::cout << "open";
        for (int i = 0; i<7;i++){
        outfile << info[i] << " ";
        }
        outfile <<"\n";
        std::cout << "done";
   
    }
}
void directNewAccount() {
    // Put this in the main function as an access to the newAccount() function
    std::string direct, login, accnum;
    std:: cout << "Would you like to create a new account?[Y/N]";
    std:: cin >> direct;
    if (direct == "y"){
        newAccount();
        std::cout << "You have created a new account";
    }
    else if (direct =="n"){
        std::cout << "Would you like to log in?";
        std::cin >> login;
        if (login == "n"){
            std::cout << "Thank you and have a great day";
        }
        else{
            std::cout << "What is your account number?";
            std::cin >> accnum;
            passwordAuth(accnum);
        }
    }
}
    int main(){
        std::string rc, yon, accnum;
        std::cout << "Hello, welcome to C++banking.com!" << "\n";
        std::cout << "Are you a returning customer? :";
        std::cin >> rc;
        if (rc == "n"){
            directNewAccount();
        }
        else{
            std::cout << "What is your account number?";
            std::cin >> accnum;
            passwordAuth(accnum);
        }
        return 0;
        }




