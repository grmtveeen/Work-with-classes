//Matveev Igor

#include <iostream>
using namespace std;

template <typename T>
class data {
    private:
T day;
T month;
T year;
bool leapYear(T y) const;   //Checking for leap years
int dpm [11];
T daysplus() const;         //Converting the date into the number of days. Returns the number of days.
void dataplus(T num);       //Converting the number of days "num" to a date. Assigning a new date to the date variable for which the method was called.
    public:
data ();
data (T d, T m, T y);
data (const data<T> &src);
~data ();

T days() const;             //Returns the number of days that have passed since January 1 of a given year

void input_day(T d);        //Enter only day
void input_month(T m);      //Enter only month
void input_year(T y);       //Enter only month

void add (T d, T m, T y);   //Enter dd / mm / yyyy immediately

T output_day()const;        //Out only a day
T output_month()const;      //Out only a month
T output_year()const;       //Out only a year

data<T> &operator= (const data<T> &src);        //Appropriation
data<T> &operator+= (const data<T> &src);       //Append date "src" to current
data<T> operator+ (const data<T> &src) const;   //Add dates
data<T> &operator+= (T d);                      //Add date and number of days
data<T> operator+ (T d) const;                  //Add the number of days "d" to the current date
bool operator== (const data<T> &src) const;     //Date comparison
bool operator!= (const data<T> &src) const;     //Date comparison
template <typename X>
friend ostream &operator<< (ostream &os, const data<X> &src);   //Out date
};

template <typename T>
bool data<T>::leapYear (T y) const {
    if((y%4==0)&&(y%100==0)&&(y%400==0)&&(y!=0)) return true;
    if((y%4==0)&&(y%100==0)&&(y!=0)) return false;
    if((y%4==0)&&(y!=0)) return true;
    return false;
}

template <typename T>
void data<T>:: dataplus(T num){
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

template <typename T>
void data<T>::add(T d, T m, T y){
    day = d;
    month = m;
    year = y;
    if(leapYear(this->year)) dpm[1]=29;
}

template <typename T>
data<T>::data (){
    day=1;
    month=1;
    year=2000;
    dpm[0]=31,dpm[1]=28,dpm[2]=31,dpm[3]=30,dpm[4]=31,dpm[5]=30,dpm[6]=31,dpm[7]=31,dpm[8]=30,dpm[9]=31,dpm[10]=30,dpm[11]=31;
    if(leapYear(this->year)) dpm[1]=29;
}

template <typename T>
T data<T>::days() const{
    int RES=0, k;
    for (k =0; k < (month-1); k++){
        RES+=dpm[k];
    }
    return RES+=day;
}

template <typename T>
T data<T>::daysplus () const{
    int num=0, y=0;
    while (y<year){
        num+=365;
        if (leapYear(y)) num++;
        y++;
    }
    return num+=(*this).days();
}

template <typename T>
data<T>::data (T d, T m, T y){
    day = d;
    month = m;
    year = y;
    dpm[0]=31,dpm[1]=28,dpm[2]=31,dpm[3]=30,dpm[4]=31,dpm[5]=30,dpm[6]=31,dpm[7]=31,dpm[8]=30,dpm[9]=31,dpm[10]=30,dpm[11]=31;
    if(leapYear(this->year)) dpm[1]=29;
};

template <typename T>
data<T>::data (const data &src){
    day = src.day;
    month = src.month;
    year = src.year;
    dpm[0]=31,dpm[1]=28,dpm[2]=31,dpm[3]=30,dpm[4]=31,dpm[5]=30,dpm[6]=31,dpm[7]=31,dpm[8]=30,dpm[9]=31,dpm[10]=30,dpm[11]=31;
    if(leapYear(this->year)) dpm[1]=29;
}

template <typename T>
data<T>:: ~data (){
}

template <typename T>
void data<T>:: input_day(T d) {
    day = d;
}

template <typename T>
void data<T>:: input_month(T m){
    month = m;
}

template <typename T>
void data<T>:: input_year(T y){
    year = y;
    if(leapYear(this->year)) dpm[1]=29;
}

template <typename T>
T data<T>:: output_day()const{
    return day;
}

template <typename T>
T data<T>:: output_month()const{
    return month;
}

template <typename T>
T data<T>:: output_year()const {
    return year;
}

template <typename T>
data<T> &data<T>::operator=(const data<T> &src){
    if(&src==this) return *this;
    year=src.year;
    month=src.month;
    day=src.day;
    return *this;
}

template <typename T>
data<T> &data<T>::operator+= (const data<T> &src){
    T DAYS = daysplus() + src.daysplus();
    dataplus(DAYS);
    return *this;
}

template <typename T>
data<T> data<T>::operator+ (const data<T> &src) const {
    data RES(*this);
    RES+=src;
    return RES;
}

template <typename T>
data<T> &data<T>::operator+= (T d){
    int DAYS = daysplus() + d;
    dataplus(DAYS);
    return *this;
}

template <typename T>
data<T> data<T>::operator+ (T d) const {
    data RES(*this);
    RES+=d;
    return RES;
}

template <typename T>
bool data<T> :: operator== (const data<T> &src) const {
    bool RES;
    if((year==src.year)&&(month==src.month)&&(day==src.day)) RES = true;
    else RES = false;
    return RES;
}

template <typename T>
bool data<T> :: operator!= (const data<T> &src) const{
    return !((*this)==src);
}

template <typename X>
ostream &operator<< (ostream &os, const data<X> &src){
    os<< src.day << "." << src.month << "." << src.year;
    return os;
}

int main (void){
    data<int> A(24,2,2002), B(1,1,0), C(20,3,2020), D(7,11,1918), F, G, P(31,12,0000), E; //The ability to enter a date using the constructor when declaring (by default, the date is set (01/01/2000))
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
    if(F==G) cout << "If you're reading this, then A == B, the method works." << endl;    // Overloaded operator ==

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
