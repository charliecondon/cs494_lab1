// Charlie Condon
// CS 494
// Lab 1
// This program will generate a jgraph of your personal finance comapred to 'ideal' personal finance.
// 'Ideal' in this case is based off of recomended set percentages and doesn't change based on income. 

#include <fstream>
#include <iostream>

using namespace std;

class finance {
    public:
        finance() {};
        void setup_file();
        ofstream jg;
        int y_max;
        float income, housing, total_debt, debt;
        float food, insurance, transport, save_invest, other;
 
};

// Generates the strings to create the jgraph
// The graph will change based on the inputted information
void finance::setup_file() {
    char a[] = "newgraph\n";
    char b[] = "xaxis size 2 min 0.1 max 31.9 hash 4 mhash 0 shash 0 no_auto_hash_labels\n ";
    char c[] = "hash_label at 4 : Housing\n hash_label at 8 : Transport\n ";
    char d[] = "hash_label at 12 : Food\n hash_label at 16 : Savings/Investments\n ";
    char e[] = "hash_label at 20 : Insurance\n hash_label at 24 : Debt Payment\n ";
    char f[] = "hash_label at 28 : Other\n label : Spending Categories\n ";
    char g[] = "hash_labels fontsize 8 hjl vjc rotate -60\n\n";

    char h[64];
    sprintf(h, "yaxis min 0 max %d size 2\n ", y_max);
    char i[] = "label : USD (thousands)\n grid_lines grid_gray .7\n\n";

    char j[] = "newline pts 0.1 0 31.9 0\nlegend top\n\nnewcurve marktype xbar cfill 0 1 1\n ";

    char k[] = "marksize 1 1\n label : Your Spending\n pts\n  ";

    char l[512];
    sprintf(l, "3.5 %f\n  7.5 %f\n  11.5 %f\n  15.5 %f\n  19.5 %f\n  23.5 %f\n  27.5 %f\n\n",
            housing / 1000, transport / 1000, food / 1000, save_invest / 1000, insurance / 1000, debt / 1000, other / 1000);
    char m[] = "newcurve marktype xbar cfill 1 0 0\n marksize 1 1\n label : Ideal Spending\n pts\n  ";

    // Calculate ideals based on researched percentages
    // With more time I would make these dynamic based on income
    float ideal_housing = income * 0.4 / 12000;
    float ideal_transport = income * 0.16 / 12000;
    float ideal_food = income * 0.1 / 12000;
    float ideal_insurance = income * 0.08 / 12000;
    float ideal_other = income * 0.11 / 12000;
    float ideal_debt = 0;
    float ideal_save_invest = income * 0.15 / 12000;
    if (total_debt > 0) {
        ideal_debt = income * 0.1 / 12000;
        ideal_save_invest = income * 0.05 / 12000;
    }

    char n[512];
    sprintf(n, "4.5 %f\n  8.5 %f\n  12.5 %f\n  16.5 %f\n  20.5 %f\n  24.5 %f\n  28.5 %f\n\n",
            ideal_housing, ideal_transport, ideal_food, ideal_save_invest, ideal_insurance, ideal_debt, ideal_other);

    char o[] = "newgraph\n x_translate 2\n xaxis min 0 max 10 nodraw\n yaxis min 0 max 10 nodraw\n\n";

    // Calculates the difference between inputted and ideal values
    int monthly_income = income / 12;
    int housing_difference = housing - ideal_housing * 1000;
    int transport_difference = transport - ideal_transport * 1000;
    int food_difference = food - ideal_food * 1000;
    int saving_inv_difference = save_invest - ideal_save_invest * 1000;
    int insurance_difference = insurance - ideal_insurance * 1000;
    int debt_difference = debt - ideal_debt * 1000;
    int other_difference = other - ideal_other * 1000;

    char p[128];
    sprintf(p, "newstring hjl vjc x 1 y 7 : Total Monthly Income: %d\nnewstring hjl vjc x 1 y 6 : Housing Differnce: %d\n", monthly_income, housing_difference);

    char q[128];
    sprintf(q, "newstring hjl vjc x 1 y 5 : Transport Differnce: %d\nnewstring hjl vjc x 1 y 4 : Food Differnce: %d\n", transport_difference, food_difference);

    char r[128];
    sprintf(r, "newstring hjl vjc x 1 y 3 : Saving/Investment Differnce: %d\nnewstring hjl vjc x 1 y 2 : Insurance Differnce: %d\n", saving_inv_difference, insurance_difference);

    char s[128];
    sprintf(s, "newstring hjl vjc x 1 y 1 : Debt Differnce: %d\nnewstring hjl vjc x 1 y 0 : Other Differnce: %d\n", debt_difference, other_difference);

    // Write everything to tmp.txt
    jg << a << b << c << d << e << f << g << h << i << j << k << l << m << n << o << p << q << r << s;
}

int main(int argc, char **argv) {

    finance *f = new finance();

    if (argc != 10) {
        cerr << "Usage (ALL INTEGERS): ./finance [post-tax income] [monthly house/rent payment] [total debt] [monthy debt payment] [monthly food] [monthly insurance] [monthy transport] [monthly savings/invesments] [other monthly payments]\n";
        return 1;
    }

    f->income = atoi(argv[1]);
    f->housing = atoi(argv[2]);
    f->total_debt = atoi(argv[3]);
    f->debt = atoi(argv[4]);
    f->food = atoi(argv[5]);
    f->insurance = atoi(argv[6]);
    f->transport = atoi(argv[7]);
    f->save_invest = atoi(argv[8]);
    f->other = atoi(argv[9]);
    
    if (f->income < 15000) {
        cerr << "Income too low for analysis to make sense\n";
        return 1;
    }

    if (f->income > 400000) {
        cerr << "Income too high for analysis to make sense (congrats btw)\n";
        return 1;
    }

    // Set the y_max based on largest possible monthly payment 
    f->y_max = (f->income / 12000) + 1;

    f->jg.open("tmp.txt");
    f->setup_file();
    f->jg.close();

    return 0;
}
