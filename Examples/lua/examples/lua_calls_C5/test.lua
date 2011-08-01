package.cpath = "./?.so"
require "wrap"
--test1  
wrap.lib_a_f_1()  
--test2   
assert(6==wrap.lib_a_f_2(2,3))  
--test3  
assert(5==wrap.lib_a_f_3("hello"))  
--test4 : use userdata to pass structure  
t=wrap.point_new(3,6)  
assert(18 == mylib.lib_a_f_4(t))  
--test5, return userdata  
t=wrap.lib_a_f_5()  
assert(600 == wrap.lib_a_f_4(t))  
assert(wrap.point_geta(t) == 20)  
assert(wrap.point_getb(t) == 30)
