#include <iostream>
#include <string>

int main() {
    //Initalizing variables
    double basisAmount;
    double pAmount;
    std::string institution;
    std::string institutionType;
    
    //Setting decimal point to 1
    std::cout.setf(std::ios::fixed);
    std::cout.precision(1);
    
    //Prompting Insitution
    do {
        std::cout << "Enter your instituion: ";
        getline(std::cin, institution);
        if (institution == "")
            std::cerr << "You must enter an institution." << std::endl;
    } while (institution == "");

    //Prompting Basis Amount
    do {
        std::cout << "Enter the basis amount (in trillions): ";
        std::cin >> basisAmount;
        std::cin.ignore(10000, '\n');
        if (basisAmount < 0)
            std::cerr << "The basis amount must be positive." << std::endl;
    } while (basisAmount < 0);
    
    //Prompting Institution Type
    do {
        std::cout << "Enter your instituion type: ";
        getline(std::cin, institutionType);
        if (institutionType == "")
            std::cerr << "You must enter an institution type." << std::endl;
    } while (institutionType == "");

    //pAmount Calculations
    if (basisAmount <= 160)
        pAmount = basisAmount * 0.07;
    if (basisAmount > 160) {
        pAmount = 160 * 0.07;
        double additionalSettlementAmount = 0.09;
        if (institutionType == "media" || institutionType == "university")
            additionalSettlementAmount = 0.17;
        pAmount = pAmount + ((basisAmount - 160) * additionalSettlementAmount);
        if (basisAmount > 760) {
            pAmount = pAmount + ((basisAmount - 760) * 0.11);
            std::cout << pAmount << std::endl;
        }
    }    

    std::cout << "---" << std::endl;
    std::cout << "The settlement amount for institution is P" << pAmount << " trillion.";
}