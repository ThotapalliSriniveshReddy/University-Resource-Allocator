#include <bits/stdc++.h>

using namespace std;

class Rollnumber{
    public:
    string r="0";
 void   createroll(string x){
    r=x;
    return;
    }
void print(){
    cout<<r<<endl;
    return;
}
bool compare(Rollnumber a, Rollnumber b){
    return a.r<b.r;
}
};


class Faculty{
    public:
string name="0";
bool permanent=0;
set<string> hostel;
vector<Rollnumber> facadfor;
vector<Rollnumber> BTPGuidefor;
vector<Rollnumber> DDPGuidefor;
vector<Rollnumber> TAs;


void addfaculty(string n,bool p){
    name=n;
    permanent=p;
    
    return;
}

void printname(){
    cout<<name<<endl;
    return;
}
friend class Btech;
friend class DualDegree;
friend class IITM;

};



class DualDegree{

  public:

   Rollnumber roll;
    string hostel="0";
    Faculty facad;
    float cgpa=-1;
    Faculty DDPGuide;
    bool projectee=0;
    bool TA=0;
    Faculty TASupervisor;

void  addstudent(Rollnumber r, string h , Faculty f, float cgp){
   roll=r;
   hostel=h;
   facad=f;
   cgpa=cgp;
   f.facadfor.push_back(roll);
   return;
    }

string getHostel(){
    return hostel;
}

Faculty getFacad(){
    return facad;
}
float getcgpa(){
    return cgpa;
}

Rollnumber getroll(){
    return roll;
}

void changeHostel(string newhostel){
    hostel=newhostel;
    return;
}

void setDDPGuide(Faculty f){
    DDPGuide= f;
    f.DDPGuidefor.push_back(roll);
    projectee=1;
    return;
}

void setTASupervisor(Faculty f){

    bool TA=1;
    TASupervisor=f;
    f.TAs.push_back(roll);
    return;
}

friend class IITM;

};

class Btech{
    public:

    Rollnumber roll;
    string hostel="0";
    Faculty facad;
    float cgpa=-1;
    Faculty BTPGuide;
    bool projectee=0;


void  addstudent(Rollnumber r, string h , Faculty f, float cgp){
   roll=r;
   hostel=h;
   facad=f;
   cgpa=cgp;
   f.facadfor.push_back(r);
   return;
    }

string getHostel(){
    return hostel;
}

Faculty getFacad(){
    return facad;
}
float getcgpa() {
    return cgpa;
}
Rollnumber getroll(){
    return roll;
}

void changeHostel(string newhostel){
    hostel=newhostel;
    return;
}

void setBTPGuide(Faculty f){
    BTPGuide= f;
    f.BTPGuidefor.push_back(roll);
    projectee=1;
    return;
}


friend class IITM;

};





class IITM{

    private:

vector<Rollnumber> students;
vector<Btech> Btechies;
vector<DualDegree> DDs;
vector<pair<Btech,DualDegree>> studs;
vector<Faculty> faculty;
vector<string> hostels;

// unordered_map<string,Faculty> faculty;
// unordered_map<Rollnumber,Btech> Btechies;
// unordered_map<Rollnumber,DualDegree> DDs;
// unordered_map<string,int> hostels;

public:

void create(int n,int m, int h){

    srand(static_cast<unsigned>(time(0))); // Seed for random number generation

    unordered_set<string> unique;

    while (hostels.size() < h) {
        int nameLength = 1 + rand() % 10; 
       string name;
        for (int i = 0; i < nameLength; ++i) {
            name += 'a' + rand() % 26;
        }

        if (unique.find(name) == unique.end()) { // Ensure uniqueness
            hostels.push_back(name);
            unique.insert(name);
        }
    }
    
    unique.clear();

    while(faculty.size()<m){
        int nameLength= 1+ rand()%14;
        string name;
        for (int i = 0; i < nameLength; ++i) {
            name += 'a' + rand() % 26;
        }
        bool p= rand()%2;
    if (unique.find(name) == unique.end()) { // Ensure uniqueness
            Faculty f;
            f.addfaculty(name,p);
            faculty.push_back(f);
            unique.insert(name);
        }

    }
    
    unique.clear();

while(students.size()<n){

    string roll;
    for (int i = 0; i < 7; ++i) {
            roll += '0' + rand() % 10; 
        }
            Rollnumber r;
    if (unique.find(roll) == unique.end()) { // Ensure uniqueness
            r.createroll(roll);
            students.push_back(r);
            unique.insert(roll);
        }
    int nameLength= 1+ rand()%14;
        string name;
        for (int i = 0; i < nameLength; ++i) {
            name += 'a' + rand() % 26;
        }

    string hostel=hostels[rand()%hostels.size()];
    Faculty& facada= faculty[rand()%faculty.size()];
    facada.facadfor.push_back(r);
    float gpa= (rand()%1001)/100.00;

    int degree= rand()%2;
    if(degree==1){
        DualDegree d;
        Btech b;
        b.addstudent(r,name,facada,gpa);
        Btechies.push_back(b);
        studs.push_back(make_pair(b,d));
    }
    else {
        DualDegree d;
        Btech b;
        d.addstudent(r,name,facada,gpa);
        DDs.push_back(d);
        studs.push_back(make_pair(b,d));
    }
    
}

// cout<<Btechies[Btechies.size()-1].hostel<<endl;
return;
}
//assigning BTP guides

void assignBTP(){

    sort(Btechies.begin(),Btechies.end(),[&]( Btech a,Btech b){
                                            return a.getcgpa() < b.getcgpa();
                                            });
    int j=0;
    for(int i=0;i<faculty.size()&&j<Btechies.size();i++){
        
        if(faculty[i].permanent ){
           int pro=rand()%3;
          
           if(pro==1) {
            Btechies[j].setBTPGuide(faculty[i]);
             j++;
             faculty[i].hostel.insert(Btechies[j-1].hostel);
            //  cout<<Btechies[j-1].hostel<<endl;
             faculty[i].BTPGuidefor.push_back(Btechies[j-1].roll);
           }
           if(pro==2){
            Btechies[j].setBTPGuide(faculty[i]);
            j++;
            faculty[i].hostel.insert(Btechies[j-1].hostel);
            faculty[i].BTPGuidefor.push_back(Btechies[j-1].roll);
        if(j<Btechies.size()) 
        {
        Btechies[j].setBTPGuide(faculty[i]);
        j++; 
        faculty[i].hostel.insert(Btechies[j-1].hostel);
        faculty[i].BTPGuidefor.push_back(Btechies[j-1].roll);
        }

        }
    }


}

}

void assignDDP(){

    sort(DDs.begin(),DDs.end(),[&](DualDegree  a, DualDegree b){
                                                return a.getHostel() < b.getHostel() ;
                                            });
    int j=0;
    for(int i=0;i<faculty.size()&&j<DDs.size();i++){
        if(faculty[i].permanent ==1){
           int pro=rand()%3;
           if(pro==1) {
            DDs[j].setDDPGuide(faculty[i]);
             j++;
             faculty[i].hostel.insert(DDs[j-1].hostel);
             faculty[i].DDPGuidefor.push_back(DDs[j-1].roll);
           }
           if(pro==2){
            DDs[j].setDDPGuide(faculty[i]);
            j++;
            faculty[i].hostel.insert(DDs[j-1].hostel);
            faculty[i].DDPGuidefor.push_back(DDs[j-1].roll);
        if(j<DDs.size()) 
        {
        DDs[j].setDDPGuide(faculty[i]);
        j++; 
        faculty[i].hostel.insert(DDs[j-1].hostel);
        faculty[i].DDPGuidefor.push_back(DDs[j-1].roll);
        }

        }
    }
}
}

void assignTA(){
int i=0;
int j=0;
for(;i<faculty.size();i++){
    if(j+4>=DDs.size()) break;
    DDs[j].setTASupervisor(faculty[i]);
    faculty[i].TAs.push_back(DDs[j].roll);
    DDs[j+1].setTASupervisor(faculty[i]);
     faculty[i].TAs.push_back(DDs[j+1].roll);
    DDs[j+2].setTASupervisor(faculty[i]);
     faculty[i].TAs.push_back(DDs[j+2].roll);
    DDs[j+3].setTASupervisor(faculty[i]);
     faculty[i].TAs.push_back(DDs[j+3].roll);
    DDs[j+4].setTASupervisor(faculty[i]);
     faculty[i].TAs.push_back(DDs[j+4].roll);
    j=j+5;
}
// cout<<DDs.size()<<" "<<j<<endl;
if(i<faculty.size()){
    for(;j<DDs.size();j++){
        DDs[j].setTASupervisor(faculty[i]);
         faculty[i].TAs.push_back(DDs[j].roll);
    }
}
}

bool check(){
    
    for(int i=0;i<faculty.size();i++){
        if(faculty[i].BTPGuidefor.size()>2||faculty[i].DDPGuidefor.size()>2||faculty[i].TAs.size()>5) {cout<<faculty[i].BTPGuidefor.size()<<" "<<faculty[i].DDPGuidefor.size()<<" "<<faculty[i].TAs.size()<<endl;
        return false;}
    }
    return true;
}

float percentage(){
    int size=Btechies.size()+DDs.size();
    int same=0;
    for(int i=0;i<DDs.size();i++){
        if(DDs[i].DDPGuide.name==DDs[i].TASupervisor.name) same++;
    }
    return float(float(same)/size);
}

void noguide(){
    for(int i=0;i<Btechies.size();i++){
        if(Btechies[i].projectee==0) Btechies[i].roll.print();
    }
    for(int i=0;i<DDs.size();i++){
        if(DDs[i].projectee==0) DDs[i].roll.print();
    }
}

vector<Faculty> maxhostel(){
    vector<Faculty> max;
    int maxnum=0;
    // cout<<faculty[0].hostel.size()<<endl;
    // cout<<faculty.size()<<endl;
    for(int i=0;i<faculty.size();i++){
        int diff= faculty[i].hostel.size();
        if(diff>maxnum) maxnum=diff;
        if(maxnum==4) break;
    }
// cout<<maxnum<<endl;
for(int i=0;i<faculty.size();i++){
    if(faculty[i].hostel.size()==maxnum) max.push_back(faculty[i]);

}
return max;
}

void samesame(string hostel,Faculty fac){
    string givenname=fac.name;
    for(int i=0;i<DDs.size();i++){
        if(DDs[i].getHostel()==hostel){
            if(givenname==DDs[i].DDPGuide.name||givenname==DDs[i].TASupervisor.name) DDs[i].roll.print();
        }
    }
    return;
}

void proll(){
    cout<<"Rollwise:"<<endl;
    sort(students.begin(),students.end(),[&](Rollnumber a, Rollnumber b){
        return a.r<b.r;
    });
    for(int i=0;i<students.size();i++){
        students[i].print();
    }
    return;
}

void pguidename(){
    cout<<"Guidenamewise:"<<endl;
    cout<<endl<<"Btech:"<<endl;

    sort(Btechies.begin(),Btechies.end(),[&](Btech a, Btech b){
        if(a.projectee&&b.projectee){
            if(a.BTPGuide.name<b.BTPGuide.name) return true;
            else if(a.BTPGuide.name>b.BTPGuide.name) return false;
            else return a.roll.r<b.roll.r;
            
        }
        else if(a.projectee) return true;
        else if(b.projectee) return false;
        else return a.roll.r<b.roll.r;

    });

    for(int i=0;i<Btechies.size();i++){
        Btechies[i].roll.print();
    }

  cout<<endl<<"DualDegree:"<<endl;

    sort(DDs.begin(),DDs.end(),[&](DualDegree a, DualDegree b){
        if(a.projectee&&b.projectee){
            if(a.DDPGuide.name<b.DDPGuide.name) return true;
            else if(a.DDPGuide.name>b.DDPGuide.name) return false;
            else return a.roll.r<b.roll.r;
            
        }
        else if(a.projectee) return true;
        else if(b.projectee) return false;
        else return a.roll.r<b.roll.r;

    });

    for(int i=0;i<DDs.size();i++){
        DDs[i].roll.print();
    }  

}

void phostel(){
    cout<<"Hostelwise:"<<endl;
    cout<<endl<<"Btech:"<<endl;

    sort(Btechies.begin(),Btechies.end(),[&](Btech a, Btech b){
        
            if(a.hostel<b.hostel) return true;
            else if(a.hostel>b.hostel) return false;
            else return a.roll.r<b.roll.r;
            
        });

    for(int i=0;i<Btechies.size();i++){
        Btechies[i].roll.print();
    }

  cout<<endl<<"DualDegree:"<<endl;

    sort(DDs.begin(),DDs.end(),[&](DualDegree a, DualDegree b){
            if(a.hostel<b.hostel) return true;
            else if(a.hostel>b.hostel) return false;
            else return a.roll.r<b.roll.r;
            
    });

    for(int i=0;i<DDs.size();i++){
        DDs[i].roll.print();
    }  
}

};





int main(){
        int n,m,h;
        cin>>n>>m>>h;
IITM community;
        community.create(n,m,h);
        community.assignBTP();
        community.assignDDP();
        community.assignTA();
        if(community.check()) cout<<"Satisfied"<<endl;
        else cout<<"Not satisfied"<<endl;
   cout<< community.percentage()<<endl;
   vector<Faculty> max= community.maxhostel();
   for(int i=0;i<max.size();i++){
    max[i].printname();
   }
   
cout<<endl;
community.proll();
cout<<endl;
community.pguidename();
cout<<endl;
community.phostel();
cout<<endl;
cout<<"No guide:"<<endl;
community.noguide();

}



