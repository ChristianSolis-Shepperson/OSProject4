#include <string>
#include "stdlib.h"
#include <fstream>
#include <iostream>
#include <mutex>

#include "../includes/waiter.h"
#include "../includes/externs.h"

using namespace std;

mutex m;

//ID is just a number used to identify this particular baker
//(used with PRINT statements)
//filename is what waiter reads in orders from
Waiter::Waiter(int id, std::string filename) :
		id(id), myIO(filename) {
}

Waiter::~Waiter() {
}

//gets next Order(s) from file_IO
//if return == SUCCESS then anOrder
//contains new order
//otherwise return contains error
int Waiter::getNext(ORDER &anOrder) {
	std::unique_lock<std::mutex> lck(m);

	if (!myIO.getNext(anOrder)) {

		return SUCCESS;

	} else {

		return NO_ORDERS;
	}
}

//contains a loop that will get orders from filename one at a time
//then puts them in order_in_Q then signals baker(s) using cv_order_inQ
//so they can be consumed by baker(s)
//when finished exits loop and signals baker(s) using cv_order_inQ that
//it is done using b_WaiterIsFinished
void Waiter::beWaiter() {
	ORDER order;
	std::unique_lock<std::mutex> lck(m);

	if (!myIO.getNext(order)) {

		b_WaiterIsFinished = true;
		cv_order_inQ.notify_all();

	} else {

		b_WaiterIsFinished = false;
		cv_order_inQ.wait(lck);

		while (myIO.getNext(order)) {
			order_in_Q.push(order);

		}

	}

}

