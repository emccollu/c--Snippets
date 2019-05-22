#include <iostream>
#include <iomanip>
#include <string>
#include "TreeN.h"
using namespace std;
/*-----postorderPrint----------------------------------------
	ARGS: Takes iterator at TreeRoot
	Operation: Print function for ordered and calculated Tree.
*/
void postorderPrint(TreeItr p){
  cout << p.getInfo().element<< " ";
  if(p.getInfo().critical==1) //Addition of critical element print
    cout << " critical      ";
  else
    cout << " not critical  ";
  cout <<p.getInfo().duration << endl;
  if (p.hasChild()){
    p.advanceChild();
    while (! p.isPast()){
      postorderPrint(p);
      p.advanceSibling();
    }
  }
}
/*-----setupTree--------------------------------------------
	ARGS: Takes empty Tree
	Operation: Creates new nodes on their respective parents.
*/
void setupTree(Tree &T){
	TreeItr current;
	//Varaibles for each leaf for small tree:
	TreeItr inter, setup, test, ceo; //lvl2
	TreeItr sort, lib, main, cio, plat, write; //lvl3
  TreeItr desi, desp, desd, desu, dese, dept; //lvl4
	Task tmp;
	//-------LVL1-------
  //Creates root node:
  current = T.TreeRoot();
  	tmp.element = "install product     ";
    tmp.duration = 4; //Takes 4 weeks to complete
  	tmp.critical = 1; //Root is set as critical
  	current.changeInfo(tmp);
    tmp.critical = 0;
	//Made tree setup fairly linear, for larger trees would minimize variables
	//Treenodes initiated backwards from parent, pointers adjusted in createChild
  //-------LVL2-------
  //Children of root:
  test = T.createChild(current);
  	tmp.element = " test main          ";
    tmp.duration = 4;
  	test.changeInfo(tmp);
  ceo = T.createChild(current);
    tmp.element = " get CEO report     ";
    tmp.duration = 1;
    ceo.changeInfo(tmp);
  setup = T.createChild(current);
    tmp.element = " set up platform    ";
    tmp.duration = 1;
    setup.changeInfo(tmp);
  inter = T.createChild(current);
    tmp.element = " test user interface";
    tmp.duration = 4;
    inter.changeInfo(tmp);
	//-------LVL3-------
	sort = T.createChild(test);
		tmp.element = "  install sort      ";
		tmp.duration = 1;
		sort.changeInfo(tmp);
	lib = T.createChild(test);
		tmp.element = "  install lib       ";
		tmp.duration = 1;
		lib.changeInfo(tmp);
	main = T.createChild(test);
		tmp.element = "  write main        ";
		tmp.duration = 3;
		main.changeInfo(tmp);
  cio = T.createChild(ceo);
  	tmp.element = "  get CIO input     ";
  	tmp.duration = 1;
    cio.changeInfo(tmp);
	plat = T.createChild(setup);
		tmp.element = "  order platform    ";
		tmp.duration = 2;
		plat.changeInfo(tmp);
	write = T.createChild(inter);
		tmp.element = "  write I/O         ";
		tmp.duration = 3;
		write.changeInfo(tmp);
	//-------LVL4-------
	dese = T.createChild(main);
  	tmp.element = "   design engine    ";
  	tmp.duration = 4;
  	dese.changeInfo(tmp);
	desu = T.createChild(main);
  	tmp.element = "   design utilities ";
  	tmp.duration = 2;
  	desu.changeInfo(tmp);
	desd = T.createChild(main);
  	tmp.element = "   design driver    ";
  	tmp.duration = 4;
  	desd.changeInfo(tmp);
	dept = T.createChild(cio);
  	tmp.element = "   get Dept report  ";
  	tmp.duration = 1;
  	dept.changeInfo(tmp);
	desp = T.createChild(write);
  	tmp.element = "   design protocol  ";
  	tmp.duration = 4;
  	desp.changeInfo(tmp);
	desi = T.createChild(write);
  	tmp.element = "   design I/O       ";
  	tmp.duration = 3;
  	desi.changeInfo(tmp);
}
/*-----calcCompletion---------------------------------------
	ARGS: Takes iterator at TreeRoot
	Operation: Loops once through children to find largest
		duration and adds that to parent duration. Recurses to
		iterate tree effectively.
*/
void calcCompletion(TreeItr cur){
	TreeItr parnt;
	Task tmp;
	int grt=0;
  if(cur.hasChild()){
		parnt = cur; //Set for adjusting parent element
    cur.advanceChild();
		grt = cur.getInfo().duration; //Set to initial for max
    while (! cur.isPast()){
			calcCompletion(cur); //Call recursion to iterate tree
			if(grt < cur.getInfo().duration)
				grt = cur.getInfo().duration; //Find max duration
			cur.advanceSibling();
    }//End while
		tmp = parnt.getInfo();
		tmp.duration += grt;
		parnt.changeInfo(tmp); //Adjusted parent to include max duration of children
  }//End main if
}//End func
/*-----determineCritical------------------------------------
	ARGS: Takes iterator at TreeRoot
	Operation: 2 loops that find criticals and set bool value to true
		Recurses to iterate tree effectively.
*/
void determineCritical(TreeItr cur){
	TreeItr nxt;
	Task tmp;
	int grt=0;
  if(cur.hasChild()){
    cur.advanceChild();
		nxt = cur; //Set for second iteration
		grt = cur.getInfo().duration; //Set initial max number
    while (! cur.isPast()){
			if(grt < cur.getInfo().duration)
				grt = cur.getInfo().duration; //Get largest duration
			cur.advanceSibling();
    }
		//Second loop to set criticals to largest durations
		while(! nxt.isPast()){
			if(nxt.getInfo().duration == grt){
				determineCritical(nxt); //Call recursion on children that are critical
				tmp = nxt.getInfo();
				tmp.critical = 1;
				nxt.changeInfo(tmp); //List element altered to critical = true
			}
			nxt.advanceSibling();
		} //End 2nd lp
  }//End if statement
}//End func
//-----Provided Main----------------------------------------
int main(){
	Tree theJobs;
	TreeItr Top;
	Top = theJobs.TreeRoot();
	setupTree(theJobs);
	calcCompletion(Top);
	determineCritical(Top);
	cout << "PROJECT SCHEDULE" << endl;
	postorderPrint(Top);
	};
