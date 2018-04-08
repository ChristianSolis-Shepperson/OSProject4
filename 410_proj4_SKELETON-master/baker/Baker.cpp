#include <mutex>

#include "../includes/baker.h"
#include "../includes/externs.h"
using namespace std;

	//ID is just a number used to identify this particular baker
	//(used with PRINT statements)
Baker::Baker(int id) :
		id(id) {
}

Baker::~Baker() {
}

	//bake, box and append to anOrder.boxes vector
	//if order has 13 donuts there should be 2 boxes
	//1 with 12 donuts, 1 with 1 donut
void Baker::bake_and_box(ORDER &anOrder) {

	//Code may be needed for this portion, may not be needed

//	int donutsPerBox = 12;
//
//	if(anOrder.number_donuts <=donutsPerBox){
//		anOrder.boxes = 1;
//	} else {
//		int boxToFill = anOrder.number_donuts % donutsPerBox;
//	}

}

	//as long as there are orders in order_in_Q then
	//for each order:
	//	create box(es) filled with number of donuts in the order
	//  then place finished order on order_outvector
	//  if waiter is finished (b_WaiterIsFinished) then
	//  finish up remaining orders in order_in_Q and exit
	//
	//You will use cv_order_inQ to be notified by waiter
	//when either order_in_Q.size() > 0 or b_WaiterIsFinished == true
	//hint: wait for something to be in order_in_Q or b_WaiterIsFinished == true
void Baker::beBaker() {

	while(order_in_Q){
		//need to create boxes

		//places orders in order_out and removes from in_Q
		order_out_Vector.push_back(order_in_Q.front());
		order_in_Q.pop();

	}

}
