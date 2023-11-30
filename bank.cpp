#include <iostream>
#include <vector>
#include <string>

class Storage {
protected:
    std::string Manager_id = "bv18062002";
    std::string Manager_password = "18062002";
    int cross_verify = 18062002;

    std::vector<std::string> account_numbers = {"99", "98", "97"};
    std::vector<std::string> account_passwords = {"9", "8", "7"};
    std::vector<long long int> account_amounts = {10000, 800000, 102931};
    std::vector<std::string> account_code = {"1ks", "2ks", "3ks"};
};

class Manager : private Storage {
public:
    bool check_manager_id(const std::string &M_id) {
        return (M_id == Manager_id);
    }

    bool check_manager_password(const std::string &M_pass, int cr) {
        return (M_pass == Manager_password && cr == cross_verify);
    }

    void Display() {
        
        for (size_t i = 0; i < account_numbers.size(); i++) {
            std::cout << account_numbers[i] << "\n" << account_code[i] << "\n" << account_amounts[i] << "\n\n";
        }
    }

    void add_member() {
        static std::string b;
        static std::string pswrd;
        static long long int amt;
        static std::string accountcode;

        std::cout << "If you want to add a new member, enter the account number. Otherwise, enter NULL or 0: ";
        std::cin >> b;

        if (b != "0" || b != "NULL") {
            for (size_t i = 0; i < account_numbers.size(); i++) {
                if (account_numbers[i] == b) {
                    std::cout << "Account number already exists...!\n";
                    return;
                }
            }

            account_numbers.push_back(b);
            std::cout << "Enter a new password: ";
            std::cin >> pswrd;
            account_passwords.push_back(pswrd);
            std::cout << "Enter the initial amount for the new account: ";
            std::cin >> amt;
            account_amounts.push_back(amt);
            std::cout << "Enter a new account id: ";
            std::cin >> accountcode;
            account_code.push_back(accountcode);
        }
    }
};

class Check : private Storage {
public:
    long long int index;

    bool check_Account_password(long long int i) {
        std::string entered_password;
        std::cout << "Enter Password: ";
        std::cin >> entered_password;

        if (account_passwords[i] == entered_password) {
            index = i;
            return true;
        } else {
            std::cout << "Invalid Password\n";
            return false;
        }
    }

    bool check_Account_Number(const std::string &entered_account_number, int choice) {
        for (size_t i = 0; i < account_numbers.size(); i++) {
            if (account_numbers[i] == entered_account_number) {
                if (choice == 4) {
                    index = i;
                    return true;
                }

                return check_Account_password(i);
            }
        }

        std::cout << "Invalid Account Number\n";
        return false;
    }
};

class Check_Balance : private Storage {
public:
    Check_Balance(long long int i) {
        std::cout << "The remaining Amount:" << account_amounts[i] << std::endl;
    }
};

class Deposit : private Storage {
public:
    Deposit(long long int i, long long int entered_amount) {
        long long int new_amount = account_amounts[i] + entered_amount;
        account_amounts[i] = new_amount;
        std::cout << account_amounts[i] << std::endl;
        std::cout << "The Deposit is successful" << std::endl;
    }
};

class Withdrawal : private Storage {
public:
    Withdrawal(long long int i, long long int entered_amount) {
        if (account_amounts[i] - entered_amount > 5000) {
            long long int new_amount = account_amounts[i] - entered_amount;
            account_amounts[i] = new_amount;

            std::cout << "The Withdrawal is successful" << std::endl;
        } else {
            std::cout << "Insufficient Funds" << std::endl;
            return ;
        }
    }
};

class PasswordChange : private Storage {
public:
    PasswordChange(long long int i) {
        std::cout << "Enter the code:";
        std::string entered_code;
        std::cin >> entered_code;
        if (account_code[i] == entered_code) {
            std::string new_password;
            std::cout << "Enter the new password:";
            std::cin >> new_password;
            account_passwords[i] = new_password;

            std::cout << "The password change is successful" << std::endl;
        } else {
            std::cout << "Invalid Code" << std::endl;
        }
    }
};

int main() {
    int exitProgram = 3;
    do {
        int option, u;
        std::cout << "\n1.Customer\n2.Manager\n" << "Enter who you are: ";
        std::cin >> u;

        if (u == 1) {
            std::cout << "\n\n1.Deposit\n2.Withdraw\n3.Bank Balance\n4.Password Change\n5.Exit\n";
            std::cout << "\nEnter the option: ";
            std::cin >> option;

            if (option >= 1 && option <= 4) {
                std::string entered_account_number;
                std::cout << "\nEnter Account Number: ";
                std::cin >> entered_account_number;
                Check check;
                if (check.check_Account_Number(entered_account_number, option)) {
                    switch (option) {
                        case 1: {
                            long long int amount;
                            std::cout << "\nEnter the amount to be deposited: ";
                            std::cin >> amount;
                            Deposit deposit(check.index, amount);
                            break;
                        }
                        case 2: {
                            long long int amount;
                            std::cout << "\nEnter the amount to be withdrawn: ";
                            std::cin >> amount;
                            Withdrawal withdrawal(check.index, amount);
                            break;
                        }
                        case 3: {
                            Check_Balance balance(check.index);
                            break;
                        }
                        case 4: {
                            PasswordChange passwordChange(check.index);
                            break;
                        }
                    }
                }
            } else if (option == 5) {
                std::cout << "\nExiting the program...\n";
                exitProgram = 0;
            } else {
                std::cout << "\nInvalid option. Please try again.\n";
            }
        } else if (u == 2) {
            Manager manager;
            std::string password;
            std::string Manager_id;
            int cr;

            std::cout << "\nEnter Your Respective User id: ";
            std::cin >> Manager_id;

            if (manager.check_manager_id(Manager_id)) {
                std::cout << "\nEnter Your password: ";
                std::cin >> password;
                std::cout << "\nEnter your Cross Verify id: ";
                std::cin >> cr;

                if (manager.check_manager_password(password, cr)) {
                    exitProgram=0;
                    std::cout << "\nWelcome Manager:\n\n What Do you Want sir?\n"
                              << "1. Show all customer details\n"
                              << "2. Add a new member to our Bank\n"
                              << "3. Exit the program\n";

                    std::cin >> cr;

                    switch (cr) {
                        case 1:
                            manager.Display();
                            break;
                        case 2:
                            manager.add_member();
                            break;
                        case 3:
                            std::cout << "\nProgram has ended!\n";
                            exitProgram =0;
                            break;
                        default:
                            std::cout << "\n\nIncorrect option. Try again!\n";
                            
                    }
                }
            } else {
                std::cout << "\nIncorrect User ID.\n";
            }
        } else {
            std::cout << "\nIncorrect option. Please try again.\n";
        }

    } while (exitProgram-1);

    return 0;
}
