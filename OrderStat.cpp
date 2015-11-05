#include "OrderStat.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using std::map;
using std::make_pair;
using std::cout;
using std::vector;
using std::random_shuffle;
using std::pair;
using std::string;

void testone() {
/*
	OrderStat<int> test; 
	pair<int,int> fst = make_pair(1,1); 
	pair<int,int> snd = make_pair(2,2);
	pair<int,int> thrd = make_pair(3,3);
	pair<int,int> fr = make_pair(4,4);
	pair<int,int> fv = make_pair(5,5);
	pair<int,int> sx = make_pair(6,4);
	pair<int,int> svn = make_pair(7,4);
	test.insert(fst);
	test.insert(snd);
	auto x = test.insert(thrd);
	test.insert(fr);
//	test.printPreOrder(test.getroot());
	test.insert(sx);
	test.insert(svn);
//	test.insert(fst);
	test.insert(fv);
	
	if(test[1] != fst.second){
		cout << "Problem with insert or bracket operator\n";
	}
	cout << test.height(test.getroot()) << "\n"; 
	cout << test.height(test.getroot()->left) << "\n";
	cout << test.height(test.getroot()->right) << "\n";
	*/
	//test.printPreOrder(test.getroot());
	//cout << test[1] << "\n";
	//cout << test[2] << "\n";
	//cout << test[3] << "\n";
	//cout << test.count(1) << "\n";
	//cout << test.count(0) << "\n";
	//cout << "This should be a 1: " << (itrfrst.first == itrfrstfail.first);
	//cout << "\nThis should be a 0: " << (itrfrst.second == itrfrstfail.second);
	
	//cout << "\n"<< test.count(2) << "\n";
	/*
	for(auto x:test){
		cout << "\n" << "Ranged loop";
		cout << x.first << "\n";
	}
	
	test.clear();
	test.push_back(sx);
	test.push_front(fst);
	*/

	OrderStat<int> firstOS;
	OrderStat<int> secondOS;
	secondOS.clear();
	secondOS.insert(secondOS.cbegin(),12);

	for(auto x=1;x!=5;++x){
		firstOS.push_front(x);
	}
	
	
	cout << "\n";
	secondOS.printPreOrder(secondOS.getroot());
	cout << "\n";
	//cout << firstOS[1];
	int x = firstOS.size();
	cout << (firstOS.size() == secondOS.size());

	OrderStat<int> thirdOS(firstOS);
	//firstOS.printPreOrder(firstOS.getroot());
	//cout << "\n";
	//thirdOS.printPreOrder(thirdOS.getroot());
	//cout <<"\n";
//
	if(thirdOS.getroot() == nullptr){
		cout << "the third OS somehow is broken way more than imaginable";
	}

	if(thirdOS != firstOS){
		cout << "Equivalency is broken";
	} 	

	thirdOS.push_front(999);
	thirdOS.push_back(10011);
	thirdOS.printPreOrder(thirdOS.getroot());

	cout << "\n";
	for(int x=0;x<thirdOS.size();x++){
		cout << thirdOS[x];
	}

}

bool equalitytest(){
	int test_size = 20000;
	bool testbool = true;
	OrderStat<int> test;
	vector<int> RandomThing;
	for(int i = 0; i<test_size; ++i){
		RandomThing.push_back(i);
	}
    random_shuffle(RandomThing.begin(), RandomThing.end());

    for(int i=0;i<test_size;++i){
    	test.push_back(RandomThing[i]);
    }

    unsigned tmpsizer = test_size; 
    for(int i=0;i<test_size;++i){
    	if(test.size() != tmpsizer){
    		cout << i << ":  Bad size ";
    		cout << test.size() << "\n";
    	}
    	test.pop_back();
    	tmpsizer--;
    	
    }
/*
    auto ths = test.begin();
    auto thsafter = ths;
    thsafter++;
    auto ers = test.erase(ths);
    test.erase(------test.end());
    cout << test.size();
    
    cout << test.size();
    if(ers != thsafter){
    	testbool = false;
    }
  */
	return testbool;
}


void stringtest() {
	OrderStat<string> test;
	auto fst = "words"; 
	auto snd = "morewords";
	auto thrd = "things";
	test.push_back(fst);
	test.push_back(snd);
	test.push_back(thrd);
	cout << test.size();
	cout << "\n";

	cout << test[0] << "\n";
	test.push_back(snd);
	cout << test[1] << "\n";
	test.push_back(thrd);
	cout << test[2] << "\n";

    auto tmpsz = test.size(); 
	test.pop_back();
	if(tmpsz-1 != test.size()){
		cout << "Erase size failed \n";
		cout << tmpsz-1 << ": Old size -1\n";
		cout << test.size() << ": current size\n";
	}
	

	test.insert(test.cbegin(),"abb");
	test.insert(++test.cbegin(),"bab");
	test.insert(test.cbegin(),----test.end(),test.end());
	for(auto x:test){
		cout << "\n" << "Ranged loop  ";
		cout << x << "\n";
	}
}


bool runAVLTestsForwards(){
	int test_size = 20;
    OrderStat<int> firstbst;
	
	vector<int> randoms;

	for(int i = 0; i<test_size; ++i){
		randoms.push_back(i);
	}
	//cout << randoms[0] << "\n";
    random_shuffle(randoms.begin(), randoms.end());
	//cout << randoms[0] << "\n";

	auto t1a = std::chrono::high_resolution_clock::now();
	for(int i=0; i<test_size; ++i){
	    firstbst.push_front(randoms[i]);
	}
	auto t2a = std::chrono::high_resolution_clock::now();

   std::cout << "inserting " << test_size << " took "
           	  << std::chrono::duration_cast<std::chrono::milliseconds>(t2a-t1a).count()///1000
              << " milliseconds\n";

	random_shuffle(randoms.begin(), randoms.end()--);

	OrderStat<int> tsbtsrif(firstbst);
	
	const auto a = tsbtsrif;
	const auto b = firstbst;

	if(a != b){
		cout << "copy construct worked\n";
		return false;
	}

	firstbst.clear();
	random_shuffle(randoms.begin(), randoms.end());
	//cout << randoms[0] << "\n";
	for(int i=0; i<test_size; ++i){
	    firstbst.push_front(randoms[i]);
		//firstmap.insert(make_pair(randoms[i],randoms[i]));
	}

	firstbst.clear();
	random_shuffle(randoms.begin(), randoms.end());
	//cout << randoms[0] << "\n";
	for(int i=0; i<test_size; ++i){
	    firstbst.push_front(randoms[i]);
		//firstmap.insert(make_pair(randoms[i],randoms[i]));
	}
	

	return true;	
}



int main(){
	testone();
	cout << "\n---------Testone passed---------\n";
	cout << "\n";
	auto t1 = std::chrono::high_resolution_clock::now();
    runAVLTestsForwards();
	auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Forwards test function took "
           	  << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()///1000
              << " milliseconds\n";

	cout << "\n---------RunTests Forwards passed---------\n";
	/*	
*/
	if(equalitytest()) {cout << "\n---------Equality Test Passed---------\n";}
	else cout << "\n---------Equality Test Failed---------\n";
	stringtest();
	cout << "\n---------StringTests ran---------\n";

	return 0; 	

	cout << "\n";

}







/*




int main(){
	OrderStat<int> firstOS;
	OrderStat<int> secondOS;

	firstOS.push_back(1);
	firstOS.push_back(2);
	firstOS.push_back(3);
	firstOS.push_back(4);
	firstOS.printPreOrder(firstOS.getroot());
	cout << "\n";
	firstOS.pop_back();
	firstOS.printPreOrder(firstOS.getroot());
	cout << "\n";

	cout << firstOS[1];
	int x = firstOS.size();
	cout << (firstOS.size() == secondOS.size());

	OrderStat<int> thirdOS(firstOS);
}	
*/