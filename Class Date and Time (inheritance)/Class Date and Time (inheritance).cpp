//Matveev Igor

using namespace std;
#include <iostream>
#define SPD 86400   //Seconds per day

class date {
private:
    int day;
    int month;
    int year;
    bool leapYear(int y) const; //Checking for leap years
    int dpm [12]{31,28,31,30,31,30,31,31,30,31,30,31};
    int daysplus() const;       //Converting the date into the number of days. Returns the number of days.
    void dataplus(int num);     //Converting the number of days "num" to a date. Assigning a new date to the date variable for which the method was called.
public:
    date ();
    date (int d, int m, int y);
    date (const date &src);
    virtual ~date ();

    int days() const;               //Returns the number of days that have passed since January 1 of a given year

    void InDay(int d);              //Enter only day
    void InMonth(int m);            //Enter only month
    void InYear(int y);             //Enter only year

    void add (int d, int m, int y); //Enter dd / mm / yyyy immediately

    int OutDay()const;              //Out only a day
    int OutMonth()const;            //Out only a month
    int OutYear()const;             //Out only a year

    virtual void print() const;

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

int date::daysplus () const{
    int num=0, y=0;
    while (y<year){
        num+=365;
        if (leapYear(y++)) num++;
    }
    return num+=(*this).days();
}

void date:: dataplus(int num){
    int y=0, m=0;
    while (num>=365){
        num-=365;
        if (leapYear(y++)) num--;
    }
    if (leapYear(y)) dpm [1]=29;
    while(num>=dpm[m]){
        num-=(dpm[m++]);
    }
    if (num<0) month=12, day=31, year=--y;
    else{
        year=y;
        month=(++m);
        day=(++num);
    }
}

date::date (){
    day=1;
    month=1;
    year=2000;
    if(leapYear(this->year)) dpm[1]=29;
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

int date::days() const{
    int RES=0, k;
    for (k =0; k < (month-1); k++){
        RES+=dpm[k];
    }
    return RES+=(day-1);
}

void date:: InDay(int d) {
    day = d;
}

void date:: InMonth(int m){
    month = m;
}

void date:: InYear(int y){
    year = y;
    if(leapYear(this->year)) dpm[1]=29;
}

void date::add(int d = 1, int m = 1, int y = 2000){
    InDay(d),InMonth(m),InYear(y);
}

int date:: OutDay()const{
    return day;
}

int date:: OutMonth()const{
    return month;
}

int date:: OutYear()const {
    return year;
}

void date::print() const{
    cout<<*this<<endl;
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
    dataplus(DAYS);
    return *this;
}

date date::operator+ (const date &src) const {
    date RES(*this);
    RES+=src;
    return RES;
}

date &date::operator+= (int d){
    int DAYS = daysplus() + d;
    dataplus(DAYS);
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





class dateTime : public date {
private:
    int *second;
    int *minute;
    int *hour;
    int secondsDay() const;     //Returns the number of seconds elapsed since 00:00:00 of the given day
    void SecondPlus(int sec);   //Translate the number of seconds into the time elapsed from 00:00:00 on a given day
public:
    dateTime();
    dateTime(int D, int M, int Y, int h, int m, int s);
    dateTime(const dateTime &src);
    ~dateTime();

    dateTime &operator= (const dateTime &src);  //Assignment

    int seconds() const;    //Returns the number of seconds that have passed since January 1 of a given year

    void InDay(int D);      //Enter only day
    void InMonth(int M);    //Enter only month
    void InYear(int Y);     //Enter only year
    void InHour(int h);     //Enter only hour
    void InMinute(int m);   //Enter only minute
    void InSecond(int s);   //Enter only second

    int OutDay()const;      //Out only a day
    int OutMonth()const;    //Out only a month
    int OutYear()const;     //Out only a year
    int OutHour()const;     //Out only a hour
    int OutMinute()const;   //Out only a minute
    int OutSecond()const;   //Out only a second

    void print() const;

    dateTime &operator+= (const dateTime &src);     //Append date and time "src" to current
    dateTime operator+ (const dateTime &src) const; //Add dates ans times
    dateTime &operator+= (int src);                 //Add seconds "src" to the current date
    dateTime operator+ (int src) const;             //Add date and time with seconds
    bool operator== (const dateTime &src) const;    //Date and time comparison
    bool operator!= (const dateTime &src) const;    //Date and time comparison
    friend ostream &operator<< (ostream &os, const dateTime &src);  //Out date and time
};

int dateTime::secondsDay() const{
    return 3600*(*hour)+60*(*minute) + (*second);
}

void dateTime:: SecondPlus(int sec){
    int h=0, m=0;
    if (sec>=SPD) date::operator+= (1), sec-=SPD;
    while (sec>=3600) h++, sec-=3600;
    while (sec>=60) m++, sec-=60;
    *second =sec;
    *minute = m;
    *hour = h;
}

dateTime::dateTime():
    date(),
    second (new int(0)),
    minute (new int(0)),
    hour (new int(0)){
}

dateTime::dateTime(int D, int M, int Y, int h, int m, int s):
    date(D, M, Y),
    second (new int(s)),
    minute (new int(m)),
    hour (new int(h)){
}

dateTime::dateTime(const dateTime &src):
    date ((const date&)(src)),
    second (new int(*src.second)),
    minute (new int(*src.minute)),
    hour (new int(*src.hour)){
}

dateTime::~dateTime(){
    delete second;
    delete minute;
    delete hour;
}

dateTime &dateTime::operator= (const dateTime &src){
    if (&src==this) return *this;
    date::operator= ((const date &)(src));
    *second=*src.second;
    *minute=*src.minute;
    *hour=*src.hour;
    return *this;
}

int dateTime:: seconds()const{
    return days()*SPD + 3600*(*hour)+60*(*minute) + (*second);
}

void dateTime::InDay(int D){
        date::InDay(D);
}

void dateTime::InMonth(int M){
        date::InMonth(M);
}

void dateTime::InYear(int Y){
        date::InYear(Y);
}

void dateTime::InHour(int h){
        *hour=h;
}

void dateTime::InMinute(int m){
        *minute=m;
}

void dateTime::InSecond(int s){
        *second=s;
}

int dateTime::OutDay()const{
    return date::OutDay();
}

int dateTime::OutMonth()const{
    return date::OutMonth();
}

int dateTime::OutYear()const{
    return date::OutYear();
}

int dateTime::OutHour()const{
    return *hour;
}

int dateTime::OutMinute()const{
    return *minute;
}

int dateTime::OutSecond()const{
    return *second;
}

void dateTime::print() const{
    cout << (const date &)(*this) <<"   "<<*hour<<":"<<*minute<<":"<<*second<<endl;
}

dateTime &dateTime::operator+= (const dateTime &src){
    date::operator+= ((const date &)(src));
    SecondPlus(secondsDay()+src.secondsDay());
    return *this;
}

dateTime dateTime::operator+ (const dateTime &src) const{
    dateTime RES(*this);
    RES+=src;
    return RES;
}

dateTime &dateTime::operator+= (int src){
    date::operator+=(src/SPD);
    SecondPlus(secondsDay()+src-(src/SPD)*SPD);
    return *this;
}

dateTime dateTime::operator+ (int src) const{
    dateTime RES(*this);
    RES+=src;
    return RES;
}

bool dateTime::operator== (const dateTime &src) const{
        if ((date::operator== (src))&&((*hour)==(*src.hour))&&((*minute)==(*src.minute))&&((*second)==(*src.second))) return true;
        return false;
}

bool dateTime::operator!= (const dateTime &src) const{
    return !((*this)==src);
}
ostream &operator<< (ostream &os, const dateTime &src){
    os<< (const date &)(src) <<"   "<< *src.hour <<":"<< *src.minute <<":"<< *src.second;
    return os;
}

int main (void){
    dateTime A(31,12,2020,23,59,59), B(1,4,1895,15,4,12), C(31,12,1999,23,59,59), D(B), H(C), K, E(31,12,2020,23,59,59), F(31,1,2020,23,59,59); //The ability to enter a date and time using the constructor when declaring (by default, the date is set (0/0/0/01/01/2000))

    cout << "It's check operator copy " << H << endl;

    K = A;  //Check operator equals
    cout<<"operator= " <<K << '\n' << endl;

    int sec = C.seconds();  //Check method seconds
    cout << "Since January 1 to " << C << " have been passed " <<sec << " seconds\n" << endl;

    A.InDay(11);
    A.InMonth(2);
    A.InYear(2065);
    A.InHour(22);
    A.InMinute(5);
    A.InSecond(25);
    cout <<"It's check methods In... <-> Out... second/minute/.../year     "<<A.OutDay() <<"."<<A.OutMonth()<<"."<<A.OutYear()<<"    "<<A.OutHour()<<":"<<A.OutMinute()<<":"<<A.OutSecond()<<'\n'<<endl;

    A+=B;           //Overloaded operator +=
    cout << "operator+= " <<A << endl;
    A=B+C;          //Overloaded operator +
    cout <<"operator+ " << A << '\n' << endl;

    C+=1;           //Overloaded operator +=
    cout <<"operator+ (int)  31.12.1999 23:59:59 + 1 (sec) equally "<< C << endl; //
    C+=1000;        //Overloaded operator +=
    cout << "C+=1000 "<<C << endl;
    C+=100000;      //Overloaded operator +=
    cout<<"C+=100000 "<<C<< endl;
    K=C+10000000;   //Overloaded operator +
    cout<<"operator+  K=C+10000000 " << K << endl;
    K=C+1000003725; //Overloaded operator +
    cout<<"operator+  K=C+1000003725 " << K << '\n' << endl;

    E+=1;   //Check problematic case
    cout<<"E+=1 it's 31.12.2020 23:59:59 + 1(sec) is equally: " << E << endl;
    F+=1;   //Check problematic case
    cout<<"F+=1 it's 31.01.2020 23:59:59 + 1(sec) is equally: " << F << '\n' << endl;

    if (D==B) cout << "If you're reading this, then D == B, the method works." << endl;
    if (A!=C) cout << "If you're reading this, then A! = C, the method works.\n" << endl;

    date *Q = new dateTime (15,12,1856,23,24,59);
    Q->print(); //Check virtual method print()

    date &W = *Q;
    W.print();  //Check virtual method print()

    return 0;
}
