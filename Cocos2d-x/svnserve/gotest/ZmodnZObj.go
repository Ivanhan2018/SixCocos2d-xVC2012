package main
 
import (
    "fmt"
    "os"	
)

type ZmodnZObj struct {
   m_k,m_mod int
}

/*
16阶全矩阵环M_2(F_2)
m:=2;
I:=[ [ ZmodnZObj( 1, m), ZmodnZObj( 0, m) ], [ ZmodnZObj( 0, m), ZmodnZObj( 1, m) ] ];
A:=[ [ ZmodnZObj( 1, m), ZmodnZObj( 0, m) ], [ ZmodnZObj( 0, m), ZmodnZObj( 0, m) ] ];
B:=[ [ ZmodnZObj( 1, m), ZmodnZObj( 0, m) ], [ ZmodnZObj( 1, m), ZmodnZObj( 1, m) ] ];
C:=[ [ ZmodnZObj( 1, m), ZmodnZObj( 0, m) ], [ ZmodnZObj( 1, m), ZmodnZObj( 0, m) ] ];
D:=[ [ ZmodnZObj( 1, m), ZmodnZObj( 1, m) ], [ ZmodnZObj( 0, m), ZmodnZObj( 1, m) ] ];
E:=[ [ ZmodnZObj( 1, m), ZmodnZObj( 1, m) ], [ ZmodnZObj( 0, m), ZmodnZObj( 0, m) ] ];
F:=[ [ ZmodnZObj( 1, m), ZmodnZObj( 1, m) ], [ ZmodnZObj( 1, m), ZmodnZObj( 1, m) ] ];
G:=[ [ ZmodnZObj( 1, m), ZmodnZObj( 1, m) ], [ ZmodnZObj( 1, m), ZmodnZObj( 0, m) ] ];
H:=[ [ ZmodnZObj( 0, m), ZmodnZObj( 0, m) ], [ ZmodnZObj( 0, m), ZmodnZObj( 1, m) ] ];
O:=[ [ ZmodnZObj( 0, m), ZmodnZObj( 0, m) ], [ ZmodnZObj( 0, m), ZmodnZObj( 0, m) ] ];
K:=[ [ ZmodnZObj( 0, m), ZmodnZObj( 0, m) ], [ ZmodnZObj( 1, m), ZmodnZObj( 1, m) ] ];
L:=[ [ ZmodnZObj( 0, m), ZmodnZObj( 0, m) ], [ ZmodnZObj( 1, m), ZmodnZObj( 0, m) ] ];
M:=[ [ ZmodnZObj( 0, m), ZmodnZObj( 1, m) ], [ ZmodnZObj( 0, m), ZmodnZObj( 1, m) ] ];
N:=[ [ ZmodnZObj( 0, m), ZmodnZObj( 1, m) ], [ ZmodnZObj( 0, m), ZmodnZObj( 0, m) ] ];
P:=[ [ ZmodnZObj( 0, m), ZmodnZObj( 1, m) ], [ ZmodnZObj( 1, m), ZmodnZObj( 1, m) ] ];
Q:=[ [ ZmodnZObj( 0, m), ZmodnZObj( 1, m) ], [ ZmodnZObj( 1, m), ZmodnZObj( 0, m) ] ];
*/
var g_I[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,2},ZmodnZObj{0,2}},
		{ZmodnZObj{0,2},ZmodnZObj{1,2}},
		}
var g_A[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,2},ZmodnZObj{0,2}},
		{ZmodnZObj{0,2},ZmodnZObj{0,2}},
		}
var g_B[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,2},ZmodnZObj{0,2}},
		{ZmodnZObj{1,2},ZmodnZObj{1,2}},
		}
var g_C[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,2},ZmodnZObj{0,2}},
		{ZmodnZObj{1,2},ZmodnZObj{0,2}},
		}	
var g_D[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,2},ZmodnZObj{1,2}},
		{ZmodnZObj{0,2},ZmodnZObj{1,2}},
		}		
var g_E[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,2},ZmodnZObj{1,2}},
		{ZmodnZObj{0,2},ZmodnZObj{0,2}},
		}
var g_F[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,2},ZmodnZObj{1,2}},
		{ZmodnZObj{1,2},ZmodnZObj{1,2}},
		}		
var g_G[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,2},ZmodnZObj{1,2}},
		{ZmodnZObj{1,2},ZmodnZObj{0,2}},
		}
var g_H[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{0,2},ZmodnZObj{0,2}},
		{ZmodnZObj{0,2},ZmodnZObj{1,2}},
		}
var g_O[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{0,2},ZmodnZObj{0,2}},
		{ZmodnZObj{0,2},ZmodnZObj{0,2}},
		}
var g_K[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{0,2},ZmodnZObj{0,2}},
		{ZmodnZObj{1,2},ZmodnZObj{1,2}},
		}
var g_L[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{0,2},ZmodnZObj{0,2}},
		{ZmodnZObj{1,2},ZmodnZObj{0,2}},
		}	
var g_M[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{0,2},ZmodnZObj{1,2}},
		{ZmodnZObj{0,2},ZmodnZObj{1,2}},
		}		
var g_N[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{0,2},ZmodnZObj{1,2}},
		{ZmodnZObj{0,2},ZmodnZObj{0,2}},
		}
var g_P[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{0,2},ZmodnZObj{1,2}},
		{ZmodnZObj{1,2},ZmodnZObj{1,2}},
		}		
var g_Q[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{0,2},ZmodnZObj{1,2}},
		{ZmodnZObj{1,2},ZmodnZObj{0,2}},
		}
		
var g_R16_300[]*[][]ZmodnZObj=[]*[][]ZmodnZObj{&g_O,&g_I,&g_A,&g_B,&g_C,&g_D,&g_E,&g_F,&g_G,&g_H,&g_K,&g_L,&g_M,&g_N,&g_P,&g_Q}


/* 
256阶全矩阵环M_2(Z/4Z)的一个16阶子环R16_101
m:=4;
A:=[ [ ZmodnZObj( 1, m), ZmodnZObj( 0, m ) ], [ ZmodnZObj( 1, m ), ZmodnZObj( 0, m ) ] ];
B:=[ [ ZmodnZObj( 1, m), ZmodnZObj( 1, m ) ], [ ZmodnZObj( 1, m ), ZmodnZObj( 1, m ) ] ];
g24_O= [[{0 4} {0 4}] [{0 4} {0 4}]]
g24_A= [[{1 4} {0 4}] [{1 4} {0 4}]]
g24_B= [[{1 4} {1 4}] [{1 4} {1 4}]]
g24_A2= [[{2 4} {0 4}] [{2 4} {0 4}]]
g24_A3= [[{3 4} {0 4}] [{3 4} {0 4}]]
g24_B2= [[{2 4} {2 4}] [{2 4} {2 4}]]
g24_B3= [[{3 4} {3 4}] [{3 4} {3 4}]]
g24_AB= [[{2 4} {1 4}] [{2 4} {1 4}]]
g24_A2B2= [[{0 4} {2 4}] [{0 4} {2 4}]]
g24_A3B3= [[{2 4} {3 4}] [{2 4} {3 4}]]
g24_AB2= [[{3 4} {2 4}] [{3 4} {2 4}]]
g24_AB3= [[{0 4} {3 4}] [{0 4} {3 4}]]
g24_A2B= [[{3 4} {1 4}] [{3 4} {1 4}]]
g24_A3B= [[{0 4} {1 4}] [{0 4} {1 4}]]
g24_A2B3= [[{1 4} {3 4}] [{1 4} {3 4}]]
g24_A3B2= [[{1 4} {2 4}] [{1 4} {2 4}]]
另一个16阶子环R16_102
m:=4;
C:=[ [ ZmodnZObj( 2, m), ZmodnZObj( 2, m ) ], [ ZmodnZObj( 1, m ), ZmodnZObj( 3, m ) ] ];
D:=[ [ ZmodnZObj( 1, m), ZmodnZObj( 3, m ) ], [ ZmodnZObj( 3, m ), ZmodnZObj( 1, m ) ] ];
g24_O= [[{0 4} {0 4}] [{0 4} {0 4}]]
g24_C= [[{2 4} {2 4}] [{1 4} {3 4}]]
g24_D= [[{1 4} {3 4}] [{3 4} {1 4}]]
g24_C2= [[{0 4} {0 4}] [{2 4} {2 4}]]
g24_C3= [[{2 4} {2 4}] [{3 4} {1 4}]]
g24_D2= [[{2 4} {2 4}] [{2 4} {2 4}]]
g24_D3= [[{3 4} {1 4}] [{1 4} {3 4}]]
g24_CD= [[{3 4} {1 4}] [{0 4} {0 4}]]
g24_C2D2= [[{2 4} {2 4}] [{0 4} {0 4}]]
g24_C3D3= [[{1 4} {3 4}] [{0 4} {0 4}]]
g24_CD2= [[{0 4} {0 4}] [{3 4} {1 4}]]
g24_CD3= [[{1 4} {3 4}] [{2 4} {2 4}]]
g24_C2D= [[{1 4} {3 4}] [{1 4} {3 4}]]
g24_C3D= [[{3 4} {1 4}] [{2 4} {2 4}]]
g24_C2D3= [[{3 4} {1 4}] [{3 4} {1 4}]]
g24_C3D2= [[{0 4} {0 4}] [{1 4} {3 4}]]

O:=[ ZmodnZObj( 0, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 0, 4 ) ]
g24_I:=[ [ ZmodnZObj( 1, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 1, 4 ) ] ];
g24_I2:=[ [ ZmodnZObj( 2, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 2, 4 ) ] ];
g24_I3:=[ [ ZmodnZObj( 3, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 3, 4 ) ] ];
g24_E:=[ [ ZmodnZObj( 2, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 3, 4 ) ] ];
g24_E2:=[ [ ZmodnZObj( 0, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 2, 4 ) ] ]
g24_E3:=[ [ ZmodnZObj( 2, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 1, 4 ) ] ]
g24_IE:=[ [ ZmodnZObj( 3, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 0, 4 ) ] ]
g24_I2E2:=[ [ ZmodnZObj( 2, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 0, 4 ) ] ]
g24_I3E3:=[ [ ZmodnZObj( 1, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 0, 4 ) ] ]
g24_IE2:=[ [ ZmodnZObj( 1, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 3, 4 ) ] ]
g24_IE3:=[ [ ZmodnZObj( 3, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 2, 4 ) ] ]
g24_I2E:=[ [ ZmodnZObj( 0, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 1, 4 ) ] ]
g24_I3E:=[ [ ZmodnZObj( 1, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 2, 4 ) ] ]
g24_I2E3:=[ [ ZmodnZObj( 0, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 3, 4 ) ] ]
g24_I3E2:=[ [ ZmodnZObj( 3, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 1, 4 ) ] ]

m:=4;
a:=[ [ ZmodnZObj(2,m), ZmodnZObj( 0, m) ], [ ZmodnZObj( 0, m), ZmodnZObj( 0, m) ] ];
b:=[ [ ZmodnZObj(0,m), ZmodnZObj( 0, m) ], [ ZmodnZObj( 0, m), ZmodnZObj( 2, m) ] ];
[ [ [ ZmodnZObj( 0, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 0, 4 ) ] ], 
[ [ ZmodnZObj( 0, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 2, 4 ) ] ],
[ [ ZmodnZObj( 2, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 0, 4 ) ] ],
[ [ ZmodnZObj( 2, 4 ), ZmodnZObj( 0, 4 ) ], [ ZmodnZObj( 0, 4 ), ZmodnZObj( 2, 4 ) ] ] ]
*/
var g24_O[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{0,4},ZmodnZObj{0,4}},
		{ZmodnZObj{0,4},ZmodnZObj{0,4}},
		}
								
var g24_A[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,4},ZmodnZObj{0,4}},
		{ZmodnZObj{1,4},ZmodnZObj{0,4}},
		}	

var g24_B[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,4},ZmodnZObj{1,4}},
		{ZmodnZObj{1,4},ZmodnZObj{1,4}},
		}	

var g24_A2[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{2,4},ZmodnZObj{0,4}},
		{ZmodnZObj{2,4},ZmodnZObj{0,4}},
		}	

var g24_A3[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{3,4},ZmodnZObj{0,4}},
		{ZmodnZObj{3,4},ZmodnZObj{0,4}},
		}

var g24_B2[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{2,4},ZmodnZObj{2,4}},
		{ZmodnZObj{2,4},ZmodnZObj{2,4}},
		}	
		
var g24_B3[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{3,4},ZmodnZObj{3,4}},
		{ZmodnZObj{3,4},ZmodnZObj{3,4}},
		}	
var g24_AB[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{2,4},ZmodnZObj{1,4}},
		{ZmodnZObj{2,4},ZmodnZObj{1,4}},
		}	

var g24_A2B2[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{0,4},ZmodnZObj{2,4}},
		{ZmodnZObj{0,4},ZmodnZObj{2,4}},
		}

var g24_A3B3[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{2,4},ZmodnZObj{3,4}},
		{ZmodnZObj{2,4},ZmodnZObj{3,4}},
		}	
var g24_AB2[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{3,4},ZmodnZObj{2,4}},
		{ZmodnZObj{3,4},ZmodnZObj{2,4}},
		}	

var g24_AB3[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{0,4},ZmodnZObj{3,4}},
		{ZmodnZObj{0,4},ZmodnZObj{3,4}},
		}	

var g24_A2B[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{3,4},ZmodnZObj{1,4}},
		{ZmodnZObj{3,4},ZmodnZObj{1,4}},
		}	

var g24_A3B[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{0,4},ZmodnZObj{1,4}},
		{ZmodnZObj{0,4},ZmodnZObj{1,4}},
		}

var g24_A2B3[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,4},ZmodnZObj{3,4}},
		{ZmodnZObj{1,4},ZmodnZObj{3,4}},
		}
		
var g24_A3B2[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,4},ZmodnZObj{2,4}},
		{ZmodnZObj{1,4},ZmodnZObj{2,4}},
		}	
		
		
var g24_C2[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{0,4},ZmodnZObj{0,4}},
		{ZmodnZObj{2,4},ZmodnZObj{2,4}},
		}	

var g24_C3[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{2,4},ZmodnZObj{2,4}},
		{ZmodnZObj{3,4},ZmodnZObj{1,4}},
		}

var g24_D2[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{2,4},ZmodnZObj{2,4}},
		{ZmodnZObj{2,4},ZmodnZObj{2,4}},
		}	
		
var g24_D3[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{3,4},ZmodnZObj{1,4}},
		{ZmodnZObj{1,4},ZmodnZObj{3,4}},
		}	
var g24_CD[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{3,4},ZmodnZObj{1,4}},
		{ZmodnZObj{0,4},ZmodnZObj{0,4}},
		}	

var g24_C2D2[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{2,4},ZmodnZObj{2,4}},
		{ZmodnZObj{0,4},ZmodnZObj{0,4}},
		}

var g24_C3D3[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,4},ZmodnZObj{3,4}},
		{ZmodnZObj{0,4},ZmodnZObj{0,4}},
		}	
var g24_CD2[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{0,4},ZmodnZObj{0,4}},
		{ZmodnZObj{3,4},ZmodnZObj{1,4}},
		}	

var g24_CD3[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,4},ZmodnZObj{3,4}},
		{ZmodnZObj{2,4},ZmodnZObj{2,4}},
		}	

var g24_C2D[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,4},ZmodnZObj{3,4}},
		{ZmodnZObj{1,4},ZmodnZObj{3,4}},
		}	

var g24_C3D[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{3,4},ZmodnZObj{1,4}},
		{ZmodnZObj{2,4},ZmodnZObj{2,4}},
		}

var g24_C2D3[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{3,4},ZmodnZObj{1,4}},
		{ZmodnZObj{3,4},ZmodnZObj{1,4}},
		}
		
var g24_C3D2[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{0,4},ZmodnZObj{0,4}},
		{ZmodnZObj{1,4},ZmodnZObj{3,4}},
		}	

var g24_C[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{2,4},ZmodnZObj{2,4}},
		{ZmodnZObj{1,4},ZmodnZObj{3,4}},
		}	

var g24_D[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,4},ZmodnZObj{3,4}},
		{ZmodnZObj{3,4},ZmodnZObj{1,4}},
		}	

var g24_I[][]ZmodnZObj=[][]ZmodnZObj{ { ZmodnZObj{ 1, 4 }, ZmodnZObj{ 0, 4 } }, { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 1, 4 } } }
var g24_I2[][]ZmodnZObj=[][]ZmodnZObj{ { ZmodnZObj{ 2, 4 }, ZmodnZObj{ 0, 4 } }, { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 2, 4 } } }
var g24_I3[][]ZmodnZObj=[][]ZmodnZObj{ { ZmodnZObj{ 3, 4 }, ZmodnZObj{ 0, 4 } }, { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 3, 4 } } }
var g24_E[][]ZmodnZObj=[][]ZmodnZObj{ { ZmodnZObj{ 2, 4 }, ZmodnZObj{ 0, 4 } }, { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 3, 4 } } }
var g24_E2[][]ZmodnZObj=[][]ZmodnZObj{ { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 0, 4 } }, { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 2, 4 } } }
var g24_E3[][]ZmodnZObj=[][]ZmodnZObj{ { ZmodnZObj{ 2, 4 }, ZmodnZObj{ 0, 4 } }, { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 1, 4 } } }
var g24_IE[][]ZmodnZObj=[][]ZmodnZObj{ { ZmodnZObj{ 3, 4 }, ZmodnZObj{ 0, 4 } }, { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 0, 4 } } }
var g24_I2E2[][]ZmodnZObj=[][]ZmodnZObj{ { ZmodnZObj{ 2, 4 }, ZmodnZObj{ 0, 4 } }, { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 0, 4 } }}
var g24_I3E3[][]ZmodnZObj=[][]ZmodnZObj{ { ZmodnZObj{ 1, 4 }, ZmodnZObj{ 0, 4 } }, { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 0, 4 } }}
var g24_IE2[][]ZmodnZObj=[][]ZmodnZObj{ { ZmodnZObj{ 1, 4 }, ZmodnZObj{ 0, 4 } }, { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 3, 4 } } }
var g24_IE3[][]ZmodnZObj=[][]ZmodnZObj{ { ZmodnZObj{ 3, 4 }, ZmodnZObj{ 0, 4 } }, { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 2, 4 } } }
var g24_I2E[][]ZmodnZObj=[][]ZmodnZObj{ { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 0, 4 } }, { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 1, 4 } } }
var g24_I3E[][]ZmodnZObj=[][]ZmodnZObj{ { ZmodnZObj{ 1, 4 }, ZmodnZObj{ 0, 4 } }, { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 2, 4 } } }
var g24_I2E3[][]ZmodnZObj=[][]ZmodnZObj{ { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 0, 4 } }, { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 3, 4 } } }
var g24_I3E2[][]ZmodnZObj=[][]ZmodnZObj{ { ZmodnZObj{ 3, 4 }, ZmodnZObj{ 0, 4 } }, { ZmodnZObj{ 0, 4 }, ZmodnZObj{ 1, 4 } } }		

var g_R16_101[]*[][]ZmodnZObj=[]*[][]ZmodnZObj{&g24_O,&g24_A,&g24_B,&g24_A2,&g24_A3,&g24_B2,&g24_B3,&g24_AB,&g24_A2B2,&g24_A3B3,&g24_AB2,&g24_AB3,&g24_A2B,&g24_A3B,&g24_A2B3,&g24_A3B2}		
var g_R16_102[]*[][]ZmodnZObj=[]*[][]ZmodnZObj{&g24_O,&g24_C,&g24_D,&g24_C2,&g24_C3,&g24_D2,&g24_D3,&g24_CD,&g24_C2D2,&g24_C3D3,&g24_CD2,&g24_CD3,&g24_C2D,&g24_C3D,&g24_C2D3,&g24_C3D2}		
var g_R16[]*[][]ZmodnZObj=[]*[][]ZmodnZObj{&g24_O,&g24_I,&g24_E,&g24_I2,&g24_I3,&g24_E2,&g24_E3,&g24_IE,&g24_I2E2,&g24_I3E3,&g24_IE2,&g24_IE3,&g24_I2E,&g24_I3E,&g24_I2E3,&g24_I3E2}		
		
func IsMtxEqual(a *[][]ZmodnZObj,b *[][]ZmodnZObj)bool {
	m:=len(*a)
	n:=len((*a)[0])
	m1:=len(*b)
	n1:=len((*b)[0])  
	if(m!=m1||n!=n1){
	  return false
	  }	
	for i:=0;i<m;i++{
		for j:=0;j<n;j++{
			if(!(*a)[i][j].isEqual((*b)[i][j])){
				return false
			}
		}
	}
	return true
}

func IdxInSet(S []*[][]ZmodnZObj,mtx *[][]ZmodnZObj)int {
    n:=len(S)
	for i:=0;i<n;i++{
		bRet := IsMtxEqual(S[i],mtx)
			if(bRet){
			   return i
			}
	}
	return -1
}

func R16_300Table()([][]int,[][]int){
	n:=len(g_R16_300)
    vvAdd:=[][]int{}
    vvMul:=[][]int{}
	 for i:=0;i<n;i++{
	  I:=[]int{}
	  I1:=[]int{}
	  for j:=0;j<n;j++{
	   IJ:=Bradd(g_R16_300[i],g_R16_300[j])
	   ij:=IdxInSet(g_R16_300,&IJ)
	   I = append(I,ij+1)
	   IJ1:=Brmul(g_R16_300[i],g_R16_300[j])
	   ij1:=IdxInSet(g_R16_300,&IJ1)
	   I1 = append(I1,ij1+1)	   
	  }
	  vvAdd = append(vvAdd,I)
	  vvMul = append(vvMul,I1)	  
	 }
	 return vvAdd,vvMul
}

func RTable(S []*[][]ZmodnZObj)([][]int,[][]int){
	n:=len(S)
    vvAdd:=[][]int{}
    vvMul:=[][]int{}
	 for i:=0;i<n;i++{
	  I:=[]int{}
	  I1:=[]int{}
	  for j:=0;j<n;j++{
	   IJ:=Bradd(S[i],S[j])
	   ij:=IdxInSet(S,&IJ)
	   I = append(I,ij+1)
	   IJ1:=Brmul(S[i],S[j])
	   ij1:=IdxInSet(S,&IJ1)
	   I1 = append(I1,ij1+1)	   
	  }
	  vvAdd = append(vvAdd,I)
	  vvMul = append(vvMul,I1)	  
	 }
	 return vvAdd,vvMul
}

func Bradd(a *[][]ZmodnZObj,b *[][]ZmodnZObj)[][]ZmodnZObj{
	p:=(*a)[0][0].m_mod;
	if(p<=0){
		return nil
	}
	if(p!=(*b)[0][0].m_mod){
		return nil
	}
	m:=len(*a)
	n:=len((*a)[0])
	m1:=len(*b)
	n1:=len((*b)[0])  
	if(m!=m1||n!=n1){
		return nil
	}	
	//fmt.Println("m=",m,"n=",n,"m1=",m1,"n1=",n1) 
	var c [][]ZmodnZObj
	for i := 0; i < m; i++ {
		temp := make([]ZmodnZObj, n)
		c = append(c, temp)
	}
	for i:=0; i<m; i++{
		for j:=0; j<n; j++{ 
			c[i][j]=(*a)[i][j].Add((*b)[i][j])
		}
	}
	return c
}
		
func Brmul(a *[][]ZmodnZObj,b *[][]ZmodnZObj)[][]ZmodnZObj{
 p:=(*a)[0][0].m_mod;
 if(p<=0){
  return nil
  }
 if(p!=(*b)[0][0].m_mod){
  return nil
  }
  m:=len(*a)
  n:=len((*a)[0])
  n1:=len(*b)
  k:=len((*b)[0])  
 if(n!=n1){
  return nil
  }
 //fmt.Println("m=",m,"n=",n,"n1=",n1,"k=",k) 
 var c [][]ZmodnZObj
 for i := 0; i < m; i++ {
	temp := make([]ZmodnZObj, k)
	c = append(c, temp)
 }
 for i:=0; i<=m-1; i++{
  for j:=0; j<=k-1; j++{ 
   c[i][j]=ZmodnZObj{0,p}
   for l:=0; l<=n-1; l++{
    c[i][j]=c[i][j].Add((*a)[i][l].Mul((*b)[l][j]))
   //下面也OK
   //{
   // c[i][j].m_k=c[i][j].m_k+((*a)[i][l].Mul((*b)[l][j]).m_k;
   // c[i][j].m_k=c[i][j].m_k%p;
   //}
  }
  }
  }
  return c
} 	
  
func (this *ZmodnZObj) isEqual(a ZmodnZObj) bool {
  return (this.m_k==a.m_k && this.m_mod==a.m_mod)
 }
 
func (this *ZmodnZObj) getName() string {
  return fmt.Sprintf("ZmodnZObj(%d,%d)",this.m_k,this.m_mod)
}
 
func (this *ZmodnZObj) Add(a ZmodnZObj) ZmodnZObj {
	var ret ZmodnZObj
	ret.m_mod=this.m_mod
	ret.m_k=(this.m_k+a.m_k)%this.m_mod
	return ret
 }
 
func (this *ZmodnZObj) InvAdd() ZmodnZObj {
	var ret ZmodnZObj
	ret.m_mod=this.m_mod
	ret.m_k=(this.m_mod*2-this.m_k)%this.m_mod
	return ret
 }
 
func (this *ZmodnZObj) Mul(a ZmodnZObj) ZmodnZObj {
	var ret ZmodnZObj
	ret.m_mod=this.m_mod
	ret.m_k=(this.m_k*a.m_k)%this.m_mod
	return ret
 }

//InverseMutable(a ZmodnZObj) bool {
func (this *ZmodnZObj) InvMul(a ZmodnZObj) ZmodnZObj {
	var ret ZmodnZObj
	for i:=0;i<this.m_mod;i++ {
	    ret=ZmodnZObj{this.m_mod,i}
		if(ret.Mul(a)==ZmodnZObj{this.m_mod,1}){
			return ret
		}
	}	
	return ZmodnZObj{0,0}
 }
 
func (this *ZmodnZObj) Idx(v *[]ZmodnZObj) int {
  for i:=0;i<len(*v);i++ {
   if(this.isEqual((*v)[i])){
    return i
	}
  }
  return -1
 } 
 
func PrintTable(vv [][]int){
	for _, v := range vv {
			for _, v2 := range v {
				fmt.Printf("%d ",v2)
			}
			fmt.Println()
		}
	return
}

func WriteTable(vv,vv1 [][]int,fn string) {
	f, err := os.OpenFile(fmt.Sprintf("%s.txt",fn), os.O_RDWR|os.O_CREATE, os.ModePerm)
	if err != nil {
		panic(err)
	}
	defer f.Close()
	
	n:=len(vv)
	var buf string
	buf = fmt.Sprintf("[R%dAdd]\n",n)
	f.WriteString(buf)	
	for i:=0;i<n;i++{
		for j:=0;j<n;j++{
			buf = fmt.Sprintf("%d ",vv[i][j])
			f.WriteString(buf)
		}
		f.WriteString("\n");
	}
	buf = fmt.Sprintf("[R%dMul]\n",n)
	f.WriteString(buf)	
	for i:=0;i<n;i++{
		for j:=0;j<n;j++{
			buf = fmt.Sprintf("%d ",vv1[i][j])
			f.WriteString(buf)
		}
		f.WriteString("\n");
	}	
}

func test1() { 
	var mtxA[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,17},ZmodnZObj{2,17},ZmodnZObj{3,17}},
		{ZmodnZObj{0,17},ZmodnZObj{5,17},ZmodnZObj{6,17}},
		{ZmodnZObj{0,17},ZmodnZObj{0,17},ZmodnZObj{9,17}},
		}
	var mtxB[][]ZmodnZObj=[][]ZmodnZObj{
		{ZmodnZObj{1,17},ZmodnZObj{3,17},ZmodnZObj{9,17}},
		{ZmodnZObj{0,17},ZmodnZObj{7,17},ZmodnZObj{1,17}},
		{ZmodnZObj{0,17},ZmodnZObj{0,17},ZmodnZObj{2,17}},
		}

	mtxC:=Brmul(&mtxA,&mtxB);
	fmt.Println("mtxC=",mtxC)
	for i := 0; i <len(mtxC); i++ {
	    fmt.Printf("{")
		for j := 0; j <len(mtxC[i]); j++ {
			fmt.Printf("%v",mtxC[i][j].getName())
			if(j<len(mtxC[i])-1){
			    fmt.Printf(",")
			}
		}
		fmt.Printf("},\n")
	}

	{
		fmt.Println("g24_O=",g24_O)		
		fmt.Println("g24_A=",g24_A)	
		fmt.Println("g24_B=",g24_B)
		g24_A2:=Bradd(&g24_A,&g24_A)
		fmt.Println("g24_A2=",g24_A2)
		g24_A3:=Bradd(&g24_A2,&g24_A)
		fmt.Println("g24_A3=",g24_A3)
		g24_B2:=Bradd(&g24_B,&g24_B)
		fmt.Println("g24_B2=",g24_B2)
		g24_B3:=Bradd(&g24_B2,&g24_B)
		fmt.Println("g24_B3=",g24_B3)
		g24_AB:=Bradd(&g24_A,&g24_B)
		fmt.Println("g24_AB=",g24_AB)
		g24_A2B2:=Bradd(&g24_AB,&g24_AB)
		fmt.Println("g24_A2B2=",g24_A2B2)
		g24_A3B3:=Bradd(&g24_AB,&g24_A2B2)
		fmt.Println("g24_A3B3=",g24_A3B3)		
		g24_AB2:=Bradd(&g24_A,&g24_B2)
		fmt.Println("g24_AB2=",g24_AB2)	
		g24_AB3:=Bradd(&g24_A,&g24_B3)
		fmt.Println("g24_AB3=",g24_AB3)	
		g24_A2B:=Bradd(&g24_A2,&g24_B)
		fmt.Println("g24_A2B=",g24_A2B)	
		g24_A3B:=Bradd(&g24_A3,&g24_B)
		fmt.Println("g24_A3B=",g24_A3B)	
		g24_A2B3:=Bradd(&g24_A2,&g24_B3)
		fmt.Println("g24_A2B3=",g24_A2B3)	
		g24_A3B2:=Bradd(&g24_A3,&g24_B2)
		fmt.Println("g24_A3B2=",g24_A3B2)		
	}
	{
		fmt.Println("g24_O=",g24_O)		
		fmt.Println("g24_C=",g24_C)	
		fmt.Println("g24_D=",g24_D)
		g24_C2:=Bradd(&g24_C,&g24_C)
		fmt.Println("g24_C2=",g24_C2)
		g24_C3:=Bradd(&g24_C2,&g24_C)
		fmt.Println("g24_C3=",g24_C3)
		g24_D2:=Bradd(&g24_D,&g24_D)
		fmt.Println("g24_D2=",g24_D2)
		g24_D3:=Bradd(&g24_D2,&g24_D)
		fmt.Println("g24_D3=",g24_D3)
		g24_CD:=Bradd(&g24_C,&g24_D)
		fmt.Println("g24_CD=",g24_CD)
		g24_C2D2:=Bradd(&g24_CD,&g24_CD)
		fmt.Println("g24_C2D2=",g24_C2D2)
		g24_C3D3:=Bradd(&g24_CD,&g24_C2D2)
		fmt.Println("g24_C3D3=",g24_C3D3)		
		g24_CD2:=Bradd(&g24_C,&g24_D2)
		fmt.Println("g24_CD2=",g24_CD2)	
		g24_CD3:=Bradd(&g24_C,&g24_D3)
		fmt.Println("g24_CD3=",g24_CD3)	
		g24_C2D:=Bradd(&g24_C2,&g24_D)
		fmt.Println("g24_C2D=",g24_C2D)	
		g24_C3D:=Bradd(&g24_C3,&g24_D)
		fmt.Println("g24_C3D=",g24_C3D)	
		g24_C2D3:=Bradd(&g24_C2,&g24_D3)
		fmt.Println("g24_C2D3=",g24_C2D3)	
		g24_C3D2:=Bradd(&g24_C3,&g24_D2)
		fmt.Println("g24_C3D2=",g24_C3D2)	
	}
	return	
	{
		vv1,vv2:=R16_300Table()
		fmt.Println("ShowAdditionTable(R16_300):")
		PrintTable(vv1)
		fmt.Println("ShowMultiplicationTable(R16_300):")
		PrintTable(vv2)
		WriteTable(vv1,vv2,"R16_300")
	}	
	{
		vv1,vv2:=RTable(g_R16_101)
		fmt.Println("ShowAdditionTable(R16_101):")
		PrintTable(vv1)
		fmt.Println("ShowMultiplicationTable(R16_101):")
		PrintTable(vv2)
		WriteTable(vv1,vv2,"R16_101")
	}	
	{
		vv1,vv2:=RTable(g_R16_102)
		fmt.Println("ShowAdditionTable(R16_102):")
		PrintTable(vv1)
		fmt.Println("ShowMultiplicationTable(R16_102):")
		PrintTable(vv2)
		WriteTable(vv1,vv2,"R16_102")
	}	
}

func main() {
	//test1()

	{
		vv1,vv2:=RTable(g_R16)
		fmt.Println("ShowAdditionTable(R16):")
		PrintTable(vv1)
		fmt.Println("ShowMultiplicationTable(R16):")
		PrintTable(vv2)
		WriteTable(vv1,vv2,"R16")
	}
}