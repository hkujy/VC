"""
    functions for set up a test
"""
import os
from os import link, pardir
from unittest import case
import mypara
import myplot
from shutil import copyfile
import shutil
import random
import read as rd
import calVulMesures as cal
import Combination as comb


def copy_file(_from, _to):
    copyfile(_from, _to)


def copy_folder(_from, _todir):
    if os.path.exists(_todir):
        shutil.rmtree(_todir)
    shutil.copytree(_from, _todir)


def set_para(mp: mypara.MyParaClass):
    """
        TODO: function to set up a test
    """
    pass


def print_para(mp: mypara.MyParaClass):
    """
        print parameters to c++ test file
    """
    target_file = mp.root_folder + "Input\\Para.txt"
    with open(target_file, "w+") as f:
        for key in mp.para_dict.keys():
            print("{0},{1}".format(key, mp.para_dict[key]), file=f)


def one_test(mp: mypara.MyParaClass, _name="try"):
    """
        run one single test
    """
    # step 1: print para
    print_para(mp)

    # step 2: copy input folder to output folder
    copy_folder(mp.input_folder, mp.output_folder+"Input")

    # step 3: run the test
    if mypara.is_run_exe:
        if mypara.is_debug_exe:
            print("Start to run debug mode")
            os.system(mp.debug_exe)
        else:
            print("Start to run release mode")
            os.system(mp.release_exe)

    # step 4: read case data
    process_type = ""
    if mp.para_dict["Procedure"] =="EvalOne":
        process_type = "Disrupt" 
    elif mp.para_dict["Procedure"] =="RecoverOne":
        process_type ="Recover"
    else:
        print("Warning: on the procedure parameter setting")
    cases = rd.main(mp, process_type)
    # step 5: calculate the vul measures
    cal.main(mp, cases)
    # step 5: plot main function
    # myplot.main()
    # step 5: copy output folder to a seperate test folder
    copy_folder(mp.output_folder, mp.root_folder+"TestCases\\"+_name+"\\")
    return cases


def write_link_list_to_file(mp: mypara.MyParaClass, _ls):
    """
        print the set of vulnerable links to the files
    """
    target_file = mp.root_folder + "InPut\\" + \
        mp.para_dict["Network"]+"_VulnerableLinks.txt"
    with open(target_file, "w+") as f:
        for l in _ls:
            print("{0},1,1.0,1.0".format(l), file=f)


def gen_random_set_link(mp: mypara.MyParaClass, _num_links=1, _lb=1, _ub=50):
    links = []
    if _num_links > 0:
        for i in range(0, _num_links):
            links.append(random.randint(_lb, _ub))
    else:
        print("Test All The Links of the Network")
        if mp.para_dict["Network"] == "SiouxFalls":
            for i in range(0, 75):
                links.append(i)
        else:
            print(
                "Warning: The Test Parameters for other networks have not been specified")
            input("Stop the code")
    
    links = [11,22,33,44,66,5,34,70,55,14]
    return links


def test_remove_link(mp: mypara.MyParaClass, _num_links=1):
    """
        random select a link between 1-50
    """
    link_id = gen_random_set_link(
        mp, _num_links, mypara.gen_linkid_lb, mypara.gen_linkid_up)
    write_link_list_to_file(mp, link_id)
    cases = one_test(
        mp, _name=mp.para_dict["Network"]+"_remove_"+str(_num_links)+"_links")

    return cases


def test_recover_case_step1_remove(mp:mypara.MyParaClass,_num_links):
    """
        step 1: write the disrupted links and also write the order of the recover links
    """
    cases = test_remove_link(mp, _num_links)
    # step 2: sort the vul link measure based on the selected links
    sort_measure = {}
    for c in cases:
        sort_measure[str(c.vul_link)] = c.vul_measure[mypara.recover_measure]

    sort_orders = sorted(sort_measure.items(), key=lambda x: x[1], reverse=True)
    # sorted(sort_measure.items(), key=lambda x: x[1], reverse=True)
    print("*****Check the order the selected measures*********")
    print("*****The following numbers should be decreasing order*********")
    # for keys, values in sort_measure.items():
    for v in sort_orders:
        print("{0},{1}".format(v[0],v[1]))
    print("**************************************************************")
    # for keys, values in sort_orders.items():
        # print('key={0},val={1}'.format(keys, values))

    # sorted(sort_measure .items(), lambda x, y: cmp(x[1], y[1]), reverse=True)
     # step 3: print these links as the disrupted links
    print("*****Print the base disruption scenario*********")
    with open("c:\GitCodes/VC/InPut/"+mp.para_dict["Network"]+"_IniDisrupt.txt", "w+") as f:
        for c in range(0, len(cases)-1):
            if cases[c].vul_link>=0:
                print("{0},".format(cases[c].vul_link),end='', file=f)
                print("{0},".format(cases[c].vul_link),end='')
        print(cases[-1].vul_link, file=f)
        print(cases[-1].vul_link)
        if cases[-1].vul_link == -1:
            print("Warning: err in the cases last vul element")
    print("*************************************************")
    print("*****print the order the links to be added")
    # step 4: print the recover links
    with open("c:\GitCodes/VC/InPut/"+mp.para_dict["Network"]+"_recover.txt", "w+") as f:
        _val = []
        for v in sort_orders:
            if int(v[0])>=0:
                _val.append(int(v[0]))

        all_vec = comb.get_all_possible_order(_val)

        for v in all_vec:
            for i in range(0, len(v)-1):
                print("{0},".format(v[i]),end='', file=f)
                print("{0},".format(v[i]),end='')
            print(v[-1], file=f)
            print(v[-1])
    print("***************************************************")

    # input("check the recover cases")


def test_recover_case(mp: mypara.MyParaClass, _num_links=1):
    """
        test recover case
    """
    # step 1: test the number
    mp.para_dict["Procedure"] = "EvalOne"
    test_recover_case_step1_remove(mp,_num_links)
    # # step 2. to rank the link index
    mp.para_dict["Procedure"] = "RecoverOne"
    cases = one_test(
        mp, _name=mp.para_dict["Network"]+"_recover_"+str(_num_links)+"_links")

    # cal.main(mp, cases)

    # cid = len(cases)-1
    # with open("Check.txt","w+") as f:
    #     for l in cases[cid].links:
    #         print("{0},{1}".format(l.cost,l.flow),file=f)


