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

int main(){
	OrderStat<int> firstOS;
	firstOS.push_back(1);
	firstOS.push_back(2);
	firstOS.push_back(3);
	firstOS.push_back(4);
	firstOS.printPreOrder(firstOS.getroot());
	cout << "\n";
	firstOS.pop_back();
	firstOS.printPreOrder(firstOS.getroot());
	cout << "\n";

}