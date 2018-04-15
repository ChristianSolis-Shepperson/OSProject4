#include <mutex>

#include "../includes/baker.h"
#include "../includes/externs.h"
#include "../includes/box.h"
using namespace std;

mutex m;
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
	int numOfBoxes = anOrder.number_donuts / DOZEN;
	int numOfDonuts = anOrder.number_donuts;
	if(anOrder.number_donuts / DOZEN < 1 && anOrder.number_donuts > 0){
		Box box;
		anOrder.boxes.push_back(box);
		for(int i = 0; i < numOfDonuts; i++){
			DONUT donut;
			anOrder.boxes.front().addDonut(donut);
		}
	}
	else if(anOrder.number_donuts % DOZEN == 0 && numOfBoxes >= 1){
		for(int i = 0; i < numOfBoxes; i++){
			Box box;
			anOrder.boxes.push_back(box);
			for(int d = 0; d < DOZEN; d++){
				DONUT donut;
				anOrder.boxes.back().addDonut(donut);
			}
		}
	}
	else if(anOrder.number_donuts % DOZEN != 0 && numOfBoxes >= 1) {
		  for(int i = 0; i < numOfBoxes + 1; i++){
		  		Box box;
		  		anOrder.boxes.push_back(box);

		  		for(int d = 0; d < DOZEN; d++){
		  			if(numOfDonuts > 0){
						DONUT donut;
						anOrder.boxes.back().addDonut(donut);
						numOfDonuts--;
		  			}
		  		}
		  }
	  }
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

	unique_lock<mutex> lck(m);


	while(!order_in_Q.empty()){
		//need to create boxes
		cv_order_inQ.wait(lck);
		bake_and_box(order_in_Q.front());
		if(b_WaiterIsFinished){
			order_out_Vector.push_back(order_in_Q.front());
			order_in_Q.pop();
		}
	}
}
