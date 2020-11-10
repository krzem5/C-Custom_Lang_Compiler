import math;
import "other-imp.l".df as duid, "bld/d378diuih/dpieo.l"



export class TestClass(BaseObject){
	public export TestClass(nm,?snm){
		this.nm = nm
		this.snm = (snm?snm:null);
	}

	public export log(){
		if (this.snm!=null){
			printf("Hello '%s %s'!",this.nm,this.snm);
		}
		else{
			printf("Hello '%s'!",this.nm);
		}
	}
};


const xhyJK=TestClass;

let tCls



tCls=TestClass("D");



d=*tCls = 729;
tCls*/=5;
