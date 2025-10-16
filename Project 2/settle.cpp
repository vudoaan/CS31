#include <iostream>
#include <string>

int main() {
    //Initalizing variables
    double basisAmount = 0;
    double pAmount = 0;
    std::string institution;
    std::string institutionType;
    std::string errorMessage;
    
    //Setting decimal point to 1
    std::cout.setf(std::ios::fixed);
    std::cout.precision(1);
    
    //Prompting Insitution
    std::cout << "Institution: ";
    getline(std::cin, institution);
    //Checking if institution is an empty string
    if (institution == "") {
        errorMessage = "You must enter an institution.";
    } else {
        //Prompting Basis Amount
        std::cout << "Basis amount (in trillions): ";
        std::cin >> basisAmount;
        std::cin.ignore(100000, '\n');
        //Cecking if basis amount is negative
        if (basisAmount <= 0) {
            errorMessage = "The basis amount must be positive.";
        } else {
            //Prompting Institution Type
            std::cout << "Institution type: ";
            getline(std::cin, institutionType);
            //Checking if institution type is an empty string
            if (institutionType == "")
                errorMessage = "You must enter an institution type.";       
        }
    }

    //Calculate total settlement based on basis amount tiers
    if (basisAmount <= 160) {
        pAmount = basisAmount * 0.07;
    } else {
        pAmount = 160 * 0.07;
        double additionalSettlementAmount = 0.09;
        if (institutionType == "media" || institutionType == "university")
            additionalSettlementAmount = 0.17;
        if (basisAmount <= 760)
            pAmount = pAmount + ((basisAmount - 160) * additionalSettlementAmount);
        else {
            pAmount = pAmount + (600 * additionalSettlementAmount);
            pAmount = pAmount + ((basisAmount - 760) * 0.11);
        }
    }
    
    //Outputs 
    std::cout << "---" << std::endl;
    if (errorMessage == "") 
        std::cout << "The settlement amount for " << institution << " is P" << pAmount << " trillion." << std::endl;
    else
        std::cout << errorMessage << std::endl;

}