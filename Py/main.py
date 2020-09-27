
"""
    write the test scrips
"""
import os
import shutil
from turtle import settiltangle
import mypara 
import setTest



if __name__== "__main__":
    # Test_Toler()
    # Test_Max_UESol()
    mp = mypara.MyParaClass()
    mp.get_root_folder()
    print("root folder is {0}".format(mp.root_folder))
    # setTest.test_remove_link(mp,_num_links = 10)
    # set _numlink = -1 is to compute all the links 
    setTest.test_remove_link(mp,_num_links = -1)   
    


