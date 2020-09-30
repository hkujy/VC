import mypara
import calVulMesures as cal
import Combination as comb
import set_test_full as stf




def test_case(mp: mypara.MyParaClass, _links,_method):
    """
    """
    stf.write_link_list_to_file(mp, _links)
    cases = stf.one_test(
        mp, _name=mp.para_dict["Network"]+"_remove_"+str(len(_links))+"_links")

    return cases

