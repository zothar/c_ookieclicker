//
// Created by remy on 16-07-20.
//

#ifndef C_OOKIECLIKER_COOKIEAMOUNTACHIEVEMENT_H
#define C_OOKIECLIKER_COOKIEAMOUNTACHIEVEMENT_H
#include "Achievement.h"
#include "CookieNumbers.h"
#include "Wallet.h"

class CookieAmountAchievement : public Achievement {
public:
    CookieAmountAchievement(const CookieNumber& amountRequired, std::string name);
    bool hasAchieved() override;
    std::string name() override;
    std::string description() override;
    void update(Subject *subject) override;

private:
    const CookieNumber& _amountRequired;
    std::string _name;
    bool _hasAchieved = false;
    cnp cp;
};


#endif //C_OOKIECLIKER_COOKIEAMOUNTACHIEVEMENT_H