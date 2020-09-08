"""
    functions for set up a test
"""
import os
import mypara 
import myplot
from shutil import copyfile
import shutil
import random
import read as rd
import calVulMesures as cal
def copy_file(_from,_to):
    copyfile(_from, _to)
def copy_folder(_from,_todir):
    if os.path.exists(_todir):
        shutil.rmtree(_todir)
    shutil.copytree(_from,_todir)


def set_para(mp:mypara.MyParaClass):
    """
        TODO: function to set up a test
    """
    pass

def print_para(mp:mypara.MyParaClass):
    """
        print parameters to c++ test file
    """
    target_file =  mp.root_folder + "Input\\Para.txt" 
    with open(target_file,"w+") as f:
        for key in mp.para_dict.keys():
            print("{0},{1}".format(key,mp.para_dict[key]),file=f)
    

def one_test(mp:mypara.MyParaClass, _name="try"):
    """
        run one single test
    """
    # step 1: print para
    print_para(mp)

    # step 2: copy input folder to output folder 
    copy_folder(mp.input_folder,mp.output_folder+"Input")
    
    # step 3: run the test
    if mypara.is_run_exe:
        if mypara.is_debug_exe:
            os.system(mp.debug_exe) 
        else:
            os.system(mp.release_exe)

    # step 4: read case data 
    cases = rd.main(mp)
    # step 5: calculate the vul measures
    cal.main(mp,cases)
    # step 5: plot main function
    # myplot.main()
    # step 5: copy output folder to a seperate test folder
    copy_folder(mp.output_folder,mp.root_folder+"TestCases\\"+_name+"\\")

def write_link_list_to_file(mp:mypara.MyParaClass,_ls):
    """
        print the set of vulnerable links to the files
    """
    target_file = mp.root_folder + "InPut\\"+ mp.para_dict["Network"]+"_VulnerableLinks.txt"
    with open(target_file,"w+") as f:
        for l in _ls:
            print("{0},1,1.0,1.0".format(l),file=f)

def test_remove_link(mp:mypara.MyParaClass,_num_links = 1):
    """
        random select a link between 1-50
    """
    lower_bound = 1
    upper_bound = 50
    link_id = []
    if _num_links > 0:
        for i in range(0, _num_links):
            link_id.append(random.randint(lower_bound,upper_bound))
    else: 
        print("Test All The Links of the Network")
        if mp.para_dict["Network"] == "SiouxFalls":
            for i in range(0, 75):
                link_id.append(i)
        else:
            print("Warning: The Test Parameters for other networks have not been specified")
            input("Stop the code")

    write_link_list_to_file(mp,link_id)
    one_test(mp,_name = mp.para_dict["Network"]+"_remove_"+str(_num_links)+"_links")



