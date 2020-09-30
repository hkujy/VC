
"""
    write the test scrips
"""
import os
import shutil
from turtle import settiltangle
import mypara 
import set_set_simple as st


def main_func(_disrupt_links,_method):
    """
        Input: set of disrupted links
        The c++ with evalute two networks  
        1. one network is the origin network without any diruption 
        2. one network with given disrupted links
    """
    mp = mypara.MyParaClass()
    mp.get_root_folder()
    print("root folder is {0}".format(mp.root_folder))
    mp.para_dict["Procedure"] = _method

    st.test_case(mp,_disrupt_links,_method)

# if __name__== "__main__":
#     # Test_Toler()
#     # Test_Max_UESol()
#     mp = mypara.MyParaClass()
#     mp.get_root_folder()
#     print("root folder is {0}".format(mp.root_folder))
#     # setTest.test_remove_link(mp,_num_links = 10)
#     # set _numlink = -1 is to compute all the links 
#     # setTest.test_remove_link(mp,_num_links = -1)   
#     setTest.test_recover_case(mp,_num_links = 3)
    


