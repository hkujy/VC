import myclass
import mypara



def print_disrupt_case_summary(mp:mypara.MyParaClass,_cs):
    """
        print the summary of the cases
    """
    target_file = mp.root_folder + "OutPut\\Disrupt_MeasureSummary.csv"
    
    with open(target_file,"w+") as f:
        print("Case,VulLink,NRI,wNRI,UNPM",file = f)
        for cid in range(1,len(_cs)):
            print("{0},{1},{2},{3},{4}".format(_cs[cid].CaseIndex,
                _cs[cid].vul_link,
            _cs[cid].vul_measure["NRI"],_cs[cid].vul_measure["wNRI"],
            _cs[cid].vul_measure["UNPM"]),file = f)

def print_reover_case_summary(mp:mypara.MyParaClass,_cs):
    """
        print the summary of the cases
    """
    target_file = mp.root_folder + "OutPut\\Recovery_MeasureSummary.csv"
    
    with open(target_file,"w+") as f:
        print("Case,VulLink,NRI,wNRI,UNPM",file = f)
        for cid in range(1,len(_cs)):
            print("{0},{1},{2},{3},{4}".format(_cs[cid].Case,_cs[cid].vul_link,
            _cs[cid].vul_measure["NRI"],_cs[cid].vul_measure["wNRI"],
            _cs[cid].vul_measure["UNPM"]),file = f)

def main(mp:mypara.MyParaClass,_cs):
    """
        compute the UE based UNPM measures
    """
    print("PyInfo: Start to compute the measures")
    for c in _cs:
        c.cal_vc_ratio(mp)
        c.cal_NRI(mp)
        c.cal_EG()
    for cid in range(1,len(_cs)):
        _cs[cid].cal_wNRI(_cs[0])
        _cs[cid].cal_UNPM(_cs[0])

    print("PyInfo: Complete computing the measures")
    
    if mp.para_dict["Procedure"] =="Eval_remove_each_one" or mp.para_dict["Procedure"]=="Eval_base_and_given_net":
        print_disrupt_case_summary(mp,_cs)
    # elif mp.para_dict["Procedure"] =="RecoverOne":
        # print_reover_case_summary(mp,_cs)
    else:
        print("Warning: The Procedure parameter is not set")
        input("Warning and Stop: Check calVulMeaure main")
        



    


