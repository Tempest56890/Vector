#include "Vector.h"
#include <ctime>
using namespace std;

int main(){
    
    cout<<"*---------------basic tests---------------*"<<endl;
    Vector<int> vec0,vec1(10),vec2(20);
    int vec_size = 0,vec_capacity = 0;
    bool empty,all = true;
    
    
    cout<<"test1 begins:"<<endl;
    cout<<"this part will test class-functions including size(),";
    cout<<"capacity(),is_empty()."<<endl;
    vec_size = vec0.size();
    vec_capacity = vec0.capacity();
    empty = vec0.is_empty();
    if (empty) {
        cout<<"Is vec0 an empty vector? yes"<<endl;
    } else {
        cout<<"Is vec0 an empty vector? no"<<endl;
    }
    cout<<"size of vec0: "<<vec_size<<endl;
    cout<<"capacity of vec0: "<<vec_capacity<<endl;
    if (empty && vec_size == 0) {
        cout<<"this part of function is correctly implemented."<<endl;
    } else {
        cout<<"something is wrong,please modify your sound code."<<endl;
        all = false;
    }
    cout<<"test1 ends."<<endl<<endl;
    
    
    cout<<"test2 begins:"<<endl;
    cout<<"this part will test class-functions including push_back(),"<<endl;
    cout<<"printVector(),ostream overload,operator overload,resize(),reverse()."<<endl;
    bool test = true;
    for (int i = 0;i < 20;i++) {
        if (i < 10) {
            vec1[i]=2*i;
            vec2[i]=i;
        } else {
            vec2[i]=i;
        }
    }
    cout<<vec1[0]<<","<<vec1[1]<<","<<vec1[2]<<endl;
    if (vec1[0] != 0 || vec1[1] != 2 || vec1[2] != 4) test = false;
    cout<<"vec1: ";vec1.printVector();
    cout<<"vec2: ";vec2.printVector();
    Vector<int> vec3(vec1);
    vec2 = vec1;
    cout<<"vec2: ";vec2.printVector();
    cout<<"vec3: ";vec3.printVector();
    vec3.resize(5);cout<<vec3.size()<<endl;
    if (vec3.size() != 10) test = false;
    cout<<"vec3: ";vec3.printVector();
    vec3.resize(20);cout<<vec3.size()<<endl;
    for (int i = 0;i < vec3.size();i++) {
        vec3[i] = 3 * i;
    }
    vec3.printVector();
    if (vec3.size() != 20) test = false;
    vec3.reserve(25);cout<<vec3.size()<<endl<<vec3.capacity()<<endl;
    if (vec3.size() != 20 || vec3.capacity() != 25) test = false;
    cout<<vec3.back()<<endl;
    if (vec3.back() != 57) test = false;
    vec3.pop_back();
    cout<<vec3.back()<<endl;
    if (vec3.back() != 54) test = false;
    vec3.push_back(57);
    cout<<vec3.back()<<endl;
    if (vec3.back() != 57) test = false;
    if (test) {
        cout<<"this part of function is correctly implemented."<<endl;
    } else {
        cout<<"something is wrong,please modify your sound code."<<endl;
        all = false;
    }
    cout<<"test2 ends."<<endl<<endl;
    
    
    cout<<"test3 begins:"<<endl;
    cout<<"this part will test iterator."<<endl;
    Vector<int>::iterator i;
    for (i = vec3.begin();i != vec3.end();++i) {
        cout<<*i<<" ";
    }
    cout<<endl;
    if (*(vec3.begin()) != 0 || *(vec3.end()-1) != 57) {
        cout<<"something is wrong,please modify your sound code."<<endl;
        all = false;
    } else {
        cout<<"this part of function is correctly implemented."<<endl;
    }
    cout<<"test3 ends."<<endl;
    if (all) {
        cout<<"*---------------basic tests all passed---------------*"<<endl<<endl;
    } else {
        cout<<"*---------------not all passed---------------*"<<endl<<endl;
    }

    int t,N,count = 1;
    clock_t start,end;
    cout<<"Now testing spare_capacity, recommend "<<endl<<"input";
    cout<<":N/10,N/5,N/4,N/3,N/2,6N/10,7N/10,8N/10,9N/10,N."<<endl;
    cout<<"input 0 to stop, 1 to try again:";
    while (cin>>t && t) {// input 0 if want to stop the experiment.
        cout<<count++<<"th try, please input N and spare_capacity:";
        cin>>N>>spare_capacity;
        start = clock();
        Vector<int> testvec;
        for (int n = 1;n < N;n++) {
            for (int i = 0;i < n;i++) {
                testvec.push_back(i);
            }
        }
            end = clock();
            cout<<"while N="<<N<<", spare_capacity="<<spare_capacity;
            cout<<":relatively caused time="<<end - start<<endl;
        cout<<"input 0 to stop, 1 to try again:";
    }
    cout<<"test ends."<<endl;
    
    return 0;
}
