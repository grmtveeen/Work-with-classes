//Matveev Igor

#include <iostream>
using namespace std;
#define SPD 86400 //Seconds per day

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

date &operator=(const date &src);           //Assignment
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
    while (num>=365){
        num-=365;
        if (leapYear(y++)) num--;
    }
    if (leapYear(y)) dpm [1]=29;
    while(num>=dpm[m]){
        num-=(dpm[m++]);
    }
    if (num<0) month=1, day=1, year=y;
    else{
        year=y;
        month=(++m);
        day=(++num);
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
    return RES+=(day-1);
}

int date::daysplus () const{
    int num=0, y=0;
    while (y<year){
        num+=365;
        if (leapYear(y++)) num++;
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

date &date::operator=(const date &src){
    if(&src==this) return *this;
    year=src.year;
    month=src.month;
    day=src.day;
    return *this;
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




class date_time{
private:
    date w;
    int *hour, *minute, *second;
    int secondsDay() const;     //Returns the number of seconds elapsed since 00:00:00 of the given day
    void SecondPlus(int sec);   //Translate the number of seconds into the time elapsed from 00:00:00 on a given day
public:
    date_time();
    date_time(int D, int M, int Y, int h, int m, int s);
    date_time(const date_time &src);
    ~date_time();

    date_time &operator= (const date_time &src);    //Assignment


    int seconds() const;       //Returns the number of seconds that have passed since January 1 of a given year

    void input_day(int D);      //Enter only day
    void input_month(int M);    //Enter only month
    void input_year(int Y);     //Enter only year
    void input_hour(int h);     //Enter only hour
    void input_minute(int m);   //Enter only minute
    void input_second(int s);   //Enter only second

    int output_day()const;      //Out only a day
    int output_month()const;    //Out only a month
    int output_year()const;     //Out only a year
    int output_hour()const;     //Out only a hour
    int output_minute()const;   //Out only a minute
    int output_second()const;   //Out only a second

    date_time &operator+= (const date_time &src);       //Append date and time "src" to current
    date_time operator+ (const date_time &src) const;   //Add dates ans times
    date_time &operator+= (int src);                    //Add seconds "src" to the current date
    date_time operator+ (int src) const;                //Add date and time with seconds
    bool operator== (const date_time &src) const;       //Date and time comparison
    bool operator!= (const date_time &src) const;       //Date and time comparison
    friend ostream &operator<< (ostream &os, const date_time &src); //Out date and time
};

int date_time::secondsDay() const{
    return 3600*(*hour)+60*(*minute) + (*second);
}

void date_time:: SecondPlus(int sec){
    int h=0, m=0;
    if (sec>=SPD) w+=1, sec-=SPD;
    while (sec>=3600) h++, sec-=3600;
    while (sec>=60) m++, sec-=60;
    *hour = h;
    *minute = m;
    *second =sec;
}

date_time::date_time(): w(1,1,0),
    hour (new int(0)),
    minute (new int(0)),
    second (new int(0)){
}

date_time::date_time(int D, int M, int Y, int h, int m, int s):
    w(D,M,Y),
    hour (new int(h)),
    minute (new int(m)),
    second (new int(s)){
}

date_time::date_time(const date_time &src): w(src.w),
    hour (new int(*src.hour)),
    minute (new int(*src.minute)),
    second (new int(*src.second)){
}

date_time::~date_time(){
    delete hour;
    delete minute;
    delete second;
}

date_time &date_time::operator= (const date_time &src){
    if (&src==this) return *this;
    w=src.w;
    *hour=*src.hour;
    *minute=*src.minute;
    *second=*src.second;
    return *this;
}

int date_time:: seconds()const{
    return w.days()*SPD + 3600*(*hour)+60*(*minute) + (*second);
}

void date_time::input_day(int D){
        w.input_day(D);
}

void date_time::input_month(int M){
        w.input_month(M);
}

void date_time::input_year(int Y){
        w.input_year(Y);
}

void date_time::input_hour(int h){
        *hour=h;
}

void date_time::input_minute(int m){
        *minute=m;
}

void date_time::input_second(int s){
        *second=s;
}

int date_time::output_day()const{
    return w.output_day();
}

int date_time::output_month()const{
    return w.output_month();
}

int date_time::output_year()const{
    return w.output_year();
}

int date_time::output_hour()const{
    return *hour;
}

int date_time::output_minute()const{
    return *minute;
}

int date_time::output_second()const{
    return *second;
}

date_time &date_time::operator+= (const date_time &src){
    w+=(src.w);
    SecondPlus(secondsDay()+src.secondsDay());
    return *this;
}

date_time date_time::operator+ (const date_time &src) const{
    date_time RES(*this);
    RES+=src;
    return RES;
}

date_time &date_time::operator+= (int src){
    w+=(src/SPD);
    SecondPlus(secondsDay()+src-(src/SPD)*SPD);
    return *this;
}

date_time date_time::operator+ (int src) const{
    date_time RES(*this);
    RES+=src;
    return RES;
}

bool date_time::operator== (const date_time &src) const{
    if ((w==src.w)&&((*hour)==(*src.hour))&&((*minute)==(*src.minute))&&((*second)==(*src.second))) return true;
    return false;
}

bool date_time::operator!= (const date_time &src) const{
    return !((*this)==src);
}

ostream &operator<< (ostream &os, const date_time &src){
    os<< src.w <<"    "<< *src.hour <<":"<< *src.minute <<":"<< *src.second;
    return os;
}

int main (void){
   date_time A(31,12,2020,23,59,59), B(1,4,1895,15,4,12), C(31,12,1999,23,59,59), D(B), H(C), K, E(31,12,2020,23,59,59), F(31,1,2020,23,59,59); //The ability to enter a date and time using the constructor when declaring (by default, the date is set (0/0/0/01/01/2000))
    cout << K << endl;      //Output operator
    cout << "It's check operator copy " << H << endl;

    K=A;                    //Check operator equals
    cout<<"operator= " <<K << '\n' << endl;

    int sec = C.seconds(); //Check method seconds
    cout << "Since January 1 to " << C << " have been passed " <<sec << " seconds\n" << endl;

    K.input_day(3);
    K.input_month(2);
    K.input_year(2046);
    K.input_hour(21);
    K.input_minute(5);
    K.input_second(2);
    cout<<"It's check methods input_ <-> output_ second/minute/.../year "<<K.output_day()<<"."<<K.output_month()<<"."<<K.output_year()<<"    "<<K.output_hour()<<":"<<K.output_minute()<<":"<<K.output_second()<<'\n'<<endl;


    A+=B;           //Overloaded operator +=
    cout << "operator+= " <<A << endl;
    A=B+C;          //Overloaded operator +
    cout <<"operator+ " << A << '\n' << endl;

    C+=1;           //Overloaded operator +=
    cout <<"operator+ (int)  31.12.1999 23:59:59 + 1sec equally "<< C << endl; //
    C+=1000;        //Overloaded operator +=
    cout << "C+=1000 "<<C << endl;
    C+=100000;      //Overloaded operator +=
    cout<<"C+=100000 "<<C<< endl;
    K=C+10000000;   //Overloaded operator +
    cout<<"operator+  K=C+10000000 " << K << endl;
    K=C+1000003725; //Overloaded operator +
    cout<<"operator+  K=C+1000003725 " << K << '\n' << endl;


    E+=1;   //Check problematic case
    cout<<"E+=1 31.12.2020 23:59:59 + 1sec equally " << E << endl;
    F+=1;   //Check problematic case
    cout<<"F+=1 31.01.2020 23:59:59 + 1sec equally " << F << '\n' << endl;

    if (D==B) cout << "If you're reading this, then D == B, the method works." << endl;
    if (A!=C) cout << "If you're reading this, then A! = C, the method works.\n" << endl;

    A = B = C;  //Check operator equals
    cout<< "Check A = B = C :\n" << A << '\n' << B << '\n' << C << endl;
return 0;
}
