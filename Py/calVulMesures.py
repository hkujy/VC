import myclass
import mypara



def print_case_summary(mp:mypara.MyParaClass,_cs):
    """
        print the summary of the cases
    """
    target_file = mp.root_folder + "OutPut\\MeasureSummary.csv"
    
    with open(target_file,"w+") as f:
        print("VulLink,NRI,wNRI,UNPM",file = f)
        for cid in range(1,len(_cs)):
            print("{0},{1},{2},{3}".format(_cs[cid].vul_link,
            _cs[cid].vul_measure["NRI"],_cs[cid].vul_measure["wNRI"],
            _cs[cid].vul_measure["UNPM"]),file = f)




def main(mp:mypara.MyParaClass,_cs):
    """
        compute the UE based UNPM measures
    """
    for c in _cs:
        c.cal_vc_ratio()
        c.cal_NRI()
        c.cal_EG()
    for cid in range(1,len(_cs)):
        _cs[cid].cal_wNRI(_cs[0])
        _cs[cid].cal_UNPM(_cs[0])
    print_case_summary(mp,_cs)



    


