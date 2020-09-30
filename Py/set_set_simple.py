import mypara
import set_test_full as stf


def test_case(mp: mypara.MyParaClass, _links,_method):
    """
    """
    print("PyInfo: Start write vul link to files as C++ input")
    stf.write_link_list_to_file(mp, _links)
    print("PyInfo: Complete write vul link to files as C++ input")
    cases = stf.one_test(
        mp, _name=mp.para_dict["Network"]+"_remove_"+str(len(_links))+"_links")

    return cases

