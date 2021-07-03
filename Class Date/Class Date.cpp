//Matveev Igor

#include <iostream>
using namespace std;

class date {
    private:
int day;
int month;
int year;
bool leapYear(int y) const; //Checking for leap years
int dpm [12]{31,28,31,30,31,30,31,31,30,31,30,31};
int daysplus() const;       //Converting the date into the number of days. Returns the number of days.
void dateplus(int num);     //Converting the number of days "num" to a date. Assigning a new date to the date variable for which the method was called.
    public:
date ();
date (int d, int m, int y);
date (const date &src);
~date ();

int days() const;               //Returns the number of days that have passed since January 1 of a given year

void input_day(int d);          //Enter only day
void input_month(int m);        //Enter only month
void input_year(int y);         //Enter only year

void add (int d, int m, int y); //Enter dd / mm / yyyy immediately

int output_day()const;          //Out only a day
int output_month()const;        //Out only a month
int output_year()const;         //Out only a year

date &operator+= (const date &src);         //Append date "src" to current
date operator+ (const date &src) const;     //Add dates
date &operator+= (int d);                   //Add date and number of days
date operator+ (int d) const;               //Add the number of days "d" to the current date
bool operator== (const date &src) const;    //Date comparison
bool operator!= (const date &src) const;    //Date comparison
friend ostream &operator<< (ostream &os, const date &src);  //Out date
};

bool date::leapYear (int y) const {
    if((y%4==0)&&(y%100==0)&&(y%400==0)&&(y!=0)) return true;
    if((y%4==0)&&(y%100==0)&&(y!=0)) return false;
    if((y%4==0)&&(y!=0)) return true;
    return false;
}

void date:: dateplus(int num){
    int y=0, m=0;
    while (num>365){
        num-=365;
        if (leapYear(y++)) num--;
    }
    if (leapYear(y)) dpm [1]=29;
    while(num>dpm[m]){
        num-=dpm[m++];
    }
    if (num==0) month=12, day=31, year=(y-1);
    else{
        year=y;
        month=(++m);
        day=num;
    }
}

void date::add(int d = 1, int m = 1, int y = 2000){
    day = d;
    month = m;
    year = y;
    if(leapYear(this->year)) dpm[1]=29;
}

date::date (){
    day=1;
    month=1;
    year=2000;
    if(leapYear(this->year)) dpm[1]=29;
}

int date::days() const{
    int RES=0;
    for (int k =0; k < (month-1); k++){
        RES+=dpm[k];
    }
    return RES+=day;
}

int date::daysplus () const{
    int num=0, y=0;
    while (y<year){
        num+=365;
        if (leapYear(y)) num++;
        y++;
    }
    return num+=(*this).days();
}

date::date (int d, int m, int y){
    day = d;
    month = m;
    year = y;
    if(leapYear(this->year)) dpm[1]=29;
};

date::date (const date &src){
    day = src.day;
    month = src.month;
    year = src.year;
    if(leapYear(this->year)) dpm[1]=29;
}

date:: ~date (){
}

void date:: input_day(int d) {
    day = d;
}

void date:: input_month(int m){
    month = m;
}

void date:: input_year(int y){
    year = y;
    if(leapYear(this->year)) dpm[1]=29;
}

int date:: output_day()const{
    return day;
}

int date:: output_month()const{
    return month;
}

int date:: output_year()const {
    return year;
}

date &date::operator+= (const date &src){
    int DAYS = daysplus() + src.daysplus();
    dateplus(DAYS);
    return *this;
}

date date::operator+ (const date &src) const {
    date RES(*this);
    RES+=src;
    return RES;
}

date &date::operator+= (int d){
    int DAYS = daysplus() + d;
    dateplus(DAYS);
    return *this;
}

date date::operator+ (int d) const {
    date RES(*this);
    RES+=d;
    return RES;
}

bool date :: operator== (const date &src) const {
    bool RES;
    if((year==src.year)&&(month==src.month)&&(day==src.day)) RES = true;
    else RES = false;
    return RES;
}

bool date :: operator!= (const date &src) const{
    return !((*this)==src);
}

ostream &operator<< (ostream &os, const date &src){
    os<< src.day << "." << src.month << "." << src.year;
    return os;
}

int main (void){
    date A(24,2,2002), B(1,1,0), C(20,3,2020), D(7,11,1918),E, F, G, P(31,12,0000);     //The ability to enter a date using the constructor when declaring (by default, the date is set (01/01/2000))
    cout << "Default date: " << E << endl;  //Output operator
    E=B+C;      //Overloaded operator +
    cout << "Operator +                                                  B+C= " << E << endl;  // Overloaded operator <<
    B+=C;       //Overloaded operator +=
    cout << "Operator +=  (B+=C)                                           B= " << B << endl;
    A+=1000;    //Overloaded operator +=
    cout << "Operator += (A+=(number of days)) February 24, 2002 + 1000 days: " << A <<endl;
    A=C+1000;   //Overloaded operator +
    cout << "Operator +  (A=C+(number of days))   March 20, 2020 + 1000 days: " << A <<endl;
    if(A!=B) cout << "If you're reading this, then A! = B, the method works." << endl;   // Overloaded operator !=
    if(F==G) cout << "If you're reading this, then A = B, the method works." << endl;    // Overloaded operator ==

    A.input_day(15);    //The ability to change only the day
    A.input_month(5);   //The ability to change only the month
    A.input_year(2020); //The ability to change only the year
    cout<< "Output dd/mm/yyyy separately: " << A.output_day() << "." << A.output_month()<< "." << A.output_year() << endl; // The ability to display the day, month, year separately

    int DAYS;
    DAYS = A.days();    //A method that allows you to get the number of days that have passed since January 01 of a given year (05/15/1920)
    cout << "From January 01, 1920 to 05/15/1920 passed: " << DAYS << " days." << endl;

    F.add(16,10,2020);  //The ability to enter the entire date at once dd/mm/yyyy
    cout<< "The ability to enter the entire date dd/mm/yyyy at once:" << F << endl;


return 0;
}
